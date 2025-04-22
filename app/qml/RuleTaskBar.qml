import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick.Controls.Universal

Item {
    function addRule() {
        var currentTab = tabBarLoader.item.tabModel.get(tabBarLoader.item.currentTabIndex).dirName;
        var exceptionsList = exceptions.text.split(", ");
        var extensions;
        var days;
        var isGreater;

        if (actionType.currentIndex === 0) {
            if (movingType.currentIndex === 0) {
                extensions = movingExt.text.split(", ");
                fileMover.addRuleToDir(currentTab, targetDirInput.text, extensions, exceptionsList);
            }
            else if (movingType.currentIndex === 1) {
                days = parseInt(movingDuration.text);
                isGreater = (movingGreater.currentIndex === 0);
                fileMover.addRuleToDir(currentTab, targetDirInput.text, days, isGreater, exceptionsList);
            }
            else if (movingType.currentIndex === 2) {
                var fileName = movingName.text;
                var caseSensitive = (movingRegister.currentIndex === 0);
                fileMover.addRuleToDir(currentTab, targetDirInput.text, fileName, caseSensitive, exceptionsList);
            }
            else {
                fileMover.addRuleToDir(currentTab, targetDirInput.text, exceptionsList);
            }
        }
        else {
            if (movingType.currentIndex === 0) {
                extensions = deletingExt.text.split(", ");
                fileMover.addRuleToDir(currentTab, extensions, exceptionsList);
            }
            else {
                days = parseInt(deletingDuration.text);
                isGreater = (deletingGreater.currentIndex === 0);
                fileMover.addRuleToDir(currentTab, days, isGreater, exceptionsList);
            }
        }

        clearFields();
        fileMover.rulesModel.loadRulesForDir(currentTab);
        listLoader.item.currentRuleIndex = -1;
    }

    function deleteRule() {
        var currentTab = tabBarLoader.item.tabModel.get(tabBarLoader.item.currentTabIndex).dirName;
        if (listLoader.item.currentRuleIndex !== -1) {
            fileMover.deleteRuleFromDir(currentTab, listLoader.item.currentRuleIndex);
            fileMover.rulesModel.loadRulesForDir(currentTab);
        }
        listLoader.item.currentRuleIndex = -1;
    }

    function clearFields()
    {
        targetDirInput.text = ""
        movingExt.text = ""
        movingDuration.text = ""
        movingName.text = ""
        exceptions.text = ""
        deletingExt.text = ""
        deletingDuration.text = ""
    }

    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: root.height / 360
        color: "black"
    }

    Rectangle {
        id: verticalLine

        anchors.left: exceptions.right
        width: root.width / 640
        height: parent.height
        color: "black"
    }

    Row {
        id: typeRow

        anchors {
            top: parent.top
            left: parent.left
        }

        width: root.width / 1.28
        height: root.height / 18

        ComboBox {
            id: actionType

            model: ["Переместить", "Удалить"]
            width: root.width / 8
            height: root.height / 18
            font {
                family: mainFont
                pixelSize: root.height / 58
            }

            onAccepted: {
                clearFields()
            }
        }

        ComboBox {
            id: movingType

            model: ["По расширению", "По дате", "По имени", "Всё"]
            width: root.width / 8
            height: root.height / 18
            font {
                family: mainFont
                pixelSize: root.height / 58
            }
            visible: actionType.currentIndex === 0

            onAccepted: {
                clearFields()
            }
        }

        ComboBox {
            id: deletingType

            model: ["По расширению", "По дате"]
            width: root.width / 8
            height: root.height / 18
            font {
                family: mainFont
                pixelSize: root.height / 58
            }
            visible: actionType.currentIndex === 1

            onAccepted: {
                clearFields()
            }
        }
    }

    TextField {
        id: exceptions

        anchors {
            top: typeRow.bottom
            left: parent.left
        }

        width: root.width / 1.28
        height: root.height / 18
        placeholderText: "Исключения"
        font {
            family: mainFont
            pixelSize: root.height / 50
        }
        readOnly: false
    }

    Item {
        id: movingRule

        anchors {
            top: exceptions.bottom
            left: parent.left
            right: verticalLine.right
        }

        visible: actionType.currentIndex === 0

        TextField {
            id: targetDirInput

            anchors {
                top: parent.top
                right: dirInputButton.left
                left: parent.left
            }

            height: root.height / 18
            placeholderText: "Выберите папку назначения"
            font {
                family: mainFont
                pixelSize: root.height / 50
            }
            readOnly: false
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

        Column {
            anchors {
                top: dirInputButton.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }

            TextField {
                id: movingExt

                width: root.width / 1.28
                height: root.height / 18
                placeholderText: "Расширения через запятую: .png, .mp3..."
                font {
                    family: mainFont
                    pixelSize: root.height / 50
                }
                readOnly: false
                visible: movingType.currentIndex === 0
            }

            TextField {
                id: movingDuration

                width: root.width / 1.28
                height: root.height / 18
                placeholderText: "Количество дней"
                font {
                    family: mainFont
                    pixelSize: root.height / 50
                }
                readOnly: false
                visible: movingType.currentIndex === 1
            }

            TextField {
                id: movingName

                width: root.width / 1.28
                height: root.height / 18
                placeholderText: "Имя файла(Поддержка regex)"
                font {
                    family: mainFont
                    pixelSize: root.height / 50
                }
                readOnly: false
                visible: movingType.currentIndex === 2
            }

            Row {
                anchors {
                    left: parent.left
                    leftMargin: root.width / 72
                }

                width: root.width / 2.4
                height: root.height / 18
                spacing: root.width / 72
                visible: movingType.currentIndex === 1

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Больше длительности?"
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }

                ComboBox {
                    id: movingGreater

                    anchors.verticalCenter: parent.verticalCenter
                    model: ["Да", "Нет"]
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }
            }

            Row {
                anchors {
                    left: parent.left
                    leftMargin: root.width / 72
                }

                width: root.width / 2.4
                height: root.height / 18
                spacing: root.width / 72
                visible: movingType.currentIndex === 2

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Учитывать регистр?"
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }

                ComboBox {
                    id: movingRegister

                    anchors.verticalCenter: parent.verticalCenter
                    model: ["Да", "Нет"]
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }
            }
        }
    }

    Item {
        id: deletingRule

        anchors {
            top: exceptions.bottom
            left: parent.left
            right: verticalLine.right
        }

        visible: actionType.currentIndex === 1

        Column {
            anchors {
                top: parent.bottom
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }

            TextField {
                id: deletingExt

                width: root.width / 1.28
                height: root.height / 18
                placeholderText: "Расширения через запятую: .png, .mp3..."
                font {
                    family: mainFont
                    pixelSize: root.height / 50
                }
                readOnly: false
                visible: deletingType.currentIndex === 0
            }

            TextField {
                id: deletingDuration

                width: root.width / 1.28
                height: root.height / 18
                placeholderText: "Количество дней"
                font {
                    family: mainFont
                    pixelSize: root.height / 50
                }
                readOnly: false
                visible: deletingType.currentIndex === 1
            }

            Row {
                anchors {
                    left: parent.left
                    leftMargin: root.width / 72
                }

                width: root.width / 2.4
                height: root.height / 18
                spacing: root.width / 72
                visible: deletingType.currentIndex === 1

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Больше длительности?"
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }

                ComboBox {
                    id: deletingGreater

                    anchors.verticalCenter: parent.verticalCenter
                    model: ["Да", "Нет"]
                    font {
                        family: mainFont
                        pixelSize: root.height / 58
                    }
                }
            }
        }
    }

    Column {
        id: ruleButtons

        anchors {
            left: exceptions.right
            right: parent.right
            verticalCenter: parent.verticalCenter
        }

        spacing: root.width / 60

        Button {
            id: addRuleButton

            anchors.horizontalCenter: parent.horizontalCenter
            width: root.width / 10.5
            height: root.height / 18

            Text {
                anchors.centerIn: parent
                text: "Добавить правило"
                color: "white"
                font {
                    family: mainFont
                    pixelSize: root.height / 58
                    bold: true
                }
            }

            onClicked: {
                addRule()
            }
        }

        Button {
            id: deleteRuleButton

            anchors.horizontalCenter: parent.horizontalCenter
            width: root.width / 10.5
            height: root.height / 18

            Text {
                anchors.centerIn: parent
                text: "Удалить правило"
                color: "white"
                font {
                    family: mainFont
                    pixelSize: root.height / 58
                    bold: true
                }
            }

            onClicked: {
                deleteRule()
            }
        }
    }

    FolderDialog {
        id: folderDialog

        title: "Выбор папки назначения"

        onAccepted: {
            targetDirInput.text = selectedFolder.toString().replace(/^file:\/\/\//, "")
        }
    }
}
