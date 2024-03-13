#include "TileArrayDataType.h"

TileArrayDataTypeAttributes::TileArrayDataTypeAttributes()
{
    m_name = "Tile Array";
    m_abbreviation = "Tiles";
}

DataTypeAttributes TileArrayDataType::getAttributes()
{
    return Magic<TileArrayDataTypeAttributes>::cast();
}

TileArrayDataType::TileArrayDataType(TileArrayModel* model)
{
    m_model = model;
}

TileArrayDataType::TileArrayDataType()
{

}

TileArrayDataType::~TileArrayDataType()
{

}

TileArrayModel* TileArrayDataType::getModel()
{
    return m_model;
}


