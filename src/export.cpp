//
// Created by Ross Wardrup on 9/24/20.
//

#include "export.h"

ExportDialog::ExportDialog(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(445, 119);
}

std::string ExportDialog::get_export_path() {
    /*
     * Getter for the export CSV path.
     * @return export_path: Path where CSV should be saved.
     */

    std::string export_path = ui.exportPathInput->text().toStdString();
    return export_path;
}
