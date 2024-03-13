#include "TileArrayModel.h"

TileArrayModel::TileArrayModel(QObject *parent) : QAbstractListModel(parent)
{

}

int TileArrayModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_tiles.size();
}

QVariant TileArrayModel::data(const QModelIndex &index, int role) const
{
    if(index.row() < 0 || index.row() >= m_tiles.count())
        return QVariant();

    //Valid index.
    switch (role)
    {
    case SideRole:
        return m_tiles[index.row()];
    default:
        return QVariant();
    }
}

bool TileArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == SideRole)
    {
        m_tiles[index.row()] = value.toBool();
        emit dataChanged(index,index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TileArrayModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TileArrayModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[SideRole] = "Side";
    return roles;
}

void TileArrayModel::addBronze(int count)
{
    const int index = m_tiles.size();

    beginInsertRows(QModelIndex(), index, index+count-1);
    for(int i = 0; i < count; i++)
        m_tiles.append(true);
    endInsertRows();

    emit tilesAdded();
}

void TileArrayModel::addGold(int count)
{
    const int index = m_tiles.size();

    beginInsertRows(QModelIndex(), index, index+count-1);
    for(int i = 0; i < count; i++)
        m_tiles.append(false);
    endInsertRows();

    emit tilesAdded();
}

void TileArrayModel::clearTiles()
{
    beginRemoveRows(QModelIndex(), 0, m_tiles.size());
    m_tiles.clear();
    endRemoveRows();

    emit tilesAdded();
}

int TileArrayModel::tileCount()
{
    return m_tiles.size();
}
