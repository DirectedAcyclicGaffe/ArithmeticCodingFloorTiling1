#include "Plugin.h"

#include "CoinFlipperIdea.h"
#include "CoinArrayDataType.h"
#include "TileArrayDataType.h"
#include "TileFloorIdea.h"

#include "RejectionSampling.h"
#include "RejectionSamplingFive.h"
#include "RejectionSamplingHundred.h"

#include "RedunantRemoval.h"
#include "RedunantRemovalFive.h"

#include "HalfSuccessFive.h"
#include "HalfSuccessHundred.h"

#include "BlackBoxHundred.h"

// #include "Plugin/DecompressionAlgorithm.h"

#include "TakeTwo.h"
#include "TakeAllot1to3.h"
#include "TakeTwoInefficient.h"

#include "MostEfficient1to3.h"
#include "MostEfficient1to5.h"
#include "MostEfficient1to100.h"

QString Plugin::PluginName()
{
    return "PLUGIN";
}

void Plugin::registerIdeas(std::shared_ptr<IdeaRegistry> ideaRegistry)
{
    ideaRegistry->registerIdea<CoinFlipperIdea>();
    ideaRegistry->registerIdea<BlackBoxHundredIdea>();

    ideaRegistry->registerIdea<RejectionSampingTilerIdea>();
    ideaRegistry->registerIdea<RejectionSampingFiveTilerIdea>();
    ideaRegistry->registerIdea<RejectionSampingHundredTilerIdea>();
    ideaRegistry->registerIdea<RedunantRemovalTilerIdea>();
    ideaRegistry->registerIdea<RedunantRemovalFiveTilerIdea>();
    ideaRegistry->registerIdea<HalfSuccessFiveTilerIdea>();
    ideaRegistry->registerIdea<HalfSuccessHundredTilerIdea>();

    ideaRegistry->registerIdea<TakeTwoInefficientTilerIdea>();
    ideaRegistry->registerIdea<TakeTwoTilerIdea>();
    ideaRegistry->registerIdea<TakeAllot1to3TilerIdea>();


    //ideaRegistry->registerIdea<DecompressionAlgorithmTilerIdea>();

    ideaRegistry->registerIdea<MostEfficient1to3TilerIdea>();
    ideaRegistry->registerIdea<MostEfficient1to5TilerIdea>();
    ideaRegistry->registerIdea<MostEfficient1to100TilerIdea>();

    ideaRegistry->registerIdea<TileFloorIdea>();

    qmlRegisterType(QUrl("qrc:/QML/RejectionSamplingRect.qml"), "com.malamute.floorTiling", 1, 0, "RejectionSamplingRect");
    qmlRegisterType(QUrl("qrc:/QML/MovingCoin.qml"), "com.malamute.floorTiling", 1, 0, "MovingCoin");
    qmlRegisterType(QUrl("qrc:/QML/NewChoiceRects.qml"), "com.malamute.floorTiling", 1, 0, "NewChoiceRects");
    qmlRegisterType(QUrl("qrc:/QML/NewChoiceRectsTile.qml"), "com.malamute.floorTiling", 1, 0, "NewChoiceRectsTile");
    qmlRegisterType(QUrl("qrc:/QML/MovingTile.qml"), "com.malamute.floorTiling", 1, 0, "MovingTile");
    qmlRegisterType(QUrl("qrc:/QML/SpeedSlider.qml"), "com.malamute.floorTiling", 1, 0, "SpeedSlider");
    qmlRegisterType(QUrl("qrc:/QML/TileController.qml"), "com.malamute.floorTiling", 1, 0, "TileController");
    qmlRegisterType(QUrl("qrc:/QML/BridgeController.qml"), "com.malamute.floorTiling", 1, 0, "BridgeController");
    qmlRegisterType(QUrl("qrc:/QML/BotController.qml"), "com.malamute.floorTiling", 1, 0, "BotController");
    qmlRegisterType(QUrl("qrc:/QML/CoinController.qml"), "com.malamute.floorTiling", 1, 0, "CoinController");
    qmlRegisterType(QUrl("qrc:/QML/CoinChoiceController.qml"), "com.malamute.floorTiling", 1, 0, "CoinChoiceController");
    qmlRegisterType(QUrl("qrc:/QML/BridgeControllerVarying.qml"), "com.malamute.floorTiling", 1, 0, "BridgeControllerVarying");
    qmlRegisterType(QUrl("qrc:/QML/TileChoiceController.qml"), "com.malamute.floorTiling", 1, 0, "TileChoiceController");
    qmlRegisterType(QUrl("qrc:/QML/ShadowController.qml"), "com.malamute.floorTiling", 1, 0, "ShadowController");
}

void Plugin::registerDataTypeAttributes(std::shared_ptr<DataTypeRegistry> dataTypeRegistry)
{
    dataTypeRegistry->registerDataTypeAttributes<CoinArrayDataTypeAttributes>();
    dataTypeRegistry->registerDataTypeAttributes<TileArrayDataTypeAttributes>();
}
