import QtQuick 2.12

Rectangle
{
    id: root

    Image
    {
        id: image
        height: 70
        width: 70;
        anchors.centerIn: parent
    }

    function setRed()
    {
        image.source = "qrc:/Images/CoinHeads.png"
        root.color = "#7f1616"
    }

    function setSilver()
    {
        image.source = "qrc:/Images/CoinTails.png"
        root.color = "silver"
    }

    function setPre()
    {
        toPreAnimation.start();
    }
    function setSelected()
    {
        toSelectedAnimation.start();
    }
    function setNotSelected()
    {
        toNotSelectedAnimation.start();
    }
    ParallelAnimation
    {
        id: toSelectedAnimation
        SequentialAnimation
        {
            PauseAnimation
            {
                duration: 0.95* idea.speed
            }
            PropertyAction
            {
                target: image
                property: "opacity"
                value: 1.0;
            }
        }
        PropertyAnimation
        {
            target: root
            property: "opacity"
            to: 1.0;
            duration: 0.95* idea.speed
        }
    }
    ParallelAnimation
    {
        id: toNotSelectedAnimation
        PropertyAnimation
        {
            target: image
            property: "opacity"
            to: 0.0;
            duration: 0.95* idea.speed
        }
        PropertyAnimation
        {
            target: root
            property: "opacity"
            to: 0.1;
            duration: 0.95* idea.speed
        }
    }
    ParallelAnimation
    {
        id: toPreAnimation
        PropertyAnimation
        {
            target: image
            property: "opacity"
            to: 0.2;
            duration: 0.95* idea.speed
        }
        PropertyAnimation
        {
            target: root
            property: "opacity"
            to: 0.8;
            duration: 0.95* idea.speed
        }
    }
}
