import QtQuick 2.12

Rectangle
{
    height: 500;
    width: 600;
    color: "black"
    radius: 10

    Text
    {
        id: questionText
        anchors.centerIn: parent
        text: "?"
        font.pointSize: 90
        font.bold: true;
        opacity: 0.6
        color: "white"

        SequentialAnimation
        {
            running: true
            loops: Animation.Infinite

            NumberAnimation
            {
                target: questionText
                property: "opacity"
                to: 0.0
                duration: 1600
            }
            NumberAnimation
            {
                target: questionText
                property: "opacity"
                to: 0.6
                duration: 1600
            }
        }
    }
}
