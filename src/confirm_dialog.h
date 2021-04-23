//
// Created by Ross Wardrup on 9/29/20.
//

#ifndef BUZZBOT_CONFIRM_DIALOG_H
#define BUZZBOT_CONFIRM_DIALOG_H

#include <QDialog>
#include "ui_delete_confirm.h"

class ConfirmDialog : public QDialog, public Ui::confirmationDialog {
    /*
     * Delete/edit confirmation dialog
     */

    Q_OBJECT
    Ui::confirmationDialog ui {};

public:
    explicit ConfirmDialog(const std::string& action);
};

#endif //BUZZBOT_CONFIRM_DIALOG_H
