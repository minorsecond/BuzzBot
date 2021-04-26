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
    }
}
