import QtQuick 2.12
import QtQuick.Controls 2.12
import com.malamute.floorTiling 1.0

Item
{
    id: root;
    width: 720
    height: 600
    Behavior on width {NumberAnimation{duration: idea.speed * 0.3}}

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

            function onShowNextChoice(x, y, width, height) {coinChoiceController.addCoinChoice(x,y,width,height);}
            function onNewCoin(isHeads, xLoc, yLoc) {coinController.addCoin(isHeads, xLoc, yLoc)}
            function onLeftBotMove(x, y) {leftBotController.move(x,y);}
            function onRightBotMove(x, y) {rightBotController.move(x,y);}
            function onAddShadow(isHeads,x,y, height)
            {
                shadowController.addShadow(x,y,height);
                if(isHeads)
                    tileChoiceController.botShadow(y)
                else
                    tileChoiceController.topShadow(y + height)
            }
            function onAddTileChoice(x,y,width,height) {tileChoiceController.addTileChoice(x,y,width,height);}
            function onAddTile(isBronze, x, y) {tileController.addTile(isBronze, x, y);}

            function onZoom(coinXMove, tileXMove, coinHeightFactor, top, bot, a, b)
            {
                zoomAnimation.start();
                coinController.reset();
                coinChoiceController.zoomReset(coinXMove, coinHeightFactor, a, b);
                tileChoiceController.zoomReset(top, bot, tileXMove, coinHeightFactor, a, b);
                shadowController.reset();
                root.width = 720; botStart.x = 310;
            }

            function onExtendLeftSide(){root.width += 21; botStart.x += 21}
            function onExtendRightSide(){root.width += 21;}

            function onReset()
            {
                tileChoiceController.reset();
                coinChoiceController.reset();
                shadowController.reset();
                coinController.reset();
                leftBotController.resetBot();
                rightBotController.resetBot();
                root.width = 720; botStart.x = 310;
            }
        }

        SequentialAnimation
        {
            id: zoomAnimation;

            ScriptAction{script: leftBotController.moveBack();}
            ScriptAction{script: rightBotController.moveBack();}
        }

        Image
        {
            anchors.verticalCenter: parent.verticalCenter
            id: leftBackground
            source: "qrc:/Images/Backgrounds/BotStart.png"
            sourceSize: Qt.size(210, 1142);
            width: 105;
            height: 571;
        }
        CoinChoiceController
        {
            id: coinChoiceController;
            coinRectWidth: 20
            stairs: false;
        }

        ShadowController
        {
            id: shadowController;
            width: botStart.x + botStart.width;
            z: 10
        }

        CoinController
        {
            id: coinController
            coinSize: 20
        }

        BotController
        {
            id: leftBotController
            source: "qrc:/Images/Bots/BlueBot3.png"
            botSize: 30
            z: 20
        }
        Image
        {
            id: botStart;
            x: 310;
            source: "qrc:/Images/Backgrounds/BotStart.png"
            sourceSize: Qt.size(210, 1142);
            width: 105;
            height: 571;
            Behavior on x {NumberAnimation{duration: idea.speed * 0.3}}



            TileController
            {
                id: tileController;
                xFinal : background.width - botStart.x + 25;
                yFinal : 280;
            }
        }
        TileChoiceController
        {
            x: botStart.x;
            id: tileChoiceController;
            tileRectWidth: 20
            Behavior on x {NumberAnimation{duration: idea.speed * 0.3}}

        }
        BotController
        {
            id: rightBotController
            x: botStart.x;
            source: "qrc:/Images/Bots/BlueBot4.png"
            botSize: 30
            z: 20
            Behavior on x {NumberAnimation{duration: idea.speed * 0.3}}

        }

    }

    SpeedSlider
    {
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -10
    }
}
