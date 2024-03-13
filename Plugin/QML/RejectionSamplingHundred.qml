import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    width: background.width
    height: 600

    Image
    {
        id: background
        anchors.verticalCenter: parent.verticalCenter
        source: "qrc:/Images/Backgrounds/Rejection1to100Background.png"
        sourceSize: Qt.size(1842, 1142)
        height: 571;
        width: 921;

        Connections
        {
            target: idea

            function onNewCoin(isHeads, xLoc, yLoc) {coinController.addCoin(isHeads, xLoc, yLoc)}
            function onForwardMoveBot(x, y) {botController.move(x,y);}
            function onAddShadow(x,y, height) {shadowController.addShadow(x,y,height);}
            function onExtendBridge(y){bridgeController.extend(y);}
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
            coinSize: 25
        }

        BridgeController
        {
            id: bridgeController;
            source: "qrc:/Images/Bridges/bridge4Wide.png"
            bridgeX: 666
        }

        BotController
        {
            id: botController
            source: "qrc:/Images/Bots/PinkBot.png"
            botSize: 30
        }

        TileController
        {
            id: tileController;
            xFinal : 940;
            yFinal : 265;
        }

    }
    SpeedSlider
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
    }
}


