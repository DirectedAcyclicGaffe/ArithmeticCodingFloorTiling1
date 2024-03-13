import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    width: background.width
    height: 600

    Image
    {
        anchors.verticalCenter: parent.verticalCenter
        id: background
        source: "qrc:/Images/Backgrounds/TakeTwoBackground.png"
        sourceSize: Qt.size(1384, 1142);
        width: 692;
        height: 571;

        Connections
        {
            target: idea

            function onNewCoin(isHeads, xLoc, yLoc) {coinController.addCoin(isHeads, xLoc, yLoc)}
            function onForwardMoveBot(x, y) {botController.move(x,y);}
            function onAddShadow(x,y, height) {shadowController.addShadow(x,y,height);}
            function onExtendBridge(x,y,height){bridgeController.extend(x,y,height);}
            function onAddTile(isBronze, x, y){tileController.addTile(isBronze, x, y);}
            function onReset()
            {
                shadowController.reset();
                coinController.reset();
                botController.resetBot();
                bridgeController.reset();
            }
        }
        ShadowController
        {
            id: shadowController;
        }
        CoinController
        {
            id: coinController
            coinSize: 50
        }

        BridgeControllerVarying
        {
            id: bridgeController;
        }

        BotController
        {
            id: botController
            source: "qrc:/Images/Bots/BlueBot1.png"
        }

        TileController
        {
            id: tileController;
            xFinal : 685;
            yFinal : 265;
        }

    }
    SpeedSlider
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
    }
}


