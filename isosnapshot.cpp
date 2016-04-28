/**********************************************************************
 *  isosnapshot.cpp
 **********************************************************************
 * Copyright (C) 2015 MX Authors
 *
 * Authors: Adrian
 *          MX & MEPIS Community <http://forum.mepiscommunity.org>
 *
 * This file is part of MX Snapshot.
 *
 * MX Snapshot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MX Snapshot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MX Snapshot.  If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/


#include "isosnapshot.h"
#include "ui_isosnapshot.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTextStream>

#include <QDebug>

isosnapshot::isosnapshot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::isosnapshot)
{
    ui->setupUi(this);

    proc = new QProcess(this);
    timer = new QTimer(this);
    proc->setReadChannel(QProcess::StandardOutput);
    proc->setReadChannelMode(QProcess::MergedChannels);

    this->setWindowTitle(tr("iso-snapshot"));
    ui->buttonBack->setHidden(true);
    ui->buttonSelectSnapshot->setHidden(true);
    ui->stackedWidget->setCurrentIndex(0);

    version = getVersion("isosnapshot");
    live = isLive();
    i686 = isi686();
    setup();
    reset_accounts = false;
    listUsedSpace();
}

isosnapshot::~isosnapshot()
{
    delete ui;
}

// load settings or use the default value
void isosnapshot::loadSettings()
{
    config_file.setFileName("/etc/iso-snapshot.conf");
    QSettings settings(config_file.fileName(), QSettings::IniFormat);

    session_excludes = "";
    snapshot_dir = settings.value("snapshot_dir", "/home/snapshot").toString();
    ui->labelSnapshot->setText(tr("The snapshot will be placed by default in ") + snapshot_dir.absolutePath());
    snapshot_excludes.setFileName(settings.value("snapshot_excludes", "/usr/local/share/excludes/iso-snapshot-exclude.list").toString());
    snapshot_basename = settings.value("snapshot_basename", "snapshot").toString();
    make_md5sum = settings.value("make_md5sum", "no").toString();
    make_isohybrid = settings.value("make_isohybrid", "yes").toString();
    mksq_opt = settings.value("mksq_opt", "-comp xz").toString();
    edit_boot_menu = settings.value("edit_boot_menu", "no").toString();
    lib_mod_dir = settings.value("lib_mod_dir", "/lib/modules/").toString();
    gui_editor.setFileName(settings.value("gui_editor", "/usr/bin/leafpad").toString());
    stamp = settings.value("stamp", "datetime").toString();
}

// setup/refresh versious items first time program runs
void isosnapshot::setup()
{
    qApp->processEvents();
    this->show();
    this->setWindowTitle(tr("iso-snapshot"));
    ui->buttonBack->setHidden(true);
    ui->buttonSelectSnapshot->setHidden(false);
    ui->stackedWidget->setCurrentIndex(0);
    ui->buttonCancel->setEnabled(true);
    ui->buttonNext->setEnabled(true);

    loadSettings();
    listFreeSpace();
}

// Util function for getting bash command output
QString isosnapshot::getCmdOut(QString cmd)
{
    QEventLoop loop;
    connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
    proc->start("/bin/bash", QStringList() << "-c" << cmd);
    loop.exec();
    disconnectAll();
    return proc->readAllStandardOutput().trimmed();
}

// Util function for running bash commands with progress bar and output in output box
int isosnapshot::runCmd(QString cmd)
{
    qApp->processEvents();
    QEventLoop loop;
    setConnections();
    connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
    proc->start("/bin/bash", QStringList() << "-c" << cmd);
    loop.exec();
    disconnectAll();
    return proc->exitCode();
}

// Util function for replacing strings in files
bool isosnapshot::replaceStringInFile(QString oldtext, QString newtext, QString filepath)
{
    QString cmd = QString("sed -i 's/%1/%2/g' %3").arg(oldtext).arg(newtext).arg(filepath);
    if (system(cmd.toUtf8()) != 0) {
        return false;
    }
    return true;
}

// Check if running from a live envoronment
bool isosnapshot::isLive()
{
    return (system("mountpoint -q /live/aufs") == 0 );
}

// Check if running from a 32bit environment
bool isosnapshot::isi686()
{
    return (getCmdOut("uname -m") == "i686");
}

// Get version of the program
QString isosnapshot::getVersion(QString name)
{
    QString cmd = QString("dpkg -l iso-snapshot | awk 'NR==6 {print $3}'").arg(name);
    return getCmdOut(cmd);
}

// return number of snapshots in snapshot_dir
int isosnapshot::getSnapshotCount()
{
    if (snapshot_dir.exists()) {
        QFileInfoList list = snapshot_dir.entryInfoList(QStringList("*.iso"), QDir::Files);
        return list.size();
    }
    return 0;
}

// return the size of the work folder
QString isosnapshot::getSnapshotSize()
{
    QString size;
    if (snapshot_dir.exists()) {
        QString cmd = QString("find %1 -maxdepth 1 -type f -name '*.iso' -exec du -shc {} + | tail -1 | awk '{print $1}'").arg(snapshot_dir.absolutePath());
        size = getCmdOut(cmd);
        if (size != "" ) {
            return size;
        }
    }
    return "0";
}

// List used space
void isosnapshot::listUsedSpace()
{
    this->show();
    ui->buttonNext->setDisabled(true);
    ui->buttonCancel->setDisabled(true);
    ui->buttonSelectSnapshot->setDisabled(true);
    QString cmd;
    if (live) {
        cmd = QString("du --exclude-from=%1 -sch / 2>/dev/null | tail -n1 | cut -f1").arg(snapshot_excludes.fileName());
    } else {
        cmd = QString("df -h / | awk 'NR==2 {print $3}'");
    }
    connect(timer, SIGNAL(timeout()), SLOT(procTime()));
    connect(proc, SIGNAL(started()), SLOT(procStart()));
    connect(proc, SIGNAL(finished(int)), SLOT(procDone(int)));
    QString out = "\n- " + tr("Used space on / (root): ") + getCmdOut(cmd);
    if (system("mountpoint -q /home") == 0 ) {
        cmd = QString("df -h /home | awk 'NR==2 {print $3}'");
        out.append("\n- " + tr("Used space on /home: ") + getCmdOut(cmd));
    }
    ui->buttonNext->setEnabled(true);
    ui->buttonCancel->setEnabled(true);
    ui->buttonSelectSnapshot->setEnabled(true);
    ui->labelUsedSpace->setText(out);
}


// List free space on drives
void isosnapshot::listFreeSpace()
{
    QString cmd;
    QString out;
    QString path = snapshot_dir.absolutePath().remove("/snapshot");
    cmd = QString("df -h %1 | awk 'NR==2 {print $4}'").arg(path);
    ui->labelFreeSpace->clear();
    out.append("- " + tr("Free space on %1, where snapshot folder is placed: ").arg(path) + getCmdOut(cmd) + "\n");
    ui->labelFreeSpace->setText(out);
    ui->labelDiskSpaceHelp->setText(tr("The free space should be sufficient to hold the compressed data from / and /home\n\n"
                                       "      If necessary, you can create more available space\n"
                                       "      by removing previous snapshots and saved copies:\n"
                                       "      %1 snapshots are taking up %2 of disk space.\n").arg(QString::number(getSnapshotCount())).arg(getSnapshotSize()));
}

// Checks if the editor listed in the config file is present
void isosnapshot::checkEditor()
{
    if (gui_editor.exists()) {
        return;
    }
    QString msg = tr("The graphical text editor is set to %1, but it is not installed. Edit %2 "
                     "and set the gui_editor variable to the editor of your choice. "
                     "(examples: /usr/bin/gedit, /usr/bin/leafpad)\n\n"
                     "Will install leafpad and use it this time.").arg(gui_editor.fileName()).arg(config_file.fileName());
    QMessageBox::information(0, QString::null, msg);
    if (installPackage("leafpad")) {
        gui_editor.setFileName("/usr/bin/leafpad");
    }
}

// Checks if package is installed
bool isosnapshot::checkInstalled(QString package)
{
    QString cmd = QString("dpkg -s %1 | grep Status").arg(package);
    if (getCmdOut(cmd) == "Status: install ok installed") {
        return true;
    }
    return false;
}

// Installs package
bool isosnapshot::installPackage(QString package)
{
    QEventLoop loop;
    this->setWindowTitle(tr("Installing ") + package);
    ui->outputBox->clear();
    ui->buttonNext->setDisabled(true);
    ui->buttonBack->setDisabled(true);
    this->show();
    ui->stackedWidget->setCurrentWidget(ui->outputPage);
    setConnections();
    connect(proc, SIGNAL(finished(int)), &loop, SLOT(quit()));
    proc->start("apt-get update");
    loop.exec();
    proc->start("apt-get install " + package);
    loop.exec();
    disconnectAll();
    this->hide();
    if (proc->exitCode() != 0) {
        QMessageBox::critical(0, tr("Error"), tr("Could not install ") + package);
        return false;
    }
    this->show();
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
    ui->buttonNext->setEnabled(true);
    ui->buttonBack->setEnabled(true);
    return true;
}

void isosnapshot::checkDirectories()
{
    //  Create snapshot dir if it doesn't exist
    if (!snapshot_dir.exists()) {
        snapshot_dir.mkpath(snapshot_dir.absolutePath());
        QString path = snapshot_dir.absolutePath();

        QString cmd = QString("chmod 777 %1").arg(path);
        system(cmd.toUtf8());
    }

    // Create a work_dir
    work_dir = getCmdOut("mktemp -d " + snapshot_dir.absolutePath() + "/iso-snapshot-XXXXXXXX");
}

void isosnapshot::openInitrd(QString file, QString initrd_dir)
{
    QString cmd = "mkdir -p " + initrd_dir;
    system(cmd.toUtf8());
    cmd = "chmod a+rx " + initrd_dir;
    system(cmd.toUtf8());
    QDir::setCurrent(initrd_dir);
    cmd = QString("gunzip -c %1 | cpio -idum").arg(file);
    system(cmd.toUtf8());
}

void isosnapshot::closeInitrd(QString initrd_dir, QString file)
{
    QDir::setCurrent(initrd_dir);
    QString cmd = "(find . | cpio -o -H newc --owner root:root | gzip -9) >" + file;
    runCmd(cmd);
    makeMd5sum(work_dir + "/iso-template/antiX", "initrd.gz");
}

// Copying the iso-template filesystem
void isosnapshot::copyNewIso()
{
    ui->outputBox->clear();

    ui->outputLabel->setText(tr("Copying the new-iso filesystem..."));
    QDir::setCurrent(work_dir);
    QString cmd = "tar xf /usr/lib/iso-template/iso-template.tar.gz";
    runCmd(cmd);
    cmd = "cp /usr/lib/iso-template/initrd.gz iso-template/antiX/";
    runCmd(cmd);

    cmd = "cp /boot/vmlinuz-" + kernel_used + " " + work_dir + "/iso-template/antiX/vmlinuz";
    runCmd(cmd);
    makeMd5sum(work_dir + "/iso-template/antiX", "vmlinuz");

    QString initrd_dir = work_dir + "/initrd";
    openInitrd(work_dir + "/iso-template/antiX/initrd.gz", initrd_dir);
    if (initrd_dir.contains("/iso-snapshot")) {  //just make sure initrd_dir is correct to avoid disaster
        // strip modules
        runCmd("test -d " + initrd_dir + "/lib/modules && rm -r " + initrd_dir  + "/lib/modules");
    }
    runCmd("test -r /usr/local/share/live-files/files/etc/initrd-release && cp /usr/local/share/live-files/files/etc/initrd-release " + initrd_dir + "/etc");
    if (initrd_dir != "") {
        copyModules(initrd_dir, kernel_used);
        closeInitrd(initrd_dir, work_dir + "/iso-template/antiX/initrd.gz");
    }
}

// copyModules(mod_dir/kernel_used kernel_used)
void isosnapshot::copyModules(QString to, QString kernel)
{
    QString cmd = QString("copy-initrd-modules -t=%1 -k=%2").arg(to).arg(kernel);
    system(cmd.toUtf8());
}

// Create the output filename
QString isosnapshot::getFilename()
{
    if (stamp == "datetime") {
        return snapshot_basename + "-" + getCmdOut("date +%Y%m%d_%H%M") + ".iso";
    } else {
        int n = 1;
        QString name = snapshot_dir.absolutePath() + "/" + snapshot_basename + QString::number(n) + ".iso";
        QDir dir;
        dir.setPath(name);
        while (dir.exists(dir.absolutePath())) {
            n++;
            QString name = snapshot_dir.absolutePath() + "/" + snapshot_basename + QString::number(n) + ".iso";
            dir.setPath(name);
        }
        return dir.absolutePath();
    }
}

// make working directory using the base filename
void isosnapshot::mkDir(QString filename)
{
    QDir dir;
    filename.chop(4); //remove ".iso" string
    dir.setPath(work_dir + "/iso-template/" + filename);
    dir.mkpath(dir.absolutePath());
}

// save package list in working directory
void isosnapshot::savePackageList(QString filename)
{
    filename.chop(4); //remove .iso
    filename = work_dir + "/iso-template/" + filename + "/package_list";
    QString cmd = "dpkg -l | grep \"ii\" | awk '{ print $2 }' >" + filename;
    system(cmd.toUtf8());
}

// setup the environment before taking the snapshot
void isosnapshot::setupEnv()
{
    // checks if work_dir looks OK
    if (!work_dir.contains("/iso-snapshot")) {
        return;
    }

    // install antix-installer if absent
    if (!checkInstalled("antix-installer")) {
        runCmd("apt-get update");
        if (!checkInstalled("antix-installer")) {
            runCmd("apt-get install antix-installer");
        }
    }
    // setup environment if creating a respin (reset root/demo, remove personal accounts)
    if (reset_accounts) {
        system("installed-to-live -b /.bind-root start empty=/home general version-file read-only");
    } else {
        // copy antixsources.desktop to Desktop on all accounts
        system("echo /home/*/Desktop | xargs -n1 cp /usr/share/applications/antix/antixsources.desktop 2>/dev/null");
        system("chmod +x /home/*/Desktop/antixsources.desktop");
        system("installed-to-live -b /.bind-root start bind=/home live-files version-file adjtime read-only");
    }
}


// create squashfs and then the iso
bool isosnapshot::createIso(QString filename)
{
    QString cmd;
    // add exclusions snapshot dir
    addRemoveExclusion(true, snapshot_dir.absolutePath());

    // squash the filesystem copy
    QDir::setCurrent(work_dir);
    cmd = "mksquashfs /.bind-root iso-template/antiX/linuxfs " + mksq_opt + " -wildcards -ef " + snapshot_excludes.fileName() + " " + session_excludes;
    ui->outputLabel->setText(tr("Squashing filesystem..."));
    if (runCmd(cmd) != 0) {
        QMessageBox::critical(0, tr("Error"), tr("Could not create linuxfs file, please check whether you have enough space on the destination partition."));
        return false;
    }
    makeMd5sum(work_dir + "/iso-template/antiX", "linuxfs");

    // mv linuxfs to another folder
    runCmd("mkdir -p " + work_dir + "/iso-2/antiX");
    runCmd("mv " + work_dir + "/iso-template/antiX/linuxfs* " + work_dir + "/iso-2/antiX");

    // create the iso file
    QDir::setCurrent(work_dir + "/iso-template");
    cmd = "genisoimage -gid 0 -uid 0 -allow-limited-size -l -V antiX-Linux-live -R -J -pad -no-emul-boot -boot-load-size 4 -boot-info-table -b boot/isolinux/isolinux.bin -c boot/isolinux/isolinux.cat -o " + snapshot_dir.absolutePath() + "/" + filename + " . "  + work_dir + "/iso-2";
    ui->outputLabel->setText(tr("Creating CD/DVD image file..."));
    if (runCmd(cmd) != 0) {
        QMessageBox::critical(0, tr("Error"), tr("Could not create ISO file, please check whether you have enough space on the destination partition."));
        return false;
    }

    // make it isohybrid
    if (make_isohybrid == "yes") {
        ui->outputLabel->setText(tr("Making hybrid iso"));
        cmd = "isohybrid " + snapshot_dir.absolutePath() + "/" + filename;
        runCmd(cmd);
    }

    // make md5sum
    if (make_md5sum == "yes") {
        makeMd5sum(snapshot_dir.absolutePath(), filename);
    }
    return true;
}

// create md5sum for different files
void isosnapshot::makeMd5sum(QString folder, QString filename)
{
    QDir dir;
    QString current = dir.currentPath();
    dir.setCurrent(folder);
    ui->outputLabel->setText(tr("Making md5sum"));
    QString cmd = "md5sum " + filename + ">" + folder + "/" + filename + ".md5";
    runCmd(cmd);
    dir.setCurrent(current);
}

// clean up changes before exit
void isosnapshot::cleanUp()
{
    QString cmd;
    ui->stackedWidget->setCurrentWidget(ui->outputPage);
    ui->outputLabel->setText(tr("Cleaning..."));
    system("pkill mksquashfs; pkill md5sum");
    QDir::setCurrent("/");
    system("installed-to-live cleanup");

    // checks if work_dir looks OK
    if (work_dir.contains("/iso-snapshot")) {        
        system("rm -r " + work_dir.toUtf8());
    }
    if (!live && !reset_accounts) {
        // remove installer icon
        system("rm /home/*/Desktop/minstall.desktop");
    }
    ui->outputLabel->clear();
}

// adds or removes exclusion to the exclusion string
void isosnapshot::addRemoveExclusion(bool add, QString exclusion)
{
    exclusion.remove(0, 1); // remove training slash
    if (add) {
        if ( session_excludes == "" ) {
            session_excludes.append("-e '" + exclusion + "'");
        } else {
            session_excludes.append(" '" + exclusion + "'");
        }
    } else {
        session_excludes.remove(" '" + exclusion + "'");
        if ( session_excludes == "-e" ) {
            session_excludes = "";
        }
    }
}

//// sync process events ////
void isosnapshot::procStart()
{
    timer->start(100);
    setCursor(QCursor(Qt::BusyCursor));
}

void isosnapshot::procTime()
{
    int i = ui->progressBar->value() + 1;
    if (i > 100) {
        i = 0;
    }
    ui->progressBar->setValue(i);
    // in live environment and first page, blink text while calculating used disk space
    if (live && (ui->stackedWidget->currentIndex() == 0)) {
        if (ui->progressBar->value()%4 == 0 ) {
            ui->labelUsedSpace->setText("\n " + tr("Please wait."));
        } else {
            ui->labelUsedSpace->setText("\n " + tr("Please wait. Calculating used disk space..."));
        }
    }
}

void isosnapshot::procDone(int)
{
    timer->stop();
    ui->progressBar->setValue(100);
    setCursor(QCursor(Qt::ArrowCursor));
}

// set proc and timer connections
void isosnapshot::setConnections()
{
    connect(timer, SIGNAL(timeout()), SLOT(procTime()));
    connect(proc, SIGNAL(started()), SLOT(procStart()));
    connect(proc, SIGNAL(readyReadStandardOutput()), SLOT(onStdoutAvailable()));
    connect(proc, SIGNAL(finished(int)), SLOT(procDone(int)));
}

// disconnect all connections
void isosnapshot::disconnectAll()
{
    disconnect(timer, SIGNAL(timeout()), 0, 0);
    disconnect(proc, SIGNAL(started()), 0, 0);
    disconnect(proc, SIGNAL(readyReadStandardOutput()), 0, 0);
    disconnect(proc, SIGNAL(finished(int)), 0, 0);
}

//// slots ////

// update output box on Stdout
void isosnapshot::onStdoutAvailable()
{
    QByteArray output = proc->readAllStandardOutput();
    ui->outputBox->insertPlainText(output);
    QScrollBar *sb = ui->outputBox->verticalScrollBar();
    sb->setValue(sb->maximum());
}


// Next button clicked
void isosnapshot::on_buttonNext_clicked()
{
    // on first page
    if (ui->stackedWidget->currentIndex() == 0) {
        this->setWindowTitle(tr("Settings"));
        ui->stackedWidget->setCurrentWidget(ui->settingsPage);
        ui->buttonBack->setHidden(false);
        ui->buttonBack->setEnabled(true);
        if (edit_boot_menu == "yes") {
            checkEditor();
        }
        kernel_used = getCmdOut("uname -r");
        ui->stackedWidget->setCurrentWidget(ui->settingsPage);
        ui->label_1->setText(tr("Snapshot will use the following settings:*"));

        ui->label_2->setText(QString("\n" + tr("- Snapshot directory:") + " %1\n" +
                       tr("- Kernel to be used:") + " %2\n").arg(snapshot_dir.absolutePath()).arg(kernel_used));
        ui->label_3->setText(tr("*These settings can be changed by editing: ") + config_file.fileName());

    // on settings page
    } else if (ui->stackedWidget->currentWidget() == ui->settingsPage) {

        int ans = QMessageBox::question(this, tr("Final chance"),
                              tr("Snapshot now has all the information it needs to create an ISO from your running system.") + "\n\n" +
                              tr("It will take some time to finish, depending on the size of the installed system and the capacity of your computer.") + "\n\n" +
                              tr("OK to start?"), QMessageBox::Ok | QMessageBox::Cancel);
        if (ans == QMessageBox::Cancel) {
            return;
        }
        checkDirectories();
        ui->buttonNext->setEnabled(false);
        ui->buttonBack->setEnabled(false);
        ui->stackedWidget->setCurrentWidget(ui->outputPage);
        this->setWindowTitle(tr("Output"));
        copyNewIso();
        QString filename = getFilename();
        ui->outputLabel->clear();
        mkDir(filename);
        savePackageList(filename);

        if (edit_boot_menu == "yes") {
            ans = QMessageBox::question(this, tr("Edit Boot Menu"),
                                  tr("The program will now pause to allow you to edit any files in the work directory. Select Yes to edit the boot menu or select No to bypass this step and continue creating the snapshot."),
                                     QMessageBox::Yes | QMessageBox::No);
            if (ans == QMessageBox::Yes) {
                this->hide();
                QString cmd = gui_editor.fileName() + " " + work_dir + "/iso-template/boot/isolinux/isolinux.cfg";
                system(cmd.toUtf8());
                this->show();
            }
        }
        setupEnv();
        bool success = createIso(filename);
        cleanUp();
        if (success) {
            QMessageBox::information(this, tr("Success"),tr("All finished!"), QMessageBox::Ok);
            ui->buttonCancel->setText(tr("Close"));
        }
    } else {
        return qApp->quit();
    }
}

void isosnapshot::on_buttonBack_clicked()
{
    this->setWindowTitle(tr("iso-snapshot"));
    ui->stackedWidget->setCurrentIndex(0);
    ui->buttonNext->setEnabled(true);
    ui->buttonBack->setHidden(true);
    ui->outputBox->clear();
}

void isosnapshot::on_buttonEditConfig_clicked()
{
    this->hide();
    checkEditor();
    system((gui_editor.fileName() + " " + config_file.fileName()).toUtf8());
    setup();
}

void isosnapshot::on_buttonEditExclude_clicked()
{
    this->hide();
    checkEditor();
    system((gui_editor.fileName() + " " + snapshot_excludes.fileName()).toUtf8());
    this->show();
}

void isosnapshot::on_excludeDocuments_toggled(bool checked)
{
    QString exclusion = "/home/*/Documents/*";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_excludeDownloads_toggled(bool checked)
{
    QString exclusion = "/home/*/Downloads/*";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_excludePictures_toggled(bool checked)
{
    QString exclusion = "/home/*/Pictures/*";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_excludeMusic_toggled(bool checked)
{
    QString exclusion = "/home/*/Music/*";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_excludeVideos_toggled(bool checked)
{
    QString exclusion = "/home/*/Videos/*";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_excludeDesktop_toggled(bool checked)
{
    QString exclusion = "/home/*/Desktop/!(minstall.desktop)";
    addRemoveExclusion(checked, exclusion);
    if (!checked) {
        ui->excludeAll->setChecked(false);
    }
}

void isosnapshot::on_radioRespin_clicked(bool checked)
{
    if (checked) {
        reset_accounts = true;
        if (!ui->excludeAll->isChecked()) {
            ui->excludeAll->click();
        }
    }
}

void isosnapshot::on_radioPersonal_clicked(bool checked)
{
    if (checked) {
        if (ui->excludeAll->isChecked()) {
            ui->excludeAll->click();
        }
    }
}


// About button clicked
void isosnapshot::on_buttonAbout_clicked()
{
    this->hide();
    QMessageBox msgBox(QMessageBox::NoIcon,
                       tr("About iso-snapshot"), "<p align=\"center\"><b><h2>" +
                       tr("iso-snapshot") + "</h2></b></p><p align=\"center\">" + tr("Version: ") +
                       version + "</p><p align=\"center\"><h3>" +
                       tr("Program for creating a live-CD from the running system for antiX Linux") + "</h3></p><p align=\"center\"><a href=\"http://antix.mepis.org/index.php?title=Main_Page\">http://antix.mepis.org/index.php?title=Main_Page</a><br /></p><p align=\"center\">" +
                       tr("Copyright (c) antiX Linux") + "<br /><br /></p>", 0, this);
    msgBox.addButton(tr("Cancel"), QMessageBox::AcceptRole); // because we want to display the buttons in reverse order we use counter-intuitive roles.
    msgBox.addButton(tr("License"), QMessageBox::RejectRole);
    if (msgBox.exec() == QMessageBox::RejectRole)
        system("dillo http://www.mepiscommunity.org/doc_mx/mx-snapshot-license.html");
    this->show();
}

// Help button clicked
void isosnapshot::on_buttonHelp_clicked()
{
    system("dillo http://mepiscommunity.org/doc_mx/snapshot.html");
}

// Select snapshot directory
void isosnapshot::on_buttonSelectSnapshot_clicked()
{
    QFileDialog dialog;
    this->hide();
    QDir selected = dialog.getExistingDirectory(this, tr("Select Snapshot Directory"), QString(), QFileDialog::ShowDirsOnly);
    if (selected.exists()) {
        snapshot_dir.setPath(selected.absolutePath() + "/snapshot");
        ui->labelSnapshot->setText(tr("The snapshot will be placed in ") + snapshot_dir.absolutePath());
        listFreeSpace();
    }
    this->show();
}

