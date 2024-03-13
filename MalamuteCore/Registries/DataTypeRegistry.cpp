#include "DataTypeRegistry.h"

QString DataTypeRegistry::dataTypeAbbreviation(int id)
{
    return m_dataTypeAbbreviations.at(id);
}

QString DataTypeRegistry::defaultDisplay(int id)
{
    return m_defaultDisplays.at(id);
}

QString DataTypeRegistry::defaultSource(int id)
{
    return m_defaultSources.at(id);
}
