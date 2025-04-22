import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Universal

Item {
    property alias currentRuleIndex: ruleList.currentIndex

    ListView {
        id: ruleList

        model: fileMover ? fileMover.rulesModel : []
        anchors.fill: parent
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
                height: root.height / 9
                color: ruleList.currentIndex === index ? "#e9ecef" : index % 2 ? secondaryColor : "#ced4da"

                Row {
                    anchors.fill: parent
                    spacing: root.width / 128

                    Rectangle {
                        width: root.width / 32
                        height: root.height / 9
                        color: ruleList.currentIndex === index ? "#e9ecef" : "#6c757d"

                        Text {
                            anchors.centerIn: parent
                            text: index + 1
                            font {
                                family: mainFont
                                pixelSize: root.height / 44
                                bold: true
                            }
                        }
                    }

                    Loader {
                        sourceComponent: {
                            switch(model.type) {
                                case "MovingByExt": return movingExtDelegate
                                case "MovingByDate": return movingDateDelegate
                                case "MovingByName": return movingNameDelegate
                                case "MovingAll": return movingAllDelegate
                                case "DeletingByExt": return deletingExtDelegate
                                case "DeletingByDate": return deletingDateDelegate
                                default: return defaultDelegate
                            }
                        }
                    }
                }

                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        ruleList.currentIndex = index
                    }
                }

                Component {
                    id: movingExtDelegate

                    Column {
                        Text {
                            text: "Переместить файлы"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "С расширениями: " + model.extensions.join(", ")
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "В папку: " + model.targetDir
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: movingDateDelegate

                    Column {
                        Text {
                            text: "Переместить файлы"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: model.isGreaterThanDuration ? "Старше " + model.duration + " дней" : "Новее " + model.duration + " дней"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "В папку: " + model.targetDir
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: movingNameDelegate

                    Column {
                        Text {
                            text: "Переместить файлы"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "C именем: " + model.name
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: model.isCheckRegister ? "С учётом регистра" : "Без учёта регистра"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "В папку: " + model.targetDir
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: movingAllDelegate

                    Column {
                        Text {
                            text: "Переместить все файлы"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "В папку: " + model.targetDir
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: deletingExtDelegate

                    Column {
                        Text {
                            text: "Удалить"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "По расширениям: " + model.extensions.join(", ")
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: deletingDateDelegate

                    Column {
                        Text {
                            text: "Удалить"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: model.isGreaterThan ? "Файлы старше " + model.duration + " дней" : "Файлы новее " + model.duration + " дней"
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                        Text {
                            text: "Исключения: " + model.exceptions
                            font {
                                family: mainFont
                                pixelSize: root.height / 50
                            }
                        }
                    }
                }

                Component {
                    id: defaultDelegate

                    Text {
                        text: "Неизвестный тип правила: " + model.type
                        font {
                            family: mainFont
                            pixelSize: root.height / 50
                        }
                    }
                }
            }
        }
    }
}
