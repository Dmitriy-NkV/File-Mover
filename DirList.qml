import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Universal

Item {
    property alias currentDirIndex: dirList.currentIndex

    ListView {
        id: dirList

        anchors.fill: parent
        model: fileMover ? fileMover.dirs : []
        boundsBehavior: Flickable.StopAtBounds
        currentIndex: -1
        clip: true

        ScrollBar.vertical: ScrollBar {
            width: root.width / 128
            policy: ScrollBar.AlwaysOn
        }

        ScrollBar.horizontal: ScrollBar {
            width: root.height / 72
            policy: ScrollBar.AlwaysOn
        }

        delegate: Component {
            Rectangle {
                width: fileArea.width
                height: root.height / 18
                color: dirList.currentIndex == index ? "#e9ecef" : index % 2 ? secondaryColor : "#ced4da"

                Row {
                    spacing: root.width / 128

                    Rectangle {
                        width: root.width / 32
                        height: root.height / 18
                        color: dirList.currentIndex == index ? "#e9ecef" : "#6c757d"

                        Text {
                            anchors.centerIn: parent
                            text: index + 1
                            font {
                                bold: true
                                family: mainFont
                                pixelSize: root.height / 44
                            }
                        }
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: modelData
                        font {
                            family: mainFont
                            pixelSize: root.height / 50
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        dirList.currentIndex = index
                    }

                    onDoubleClicked: {
                        findIndex(modelData, tabBarLoader.item.tabModel) === -1 ? tabBarLoader.item.tabModel.append({ dirName: modelData }) : false
                        fileMover.rulesModel.loadRulesForDir(tabBarLoader.item.tabModel.get(findIndex(modelData, tabBarLoader.item.tabModel)).dirName)
                        tabBarLoader.item.currentTabIndex = findIndex(modelData, tabBarLoader.item.tabModel)
                    }
                }
            }
        }
    }
}
