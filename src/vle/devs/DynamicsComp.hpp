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


#ifndef VLE_DEVS_DYNAMICSCOMP_HPP
#define VLE_DEVS_DYNAMICSCOMP_HPP

#include <vle/devs/Dynamics.hpp>

namespace vle { namespace devs {

/**
 * A Dynamics proxy class that wraps an another Dynamics to show
 * debug information. This class inherits \e Dynamics class.
 */
class DynamicsComp : public Dynamics
{
private:    
    std::string mName;
    Time tn;
    Time tl;
    std::vector<std::unique_ptr<DynamicsComp>> influancer;
    std::vector<std::unique_ptr<DynamicsComp>> influances;

public:
    /**
     * @brief Constructor of Dynamics for an atomic model.
     *
     * @param init The initialiser of Dynamics.
     * @param events The parameter from the experimental frame.
     */
    DynamicsComp(const DynamicsInit& init,
                const InitEventList& events);

    /**
     * @brief Destructor.
     */
    virtual ~DynamicsComp() = default;

    /**
     * @brief If this function return true, then a cast to an Executive
     * object is produce and the set_coordinator function is call. Executive
     * permit to manipulate vpz::CoupledModel and devs::Coordinator at
     * runtime of the simulation.
     * @return false if Dynamics is not an Executive.
     */
    /*virtual bool isExecutive() const override
    {
        return mDynamics->isExecutive();
    }*/

    /**
     * @brief If this function return true, then a cast to a DynamicsWrapper
     * object is produce and the set_model and set_library function are call.
     * @return false if Dynamics is not a DynamicsWrapper.
     */
   
    /**
     * @brief Process the initialization of the model by initializing the
     * initial state and return the duration (or timeAdvance) of the initial
     * state.
     * @param time the time of the creation of this model.
     * @return duration of the initial state.
     */
    virtual Time init(Time time) override;

    /**
     * @brief Process the output function: compute the output function.
     * @param time the time of the occurrence of output function.
     * @param output the list of external events (output parameter).
     */
    virtual void output(Time time, ExternalEventList& output) const override;

    /**
     * @brief Process the time advance function: compute the duration of the
     * current state.
     * @return duration of the current state.
     */
    virtual Time timeAdvance() const override;

    /**
     * @brief Process an internal transition: compute the new state of the
     * model with the internal transition function.
     * @param time the date of occurence of this event.
     */
    virtual void internalTransition(Time time) override;

    /**
     * @brief Process an external transition: compute the new state of the
     * model when an external event occurs.
     * @param event the external event with of the port.
     * @param time the date of occurrence of this event.
     */
    virtual void
        externalTransition(const ExternalEventList& event,
                           Time time) override;

    /**
     * @brief Process the confluent transition: select the transition to
     * call when an internal and one or more external event appear in the
     * same time.
     * @param internal the internal event.
     * @param extEventlist the external events list.
     */
    virtual void
        confluentTransitions(Time time,
                             const ExternalEventList& extEventlist) override;

    /**
     * @brief Process an observation event: compute the current state of the
     * model at a specified time and for a specified port.
     * @param event the state event with of the port
     * @return the value of state variable
     */
    virtual std::unique_ptr<vle::value::Value>
        observation(const ObservationEvent& event) const override;

    /**
     * @brief When the simulation of the atomic model is finished, the
     * finish method is invoked.
     */
    virtual void finish() override;
    
    void setTn(Time time)
    {
		tl = tn;
		tn = time;
	}
	
	Time getTn()
	{
		return tn;
	}
	Time getTl()
	{
		return tl;
	}
	
	std::string getName()
	{
		return mName;
	}
	/*
	void setInfluancer(std::vector<std::unique_ptr<DynamicsComp>> comps)
	{
		influancer (comps);
	}
	void setInfluances(std::vector<std::unique_ptr<DynamicsComp>> comps)
	{
		influances (comps);
	}
	
	void addInfluancer(DynamicsComp *comp)
	{
		influancer.push_back(std::unique_ptr<Dynamics>(std::move(comp)));
	}
	void addInfluances(std::unique_ptr<DynamicsComp> comp)
	{
		influances.push_back(std::move(comp));
	}
	void removeInfluancer(std::unique_ptr<DynamicsComp> comp)
	{
	}
	void removeInfluances(std::unique_ptr<DynamicsComp> comp)
	{
	}
	
	/*std::vector<std::unique_ptr<DynamicsComp>>  getInfluancer()
	{
		return std::move(influancer);
	}
	
	std::vector<std::unique_ptr<DynamicsComp>>  getInfluances()
	{
		return influances;
	}
	 */
};

}} // namespace vle devs

#endif
