/*
 * This file is part of VLE, a framework for multi-modeling, simulation
 * and analysis of complex dynamical systems.
 * http://www.vle-project.org
 *
 * Copyright (c) 2003-2016 Gauthier Quesnel <quesnel@users.sourceforge.net>
 * Copyright (c) 2003-2016 ULCO http://www.univ-littoral.fr
 * Copyright (c) 2007-2016 INRA http://www.inra.fr
 *
 * See the AUTHORS or Authors.txt file for copyright owners and
 * contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vle/devs/SimulatorMulti.hpp>
#include <vle/devs/Dynamics.hpp>
#include <vle/devs/Time.hpp>
#include <vle/vpz/MultiComponent.hpp>
#include <vle/utils/Exception.hpp>
#include <vle/utils/i18n.hpp>
#include <iostream>

namespace vle
{
namespace devs
{

SimulatorMulti::SimulatorMulti(vpz::MultiComponent *atomic)
    : m_multiComponent(atomic)
    , m_tn(negativeInfinity)
    , m_have_handle(false)
    , m_have_internal(false)
{
    assert(atomic && "Simulator: missing vpz::MultiComponent");

    m_multiComponent->m_simulator = this;
    std::cout << "simulateur multi créé"<< std::endl;
}

void SimulatorMulti::updateSimulatorTargets(const std::string &port)
{
    assert(m_multiComponent);

    mTargets.erase(port);

    vpz::ModelPortList result;
    m_multiComponent->getAtomicModelsTarget(port, result);

    if (result.begin() == result.end()) {
        mTargets.emplace(port, TargetSimulator(nullptr, std::string()));
        return;
    }

    for (auto &elem : result)
        mTargets.emplace(port,
                         TargetSimulator(static_cast<vpz::MultiComponent *>(
                                             elem.first)->get_simulator(),
                                         elem.second));
}

std::pair<SimulatorMulti::iterator, SimulatorMulti::iterator>
SimulatorMulti::targets(const std::string &port)
{
    auto x = mTargets.equal_range(port);

    // If the updateSimulatorTargets function was never call, we update
    // the simulator targets and try to retrieve the newest simulator
    // targets.
    if (x.first == x.second) {
        updateSimulatorTargets(port);
        x = mTargets.equal_range(port);
    }

    if (x.first->second.first == nullptr)
        return {mTargets.end(), mTargets.end()};

    return x;
}

void SimulatorMulti::removeTargetPort(const std::string &port)
{
    auto it = mTargets.find(port);

    if (it != mTargets.end()) {
        mTargets.erase(it);
    }
}

void SimulatorMulti::addTargetPort(const std::string &port)
{
    assert(mTargets.find(port) == mTargets.end());

    mTargets.insert(value_type(
        port, TargetSimulator((SimulatorMulti *)nullptr, std::string())));
}

void SimulatorMulti::addDynamics(std::unique_ptr<Dynamics> dynamics)
{
   throw utils::InternalError(_("Simulator Multi wrong model"));
   //auto *dyn =  dynamic_cast<std::unique_ptr<DynamicsComp>>(std::move(dynamics));  
   //std::unique_ptr<DynamicsComp>  dyn = dynamics;
    //m_dynamics->push_back(std::move(dynamics));
}
void SimulatorMulti::addDynamics(std::unique_ptr<DynamicsComp> dynamics)
{
    
    std::cout << "add dynamics Comp " << dynamics->getName() <<" au model: " << dynamics->getModelName() << std::endl;
    m_dynamics.push_back(std::move(dynamics));
}
void SimulatorMulti::addDynamics(std::vector<std::unique_ptr<DynamicsComp>> *dynamics)
{
    //m_dynamics = dynamics;
}

const std::string &SimulatorMulti::getName() const
{
    if (not m_multiComponent)
        throw utils::InternalError(_("Simulator destroyed"));

    return m_multiComponent->getName();
}

void SimulatorMulti::finish() 
{
	 //m_dynamics->finish(); 
}

void SimulatorMulti::output(Time time)
{
    assert(m_result.empty());
//std::cout  << " output" << std::endl;
    //m_dynamics->output(time, m_result);
     for (auto &dyn : m_dynamics)
    {
		std::cout << dyn->getName() << " output" << std::endl;
		if(dyn->getTn() == time){
		dyn->output(time, m_result);
	}
		
	}
}

Time SimulatorMulti::timeAdvance()
{
    Time tn = infinity;//= m_dynamics->timeAdvance();
    Time temp;
	for (auto &dyn : m_dynamics)
    {
      temp = dyn->timeAdvance();
      //m_eventTable.init(temp);
      if(!(temp>tn))
      {
		  tn = temp;
	  }
    }

    if (tn < 0.0)
        throw utils::ModellingError(
            (fmt(_("Negative time advance in '%1%' (%2%)")) % getName() % tn)
                .str());
tn =1;
std::cout  << " time advence " << tn << std::endl;
    return tn;
    
}

Time SimulatorMulti::init(Time time)
{
    Time tn = infinity;//= m_dynamics.front()->init(time);
    Time temp;
    
    for (auto &dyn : m_dynamics)
    {
      temp = dyn->init(time);
      std::cout  << " retour dyn init " << dyn->init(time) << std::endl;
      //m_eventTable.init(temp);
      std::cout  << " temp:" << temp << " tn " << tn << " comparaison: " << (temp < tn) << std::endl;
      if(temp < tn)
      {
		  tn = temp;
	  }
    }

    if (tn < 0.0)
        throw utils::ModellingError(
            (fmt(_("Negative init function in '%1%' (%2%)")) % getName() % tn)
                .str());

    m_tn = tn + time;
    std::cout  << " time init " << m_tn << std::endl;
   // return m_tn;
    return 0;
}

Time SimulatorMulti::confluentTransitions(Time time)
{
    assert(not m_external_events.empty() and "Simulator d-conf error");
    assert(m_have_internal == true and "Simulator d-conf error");
   // m_dynamics->confluentTransitions(time, m_external_events);
    Time temp;
for (auto &dyn : m_dynamics)
    {
		if(dyn->getTn() == time)
		{
		dyn->confluentTransitions(time, m_external_events);		
		
		}else
		{
		//dyn->externalTransition(time, m_external_events);
		
		dyn->externalTransition(m_external_events, time);
		}
		dyn->setTn(dyn->timeAdvance()+time);
		if(temp>dyn->timeAdvance())
		{
			temp=dyn->timeAdvance();
		}
	}
    m_external_events.clear();
    m_have_internal = false;

   m_tn = timeAdvance() + time;
    return m_tn;
}

Time SimulatorMulti::internalTransition(Time time)
{
    assert(m_have_internal == true and "Simulator d-int error");
    std::cout  << " delta int 1" <<  std::endl;
    for (auto &dyn : m_dynamics)
    {
    dyn->internalTransition(time);
	}
	std::cout  << " delta int 2" <<  std::endl;
    m_have_internal = false;

    m_tn = timeAdvance() + time;
    std::cout  << " delta int 3" <<  std::endl;
    return m_tn;
}

Time SimulatorMulti::externalTransition(Time time)
{
    assert(not m_external_events.empty() and "Simulator d-ext error");
     Time temp;
    //m_dynamics->externalTransition(m_external_events, time);
for (auto &dyn : m_dynamics)
    {
		
		dyn->externalTransition(m_external_events, time);
		dyn->setTn(dyn->timeAdvance()+time);
		if(temp>dyn->timeAdvance())
		{
			temp=dyn->timeAdvance();
		}
	}
    m_external_events.clear();

    m_tn = timeAdvance() + time;
    return m_tn;
}

std::unique_ptr<value::Value> SimulatorMulti::observation(const ObservationEvent &event) const
{
    return nullptr; //m_dynamics->observation(event);
}
}
} // namespace vle devs
