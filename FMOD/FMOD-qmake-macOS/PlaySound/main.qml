import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.13
import QtQuick.Controls 2.13
import QtQuick.Dialogs 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Play Sound")

    ColumnLayout{
        spacing: 2

        RowLayout {
            TextField {
                id: filePath
                placeholderText: qsTr("Enter name")
            }

            FileDialog {
                id: fileDialog
                title: "Please choose a file"
                folder: shortcuts.home
                onAccepted: {
                    console.log("You chose: " + fileDialog.fileUrls)
                    filePath.text = fileDialog.fileUrl
                    player.filePath = fileDialog.fileUrl
                }
                onRejected: {
                    console.log("Canceled")
                }

                nameFilters: [ "Sound files (*.wav *.mp3)", "All files (*)" ]
            }

            Button {
                text: "Open"

                onClicked: {
                    fileDialog.open()
                }
            }

        }

        RowLayout {
            spacing: 2

            Button {
                signal playClicked()

                objectName: "btnPlay"
                text: "Play"

                onClicked: playClicked()
            }

            Button {
                signal resumeClicked()

                objectName: "btnResume"
                text: "Resume"

                onClicked: resumeClicked()
            }

            Button {
                signal pauseClicked()

                objectName: "btnPause"
                text: "Pause"

                onClicked: pauseClicked()
            }
        }
    }

}
