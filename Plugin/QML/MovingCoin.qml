import QtQuick 2.12

Image
{
    property bool isHeads: true;
    id: root
    source: isHeads ? "qrc:/Images/CoinHeads400.png" : "qrc:/Images/CoinTails400.png"
    sourceSize: Qt.size(400,400)
    width: 100;
    height: root.width
    x: -100
    y: 228;
    z: 10
    opacity: 1.0;

    property double xLoc : 0;
    property double yLoc: 0;

    function animate(xLocation, yLocation)
    {
        xLoc = xLocation - root.width / 2;
        yLoc = yLocation - root.height / 2;
        move.restart();
    }

    SequentialAnimation
    {
        id: move;
        PropertyAction{target: root; property: "opacity"; value: 1.0}
        PauseAnimation{duration: 0.2 * idea.speed}
        ParallelAnimation
        {
            PropertyAnimation
            {
                target: root
                property: "x"
                to: root.xLoc
                duration: 0.7 * idea.speed
            }
            PropertyAnimation
            {
                target: root
                property: "y"
                to: root.yLoc
                duration: 0.7 * idea.speed
                easing.type: Easing.OutQuad;
            }
        }
    }
}
