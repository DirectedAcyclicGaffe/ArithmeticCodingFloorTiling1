#include "HalfSuccessHundred.h"
#include <QtMath>
#include <QDebug>

HalfSuccessHundredAttributes::HalfSuccessHundredAttributes()
{
    m_listName = "Half Success 1 to 100";
    m_displayName = "1 Gold to 100 Bronze\n50% Success Method";
    m_iconPath = "qrc:/Icons/HalfSuccess1to100.png";

    m_dataTypesIn.push_back(Magic<CoinArrayDataTypeAttributes>::cast().id());
    m_dataTypesOut.push_back(Magic<TileArrayDataTypeAttributes>::cast().id());

    m_embeddedQMLPath = ":/QML/HalfSuccess1to100.qml";
}

const IdeaAttributes HalfSuccessHundredTilerIdea::attributes()
{
    return Magic<HalfSuccessHundredAttributes>::cast();
}

HalfSuccessHundredTilerIdea::HalfSuccessHundredTilerIdea() :
    m_speed(1000.0)
{
    m_bot = 0.0;
    m_top = 1.0;

    m_tiles = std::make_shared<TileArrayDataType>(new TileArrayModel());

    m_timer = new QTimer(this);
    m_timer->setInterval(0.6 * m_speed);
    connect(m_timer, &QTimer::timeout, this, &HalfSuccessHundredTilerIdea::step);

    restart();
}

std::shared_ptr<DataType> HalfSuccessHundredTilerIdea::dataOut(PlugNumber)
{
    return std::dynamic_pointer_cast<DataType>(m_tiles);
}

void HalfSuccessHundredTilerIdea::onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber)
{
    auto dataSource = std::dynamic_pointer_cast<CoinArrayDataType>(dataType);
    m_input = dataSource;

    auto n = m_input.lock();
    if(n)
    {
        setStatus(IdeaStatus::Working);
        setContextProperty("CoinModel", n->getModel());
        connect(n->getModel(),&CoinArrayModel::coinsAdded,this, &HalfSuccessHundredTilerIdea::coinsAdded);
        connect(n->getModel(),&CoinArrayModel::coinsCleared, this, &HalfSuccessHundredTilerIdea::coinsCleared);
        emit n->getModel()->coinsAdded();
        emit newData(0);
    }
    else
    {
        setContextProperty("CoinModel", nullptr);
        restart();
        emit modelCleared();
        setDefaultStatus();
    }
}

void HalfSuccessHundredTilerIdea::coinsAdded()
{
    step();
    m_timer->start();
}

void HalfSuccessHundredTilerIdea::coinsCleared()
{
    restart();
    m_tiles->getModel()->clearTiles();
}

void HalfSuccessHundredTilerIdea::step()
{
    auto n = m_input.lock();

    if(m_botMoveStep)
    {
        m_botMoveStep = false;
        botMove();
        return;
    }
    if(m_addCoinChoiceStep)
    {
        if(m_coinsCounter >= 2)
            emit setBackgroundWidth(448 + 79 * m_coinsCounter);
        m_addCoinChoiceStep = false;
        addCoinChoice();
        return;
    }
    if(m_backgroundResizeStep)
    {
        m_backgroundResizeStep = false;
        emit setBackgroundWidth(369 + 79 * m_coinsCounter);
        return;
    }
    if(m_bridgeExtendStep)
    {
        m_bridgeExtendStep = false;
        m_botMoveStep = true;
        m_addTileStep = true;
        m_botXGoal = m_botXGoal + 35.0 + 118.0 + 70;
        emit extendBridge(105.000 + 79*m_coinsCounter + 9.0, 560 - 560 * m_top,
                          560 / qPow(2, m_coinsCounter));
        return;
    }

    if(m_addTileStep)
    {
        m_resetStep = true;
        m_addTileStep = false;
        addTileStep();
        return;
    }
    if(m_resetStep)
    {
        m_resetStep = false;
        emit reset();
        return;
    }

    if(n->getModel()->numCoins() > m_coinsUsed)
    {
        bool isHeads = n->getModel()->isHeads(m_coinsUsed);
        m_botXGoal = 149 + 79 * m_coinsCounter;

        double newTop = m_top;
        double newBot = m_bot;

        if(isHeads)
        {
            m_coinsSum += qPow(2, (6 - m_coinsCounter));
            newBot = m_bot + (m_top - m_bot) / 2;
            emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newBot) , 560.0 * (newBot - m_bot));
        }
        else
        {
            newTop = m_top - (m_top - m_bot) / 2;
            emit addShadow(m_botXGoal - 35.0, 560.0*(1.0-newTop) - 560.0 *(m_top - newTop) , 560.0 * (m_top - newTop));
        }
        m_bot = newBot; m_top = newTop;

        double a = -4.375;
        double b = 560 - 140.0 / qPow(2, m_coinsCounter);
        m_botYGoal = a * m_coinsSum + b;
        m_botMoveStep = true;
        emit newCoin(isHeads, m_botXGoal, m_botYGoal);

        if(m_top < 100.0/101.0)
        {
            if(m_coinsCounter <= 2)
            {
                m_backgroundResizeStep = true;
            }
            m_bridgeExtendStep = true;
            m_addTileStep = true;
            m_addGold = false;
        }
        else if(m_bot > 100.0 / 101.0)
        {
            if(m_coinsCounter <= 2)
            {
                m_backgroundResizeStep = true;
            }
            m_bridgeExtendStep = true;
            m_addTileStep = true;
            m_addGold = true;
        }
        else
        {
            m_addCoinChoiceStep = true;
        }

        m_coinsCounter++;
        m_coinsUsed++;
    }
    else
    {
        if(!m_bridgeExtendStep)
            m_timer->stop();
    }
}

void HalfSuccessHundredTilerIdea::restart()
{
    emit reset();
    m_addCoinChoiceStep = false;
    m_botMoveStep = false;
    m_bridgeExtendStep = false;
    m_addTileStep = false;
    m_resetStep = false;

    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_bot = 0.0;
    m_top = 1.0;

    emit setBackgroundWidth(606);

    m_tiles->getModel()->clearTiles();
    m_coinsUsed = 0;
    auto n = m_input.lock();
    if(n)
        coinsAdded();
}

void HalfSuccessHundredTilerIdea::addCoinChoice()
{
    emit showNextChoice(105.000 + 79*m_coinsCounter, 560 - 560 * m_top,
                        79.0, 560 * (m_top - m_bot));
}

void HalfSuccessHundredTilerIdea::addTileStep()
{
    if(m_addGold)
    {
        emit addTile(false, m_botXGoal, m_botYGoal);
        m_tiles->getModel()->addGold(1);
        emit m_tiles->getModel()->tilesAdded();
    }
    else
    {
        emit addTile(true, m_botXGoal, m_botYGoal);
        m_tiles->getModel()->addBronze(1);
        emit m_tiles->getModel()->tilesAdded();
    }

    m_coinsCounter = 0;
    m_coinsSum = 0;
    m_bot = 0.0;
    m_top = 1.0;
}

void HalfSuccessHundredTilerIdea::botMove()
{
    emit forwardMoveBot(m_botXGoal, m_botYGoal);
}

double HalfSuccessHundredTilerIdea::speed() const
{
    return m_speed;
}


void HalfSuccessHundredTilerIdea::setSpeed(double newSpeed)
{
    if (m_speed == newSpeed)
        return;

    m_speed = newSpeed;
    m_timer->setInterval(0.6 * m_speed);
    emit speedChanged();
}
