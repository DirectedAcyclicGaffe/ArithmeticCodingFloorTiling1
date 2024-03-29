#include "IdeaAttributes.h"

bool ExternalQMLLocation::offsetByWidth() const
{
    return m_offsetByWidth;
}

bool ExternalQMLLocation::offsetByHeight() const
{
    return m_offsetByHeight;
}

int ExternalQMLLocation::extraXOffset() const
{
    return m_extraXOffset;
}

int ExternalQMLLocation::extraYOffset() const
{
    return m_extraYOffset;
}

QString IdeaAttributes::listName() const
{
    return m_listName;
}

QString IdeaAttributes::displayName() const
{
    return m_displayName;
}

QString IdeaAttributes::iconPath() const
{
    return m_iconPath;
}

std::vector<int> IdeaAttributes::dataTypesIn() const
{
    return m_dataTypesIn;
}

QStringList IdeaAttributes::labelsIn() const
{
    return m_labelsIn;
}

std::vector<int> IdeaAttributes::dataTypesOut() const
{
    return m_dataTypesOut;
}

QStringList IdeaAttributes::labelsOut() const
{
    return m_labelsOut;
}

bool IdeaAttributes::customLabels() const
{
    return m_customLabels;
}

bool IdeaAttributes::hasGear() const
{
    return m_gear;
}

bool IdeaAttributes::resizeable() const
{
    return m_resizeable;
}

QString IdeaAttributes::embeddedQMLPath() const
{
    return m_embeddedQMLPath;
}

bool IdeaAttributes::minimizable() const
{
    return !m_minimizedQMLPath.isNull();
}

QStringList IdeaAttributes::externalQMLPaths() const
{
    return m_externalQMLPaths;
}

std::vector<ExternalQMLLocation> IdeaAttributes::externalQMLLocations() const
{
    return m_externalQMLLocations;
}

bool IdeaAttributes::differentNameOnMinimized() const
{
    return !m_minimizedName.isNull();
}

QString IdeaAttributes::minimizedName() const
{
    return m_minimizedName;
}

QString IdeaAttributes::minimizedQMLPath() const
{
    return m_minimizedQMLPath;
}

bool IdeaAttributes::startMinimized() const
{
    return m_startMinimized;
}
