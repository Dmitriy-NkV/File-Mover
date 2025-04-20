import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Universal

ApplicationWindow {
    visible: true
    width: 1280
    height: 720
    title: "File-Mover"

    property string mainColor: "#DEE2E6"
    property string secondaryColor: "#adb5bd"
    property string selectColor: "#f8f9fa"

    Component.onCompleted: {
        ApplicationWindow.style = Universal
    }


    Rectangle {
        id: header
        anchors.top: parent.top
        anchors.left: sideMenu.right
        anchors.right: parent.right
        height: 40
        color: secondaryColor

        TabBar {
            id: tabBar
            anchors.fill: parent
            background: Rectangle {
                color: "transparent"
            }

            ListModel {
                id: tabModel
                ListElement { dirName: "Главная" }
                ListElement { dirName: "Поиск" }
                ListElement { dirName: "Настройки" }
            }
            Repeater {
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                model: tabModel
                delegate: TabButton {
                    text: dirName
                    background: Rectangle {
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                        implicitWidth: 100
                        color: secondaryColor
                    }
                    Rectangle {
                        anchors.right: parent.right
                        width: 2
                        height: parent.height
                        color: "black"
                        visible: index !== tabModel.count - 1
                    }
                    Rectangle {
                        anchors.top: parent.top
                        width: parent.width
                        height: 2
                        color: "black"
                    }
                    Rectangle {
                        anchors.bottom: parent.bottom
                        width: parent.width
                        height: 2
                        color: "black"
                        visible: tabBar.currentIndex !== index
                    }

                    Button {
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        width: 20
                        height: 20

                        background: Rectangle {
                            anchors.fill: parent
                            color: mainColor
                            visible: parent.hovered ? true : false
                        }

                        Text {
                            text: "✕"
                            anchors.centerIn: parent
                        }

                        onClicked: {
                            tabModel.remove(index)
                        }
                        visible: index !== 0
                    }
                }
            }
        }

        Rectangle {
            anchors.bottom: parent.bottom
            anchors.left: tabBar.right
            anchors.right: parent.right
            height: 2
            color: "black"
        }
    }

    Rectangle {
        id: sideMenu
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        width: 100
        color: mainColor

        Column {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 20
            spacing: 30

            Button {
                background: Image {
                    sourceSize.width: 40
                    source: "images/play-button.png"
                }
            }

            Button {
                background: Image {
                    sourceSize.width: 40
                    source: "images/file-export.png"
                }
            }

            Button {
                background: Image {
                    sourceSize.width: 40
                    source: "images/file-import.png"
                }
            }

            Button {
                background: Image {
                    sourceSize.width: 40
                    source: "images/file.png"
                }
            }

            Button {
                background: Image {
                    sourceSize.width: 40
                    source: "images/file-minus.png"
                }
            }
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 20
            background: Image {
                sourceSize.width: 40
                source: "images/setting.png"
            }
        }

        Rectangle {
            anchors.right: parent.right
            width: 4
            height: parent.height
            color: "black"
        }
    }

    Loader {
        id: mainPart
        anchors.top: header.bottom
        anchors.left: sideMenu.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: tabBar.currentIndex === 0 ? "DirManager.qml" : "RuleManager.qml"
    }


    Component {
        id: tabButton
        TabButton { }
    }
}
