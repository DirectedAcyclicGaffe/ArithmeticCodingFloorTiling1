#include "Idea.h"

#include <QClipboard>
#include <QMimeData>

QJsonObject Idea::save() const
{
    QJsonObject saveJson;
    QJsonArray arr;
    for(int i = 0; i < m_outPortLabelColors.size(); i++)
        arr.append(m_outPortLabelColors.at(i).name());
    saveJson["c"] = arr;
    return saveJson;
}

void Idea::load(const QJsonObject &obj)
{
    QJsonValue v = obj["c"];
    if(!v.isUndefined())
    {
        m_outPortLabelColors.clear();
        QJsonArray arr = v.toArray();
        for(int i = 0; i < arr.size(); i++)
            m_outPortLabelColors.push_back(QColor(arr.at(i).toString()));
        emit outPortLabelColorsChanged(m_outPortLabelColors);
    }
}

void Idea::onNewDataIn(std::shared_ptr<DataType>, PlugNumber)
{

}

std::shared_ptr<DataType> Idea::dataOut(PlugNumber)
{
    return nullptr;
}

void Idea::resetDisplay()
{

}

void Idea::updateOnInPortLabelColor()
{

}

void Idea::updateOnOutPortLabelColor()
{

}

void Idea::finishSetupQmlContext()
{

}

QString Idea::statusMessage() const
{
    return m_statusMessage;
}

IdeaStatus Idea::status() const
{
    return m_status;
}

bool Idea::valid() const
{
    if(m_status == IdeaStatus::Working || m_status == IdeaStatus::Warning || m_status == IdeaStatus::DisplayWarning)
        return true;
    else
        return false;
}

bool Idea::minimized() const
{
    return m_minimized;
}

QList<QColor> Idea::inPortLabelColors() const
{
    return m_inPortLabelColors;
}

QList<QColor> Idea::outPortLabelColors() const
{
    return m_outPortLabelColors;
}


void Idea::setStatus(IdeaStatus status, QString message)
{
    m_status = status;
    m_statusMessage = message;
    emit statusChanged();

    if(status == IdeaStatus::StandBy || status == IdeaStatus::Error || status == IdeaStatus::Fatal)
    {
        emit clearDataAllPlugs();
        emit validChanged(false);
    }
    else
    {
        emit validChanged(true);
    }
}

void Idea::setDefaultStatus()
{
    IdeaStatus oldStatus = m_status;
    m_status = IdeaStatus::StandBy;
    m_statusMessage = "Standing By";
    emit statusChanged();
    emit validChanged(false);

    //Clear data if necessary
    if(oldStatus == IdeaStatus::Working || oldStatus == IdeaStatus::Warning || oldStatus == IdeaStatus::DisplayWarning)
        emit clearDataAllPlugs();
}

void Idea::sendTextToClipboard(QString text)
{
    QMimeData* mimeData = new QMimeData;
    mimeData->setText(text);

    QClipboard* clipboard = QGuiApplication::clipboard();
    clipboard->setMimeData(mimeData);
}

void Idea::setMinimized(bool minimized)
{
    if (m_minimized == minimized)
        return;

    m_minimized = minimized;
    emit minimizedChanged(m_minimized);
}

void Idea::setInPortLabelColor(int i, QColor color)
{
    if(m_inPortLabelColors.at(i) == color)
        return;

    m_inPortLabelColors[i] = color;
    emit inPortLabelColorsChanged(m_inPortLabelColors);

    updateOnInPortLabelColor();
}

void Idea::setOutPortLabelColor(int i, QColor color)
{
    if(m_outPortLabelColors.at(i) == color)
        return;

    m_outPortLabelColors[i] = color;
    emit outPortLabelColorsChanged(m_outPortLabelColors);

    updateOnOutPortLabelColor();
}

const QColor Idea::getInPortLabelColor(int i)
{
    return m_inPortLabelColors.at(i);
}

const QColor Idea::getOutPortLabelColor(int i)
{
    return m_outPortLabelColors.at(i);
}

void Idea::prepareInPortLabelColors(int n, QColor color)
{
    m_inPortLabelColors.reserve(n);
    for(int i = 0; i < n; i++)
        m_inPortLabelColors.push_back(color);
}

void Idea::prepareOutPortLabelColors(QList<QColor> colorList)
{
    m_outPortLabelColors = colorList;
    emit outPortLabelColorsChanged(m_outPortLabelColors);
}
