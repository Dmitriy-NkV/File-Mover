import QtQuick 2.15

Item {
    id: ruleManager
    anchors.fill: parent
    Rectangle {
        id: fileArea
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 550
        color: selectColor

        // Loader {
        //     anchors.fill: parent
        //     source: "DirManagerList.qml"
        // }
    }

    Rectangle {
        id: taskBar
        anchors.top: fileArea.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: secondaryColor

        // Loader {
        //     anchors.fill: parent
        //     source: "DirManagerTaskBar.qml"
        // }
    }

    ListModel {
        id: contact
    }
}
