import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    width: 670
    height: 600

    Image
    {
        anchors.verticalCenter: parent.verticalCenter
        id: background
        source: "qrc:/Images/Backgrounds/RejectionBackground.png"
        sourceSize: Qt.size(1340.000, 1142);
        width: 670;
        height: 571;

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
        }

        BridgeController
        {
            id: bridgeController;
            source: "qrc:/Images/Bridges/bridge140Wide.png"
            bridgeX: 411.356

        }

        BotController
        {
            id: botController
            source: "qrc:/Images/Bots/RedBot.png"
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


