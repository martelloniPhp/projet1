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

int DynamicsComp::nb;
std::vector<utils::State *> DynamicsComp::influanceur;
DynamicsComp::DynamicsComp(const DynamicsCompInit& init,
                   const InitEventList& /* events */)
    : m_context(init.context)
    , m_model(init.model)
    , m_packageid(init.packageid)
{
	tn=0;
}

DynamicsComp::DynamicsComp(const DynamicsCompInit& init,
                   const InitEventList& events, std::string name)
    : m_context(init.context)
    , m_model(init.model)
    , m_packageid(init.packageid)
    ,m_Name(name)
{
	
}

std::string DynamicsComp::getPackageDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not " "installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageSimulatorDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getPluginSimulatorDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not " "installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageSrcDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getSrcDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageDataDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getDataDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageDocDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getDocDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageExpDir() const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getExpDir(vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not " "installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageLibFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getLibFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageSrcFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getSrcFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageDataFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getDataFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageDocFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getDocFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

std::string DynamicsComp::getPackageExpFile(const std::string& name) const
{
    vle::utils::Package pkg(m_context, *m_packageid);
    if (pkg.existsBinary()) {
        return pkg.getExpFile(name, vle::utils::PKG_BINARY);
    } else {
        throw vle::utils::FileError(
            (fmt(_("Package '%1%' is not installed")) % *m_packageid).str());
    }
}

}}// namespace vle extension 

