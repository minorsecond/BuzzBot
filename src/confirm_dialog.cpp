//
// Created by Ross Wardrup on 9/29/20.
//

#include "confirm_dialog.h"

ConfirmDialog::ConfirmDialog(const ConfirmStatus status) {
    /*
     * Delete/edit confirmation dialog.
     * @param parent: Parent QtWidget.
     * @param action: String denoting either edit or delete. This changes the display text.
     */

    ui.setupUi(this);

    if (status == ConfirmStatus::Delete) {
        ui.actionConfirmationLabel->setText("You are attempting to delete a row. Click OK to confirm.");
    } else if (status == ConfirmStatus::Update) {
        ui.actionConfirmationLabel->setText("You are attempting to edit a row. Click OK to confirm.");
    } else if (status == ConfirmStatus::ClearData) {
        ui.actionConfirmationLabel->setText("You are attempting to clear the database. Click OK to confirm.");
    } else if (status == ConfirmStatus::MovingDb) {
        ui.actionConfirmationLabel->setText(
                "After moving the DB, the app will close. You will have to reopoen it after saving preferences.");
    } else if (status == ConfirmStatus::MovedDb) {
        ui.actionConfirmationLabel->setText("Closing app. Restart to load data from new location.");
    } else if (status == ConfirmStatus::NoDbPathChange) {
        ui.actionConfirmationLabel->setText("Database path unchanged. It is not being moved.");
    } else if (status == ConfirmStatus::DestFileExists) {
        ui.actionConfirmationLabel->setText("Destination file already exists. BuzzBot will load it upon next launch. \n"
                                            "Do you want to delete the current file, keeping the destination file?\n"
                                            "BuzzBot will close after your response.");
    } else if (status == ConfirmStatus::ErrorMovingDbFile) {
        ui.actionConfirmationLabel->setText("Error copying file. Restore from backup? Cancelling will exit the app.");
    }
}
