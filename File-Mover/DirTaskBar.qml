import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Dialogs
import QtQuick.Layouts
import QtQuick.Controls.Universal

Item {
    Button {
        id: dirInputButton
        width: 100
        height: 40
        anchors.top: parent.top
        anchors.right: parent.right
        Text {
            anchors.centerIn: parent
            text: "Обзор папок"
            color: "white"
        }

        onClicked: folderDialog.open()
    }

    Row
    {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: dirInputButton.bottom
        anchors.topMargin: 10
        spacing: 20
        width: 250

        Button {
            id: addDirButton
            width: 100
            height: 40

            Text {
                anchors.centerIn: parent
                text: "Добавить папку"
                color: "white"
            }

            onClicked: {
                containsItem(dirInput.text, contact) ? true : contact.append({dirName: dirInput.text, numberOfRules: 0})
            }
        }

        Button {
            id: deleteDirButton
            width: 100
            height: 40

            Text {
                anchors.centerIn: parent
                text: "Удалить папку"
                color: "white"
            }

            onClicked: {
                var index = DirManagerList.currentListViewIndex
                var tabIndex = findIndex(contact.get(index).dirName, tabModel)
                tabIndex !== -1 ? tabModel.remove(tabIndex) : false
                contact.remove(index)
            }
        }
    }

    TextField {
        id: dirInput
        anchors.top: parent.top
        anchors.right: dirInputButton.left
        anchors.left: parent.left
        placeholderText: "Выберите папку..."
        readOnly: false
        height: 40
    }

    Rectangle {
        anchors.top: parent.top
        height: 2
        width: parent.width
        color: "black"
    }

    FolderDialog {
        id: folderDialog
        onAccepted: {
            dirInput.text = selectedFolder.toString().replace(/^file:\/\/\//, "")
        }
    }
}
