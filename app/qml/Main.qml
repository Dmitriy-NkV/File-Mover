import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal
import TrayIcon

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 720
    title: "File-Mover"

    Component.onCompleted: {
        ApplicationWindow.style = Universal
    }

    function findIndex(searchText, modelName) {
        for (var i = 0; i < modelName.count; i++) {
            if (modelName.get(i).dirName === searchText) {
                return i;
            }
        }
        return -1;
    }

    TrayIcon {
        id: trayIcon

        onActivated: {
            root.show()
            root.raise()
            root.requestActivate()
        }
    }

    onClosing: function(close) {
        if (Qt.platform.os === "windows" || Qt.platform.os === "linux") {
            close.accepted = false
            trayIcon.minimizeToTray()
        }
    }

    property string mainFont: "Onest"
    property string mainColor: "#DEE2E6"
    property string secondaryColor: "#adb5bd"
    property string selectColor: "#f8f9fa"

    Rectangle {
        id: sideMenu

        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: parent.width / 12.8
        color: mainColor

        Loader {
            id: sideMenuButtonsLoader

            source: "SideMenuButtons.qml"
            anchors.fill: parent
        }

        Rectangle {
            anchors.right: parent.right
            width: root.width / 320
            height: parent.height
            color: "black"
        }
    }

    Rectangle {
        id: header

        anchors {
            top: parent.top
            left: sideMenu.right
            right: parent.right
        }

        height: parent.height / 18
        color: secondaryColor

        Loader {
            id: tabBarLoader

            source: "TabBar.qml"
            anchors.fill: parent
        }
    }

    Loader {
        id: mainPart

        source: "FileManager.qml"

        anchors {
            top: header.bottom
            left: sideMenu.right
            right: parent.right
            bottom: parent.bottom
        }
    }
}
