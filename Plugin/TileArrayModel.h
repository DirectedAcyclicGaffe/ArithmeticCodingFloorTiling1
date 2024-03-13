#ifndef TILEARRAYPROPERTY_H
#define TILEARRAYPROPERTY_H

#include <QAbstractListModel>
#include <QDebug>
#include <QRandomGenerator>

class TileArrayModel : public QAbstractListModel
{
    Q_OBJECT
    enum CoinRoles
    {
        SideRole = Qt::UserRole + 1
    };

public:
    explicit TileArrayModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;
    
    Q_INVOKABLE void addBronze(int count);
    Q_INVOKABLE void addGold(int count);
    Q_INVOKABLE void clearTiles();
    Q_INVOKABLE int tileCount();

signals:
    void tilesAdded();

private:
    QList<bool> m_tiles; //Head=Blue tails=Gold
};

#endif // COINARRAYPROPERTY_H
