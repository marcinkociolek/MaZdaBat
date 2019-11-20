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
    regex FilePattern(FilePaternStr);
    for (directory_entry& FileToProcess : directory_iterator(FileFolder))
    {

        if (!regex_match(FileToProcess.path().filename().string().c_str(), FilePattern ))
            continue;
        path PathLocal = FileToProcess.path();

        FileNamesVector->push_back(PathLocal.filename().string());
    }
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
}

MainWindow::~MainWindow()
{
    delete ui;
}
//------------------------------------------------------------------------------------------------------------------------------


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
    if (!exists(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + QMaZdaFolder.string()+ " not exists "));
        QMaZdaFolder = path("C:/");
    }
    if (!is_directory(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + QMaZdaFolder.string()+ " This is not a directory path "));
        QMaZdaFolder = path("C:/");
    }
    path MZGeneratorPath = QMaZdaFolder;
    MZGeneratorPath.append("MzGenerator.exe");
    if (!exists(MZGeneratorPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MZGeneratorPath.string()+ " not exists "));
        QMaZdaFolder = path("C:\\");
    }

    ui->lineEditMaZdaFolder->setText(QString::fromStdString(QMaZdaFolder.string()));
}



/*
    ui->listWidgetFiles->clear();
    for (directory_entry& FileToProcess : directory_iterator(FileFolder))
    {
        regex FilePattern(ui->lineEditRegexFile->text().toStdString());
        if (!regex_match(FileToProcess.path().filename().string().c_str(), FilePattern ))
            continue;
        path PathLocal = FileToProcess.path();
        if (!exists(PathLocal))
        {
            ui->textEditOut->append(QString::fromStdString(PathLocal.filename().string() + " File not exists" ));
            break;
        }
        ui->listWidgetFiles->addItem(PathLocal.filename().string().c_str());
    }
*/

void MainWindow::on_pushButtonUpenImageFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(ImageFolder.string()));

    if(dialog.exec())
    {
        ImageFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ImageFolder.string()+ " not exists "));
        ImageFolder = path("C:/");
    }
    if (!is_directory(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ImageFolder.string()+ " This is not a directory path "));
        ImageFolder = path("C:/");
    }
    ui->lineEditImageFolder->setText(QString::fromStdString(ImageFolder.string()));
    ReadFolder(ImageFolder, &ImageFileNamesVector, FilePattern );
    ui->textEditImageFiles->clear();
    ui->textEditImageFiles->append(QString::fromStdString(StringVectorToString(ImageFileNamesVector)));

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
    if (!exists(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ROIFolder.string()+ " not exists "));
        ROIFolder = path("C:/");
    }
    if (!is_directory(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ROIFolder.string()+ " This is not a directory path "));
        ROIFolder = path("C:/");
    }
    ui->lineEditROIFolder->setText(QString::fromStdString(ROIFolder.string()));
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
    if (!exists(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + OptionsFolder.string()+ " not exists "));
        OptionsFolder = path("C:/");
    }
    if (!is_directory(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + OptionsFolder.string()+ " This is not a directory path "));
        OptionsFolder = path("C:/");
    }
    ui->lineEditOptionsFolder->setText(QString::fromStdString(OptionsFolder.string()));
}

void MainWindow::on_pushButtonOpenOutFolder_clicked()
{
    QFileDialog dialog(this, "Open Folder");
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QString::fromStdString(OutFolder.string()));

    if(dialog.exec())
    {
        OutFolder = dialog.directory().path().toStdWString();
    }
    else
        return;
    if (!exists(OutFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + OutFolder.string()+ " not exists "));
        OutFolder = path("C:/");
    }
    if (!is_directory(OutFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + OutFolder.string()+ " This is not a directory path "));
        OutFolder = path("C:/");
    }
    ui->lineEditOutFolder->setText(QString::fromStdString(OutFolder.string()));
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

void MainWindow::on_lineEditFilePattern_returnPressed()
{
    FilePattern = ui->lineEditFilePattern->text().toStdString();
}
