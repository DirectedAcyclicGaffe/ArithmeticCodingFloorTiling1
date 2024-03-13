import QtQuick 2.12

Rectangle
{
    id: root
    width: parent.width - x;
    color: "black"
    opacity: 0.0

    NumberAnimation
    {
        running: true
        target: root
        property: "opacity"
        to: 0.5;
        duration: 0.8 * idea.speed
    }
}

