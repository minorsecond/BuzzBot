//
// Created by Ross Wardrup on 9/16/20.
//

#include "about.h"
#include <QDir>
#include <CoreFoundation/CFBundle.h>
#include "iostream"

About::About(QWidget *parent) {
    /*
     * About app dialog
     */

    ui.setupUi(this);
    this->setFixedSize(237, 272);

    // Version text
    std::string version = "0.8.0";
    ui.versionLabel->setText(QString::fromStdString("Version " + version));

    CFURLRef app_url_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef mac_path = CFURLCopyFileSystemPath(app_url_ref, kCFURLPOSIXPathStyle);
    QString icon_path_qstring = CFStringGetCStringPtr(mac_path, CFStringGetSystemEncoding());
    std::string icon_path = icon_path_qstring.toStdString() + "/Contents/Resources/icon.icns";
    CFRelease(app_url_ref);
    CFRelease(mac_path);
    std::cout << "Icon path" << icon_path << std::endl;
    QPixmap pixmap(QString::fromStdString(icon_path));
    ui.miniIcon->setPixmap(pixmap);
    ui.miniIcon->repaint();
}