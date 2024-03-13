#include "CoinFlipperIdea.h"
#include <QtMath>
#include <QDebug>

CoinFlipperAttributes::CoinFlipperAttributes()
{
    m_listName = "Coin Flipper";
    m_displayName = "Coin Flipper";
    m_iconPath = "qrc:/Icons/CoinFlipper.png";

    m_embeddedQMLPath = ":/QML/CoinFlipper.qml";

    m_dataTypesOut.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_labelsOut << "";
    m_customLabels = true;
}

const IdeaAttributes CoinFlipperIdea::attributes()
{
    return Magic<CoinFlipperAttributes>::cast();
}

CoinFlipperIdea::CoinFlipperIdea()
{
    setStatus(IdeaStatus::Working);
    m_coins = std::make_shared<CoinArrayDataType>(new CoinArrayModel());
}

void CoinFlipperIdea::finishSetupQmlContext()
{
    setContextProperty("CoinModel", m_coins->getModel());
}

std::shared_ptr<DataType> CoinFlipperIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_coins);
}






