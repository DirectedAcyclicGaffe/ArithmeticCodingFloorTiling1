import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    width: background.width
    height: 600

    Rectangle
    {
        id: background
        anchors.verticalCenter: parent.verticalCenter
        height: 571;
        width: 606
        color: "black"

        Behavior on width {NumberAnimation{duration: idea.speed * 0.3}}

        Image
        {
            id: botStart
            source: "qrc:/Images/Backgrounds/BotStart.png"
            sourceSize: Qt.size(210, 1142);
            width: 105;
            height: 571;
        }
        Rectangle
        {
            id: midsection
            anchors.right: tilePick.left
            anchors.left: botStart.right
            height: 560
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -1
            color: "#1f230c"
        }
        Image
        {
            id: tilePick
            source: "qrc:/Images/Backgrounds/PickTile1to100.png"
            anchors.right: parent.right
            sourceSize: Qt.size(528, 1142);
            width: 264;
            height: 571;
        }

        Connections
        {
            target: idea

            function onShowNextChoice(x, y, width, height) {coinChoiceController.addCoinChoice(x,y,width,height);}
            function onNewCoin(isHeads, x, y) {coinController.addCoin(isHeads, x, y)}
            function onForwardMoveBot(x, y) {botController.move(x,y);}
            function onAddShadow(x,y, height) {shadowController.addShadow(x,y,height);}
            function onExtendBridge(x,y,height){bridgeController.extend(x,y,height);}
            function onAddTile(isBronze, x, y){tileController.addTile(isBronze, x, y);}
            function onReset()
            {
                shadowController.reset();
                coinChoiceController.reset();
                coinController.reset();
                botController.resetBot();
                bridgeController.reset();
                background.width = 606;
            }
            function onSetBackgroundWidth(width){background.width = width}
        }

        CoinChoiceController
        {
            id: coinChoiceController;
            coinRectWidth: 70
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
            source: "qrc:/Images/Bots/TealBot.png"
            botSize: 30
        }

        TileController
        {
            id: tileController;
            xFinal : background.width + 30;
            yFinal : 265;
        }

    }
    SpeedSlider
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
    }
}


