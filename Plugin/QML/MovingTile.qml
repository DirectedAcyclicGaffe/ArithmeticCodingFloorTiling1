import QtQuick 2.12

Rectangle
{
    property bool isBronze: true;
    id: root

    width: 50;
    height: 50;
    x: -60
    y: 278;
    z: 10

    color: isBronze ? "#CD7F32" : "#d4af37";
    opacity: 0.0;
    border.width: 5
    border.color: Qt.lighter(color);

    property double xLoc : 0;
    property double yLoc: 0;

    function animate(xLocation, yLocation, xGoal, yGoal)
    {
        x = xLocation - width / 2;
        y = yLocation - height / 2;
        xLoc = xGoal;
        yLoc = yGoal;
        move.restart();
    }

    SequentialAnimation
    {
        id: move;
        PropertyAction{target: root; property: "opacity"; value: 1.0}
        PauseAnimation{duration: 0.15 * idea.speed}
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: root
                property: "x"
                to: root.xLoc
                duration: 0.25 * idea.speed
            }
            PropertyAnimation
            {
                target: root
                property: "y"
                to: root.yLoc
                duration: 0.25 * idea.speed
                easing.type: Easing.OutQuad;
            }
        }
        PauseAnimation
        {
            duration: 0.2 * idea.speed;
        }
        ScriptAction
        {
            script: root.destroy();
        }
    }
}
