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

#ifndef VLE_DEVS_SIMULATORATOMIC_HPP
#define VLE_DEVS_SIMULATORATOMIC_HPP

#include <vle/DllDefines.hpp>
#include <vle/devs/Time.hpp>
#include <vle/devs/InternalEvent.hpp>
#include <vle/devs/ObservationEvent.hpp>
#include <vle/devs/ExternalEventList.hpp>
#include <vle/devs/Scheduler.hpp>
#include <vle/devs/Dynamics.hpp>
#include <vle/devs/View.hpp>
#include <vle/vpz/AtomicModel.hpp>
#include <vle/devs/Simulator.hpp>
#include <vle/vpz/MultiComponent.hpp>
#include <vle/devs/SimulatorMulti.hpp>

namespace vle
{
namespace devs
{

class Dynamics;
class Simulator;
class MultiComponent;


/**
 * @brief Represent a couple devs::AtomicModel and devs::Dynamic class to
 * represent the DEVS simulator.
 *
 */
class VLE_LOCAL SimulatorAtomic : public Simulator
{
public:
    /*typedef std::pair<SimulatorAtomic *, std::string> TargetSimulator;
    typedef std::multimap<std::string, TargetSimulator> TargetSimulatorList;
    typedef TargetSimulatorList::const_iterator const_iterator;
    typedef TargetSimulatorList::iterator iterator;
    typedef TargetSimulatorList::size_type size_type;
    typedef TargetSimulatorList::value_type value_type;*/

   
    SimulatorAtomic(vpz::AtomicModel *a);

    ~SimulatorAtomic() = default;

 
    void addDynamics(std::unique_ptr<Dynamics> dynamics) override;
    void addDynamics(std::unique_ptr<DynamicsComp> dynamics) override;

 
    const std::string &getName() const override;

    vpz::AtomicModel *getStructure() const 
    {
        return m_atomicModel;
    }
	vpz::MultiComponent *getStruc() const 
    {
        return nullptr;
    }
    
    const std::unique_ptr<Dynamics> &dynamics() const override
    {
        return m_dynamics;
    }

    
    void updateSimulatorTargets(const std::string &port) override; 

   
    std::pair<iterator, iterator> targets(const std::string &port) override;

    void removeTargetPort(const std::string &port) override;

 
    void addTargetPort(const std::string &port) override;


    Time init(Time time) override;
    Time timeAdvance() override;
    void finish() override;
    void output(Time time) override;
    Time internalTransition(Time time) override;
    Time externalTransition(Time time) override;
    Time confluentTransitions(Time time) override;
    std::unique_ptr<value::Value>
    observation(const ObservationEvent &event) const  override; 

     const ExternalEventList &result() const noexcept override
    {
        return m_result;
    }

     void clear_result() noexcept override
    {
        m_result.clear();
    }

     Time getTn() const noexcept override
    {
        return m_tn;
    }

     HandleT handle() const noexcept override
    {
        assert(m_have_handle && "Simulator: handle is not defined");
        return m_handle;
    }

     bool haveHandle() const noexcept override
    {
        return m_have_handle;
    }

     void setHandle(HandleT handle) noexcept override
    {
        m_have_handle = true;
        m_handle = handle;
    }

     void resetHandle() noexcept override
    {
        m_have_handle = false;
    }

     bool haveExternalEvents() const noexcept override
    {
        return not m_external_events.empty();
    }

     void addExternalEvents(std::shared_ptr<value::Value> values,
                                  const std::string &portname) override
    {
        m_external_events.emplace_back(values, portname);
    }

     void setInternalEvent() noexcept override
    {
        m_have_internal = true;
    }

     bool haveInternalEvent() const noexcept override
    {
        return m_have_internal;
    }

     void resetInternalEvent() noexcept override
    {
        m_have_internal = false;
    }

     std::vector<Observation> &getObservations() noexcept override
    {
        return m_observations;
    }
 virtual bool isAtomic() const override { 
			
			return true; }
private:
	vpz::AtomicModel *m_atomicModel;
    std::unique_ptr<Dynamics> m_dynamics;
   
    TargetSimulatorList mTargets;
    ExternalEventList m_external_events;
    ExternalEventList m_result;
    std::vector<Observation> m_observations;
    std::string m_parents;
    Time m_tn;
    HandleT m_handle;
    bool m_have_handle;
    bool m_have_internal;
};
}
} // namespace vle devs

#endif
