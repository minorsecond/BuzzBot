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
    QPixmap pixmap("../Resources/mini-icon.png");
    ui.miniIcon->setPixmap(pixmap);
}