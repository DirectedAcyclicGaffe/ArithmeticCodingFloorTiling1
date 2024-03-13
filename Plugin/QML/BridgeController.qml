import QtQuick 2.12

Item
{
    id: bridgeController;

    property alias source : bridge.source;
    property alias bridgeX : bridgeClipper.x;

    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -1

    width: parent.width;
    height: 560

    function extend(yLoc)
    {
        bridgeClipper.y = yLoc;
        bridgeExtendAnimation.start();
    }
    function reset()
    {
        bridgeClipper.width = 0;
    }

    Rectangle
    {
        id: bridgeClipper
        y: 420
        height: bridge.height
        width: 0
        clip: true
        color: "transparent"

        Image
        {
            id: bridge
            source: ""
        }

        SequentialAnimation
        {
            id: bridgeExtendAnimation
            NumberAnimation
            {
                target: bridgeClipper
                property: "width"
                duration: 0.98 * idea.speed
                to: 100
                easing.type: Easing.InOutQuad
            }
        }
    }
}
