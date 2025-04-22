import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal

TabBar {
    id: tabBar

    property alias currentTabIndex: tabBar.currentIndex
    property alias tabModel: tabModel

    anchors.fill: parent
    currentIndex: 0

    background: Rectangle {
        color: "transparent"
    }

    ListModel {
        id: tabModel

        ListElement {
            dirName: "Папки"
        }
    }

    Repeater {
        id: tabList

        anchors.fill: parent


        model: tabModel

        delegate: TabButton {
            anchors {
                top: parent.top
                bottom: parent.bottom
            }

            onClicked: {
                currentIndex !== 0 ? fileMover.rulesModel.loadRulesForDir(dirName) : false
            }

            background: Rectangle {
                anchors {
                    top: parent.top
                    bottom: parent.bottom
                }

                color: secondaryColor
            }

            Text {
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: closeTabButton.left
                    left: parent.left
                    leftMargin: root.width / 128
                    rightMargin: root.width / 128
                }

                text: dirName
                horizontalAlignment: Text.AlignHCenter
                font {
                    bold: true
                    family: mainFont
                    pixelSize: root.height / 55
                }
                elide: Text.ElideLeft
            }

            Rectangle {
                anchors.right: parent.right
                width: root.width / 640
                height: parent.height
                color: "black"
                visible: index !== tabModel.count - 1
            }

            Rectangle {
                anchors.bottom: parent.bottom
                width: parent.width
                height: root.height / 360
                color: "black"
                visible: tabBar.currentIndex !== index
            }

            Button {
                id: closeTabButton
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: root.width / 120
                }

                width: root.width / 64
                height: root.height / 36
                visible: index !== 0

                background: Rectangle {
                    anchors.fill: parent
                    color: mainColor
                    visible: parent.hovered ? true : false
                }

                Text {
                    anchors.centerIn: parent
                    font {
                        bold: true
                        family: mainFont
                        pixelSize: root.height / 44
                    }
                    text: "✕"
                }

                onClicked: {
                    var oldIndex = index
                    tabBar.currentIndex = index - 1
                    currentIndex !== 0 ? fileMover.rulesModel.loadRulesForDir(tabModel.get(tabBar.currentIndex).dirName) : false
                    tabModel.remove(oldIndex)
                }
            }
        }
    }
}
