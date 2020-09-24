//
// Created by Ross Wardrup on 9/24/20.
//

#ifndef BUZZBOT_EXPORT_H
#define BUZZBOT_EXPORT_H

#include "QDialog"
#include "ui_export_data.h"

class ExportDialog : public QDialog, public Ui::exportDialog {
    Q_OBJECT
    Ui::exportDialog ui {};

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    std::string get_export_path();

};


#endif //BUZZBOT_EXPORT_H
