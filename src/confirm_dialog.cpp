//
// Created by Ross Wardrup on 9/29/20.
//

#include "confirm_dialog.h"

ConfirmDialog::ConfirmDialog(const std::string& action) {
    /*
     * Delete/edit confirmation dialog.
     * @param parent: Parent QtWidget.
     * @param action: String denoting either edit or delete. This changes the display text.
     */

    ui.setupUi(this);

    if (action == "Delete") {
        ui.actionConfirmationLabel->setText("You are attempting to delete a row. Click OK to confirm.");
    } else if (action == "Update") {
        ui.actionConfirmationLabel->setText("You are attempting to edit a row. Click OK to confirm.");
    } else if (action == "Clear Data") {
        ui.actionConfirmationLabel->setText("You are attempting to clear the database. Click OK to confirm.");
    } else if (action == "Moving DB") {
        ui.actionConfirmationLabel->setText(
                "After moving the DB, the app will close. You will have to reopoen it after saving preferences.");
    } else if (action == "Moved DB") {
        ui.actionConfirmationLabel->setText("Closing app. Restart to load data from new location.");
    } else if (action == "NoDbPathChange") {
        ui.actionConfirmationLabel->setText("Database path unchanged. It is not being moved.");
    } else if (action == "DestFileExists") {
        ui.actionConfirmationLabel->setText("Destination file already exists. BuzzBot will load it upon next launch. \n"
                                            "Do you want to delete the current file, keeping the destination file?\n"
                                            "BuzzBot will close after your response.");
    }
}
