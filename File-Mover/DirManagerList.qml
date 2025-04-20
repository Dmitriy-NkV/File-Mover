import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Universal

Item {
    property int currentListViewIndex: list.currentIndex

    ListView {
        id: list
        anchors.fill: parent
        boundsBehavior: Flickable.StopAtBounds
        model: contact
        delegate: contactDelegate

        clip: true
        ScrollBar.vertical: ScrollBar {
            width: 10
            policy: ScrollBar.AlwaysOn
        }

        ScrollBar.horizontal: ScrollBar {
            width: 10
            policy: ScrollBar.AlwaysOn
        }
    }

    Component {
        id: contactDelegate
        Rectangle {
            id: contactDelegateBackground
            width: fileArea.width
            height: 40
            color: list.currentIndex == index ? "#e9ecef" : index % 2 ? secondaryColor : "#ced4da"

            Row {
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    Text {
                        text: index + 1
                        anchors.centerIn: parent
                    }
                    color: list.currentIndex == index ? "#e9ecef" : "#6c757d"
                }

                Column {
                    Text {
                        text: '<b>Name:</b> ' + dirName
                    }
                    Text {
                        text: '<b>Number of rules:</b> ' + numberOfRules
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    list.currentIndex = index
                }

                onDoubleClicked: {
                    findIndex(dirName, tabModel) === -1 ? tabModel.append({ dirName: dirName }) : tabBar.currentIndex = findIndex(dirName, tabModel)
                    tabBar.currentIndex = findIndex(dirName, tabModel)
                }
            }
        }
    }
}
