//
// Created by Ross Wardrup on 9/16/20.
//

#include "about.h"
#include "utilities.h"
#include <QDir>

About::About() {
    /*
     * About app dialog
     */

    ui.setupUi(this);
    this->setFixedSize(237, 272);

    // Version text
    std::string version = "2.2.1";
    ui.versionLabel->setText(QString::fromStdString("Version " + version));

    ui.copyrightLabel->setText("Ross Wardrup, 2021");

    // Make Qt URL clickable
    ui.acknowledgementsLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui.acknowledgementsLabel->setOpenExternalLinks(true);

    const std::string home_path = utilities::get_home_path();
    const std::string icon_path = home_path + "/.local/share/com.rwardrup.buzzbot/mini-icon.png";

    // Set icon
    QPixmap pixmap(QString::fromStdString(icon_path));
    ui.miniIcon->setPixmap(pixmap);
    ui.miniIcon->repaint();
}
