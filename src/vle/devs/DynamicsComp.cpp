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


#include <vle/devs/DynamicsComp.hpp>
#include <vle/devs/DynamicsInit.hpp>
#include <vle/devs/ExternalEvent.hpp>
#include <vle/value/Double.hpp>
#include <vle/value/Integer.hpp>
#include <vle/value/Boolean.hpp>
#include <vle/value/String.hpp>
#include <vle/utils/Package.hpp>
#include <vle/utils/Exception.hpp>
#include <vle/utils/i18n.hpp>

namespace vle { namespace devs {

DynamicsComp::DynamicsComp(const DynamicsInit& init,
                   const InitEventList& /* events */)
    : Dynamics(init)
{
}

DynamicsComp::DynamicsComp(const DynamicsInit& init,
                   const InitEventList& /* events */)
    : Dynamics(init)
{
}


Time DynamicsComp::init(Time /* time */ )
{
    setLastTime(Time(0));
    m_neighbourModified = false;
    return devs::infinity;
}

void DynamicsComp::output(Time /* time */, ExternalEventList& output) const
{
    if (m_modified) {
        output.emplace_back("out");
        value::Map& attr = output.back().addMap();

        map <string ,
             pair< std::unique_ptr<value::Value>,bool > >::const_iterator it =
            m_state.begin();

        while (it != m_state.end()) {
            if (it->second.second)
                attr.add(it->first,it->second.first->clone());
            ++it;
        }
    }
}

/*Time DynamicsComp::timeAdvance() const
{
    return m_sigma;
}*/

void DynamicsComp::internalTransition(vle::devs::Time /* time */)
{
    if (m_modified)
        m_modified = false;
}

void DynamicsComp::externalTransition(const ExternalEventList& event,
                                  Time time)
{
    ExternalEventList::const_iterator it = event.begin();

    while (it != event.end()) {
        string v_portName = it->getPortName();

        if (existNeighbourState(v_portName)) {
            map <string, std::unique_ptr<value::Value> >::const_iterator it2 =
                m_neighbourState[v_portName].begin();

            while (it2 != m_neighbourState[v_portName].end()) {
                string v_name = it2->first;
                const value::Value& v_value =
                        *it->attributes()->toMap().get(v_name);
                setNeighbourState(v_portName,v_name,v_value);
                ++it2;
            }
            m_neighbourModified = true;
            updateSigma(time);
        }
        else // c'est une perturbation
            processPerturbation(*it);
        ++it;
    }
}

std::unique_ptr<vle::value::Value> CellDevs::observation(
        const ObservationEvent& event) const
{
    if (existState(event.getPortName())) {
        return getState(event.getPortName()).clone();
    } else {
        return 0;
    }
}

}} // namespace vle extension 

