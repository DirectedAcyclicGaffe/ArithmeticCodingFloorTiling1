import QtQuick 2.12
import QtQuick.Controls 2.15

Item
{
    width: speedText.width + speedslider.width;
    anchors.horizontalCenter: parent.horizontalCenter
    height: 30
    Text
    {
        id: speedText;
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        text: "Speed"
        font.family: "verdana"
        font.pointSize: 12
        font.bold: true;
        color: "silver"
    }
    Slider
    {
        id: speedslider
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        from: -1
        to: 3
        value: -1.0 * Math.log(idea.speed / 1000.0)

        onMoved:
        {
            idea.setSpeed(1000 * Math.exp(-1.0*value));
        }
    }
}
