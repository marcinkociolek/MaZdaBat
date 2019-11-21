#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <string>

#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

using namespace boost;
using namespace std;
using namespace boost::filesystem;
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          My functions outside the Mainwindow class
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
void ReadFolder(path FileFolder, std::vector<std::string> *FileNamesVector, string FilePaternStr = ".+")
{
    FileNamesVector->clear();
    if (!exists(FileFolder))
    {
        return;
    }
    if (!is_directory(FileFolder))
    {
        return;
    }
    regex FilePattern(FilePaternStr);
    for (directory_entry& FileToProcess : directory_iterator(FileFolder))
    {

        if (!regex_match(FileToProcess.path().filename().string().c_str(), FilePattern ))
            continue;
        path PathLocal = FileToProcess.path();

        FileNamesVector->push_back(PathLocal.filename().string());
    }
    std::sort(FileNamesVector->begin(),FileNamesVector->end());
}
//------------------------------------------------------------------------------------------------------------------------------
string StringVectorToString(std::vector<std::string> FileNamesVector)
{
    string OutStr = "";
    if(FileNamesVector.empty())
        return OutStr;
    for(vector<string>::iterator iFileNamesVector = FileNamesVector.begin(); iFileNamesVector != FileNamesVector.end(); iFileNamesVector++)
    {
        OutStr += *iFileNamesVector + "\n";
    }

    return OutStr;
}

//------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          My functions in the Mainwindow class
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ReloadPaths();
}

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::ReloadPaths()
{
    QMaZdaFolder = path(ui->lineEditMaZdaFolder->text().toStdString());
    ImageFolder = path(ui->lineEditImageFolder->text().toStdString());
    ROIFolder = path(ui->lineEditROIFolder->text().toStdString());
    OptionsFolder = path(ui->lineEditOptionsFolder->text().toStdString());
    OpenQMaZdaFolder();
    OpenImageFolder();
    OpenROIFolder();
    OpenOptionsFolder();
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenQMaZdaFolder()
{
    if (!exists(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString("QMaZda folder : " + QMaZdaFolder.string()+ " not exists "));
    }
    if (!is_directory(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString( "QMaZda folder : " + QMaZdaFolder.string()+ " This is not a directory path "));
    }
    path MZGeneratorPath = QMaZdaFolder;
    MZGeneratorPath.append("MzGenerator.exe");
    if (!exists(MZGeneratorPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MZGeneratorPath.string()+ " not exists "));
    }
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenImageFolder()
{
    if (!exists(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ImageFolder.string()+ " not exists "));
    }
    if (!is_directory(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ImageFolder.string()+ " This is not a directory path "));
    }
    ui->lineEditImageFolder->setText(QString::fromStdString(ImageFolder.string()));
    ReadFolder(ImageFolder, &ImageFileNamesVector, ui->lineEditImageFilePattern->text().toStdString() );
    ui->textEditImageFiles->clear();
    ui->textEditImageFiles->append(QString::fromStdString(StringVectorToString(ImageFileNamesVector)));
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenROIFolder()
{
    if (!exists(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString("ROI folder : " + ROIFolder.string()+ " not exists "));
        ROIFolder = path("C:/");
    }
    if (!is_directory(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ROIFolder.string()+ " This is not a directory path "));
        ROIFolder = path("C:/");
    }
    ui->lineEditROIFolder->setText(QString::fromStdString(ROIFolder.string()));
    ReadFolder(ROIFolder, &ROIFileNamesVector, ui->lineEditROIFilePattern->text().toStdString() );
    ui->textEditROIFiles->clear();
    ui->textEditROIFiles->append(QString::fromStdString(StringVectorToString(ROIFileNamesVector)));
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenOptionsFolder()
{
    if (!exists(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Options folder : " + OptionsFolder.string()+ " not exists "));
        OptionsFolder = path("C:/");
    }
    if (!is_directory(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Options folder : " + OptionsFolder.string()+ " This is not a directory path "));
        OptionsFolder = path("C:/");
    }
    ui->lineEditOptionsFolder->setText(QString::fromStdString(OptionsFolder.string()));
    ReadFolder(OptionsFolder, &OptionsFileNamesVector, ui->lineEditOptionsFilePattern->text().toStdString() );
    ui->textEditOptionsFiles->clear();
    ui->textEditOptionsFiles->append(QString::fromStdString(StringVectorToString(OptionsFileNamesVector)));
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//          Slots
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

void MainWindow::on_pushButtonOpenQMaZdaFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(QMaZdaFolder.string()));

    if(dialog.exec())
    {
        QMaZdaFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenQMaZdaFolder();
}

void MainWindow::on_pushButtonUpenImageFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    //dialog.setDirectory(QString::fromStdString(ImageFolder.string()));
    dialog.setDirectory(ui->lineEditImageFolder->text());

    if(dialog.exec())
    {
        ImageFolder = dialog.directory().path().toStdWString();
    }
    else
        return;

    OpenImageFolder();
}

void MainWindow::on_pushButtonOpenRoiFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(ROIFolder.string()));

    if(dialog.exec())
    {
        ROIFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenROIFolder();
}

void MainWindow::on_pushButtonOpenOptionsFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(OptionsFolder.string()));

    if(dialog.exec())
    {
        OptionsFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    OpenOptionsFolder();
}

void MainWindow::on_pushButtonOpenBatFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(BatFolder.string()));

    if(dialog.exec())
    {
        BatFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + BatFolder.string()+ " not exists "));
        BatFolder = path("C:/");
    }
    if (!is_directory(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + BatFolder.string()+ " This is not a directory path "));
        BatFolder = path("C:/");
    }
    ui->lineEditBatFolder->setText(QString::fromStdString(BatFolder.string()));
}



void MainWindow::on_pushButtonOpenClassyfiersFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(ClassyfiersFolder.string()));

    if(dialog.exec())
    {
        ClassyfiersFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ClassyfiersFolder.string()+ " not exists "));
        BatFolder = path("C:/");
    }
    if (!is_directory(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ClassyfiersFolder.string()+ " This is not a directory path "));
        ClassyfiersFolder = path("C:/");
    }
    ui->lineEditClassyfiersFolder->setText(QString::fromStdString(ClassyfiersFolder.string()));
}


void MainWindow::on_pushButtonOpenClassyfiersOptionsFile_clicked()
{
    QFileDialog dialog(this, "Open File");
    dialog.setFileMode(QFileDialog::AnyFile);
    //dialog.setDirectory(QString::fromStdString(ClassyfiersOptionFile..string()));

    if(dialog.exec())
    {
        ClassyfiersOptionFile = path(dialog.selectedFiles()[0].toStdWString());
    }
    else
        return;
    if (!exists(ClassyfiersOptionFile))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ClassyfiersOptionFile.string()+ " not exists "));
        BatFolder = path("C:/");
    }

    ui->lineEditClassyfiersOptionsFile->setText(QString::fromStdString(ClassyfiersOptionFile.string()));
}

void MainWindow::on_pushButtonOpenPredictorOutputFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(PredictorOutputFolder.string()));

    if(dialog.exec())
    {
        PredictorOutputFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + PredictorOutputFolder.string()+ " not exists "));
        PredictorOutputFolder = path("C:/");
    }
    if (!is_directory(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + PredictorOutputFolder.string()+ " This is not a directory path "));
        PredictorOutputFolder = path("C:/");
    }
    ui->lineEditPredictorOutputFolder->setText(QString::fromStdString(PredictorOutputFolder.string()));
}

void MainWindow::on_pushButtonOpenMzFeaturesOutFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(MzFeaturesOutFolder.string()));

    if(dialog.exec())
    {
        MzFeaturesOutFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + MzFeaturesOutFolder.string()+ " not exists "));
        MzFeaturesOutFolder = path("C:/");
    }
    if (!is_directory(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + MzFeaturesOutFolder.string()+ " This is not a directory path "));
        MzFeaturesOutFolder = path("C:/");
    }
    ui->lineEditMzFeaturesOutFolder->setText(QString::fromStdString(MzFeaturesOutFolder.string()));
}

void MainWindow::on_lineEditImageFilePattern_returnPressed()
{
    OpenImageFolder();
}

void MainWindow::on_lineEditOptionsFilePattern_returnPressed()
{
    OpenOptionsFolder();
}

void MainWindow::on_lineEditROIFilePattern_returnPressed()
{
    OpenROIFolder();
}

void MainWindow::on_lineEditImageFolder_returnPressed()
{
    ImageFolder = path(ui->lineEditImageFolder->text().toStdString());
    OpenImageFolder();
}

void MainWindow::on_lineEditROIFolder_returnPressed()
{
    ROIFolder = path(ui->lineEditROIFolder->text().toStdString());
    OpenROIFolder();
}

void MainWindow::on_lineEditOptionsFolder_returnPressed()
{
    OptionsFolder = path(ui->lineEditOptionsFolder->text().toStdString());
    OpenOptionsFolder();
}

void MainWindow::on_lineEditMaZdaFolder_returnPressed()
{
    QMaZdaFolder = path(ui->lineEditMaZdaFolder->text().toStdString());
}
