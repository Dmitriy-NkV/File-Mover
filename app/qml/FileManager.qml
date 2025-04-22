import QtQuick

Item {
    id: fileManager

    anchors.fill: parent

    Rectangle {
        id: fileArea

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        color: selectColor

        Loader {
            id: listLoader

            source: tabBarLoader.item.currentTabIndex === 0 ? "DirList.qml" : "RuleList.qml"
            anchors.fill: parent
        }

        height: tabBarLoader.item ? tabBarLoader.item.currentTabIndex === 0 ? root.height / 1.31 : root.height / 1.5 : root.height / 1.5
    }

    Rectangle {
        id: taskBar

        anchors {
            top: fileArea.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        color: secondaryColor

        enabled: fileMover ? !fileMover.isWatching : true

        Loader {
            id: taskBarLoader

            source: tabBarLoader.item.currentIndex === 0 ? "DirTaskBar.qml" : "RuleTaskBar.qml"
            anchors.fill: parent
        }
    }
}
