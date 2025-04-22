import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Universal

Item {
    function clearAllTabs() {
        while (tabBarLoader.item.tabModel.count > 1) {
            tabBarLoader.item.tabModel.remove(1);
        }
    }

    Column {
        id: sideMenuButtons

        anchors {
            horizontalCenter: parent.horizontalCenter
            top: parent.top
            topMargin: root.height / 36
        }

        spacing: root.height / 24

        Button {
            id: startSortButton

            background: Image {
                source: fileMover ? fileMover.isWatching ? "../images/pause-button.png" : "../images/play-button.png" :  "../images/play-button.png"

                sourceSize {
                    width: root.width / 32
                    height: root.height / 18
                }
            }

            onClicked: {
                fileMover.isWatching ? fileMover.stopWatching() : fileMover.startWatching()
            }
        }

        Button {
            id: exportConfigButton

            enabled: fileMover ? !fileMover.isWatching : true

            background: Image {
                source: "../images/file-export.png"

                sourceSize {
                    width: root.width / 32
                    height: root.height / 18
                }
            }

            onClicked: {
                exportConfigDialog.open()
            }
        }

        Button {
            id: importConfigButton

            enabled: fileMover ? !fileMover.isWatching : true

            background: Image {
                source: "../images/file-import.png"

                sourceSize {
                    width: root.width / 32
                    height: root.height / 18
                }
            }

            onClicked: {
                importConfigDialog.open()
            }
        }

        Button {
            id: addConfigButton

            enabled: fileMover ? !fileMover.isWatching : true

            background: Image {
                source: "../images/file.png"

                sourceSize {
                    width: root.width / 32
                    height: root.height / 18
                }
            }

            onClicked: {
                addConfigDialog.open()
            }
        }
    }

    Button {
        id: settingsButton

        enabled: fileMover ? !fileMover.isWatching : true

        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: root.height / 36
        }

        background: Image {
            source: "../images/setting.png"

            sourceSize {
                width: root.width / 32
                height: root.height / 18
            }
        }
    }

    FileDialog {
        id: exportConfigDialog

        title: "Загрузка конфигурации"
        nameFilters: { "*.JSON" }

        onAccepted: {
            clearAllTabs()
            fileMover.importConfig(selectedFile.toString().replace(/^file:\/\/\//, ""))
            fileMover.dirsChanged()
        }
    }

    FileDialog {
        id: importConfigDialog

        title: "Сохранение конфигурации"
        fileMode: FileDialog.SaveFile
        nameFilters: { "*.JSON" }

        onAccepted: {
            fileMover.saveConfig(selectedFile.toString().replace(/^file:\/\/\//, ""))
        }
    }

    FileDialog {
        id: addConfigDialog

        title: "Сохранение конфигурации"

        fileMode: FileDialog.SaveFile
        nameFilters: { "*.JSON" }

        onAccepted: {
            fileMover.saveConfig(selectedFile.toString().replace(/^file:\/\/\//, ""))
            clearAllTabs()
            fileMover.clear()
            fileMover.dirsChanged()
        }

        onRejected: {
            clearAllTabs()
            fileMover.clear()
            fileMover.dirsChanged()
        }
    }
}
