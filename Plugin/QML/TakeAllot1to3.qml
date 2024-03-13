import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    width: 920
    height: 600

    Rectangle
    {
        id: background
        anchors.verticalCenter: parent.verticalCenter
        height: 571
        width: parent.width
        color: "black"

        Connections
        {
            target: idea

            function onNewCoin(isHeads, xLoc, yLoc) {coinController.addCoin(isHeads, xLoc, yLoc)}
            function onLeftBotMove(x, y) {leftBotController.move(x,y);}
            function onRightBotMove(x, y) {rightBotController.move(x,y);}
            function onAddShadow(x,y, height) {shadowController.addShadow(x,y,height);}
            //function onAddTileChoice(x,y,width,height) {tileChoiceController.addTileChoice(x,y,width,height);}

            function onAddTile(isBronze, x, y)
            {
                tileController.addTile(isBronze, x, y);
            }

            function onReset()
            {
                //tileChoiceController.reset();
                shadowController.reset();
                coinController.reset();
                leftBotController.resetBot();
                rightBotController.resetBot();
                bridgeController.reset();
            }
        }
        Image
        {
            anchors.verticalCenter: parent.verticalCenter
            id: leftBackground
            source: "qrc:/Images/Backgrounds/TakeAllot1to3Left.png"
            sourceSize: Qt.size(800, 1142);
            width: 400;
            height: 571;
        }
        ShadowController
        {
            id: shadowController;
            z: 10
        }

        CoinController
        {
            id: coinController
            coinSize: 40
        }

        BridgeControllerVarying
        {
            id: bridgeController;
        }

        BotController
        {
            id: leftBotController
            source: "qrc:/Images/Bots/BlueBot2.png"
            botSize: 30
            z: 20
        }
        Image
        {
            id: botStart;
            x: 310;
            source: "qrc:/Images/Backgrounds/TakeAllot1to3Right.png"
            sourceSize: Qt.size(1206, 1142);
            width: 603;
            height: 571;

            BotController
            {
                id: rightBotController
                source: "qrc:/Images/Bots/BlueBot3.png"
                botSize: 30
                z: 20
            }
            TileController
            {
                id: tileController;
                xFinal : background.width - botStart.x + 25;
                yFinal : 280;
            }
        }

    }

    SpeedSlider
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
    }
}


