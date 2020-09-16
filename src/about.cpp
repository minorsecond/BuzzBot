//
// Created by Ross Wardrup on 9/16/20.
//

#include "about.h"

About::About(QWidget *parent) {
    /*
     * About app dialog
     */

    ui.setupUi(this);
    this->setFixedSize(230, 252);

    // Version text
    std::string version = "0.8.0";
    ui.versionLabel->setText(QString::fromStdString("Version " + version));

    QPixmap pixmap("../Resources/mini-icon.png");
    ui.miniIcon->setPixmap(pixmap);
    ui.miniIcon->repaint();
}