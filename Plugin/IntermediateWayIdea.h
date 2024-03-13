#ifndef INTERMEDIATEWAYIDEA_H
#define INTERMEDIATEWAYIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct IntermediateWayAttributes : public IdeaAttributes
{
    IntermediateWayAttributes();
};

class IntermediateWayIdea : public Idea
{
    Q_OBJECT
    Q_PROPERTY(double probability READ probability WRITE setProbability NOTIFY probabilityChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int coinRows READ coinRows WRITE setCoinRows NOTIFY coinRowsChanged)

public:
    explicit IntermediateWayIdea();
    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    double probability() const;    
    bool running() const;
    double speed() const;   
    int coinRows() const;

public slots:
    void coinsAdded();
    void coinsCleared();

    void setProbability(double probability);  
    void setRunning(bool running);
    void setSpeed(double speed);
    void setCoinRows(int coinRows);

    void step();

signals:
    void probabilityChanged(double probability);    
    void runningChanged(bool running);
    void speedChanged(double speed);
    void coinRowsChanged(int coinRows);

    void startTimer();

private:
    CoinArrayModel* m_nullModel;

    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    double intervalTop;
    double intervalHeight;

    int m_coinsUsed;

    double m_probability;
    bool m_running;
    double m_speed;
    int m_coinRows;
};

#endif // INTERMEDIATEWAYIDEA_H
