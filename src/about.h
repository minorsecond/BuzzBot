//
// Created by Ross Wardrup on 9/16/20.
//

#ifndef BEERTABS_ABOUT_H
#define BEERTABS_ABOUT_H

#include "../ui/ui_about.h"


class About : public QDialog, public Ui::aboutDialog {
    /*
     * About dialog
     */

    Q_OBJECT
    Ui::aboutDialog ui{};
public:
    explicit About();
};

#endif //BEERTABS_ABOUT_H
