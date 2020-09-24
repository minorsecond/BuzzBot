//
// Created by Ross Wardrup on 9/24/20.
//

#include "export.h"
#include <QFileDialog>
#include <QStandardPaths>

ExportDialog::ExportDialog(QWidget *parent) {
    ui.setupUi(this);
    this->setFixedSize(445, 119);

    connect(ui.exportPathBrowse, &QPushButton::clicked, this, &ExportDialog::open_browse_dialog);
}

std::string ExportDialog::get_export_path() {
    /*
     * Getter for the export CSV path.
     * @return export_path: Path where CSV should be saved.
     */

    std::string export_path = ui.exportPathInput->text().toStdString();
    return export_path;
}

void ExportDialog::open_browse_dialog() {
    /*
     * Allow user to browse for CSV save location.
     */

    QString filter = "CSV Files (*.csv)";
    QString desktop_path = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).at(0);
    QString preferred_path = desktop_path + "/buzzbot.csv";
    QString filepath_qstring = QFileDialog::getSaveFileName(this, "Save File", preferred_path, filter, &filter);

    if (filepath_qstring.isEmpty()) {
        if (ui.exportPathInput->text().isEmpty()) {
            ui.exportPathButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        } else {
            ui.exportPathButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        } return;
    } else {
        ui.exportPathButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        ui.exportPathInput->setText(filepath_qstring);
    }

}
