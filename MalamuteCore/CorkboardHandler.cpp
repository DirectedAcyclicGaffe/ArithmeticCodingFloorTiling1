#include "CorkboardHandler.h"
#include <QDir>
#include <QThread>
#include <QMimeData>
#include <QClipboard>
#include <QSettings>
#include <QQmlApplicationEngine>

#include "Plugin/Plugin.h"

#include "Registries/DataTypeRegistry.h"
#include "Registries/IdeaRegistry.h"


CorkboardHandler::CorkboardHandler(QObject *parent) :
    QObject(parent),
    openFileUrl("")
{
    //Initialize the registries
    m_ideaRegistry = std::make_shared<IdeaRegistry>();
    m_dataTypeRegistry = std::make_shared<DataTypeRegistry>();

    loadPlugin(new Plugin());

    m_ideaList = m_ideaRegistry->registeredIdeaNames();
}

void CorkboardHandler::loadInitialFile()
{
    load(QUrl("qrc:/DemoFiles/InitialMutt.mutt"));
}

Corkboard *CorkboardHandler::getCorkboard() const
{
    return m_corkboard;
}

void CorkboardHandler::resetCorkboard(Corkboard *corkboard)
{
    m_corkboard = corkboard;

    m_corkboard->createBackend(m_ideaRegistry);
    m_corkboard->setQmlEngine(qmlEngine(corkboard));
    m_corkboard->setDataTypeRegistry(m_dataTypeRegistry);

    loadInitialFile();
}

void CorkboardHandler::setVisibleWindowProperties(int width, int height)
{
    m_corkboard->setVisibleWindowParams(width,height);
}

void CorkboardHandler::loadPlugin(MalamutePlugin* plugin)
{
    if(plugin)
    {
        //DO NOT CHANGE THE ORDER!!!
        plugin->registerDataTypeAttributes(m_dataTypeRegistry);
        plugin->registerIdeas(m_ideaRegistry);
    }
    delete plugin;
}

QString CorkboardHandler::ideaIconPath(QString ideaName)
{
    QString iconPath = m_ideaRegistry->iconPath(ideaName);
    return iconPath != "" ? iconPath : "qrc:/Images/Blank.png";
}

QStringList CorkboardHandler::ideaList() const
{
    return m_ideaList;
}

void CorkboardHandler::save()
{
    QString filePath = openFileUrl.toLocalFile();
    if(QFileInfo(filePath).suffix() != "mutt")
        filePath.append(".mutt");

    QFile file(filePath);

    if(!file.open(QFile::WriteOnly))
        return;

    file.write(m_corkboard->saveData());
    file.close();
}

void CorkboardHandler::saveAs(const QUrl &fileUrl)
{
    openFileUrl = fileUrl;
    QString filePath = fileUrl.toLocalFile();
    if(QFileInfo(filePath).suffix() != "mutt")
        filePath.append(".mutt");

    QFile file(filePath);

    if(!file.open(QFile::WriteOnly))
        return;

    file.write(m_corkboard->saveData());
    file.close();

    setOpenFileUrl(fileUrl);
}

void CorkboardHandler::load(const QUrl &fileUrl)
{
    m_corkboard->deleteAll();

    QString filePath = fileUrl.toDisplayString();
    if(filePath.startsWith("file"))
        filePath.remove(0,7);
    if(filePath.startsWith("qrc"))
        filePath.remove(0,3);

    if (!QFileInfo::exists(filePath))
        return;

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
        return;

    m_corkboard->loadData(file.readAll());

    file.close();

    setOpenFileUrl(fileUrl);
}

QUrl CorkboardHandler::getOpenFileUrl() const
{
    return openFileUrl;
}

bool CorkboardHandler::validOpenFileUrl() const
{
    return openFileUrl.isEmpty() ? false : true;
}

void CorkboardHandler::setOpenFileUrl(const QUrl &value)
{
    openFileUrl = value;
}
