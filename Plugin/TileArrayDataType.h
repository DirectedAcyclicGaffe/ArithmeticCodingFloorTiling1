#ifndef TILEARRAYDATATYPE_H
#define TILEARRAYDATATYPE_H

#include <QVariant>
#include <QString>
#include <QColor>
#include <QtPlugin>

#include "../MalamuteCore/InheritedClasses/DataType.h"
#include "TileArrayModel.h"

struct TileArrayDataTypeAttributes : public DataTypeAttributes
{
    TileArrayDataTypeAttributes();
};

class TileArrayDataType : public DataType
{

public:

    explicit TileArrayDataType(TileArrayModel* model); //Default value of 0.
    TileArrayDataType();
    ~TileArrayDataType() override;
    DataTypeAttributes getAttributes() override;

    TileArrayModel* getModel();

private:
    TileArrayModel* m_model;
};

#endif
