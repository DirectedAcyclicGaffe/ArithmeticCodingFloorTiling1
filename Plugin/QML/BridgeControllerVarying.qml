import QtQuick 2.12

Item
{
    id: bridgeController;

    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -1

    width: parent.width;
    height: 560

    function extend(x, y, height)
    {
        bridgeClipRect.x = x;
        bridgeClipRect.y = y;
        bridgeClipRect.height = height;
        bridgeExtendAnimation.start();
    }
    function reset()
    {
        bridgeClipRect.width = 0.0;
    }

    Rectangle
    {
        id: bridgeClipRect;
        clip: true;

        Repeater
        {
            model: 10
            delegate: Rectangle
            {
                height: bridgeClipRect.height
                id: bridgeRect
                width: 10;
                x: 10*index;
                color: "#6e4124"
                border.width: 1
                border.color: "#452716"
            }
        }
        Rectangle
        {
            width: 100
            anchors.top: parent.top
            height: parent.height / 10
            color: "#452716"
        }
        Rectangle
        {
            width: 100
            anchors.bottom: parent.bottom
            height: parent.height / 10
            color: "#452716"
        }



        NumberAnimation
        {
            id: bridgeExtendAnimation
            target: bridgeClipRect
            property: "width"
            to: 100
            duration: 0.8*idea.speed;
        }
    }


}
