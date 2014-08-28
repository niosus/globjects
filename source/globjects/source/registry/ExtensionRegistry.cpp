#include "ExtensionRegistry.h"
#include "Registry.h"

#include <glbinding/Meta.h>

#include <globjects/globjects.h>

namespace glo {

ExtensionRegistry::ExtensionRegistry()
: m_initialized(false)
{
}

ExtensionRegistry & ExtensionRegistry::current()
{
    return Registry::current().extensions();
}


std::set<gl::GLextension>::iterator ExtensionRegistry::begin()
{
    return availableExtensions().begin();
}

std::set<gl::GLextension>::iterator ExtensionRegistry::end()
{
    return availableExtensions().end();
}

const std::set<gl::GLextension> & ExtensionRegistry::availableExtensions()
{
    initialize();
    return m_availableExtensions;
}

const std::set<std::string> & ExtensionRegistry::unknownAvailableExtensions()
{
    initialize();
    return m_unknownAvailableExtensions;
}

void ExtensionRegistry::initialize()
{
    if (m_initialized)
        return;

    for (const std::string & extensionName : getExtensions())
    {
        gl::GLextension extension = glbinding::Meta::getExtension(extensionName);

        if (extension != gl::GLextension::UNKNOWN)
        {
            m_availableExtensions.insert(extension);
        }
        else
        {
            m_unknownAvailableExtensions.insert(extensionName);
        }
    }

    m_initialized = true;
}

bool ExtensionRegistry::hasExtension(gl::GLextension extension)
{
    initialize();

    if (isInCoreProfile(extension))
        return true;

    return m_availableExtensions.find(extension) != m_availableExtensions.end();
}

bool ExtensionRegistry::hasExtension(const std::string & extensionName)
{
    initialize();

    gl::GLextension extension = glbinding::Meta::getExtension(extensionName);

    if (extension != gl::GLextension::UNKNOWN)
    {
        return hasExtension(extension);
    }
    else
    {
        return m_unknownAvailableExtensions.find(extensionName) != m_unknownAvailableExtensions.end();
    }
}

glbinding::Version getCoreVersion(gl::GLextension extension)
{
    return glbinding::Meta::getRequiringVersion(extension);
}

bool ExtensionRegistry::isInCoreProfile(gl::GLextension extension, const glbinding::Version & version)
{
    glbinding::Version coreVersion = getCoreVersion(extension);

    if (!coreVersion.isValid())
        return false;

    return coreVersion <= version;
}


bool ExtensionRegistry::isInCoreProfile(gl::GLextension extension)
{
    return isInCoreProfile(extension, glo::version());
}

} // namespace glo
