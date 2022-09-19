//
// Created by Ross Wardrup on 9/16/20.
//

#include "about.h"
#include <QDir>
#ifdef __APPLE__
    #include <CoreFoundation/CFBundle.h>
#elif __linux
    #include "utilities.h"
#endif

About::About() {
    /*
     * About app dialog
     */

    ui.setupUi(this);
    this->setFixedSize(237, 272);

    // Version text
    const std::string version = "2.2.1";
    ui.versionLabel->setText(QString::fromStdString("Version " + version));

    ui.copyrightLabel->setText("Ross Wardrup, 2021");

    // Make Qt URL clickable
    ui.acknowledgementsLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui.acknowledgementsLabel->setOpenExternalLinks(true);

#ifdef __linux__
    const std::string home_path = utilities::get_home_path();
    const std::string icon_path = home_path + "/.local/share/com.rwardrup.buzzbot/mini-icon.png";
#elif __APPLE__
    const CFURLRef app_url_ref = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    const CFStringRef mac_path = CFURLCopyFileSystemPath(app_url_ref, kCFURLPOSIXPathStyle);
    const QString icon_path_qstring = CFStringGetCStringPtr(mac_path, CFStringGetSystemEncoding());

    // Set path to icon
    const std::string icon_path = icon_path_qstring.toStdString() + "/Contents/Resources/mini-icon.png";
    CFRelease(app_url_ref);
    CFRelease(mac_path);
#endif
    // Set icon
    QPixmap pixmap(QString::fromStdString(icon_path));
    ui.miniIcon->setPixmap(pixmap);
    ui.miniIcon->repaint();
}
