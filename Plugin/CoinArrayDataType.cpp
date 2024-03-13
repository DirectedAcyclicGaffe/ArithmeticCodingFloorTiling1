#include "CoinArrayDataType.h"

CoinArrayDataTypeAttributes::CoinArrayDataTypeAttributes()
{
    m_name = "CoinArray";
    m_abbreviation = "Coins";
}

DataTypeAttributes CoinArrayDataType::getAttributes()
{
    return Magic<CoinArrayDataTypeAttributes>::cast();
}

CoinArrayDataType::CoinArrayDataType(CoinArrayModel* model)
{
    m_model = model;
}

CoinArrayDataType::CoinArrayDataType()
{

}

CoinArrayDataType::~CoinArrayDataType()
{

}


CoinArrayModel *CoinArrayDataType::getModel()
{
    return m_model;
}





