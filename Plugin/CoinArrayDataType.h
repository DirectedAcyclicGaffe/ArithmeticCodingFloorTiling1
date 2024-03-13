#ifndef COINARRAYDATATYPE_H
#define COINARRAYDATATYPE_H

#include <QVariant>
#include <QString>
#include <QColor>
#include <QtPlugin>

#include "../MalamuteCore/InheritedClasses/DataType.h"
#include "CoinArrayModel.h"

struct CoinArrayDataTypeAttributes : public DataTypeAttributes
{
    CoinArrayDataTypeAttributes();
};

class CoinArrayDataType : public DataType
{

public:
    explicit CoinArrayDataType(CoinArrayModel* model);
    CoinArrayDataType();
    ~CoinArrayDataType() override;

    DataTypeAttributes getAttributes() override;

    CoinArrayModel* getModel();

private:
    CoinArrayModel* m_model;
};

#endif
