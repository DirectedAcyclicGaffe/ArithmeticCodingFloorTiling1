#ifndef SLICKWAYIDEA_H
#define SLICKWAYIDEA_H

#include "../MalamuteCore/InheritedClasses/Idea.h"
#include "CoinArrayModel.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"

struct SlickWayAttributes : public IdeaAttributes
{
    SlickWayAttributes();
};

class SlickWayIdea : public Idea
{
    Q_OBJECT
    Q_PROPERTY(double probability READ probability WRITE setProbability NOTIFY probabilityChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int coinRows READ coinRows WRITE setCoinRows NOTIFY coinRowsChanged)
    Q_PROPERTY(int tileRows READ tileRows WRITE setTileRows NOTIFY tileRowsChanged)
    Q_PROPERTY(bool zoom READ zoom WRITE setZoom NOTIFY zoomChanged)

public:
    explicit SlickWayIdea();
    const IdeaAttributes attributes() override;

    void onNewDataIn(std::shared_ptr<DataType> dataType, PlugNumber plugNumber) override;
    std::shared_ptr<DataType> dataOut(PlugNumber plugNumber) override;

    QJsonObject save() const override;
    void load(const QJsonObject &) override;

    double probability() const;
    bool zoom() const;
    bool running() const;
    int coinRows() const;
    int tileRows() const;
    double speed() const;


public slots:
    void coinsAdded();
    void coinsCleared();

    void setProbability(double probability);
    void setZoom(bool zoom);
    void setRunning(bool running);
    void setSpeed(double speed);
    void setCoinRows(int coinRows);
    void setTileRows(int tileRows);

    void step();


signals:
    void probabilityChanged(double probability);
    void runningChanged(bool running);
    void zoomChanged(bool zoom);
    void speedChanged(double speed);
    void coinRowsChanged(int coinRows);
    void tileRowsChanged(int tileRows);

    void startTimer();

private:
    CoinArrayModel* m_nullModel;

    std::weak_ptr<CoinArrayDataType> m_input;
    std::shared_ptr<TileArrayDataType> m_tiles;

    double top;
    double mid;
    double bot;

    int m_coinsUsed;

    double m_probability;
    bool m_zoom;
    bool m_running;
    double m_speed;
    int m_coinRows;
    int m_tileRows;
};

#endif // SLICKWAYIDEA_H
