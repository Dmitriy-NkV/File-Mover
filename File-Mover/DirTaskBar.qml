import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Universal

Item {
    function deleteDir() {
        if (listLoader.item.currentDirIndex !== -1)
        {
            var currentDir = fileMover.dirs[listLoader.item.currentDirIndex];
            var tabIndex = findIndex(currentDir, tabBarLoader.item.tabModel);
            if (tabIndex !== -1) {
                tabBarLoader.item.tabModel.remove(tabIndex);
            }
            fileMover.deleteDir(currentDir);
        }
        listLoader.item.currentDirIndex = -1;
    }

    Button {
        id: dirInputButton

        anchors {
            top: parent.top
            right: parent.right
        }

        width: root.width / 12.8
        height: root.height / 18

        Text {
            anchors.centerIn: parent
            text: "Обзор папок"
            color: "white"
            font {
                family: mainFont
                pixelSize: root.height / 58
                bold: true
            }
        }

        onClicked: {
            folderDialog.open()
        }
    }

    Row
    {
        anchors {
            top: dirInputButton.bottom
            bottom: parent.bottom
            right: parent.right
            topMargin: root.height / 40
            rightMargin: root.width / 32
        }

        width: root.width / 5.12
        spacing: root.width / 64

        Button {
            id: addDirButton

            width: root.width / 10.5
            height: root.height / 18

            Text {
                anchors.centerIn: parent
                text: "Добавить папку"
                color: "white"
                font {
                    family: mainFont
                    pixelSize: root.height / 58
                    bold: true
                }
            }

            onClicked: {
                fileMover.addDir(dirInput.text)
                dirInput.text = ""
                listLoader.item.currentDirIndex = -1;
            }
        }

        Button {
            id: deleteDirButton

            width: root.width / 10.5
            height: root.height / 18

            Text {
                anchors.centerIn: parent
                text: "Удалить папку"
                color: "white"
                font {
                    family: mainFont
                    pixelSize: root.height / 58
                    bold: true
                }
            }

            onClicked: {
                deleteDir()
            }
        }
    }

    TextField {
        id: dirInput

        anchors {
            top: parent.top
            right: dirInputButton.left
            left: parent.left
        }

        height: root.height / 18
        placeholderText: "Выберите папку"
        font {
            family: mainFont
            pixelSize: root.height / 50
        }
        readOnly: false
    }

    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: root.height / 360
        color: "black"
    }

    FolderDialog {
        id: folderDialog

        title: "Выбор папки"

        onAccepted: {
            dirInput.text = selectedFolder.toString().replace(/^file:\/\/\//, "")
        }
    }
}
