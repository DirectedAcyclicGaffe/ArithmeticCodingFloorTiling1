import QtQuick 2.12

Item
{
    id: botController

    property alias source : bot.source;
    property alias botSize: bot.width;

    height: 560
    width: parent.width
    anchors.verticalCenter: parent.verticalCenter

    property double moveRotAngle : 0;
    property double moveXGoal: 0;
    property double moveYGoal: 0;

    function move(xGoal, yGoal)
    {
        waitingAnimation.stop();
        botController.moveXGoal = xGoal - bot.width / 2.0;
        botController.moveYGoal = yGoal - bot.height / 2.0;
        let xDif = xGoal - (bot.x + bot.width / 2.0);
        let yDif = -1.0 * (yGoal - (bot.y + bot.height / 2.0)); // QML coords have y reversed from normal;
        botController.moveRotAngle = 90 - 180 / 3.14159 * Math.atan(yDif/xDif);
        moveAnimation.start();
    }
    function resetBot()
    {
        moveAnimation.stop();
        fadeMoveAnimation.start();
    }

    function moveBack()
    {
        waitingAnimation.stop();
        botController.moveXGoal = 50 - bot.width / 2.0;
        botController.moveYGoal = 280 - bot.height / 2.0;
        let xDif = 50 - (bot.x + bot.width / 2.0);
        let yDif = -1.0 * (280 - (bot.y + bot.height / 2.0)); // QML coords have y reversed from normal;
        botController.moveRotAngle = 270 - 180 / 3.14159 * Math.atan(yDif/xDif);
        moveAnimation.start();
    }

    Component.onCompleted: resetBot();

    Image
    {
        id: bot
        rotation: 90;
        source: ""
        sourceSize: Qt.size(120, 120)
        width: 60
        height: width
    }

    SequentialAnimation
    {
        id: moveAnimation
        NumberAnimation
        {
            target: bot
            property: "rotation";
            to: botController.moveRotAngle
            duration: 0.2 * idea.speed
        }
        ParallelAnimation
        {
            NumberAnimation
            {
                target: bot
                property: "x";
                to: botController.moveXGoal
                duration: 0.4 * idea.speed
            }
            NumberAnimation
            {
                target: bot
                property: "y";
                to: botController.moveYGoal
                duration: 0.4 * idea.speed
            }
        }
        NumberAnimation
        {
            target: bot
            property: "rotation";
            to: 90;
            duration: 0.2 * idea.speed
        }
        ScriptAction{script: waitingAnimation.start()}
    }

    SequentialAnimation
    {
        id: waitingAnimation
        running: true;
        loops: Animation.Infinite

        SequentialAnimation
        {
            NumberAnimation
            {
                target: bot
                property: "rotation"
                duration: 2000
                to: 105
                easing.type: Easing.InOutQuad
            }

            NumberAnimation
            {
                target: bot
                property: "rotation"
                duration: 2000
                to: 75
                easing.type: Easing.InOutQuad
            }
        }
    }
    SequentialAnimation
    {
        id: fadeMoveAnimation
        NumberAnimation
        {
            target: bot
            property: "opacity"
            duration: 0.2*idea.speed
            to: 0.0
            easing.type: Easing.InOutQuad
        }
        PropertyAction{target: bot; property: "x"; value: 50 - bot.width / 2}
        PropertyAction{target: bot; property: "y"; value: 280 - bot.height / 2}
        PropertyAction{target: bot; property: "rotation"; value: 0}

        NumberAnimation
        {
            target: bot
            property: "opacity"
            duration: 0.4*idea.speed
            to: 1.0
            easing.type: Easing.InOutQuad
        }
        ScriptAction{script: waitingAnimation.start()}
    }
}

