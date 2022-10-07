//
// Created by Ross Wardrup on 9/29/20.
//

#ifndef BUZZBOT_CONFIRM_DIALOG_H
#define BUZZBOT_CONFIRM_DIALOG_H

#include <QDialog>
#include "../ui/ui_delete_confirm.h"

enum class ConfirmStatus{
    Delete,
    Update,
    ClearData,
    MovingDb,
    MovedDb,
    NoDbPathChange,
    DestFileExists,
    ErrorMovingDbFile
};

class ConfirmDialog : public QDialog, public Ui::confirmationDialog {
    /*
     * Delete/edit confirmation dialog
     */

    Q_OBJECT
    Ui::confirmationDialog ui {};

public:
    explicit ConfirmDialog(const ConfirmStatus status);
};

#endif //BUZZBOT_CONFIRM_DIALOG_H
