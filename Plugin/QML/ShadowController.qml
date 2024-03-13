import QtQuick 2.12

Item
{
    id: root
    height: 560
    width: parent.width
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -1
    clip: true;

    function reset()
    {
        let i;
        for(i = 0; i < root.children.length; i++)
        {
            root.children[i].destroy();
        }
    }

    function addShadow(x, y, height)
    {
        let comp; let obj;
        comp = Qt.createComponent("ShadowRectangle.qml");
        obj = comp.createObject(root, {x: x, y: y, height: height})
    }
}
