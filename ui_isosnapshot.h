/********************************************************************************
** Form generated from reading UI file 'isosnapshot.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISOSNAPSHOT_H
#define UI_ISOSNAPSHOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_isosnapshot
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *selectionPage;
    QGridLayout *gridLayout_2;
    QLabel *labelLocation;
    QLabel *labelIntro;
    QLabel *labelCurrentSpace;
    QLabel *labelDiskSpaceHelp;
    QFrame *line_4;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelUsedSpace;
    QLabel *labelFreeSpace;
    QLabel *labelIsoName;
    QPushButton *buttonSelectSnapshot;
    QLabel *labelSnapshotDir;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEditName;
    QWidget *settingsPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_1;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_3;
    QFrame *line_2;
    QLabel *label_3;
    QPushButton *buttonEditConfig;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_3;
    QLabel *labelExclude;
    QFrame *frame;
    QGridLayout *gridLayout;
    QCheckBox *excludeDownloads;
    QCheckBox *excludeDocuments;
    QCheckBox *excludeAll;
    QCheckBox *excludePictures;
    QCheckBox *excludeMusic;
    QCheckBox *excludeDesktop;
    QCheckBox *excludeVideos;
    QPushButton *buttonEditExclude;
    QFrame *line;
    QFrame *frame_3;
    QGridLayout *gridLayout_3;
    QRadioButton *radioRespin;
    QLabel *label;
    QRadioButton *radioPersonal;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QWidget *outputPage;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *outputBox;
    QLabel *outputLabel;
    QProgressBar *progressBar;
    QGridLayout *buttonBar;
    QSpacerItem *horizontalSpacer1;
    QPushButton *buttonCancel;
    QPushButton *buttonHelp;
    QSpacerItem *horizontalSpacer2;
    QPushButton *buttonAbout;
    QLabel *labelMX;
    QPushButton *buttonNext;
    QPushButton *buttonBack;

    void setupUi(QDialog *iso_snapshot)
    {
        if (iso_snapshot->objectName().isEmpty())
            iso_snapshot->setObjectName(QStringLiteral("iso_snapshot"));
        iso_snapshot->resize(804, 517);
        verticalLayout = new QVBoxLayout(iso_snapshot);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        stackedWidget = new QStackedWidget(iso_snapshot);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        selectionPage = new QWidget();
        selectionPage->setObjectName(QStringLiteral("selectionPage"));
        gridLayout_2 = new QGridLayout(selectionPage);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        labelLocation = new QLabel(selectionPage);
        labelLocation->setObjectName(QStringLiteral("labelLocation"));

        gridLayout_2->addWidget(labelLocation, 10, 0, 1, 1);

        labelIntro = new QLabel(selectionPage);
        labelIntro->setObjectName(QStringLiteral("labelIntro"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelIntro->sizePolicy().hasHeightForWidth());
        labelIntro->setSizePolicy(sizePolicy);
        labelIntro->setWordWrap(true);

        gridLayout_2->addWidget(labelIntro, 0, 0, 1, 6);

        labelCurrentSpace = new QLabel(selectionPage);
        labelCurrentSpace->setObjectName(QStringLiteral("labelCurrentSpace"));
        labelCurrentSpace->setWordWrap(true);

        gridLayout_2->addWidget(labelCurrentSpace, 1, 0, 1, 6);

        labelDiskSpaceHelp = new QLabel(selectionPage);
        labelDiskSpaceHelp->setObjectName(QStringLiteral("labelDiskSpaceHelp"));
        labelDiskSpaceHelp->setWordWrap(true);

        gridLayout_2->addWidget(labelDiskSpaceHelp, 5, 0, 1, 6);

        line_4 = new QFrame(selectionPage);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_4, 7, 0, 1, 6);

        frame_2 = new QFrame(selectionPage);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Plain);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelUsedSpace = new QLabel(frame_2);
        labelUsedSpace->setObjectName(QStringLiteral("labelUsedSpace"));
        sizePolicy.setHeightForWidth(labelUsedSpace->sizePolicy().hasHeightForWidth());
        labelUsedSpace->setSizePolicy(sizePolicy);
        labelUsedSpace->setAutoFillBackground(false);
        labelUsedSpace->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 205);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(0, 0, 0);"));
        labelUsedSpace->setFrameShape(QFrame::NoFrame);
        labelUsedSpace->setTextFormat(Qt::PlainText);
        labelUsedSpace->setWordWrap(true);

        verticalLayout_4->addWidget(labelUsedSpace);

        labelFreeSpace = new QLabel(frame_2);
        labelFreeSpace->setObjectName(QStringLiteral("labelFreeSpace"));
        labelFreeSpace->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 205);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(0, 0, 0);"));
        labelFreeSpace->setFrameShape(QFrame::NoFrame);
        labelFreeSpace->setTextFormat(Qt::PlainText);
        labelFreeSpace->setWordWrap(true);

        verticalLayout_4->addWidget(labelFreeSpace);


        gridLayout_2->addWidget(frame_2, 2, 0, 1, 6);

        labelIsoName = new QLabel(selectionPage);
        labelIsoName->setObjectName(QStringLiteral("labelIsoName"));

        gridLayout_2->addWidget(labelIsoName, 13, 0, 1, 1);

        buttonSelectSnapshot = new QPushButton(selectionPage);
        buttonSelectSnapshot->setObjectName(QStringLiteral("buttonSelectSnapshot"));

        gridLayout_2->addWidget(buttonSelectSnapshot, 11, 3, 1, 1);

        labelSnapshotDir = new QLabel(selectionPage);
        labelSnapshotDir->setObjectName(QStringLiteral("labelSnapshotDir"));
        labelSnapshotDir->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 205);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(0, 0, 0);"));
        labelSnapshotDir->setFrameShape(QFrame::Box);
        labelSnapshotDir->setWordWrap(true);

        gridLayout_2->addWidget(labelSnapshotDir, 11, 0, 1, 3);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 16, 0, 1, 6);

        lineEditName = new QLineEdit(selectionPage);
        lineEditName->setObjectName(QStringLiteral("lineEditName"));

        gridLayout_2->addWidget(lineEditName, 14, 0, 1, 3);

        stackedWidget->addWidget(selectionPage);
        settingsPage = new QWidget();
        settingsPage->setObjectName(QStringLiteral("settingsPage"));
        verticalLayout_3 = new QVBoxLayout(settingsPage);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_1 = new QLabel(settingsPage);
        label_1->setObjectName(QStringLiteral("label_1"));
        label_1->setWordWrap(true);

        verticalLayout_3->addWidget(label_1);

        label_2 = new QLabel(settingsPage);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 205);\n"
"border-color: rgb(0, 0, 0);\n"
"color: rgb(0, 0, 0);"));
        label_2->setFrameShape(QFrame::Box);
        label_2->setWordWrap(true);

        verticalLayout_3->addWidget(label_2);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        line_2 = new QFrame(settingsPage);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_3 = new QLabel(settingsPage);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_3->addWidget(label_3);

        buttonEditConfig = new QPushButton(settingsPage);
        buttonEditConfig->setObjectName(QStringLiteral("buttonEditConfig"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(buttonEditConfig->sizePolicy().hasHeightForWidth());
        buttonEditConfig->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(buttonEditConfig);

        verticalSpacer_4 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout_3->addItem(verticalSpacer_4);

        line_3 = new QFrame(settingsPage);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_3);

        labelExclude = new QLabel(settingsPage);
        labelExclude->setObjectName(QStringLiteral("labelExclude"));
        labelExclude->setWordWrap(true);

        verticalLayout_3->addWidget(labelExclude);

        frame = new QFrame(settingsPage);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(0);
        frame->setMidLineWidth(1);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        excludeDownloads = new QCheckBox(frame);
        excludeDownloads->setObjectName(QStringLiteral("excludeDownloads"));

        gridLayout->addWidget(excludeDownloads, 1, 1, 1, 1);

        excludeDocuments = new QCheckBox(frame);
        excludeDocuments->setObjectName(QStringLiteral("excludeDocuments"));

        gridLayout->addWidget(excludeDocuments, 1, 0, 1, 1);

        excludeAll = new QCheckBox(frame);
        excludeAll->setObjectName(QStringLiteral("excludeAll"));

        gridLayout->addWidget(excludeAll, 4, 0, 1, 1);

        excludePictures = new QCheckBox(frame);
        excludePictures->setObjectName(QStringLiteral("excludePictures"));

        gridLayout->addWidget(excludePictures, 2, 1, 1, 1);

        excludeMusic = new QCheckBox(frame);
        excludeMusic->setObjectName(QStringLiteral("excludeMusic"));

        gridLayout->addWidget(excludeMusic, 2, 0, 1, 1);

        excludeDesktop = new QCheckBox(frame);
        excludeDesktop->setObjectName(QStringLiteral("excludeDesktop"));

        gridLayout->addWidget(excludeDesktop, 1, 2, 1, 1);

        excludeVideos = new QCheckBox(frame);
        excludeVideos->setObjectName(QStringLiteral("excludeVideos"));

        gridLayout->addWidget(excludeVideos, 2, 2, 1, 1);


        verticalLayout_3->addWidget(frame);

        buttonEditExclude = new QPushButton(settingsPage);
        buttonEditExclude->setObjectName(QStringLiteral("buttonEditExclude"));
        sizePolicy1.setHeightForWidth(buttonEditExclude->sizePolicy().hasHeightForWidth());
        buttonEditExclude->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(buttonEditExclude);

        line = new QFrame(settingsPage);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        frame_3 = new QFrame(settingsPage);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Plain);
        frame_3->setLineWidth(0);
        gridLayout_3 = new QGridLayout(frame_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        radioRespin = new QRadioButton(frame_3);
        radioRespin->setObjectName(QStringLiteral("radioRespin"));

        gridLayout_3->addWidget(radioRespin, 2, 0, 1, 1);

        label = new QLabel(frame_3);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        radioPersonal = new QRadioButton(frame_3);
        radioPersonal->setObjectName(QStringLiteral("radioPersonal"));
        radioPersonal->setChecked(true);

        gridLayout_3->addWidget(radioPersonal, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 1, 1, 1, 1);


        verticalLayout_3->addWidget(frame_3);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        stackedWidget->addWidget(settingsPage);
        outputPage = new QWidget();
        outputPage->setObjectName(QStringLiteral("outputPage"));
        verticalLayout_2 = new QVBoxLayout(outputPage);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        outputBox = new QTextBrowser(outputPage);
        outputBox->setObjectName(QStringLiteral("outputBox"));

        verticalLayout_2->addWidget(outputBox);

        outputLabel = new QLabel(outputPage);
        outputLabel->setObjectName(QStringLiteral("outputLabel"));
        outputLabel->setWordWrap(true);

        verticalLayout_2->addWidget(outputLabel);

        progressBar = new QProgressBar(outputPage);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        verticalLayout_2->addWidget(progressBar);

        stackedWidget->addWidget(outputPage);

        verticalLayout->addWidget(stackedWidget);

        buttonBar = new QGridLayout();
        buttonBar->setSpacing(5);
        buttonBar->setObjectName(QStringLiteral("buttonBar"));
        buttonBar->setSizeConstraint(QLayout::SetDefaultConstraint);
        buttonBar->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer1 = new QSpacerItem(183, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        buttonBar->addItem(horizontalSpacer1, 0, 2, 1, 1);

        buttonCancel = new QPushButton(iso_snapshot);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonCancel->sizePolicy().hasHeightForWidth());
        buttonCancel->setSizePolicy(sizePolicy2);
        QIcon icon;
        icon.addFile(QStringLiteral("../../../../../../../../usr/share/iso-snapshot/icons/gtk-cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonCancel->setIcon(icon);
        buttonCancel->setAutoDefault(true);

        buttonBar->addWidget(buttonCancel, 0, 10, 1, 1);

        buttonHelp = new QPushButton(iso_snapshot);
        buttonHelp->setObjectName(QStringLiteral("buttonHelp"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../../../../../../usr/share/iso-snapshot/icons/gnome-help.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonHelp->setIcon(icon1);

        buttonBar->addWidget(buttonHelp, 0, 1, 1, 1);

        horizontalSpacer2 = new QSpacerItem(100, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        buttonBar->addItem(horizontalSpacer2, 0, 5, 1, 1);

        buttonAbout = new QPushButton(iso_snapshot);
        buttonAbout->setObjectName(QStringLiteral("buttonAbout"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("../../../../../../../../usr/share/iso-snapshot/icons/accessories-text-editor.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonAbout->setIcon(icon2);
        buttonAbout->setAutoDefault(true);

        buttonBar->addWidget(buttonAbout, 0, 0, 1, 1);

        labelMX = new QLabel(iso_snapshot);
        labelMX->setObjectName(QStringLiteral("labelMX"));
        labelMX->setMaximumSize(QSize(32, 32));
        labelMX->setMidLineWidth(0);
        labelMX->setPixmap(QPixmap(QString::fromUtf8("../../../../../../../../usr/share/iso-snapshot/icons/mxfcelogo.png")));
        labelMX->setScaledContents(true);

        buttonBar->addWidget(labelMX, 0, 3, 1, 1);

        buttonNext = new QPushButton(iso_snapshot);
        buttonNext->setObjectName(QStringLiteral("buttonNext"));
        sizePolicy2.setHeightForWidth(buttonNext->sizePolicy().hasHeightForWidth());
        buttonNext->setSizePolicy(sizePolicy2);
        buttonNext->setAutoDefault(true);

        buttonBar->addWidget(buttonNext, 0, 8, 1, 1);

        buttonBack = new QPushButton(iso_snapshot);
        buttonBack->setObjectName(QStringLiteral("buttonBack"));
        sizePolicy2.setHeightForWidth(buttonBack->sizePolicy().hasHeightForWidth());
        buttonBack->setSizePolicy(sizePolicy2);

        buttonBar->addWidget(buttonBack, 0, 7, 1, 1);


        verticalLayout->addLayout(buttonBar);


        retranslateUi(iso_snapshot);
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludeDesktop, SLOT(setChecked(bool)));
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludeDocuments, SLOT(setChecked(bool)));
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludeDownloads, SLOT(setChecked(bool)));
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludeMusic, SLOT(setChecked(bool)));
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludePictures, SLOT(setChecked(bool)));
        QObject::connect(excludeAll, SIGNAL(clicked(bool)), excludeVideos, SLOT(setChecked(bool)));

        stackedWidget->setCurrentIndex(2);
        buttonNext->setDefault(true);


        QMetaObject::connectSlotsByName(iso_snapshot);
    } // setupUi

    void retranslateUi(QDialog *iso_snapshot)
    {
        iso_snapshot->setWindowTitle(QApplication::translate("isosnapshot", "Snapshot", Q_NULLPTR));
        labelLocation->setText(QApplication::translate("isosnapshot", "Snapshot location:", Q_NULLPTR));
        labelIntro->setText(QApplication::translate("isosnapshot", "<html><head/><body><p>Snapshot is a utility that creates a bootable image (ISO) of your working system that you can use for storage or distribution. You can continue working with undemanding applications while it is running.<br/></p></body></html>", Q_NULLPTR));
        labelCurrentSpace->setText(QApplication::translate("isosnapshot", "Used space on / (root) and /home partitions:", Q_NULLPTR));
        labelDiskSpaceHelp->setText(QString());
        labelUsedSpace->setText(QString());
        labelFreeSpace->setText(QString());
        labelIsoName->setText(QApplication::translate("isosnapshot", "Snapshot name:", Q_NULLPTR));
        buttonSelectSnapshot->setText(QApplication::translate("isosnapshot", "Select a different snapshot directory", Q_NULLPTR));
        labelSnapshotDir->setText(QString());
        label_1->setText(QApplication::translate("isosnapshot", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("isosnapshot", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("isosnapshot", "TextLabel", Q_NULLPTR));
        buttonEditConfig->setText(QApplication::translate("isosnapshot", "Edit Configuration File", Q_NULLPTR));
        labelExclude->setText(QApplication::translate("isosnapshot", "You can also exclude certain directories by ticking the common choices below, or by clicking on the button to directly edit /usr/lib/iso-snapshot/snapshot-exclude.list.", Q_NULLPTR));
        excludeDownloads->setText(QApplication::translate("isosnapshot", "Downloads", Q_NULLPTR));
        excludeDocuments->setText(QApplication::translate("isosnapshot", "Documents", Q_NULLPTR));
        excludeAll->setText(QApplication::translate("isosnapshot", "All of the above", Q_NULLPTR));
        excludePictures->setText(QApplication::translate("isosnapshot", "Pictures", Q_NULLPTR));
        excludeMusic->setText(QApplication::translate("isosnapshot", "Music", Q_NULLPTR));
        excludeDesktop->setText(QApplication::translate("isosnapshot", "Desktop", Q_NULLPTR));
        excludeVideos->setText(QApplication::translate("isosnapshot", "Videos", Q_NULLPTR));
        buttonEditExclude->setText(QApplication::translate("isosnapshot", "Edit Exclusion File", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        radioRespin->setToolTip(QApplication::translate("isosnapshot", "<html><head/><body><p>This option will reset &quot;demo&quot; and &quot;root&quot; passwords to the antiX Linux defaults and will not copy any personal accounts created.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        radioRespin->setText(QApplication::translate("isosnapshot", "Resetting accounts (for distribution to others)", Q_NULLPTR));
        label->setText(QApplication::translate("isosnapshot", "Type of snapshot:", Q_NULLPTR));
        radioPersonal->setText(QApplication::translate("isosnapshot", "Preserving accounts (for personal backup)", Q_NULLPTR));
        outputLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonCancel->setToolTip(QApplication::translate("isosnapshot", "Quit application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonCancel->setText(QApplication::translate("isosnapshot", "Cancel", Q_NULLPTR));
        buttonCancel->setShortcut(QApplication::translate("isosnapshot", "Alt+N", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonHelp->setToolTip(QApplication::translate("isosnapshot", "Display help ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonHelp->setText(QApplication::translate("isosnapshot", "Help", Q_NULLPTR));
        buttonHelp->setShortcut(QApplication::translate("isosnapshot", "Alt+H", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        buttonAbout->setToolTip(QApplication::translate("isosnapshot", "About this application", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        buttonAbout->setText(QApplication::translate("isosnapshot", "About...", Q_NULLPTR));
        buttonAbout->setShortcut(QApplication::translate("isosnapshot", "Alt+B", Q_NULLPTR));
        labelMX->setText(QString());
        buttonNext->setText(QApplication::translate("isosnapshot", "Next >", Q_NULLPTR));
        buttonNext->setShortcut(QString());
        buttonBack->setText(QApplication::translate("isosnapshot", "< Back", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class isosnapshot: public Ui_isosnapshot {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISOSNAPSHOT_H
