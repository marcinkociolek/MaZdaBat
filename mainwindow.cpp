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
    MzFeaturesOutFolder = path(ui->lineEditMzFeaturesOutFolder->text().toStdString());
    ClassyfiersFolder = path(ui->lineEditClassyfiersFolder->text().toStdString());
    ClassyfiersOptionFile = path(ui->lineEditClassyfiersOptionsFile->text().toStdString());
    PredictorOutputFolder = path(ui->lineEditPredictorOutputFolder->text().toStdString());
    BatFolder = path(ui->lineEditBatFolder->text().toStdString());
    if(ui->checkBoxUseSubfolders->checkState())
    {
        ImageFolder = ImageFolder.append(ui->lineEditImageClass->text().toStdString());

        MzFeaturesOutFolder = MzFeaturesOutFolder.append(ui->lineEditFeatureFamily->text().toStdString());
        MzFeaturesOutFolder = MzFeaturesOutFolder.append(ui->lineEditImageClass->text().toStdString());

        ClassyfiersFolder = ClassyfiersFolder.append(ui->lineEditFeatureFamily->text().toStdString());
        ClassyfiersFolder = ClassyfiersFolder.append(ui->lineEditImageClass->text().toStdString());

        PredictorOutputFolder = PredictorOutputFolder.append(ui->lineEditFeatureFamily->text().toStdString());
        PredictorOutputFolder = PredictorOutputFolder.append(ui->lineEditImageClass->text().toStdString());
    }

    OpenQMaZdaFolder();
    OpenImageFolder();
    OpenROIFolder();
    OpenOptionsFolder();
    OpenMzFeauresFolder();
    OpenClassyfiersFolder();
    OpenClassyfiersOptionsFile();
    OpenPredictorOutputFotder();
    OpenBatFolder();
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
    ui->lineEditMaZdaFolder->setText(QString::fromStdString(QMaZdaFolder.string()));
    path MZGeneratorPath = QMaZdaFolder;
    MZGeneratorPath.append("MzGenerator.exe");
    if (!exists(MZGeneratorPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MZGeneratorPath.string()+ " not exists "));
    }
    path MzTrainerPath = QMaZdaFolder;
    MzTrainerPath.append("MzTrainer.exe");
    if (!exists(MzTrainerPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzTrainerPath.string()+ " not exists "));
    }
    path MzPredictPath = QMaZdaFolder;
    MzPredictPath.append("MzTrainer.exe");
    if (!exists(MzPredictPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzPredictPath.string()+ " not exists "));
    }


}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenImageFolder()
{
    if (!exists(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ImageFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ImageFolder.string()+ " This is not a directory path "));
        return;
    }
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
        return;
    }
    if (!is_directory(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ROIFolder.string()+ " This is not a directory path "));
        return;
    }
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
        return;
    }
    if (!is_directory(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Options folder : " + OptionsFolder.string()+ " This is not a directory path "));
        return;
    }
    string optionsPattern;
    if(ui->checkBoxUseSubfolders->checkState())
    {
        optionsPattern = ".+" +
                         ui->lineEditFeatureFamily->text().toStdString() +
                         ui->lineEditOptionsFilePattern->text().toStdString();
    }
    else
    {
        optionsPattern = ui->lineEditOptionsFilePattern->text().toStdString();
    }
    ReadFolder(OptionsFolder, &OptionsFileNamesVector, optionsPattern );
    ui->textEditOptionsFiles->clear();
    ui->textEditOptionsFiles->append(QString::fromStdString(StringVectorToString(OptionsFileNamesVector)));
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenMzFeauresFolder()
{
    if (!exists(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString("MzFeatutes folder : " + MzFeaturesOutFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " MzFeatutes folder : " + MzFeaturesOutFolder.string()+ " This is not a directory path "));
        return;
    }

}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenClassyfiersFolder()
{
    if (!exists(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Classyfiers folder : " + ClassyfiersFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Classyfiers folder : " + ClassyfiersFolder.string()+ " This is not a directory path "));
        return;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenClassyfiersOptionsFile()
{
    if (!exists(ClassyfiersOptionFile))
    {
        ui->textEditOut->append(QString::fromStdString("Classyfiers Options File : " + ClassyfiersOptionFile.string()+ " not exists "));
        return;
    }

}

//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenPredictorOutputFotder()
{
    if (!exists(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Predictor Output folder : " + PredictorOutputFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString( "Predictor Output folder : " + PredictorOutputFolder.string()+ " This is not a directory path "));
        return;
    }

}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::OpenBatFolder()
{
    if (!exists(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + BatFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + BatFolder.string()+ " This is not a directory path "));
        return;
    }
}
//------------------------------------------------------------------------------------------------------------------------------
void MainWindow::CreateBat()
{
    ReloadPaths();

    if (!exists(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString("QMaZda folder : " + QMaZdaFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(QMaZdaFolder))
    {
        ui->textEditOut->append(QString::fromStdString( "QMaZda folder : " + QMaZdaFolder.string()+ " This is not a directory path "));
        return;
    }
    path MZGeneratorPath = QMaZdaFolder;
    MZGeneratorPath.append("MzGenerator.exe");
    if (!exists(MZGeneratorPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MZGeneratorPath.string()+ " not exists "));
        return;
    }
    path MzTrainerPath = QMaZdaFolder;
    MzTrainerPath.append("MzTrainer.exe");
    if (!exists(MzTrainerPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzTrainerPath.string()+ " not exists "));
        return;
    }
    path MzTrainerPluginPath = QMaZdaFolder;
    MzTrainerPluginPath.append("LdaPlugin.dll");
    if (!exists(MzTrainerPluginPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzTrainerPluginPath.string()+ " not exists "));
        return;
    }

    path MzPredictPath = QMaZdaFolder;
    MzPredictPath.append("MzPredict.exe");
    if (!exists(MzPredictPath))
    {
        ui->textEditOut->append(QString::fromStdString("File : " + MzPredictPath.string()+ " not exists "));
        return;
    }

    if (!exists(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + ImageFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(ImageFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ImageFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString("ROI folder : " + ROIFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(ROIFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + ROIFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Options folder : " + OptionsFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(OptionsFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Options folder : " + OptionsFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString("MzFeatutes folder : " + MzFeaturesOutFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(MzFeaturesOutFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " MzFeatutes folder : " + MzFeaturesOutFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Classyfiers folder : " + ClassyfiersFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(ClassyfiersFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Classyfiers folder : " + ClassyfiersFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(ClassyfiersOptionFile))
    {
        ui->textEditOut->append(QString::fromStdString("Classyfiers Options File : " + ClassyfiersOptionFile.string()+ " not exists "));
        return;
    }
    if (!exists(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Predictor Output folder : " + PredictorOutputFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(PredictorOutputFolder))
    {
        ui->textEditOut->append(QString::fromStdString( "Predicto rOutput folder : " + PredictorOutputFolder.string()+ " This is not a directory path "));
        return;
    }
    if (!exists(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString("Image folder : " + BatFolder.string()+ " not exists "));
        return;
    }
    if (!is_directory(BatFolder))
    {
        ui->textEditOut->append(QString::fromStdString( " Image folder : " + BatFolder.string()+ " This is not a directory path "));
        return;
    }

    int optionsCount = OptionsFileNamesVector.size();
    if(optionsCount == 0)
    {
        ui->textEditOut->append(QString::fromStdString( " No option files"));
        return;
    }
    int imagesCount = ImageFileNamesVector.size();
    if(imagesCount == 0)
    {
        ui->textEditOut->append(QString::fromStdString( " No image files"));
        return;
    }
    int roisCount = ImageFileNamesVector.size();
    if(roisCount == 0)
    {
        ui->textEditOut->append(QString::fromStdString( " No ROI files"));
        return;
    }

    if(imagesCount !=  roisCount)
    {
        ui->textEditOut->append(QString::fromStdString( "number of imaged doesnot match nr of ROIs"));
        return;
    }
    path BatFile;


    if(ui->checkBoxCreateFeaturesBat->checkState())
    {
        BatFile = BatFolder;
        string prefix;
        if(ui->checkBoxUseSubfolders->checkState())
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString() +
                           ui->lineEditFeatureFamily->text().toStdString() +
                           ui->lineEditImageClass->text().toStdString() +
                           "Feat.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString() +
                     ui->lineEditImageClass->text().toStdString();
        }
        else
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString()
                           + "Feat.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString();
        }


        string BatFileContent = "cls\n";
        path ImFile, RoiFile, FeaturesFile, OptionsFile;
        for(int o = 0; o < optionsCount; o++)
        {
            BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
            BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
            ImFile = ImageFolder;
            ImFile.append(ImageFileNamesVector[0]);
            RoiFile = ROIFolder;
            RoiFile.append(ROIFileNamesVector[0]);


            OptionsFile = OptionsFolder;
            OptionsFile.append(OptionsFileNamesVector[o]);

            FeaturesFile = MzFeaturesOutFolder;
            FeaturesFile.append(prefix + OptionsFile.stem().string() + ".csv");

            BatFileContent += MZGeneratorPath.string()
                              + " -m roi -i " + ImFile.string()
                              + " -r " + RoiFile.string()
                              + "    -o " + FeaturesFile.string()
                              + " -f " + OptionsFile.string()
                              + "\n";

            for(int i = 1; i < imagesCount; i++)
            {
                ImFile = ImageFolder;
                ImFile.append(ImageFileNamesVector[i]);
                RoiFile = ROIFolder;
                RoiFile.append(ROIFileNamesVector[i]);

                BatFileContent += MZGeneratorPath.string()
                                  + " -m roi -i " + ImFile.string()
                                  + " -r " + RoiFile.string()
                                  + " -a -o " + FeaturesFile.string()
                                  + "\n";
            }

        }
        BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
        BatFileContent += "echo \"     Training  data           \"\n";
        BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
        for(int o = 0; o < optionsCount; o++)
        {
            BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
            BatFileContent += "echo \"------------------------------------------------------------------------------------------\"\n";
            ImFile = ImageFolder;
            ImFile.append(ImageFileNamesVector[0]);
            RoiFile = ROIFolder;
            RoiFile.append(ROIFileNamesVector[0]);


            OptionsFile = OptionsFolder;
            OptionsFile.append(OptionsFileNamesVector[o]);

            FeaturesFile = MzFeaturesOutFolder;

            FeaturesFile.append("t_" + prefix + OptionsFile.stem().string() + ".csv");

            BatFileContent += MZGeneratorPath.string()
                              + " -m roi -i " + ImFile.string()
                              + " -r " + RoiFile.string()
                              + "    -o " + FeaturesFile.string()
                              + " -f " + OptionsFile.string()
                              + "\n";

            for(int i = 2; i < imagesCount; i+=2)
            {
                ImFile = ImageFolder;
                ImFile.append(ImageFileNamesVector[i]);
                RoiFile = ROIFolder;
                RoiFile.append(ROIFileNamesVector[i]);

                BatFileContent += MZGeneratorPath.string()
                                  + " -m roi -i " + ImFile.string()
                                  + " -r " + RoiFile.string()
                                  + " -a -o " + FeaturesFile.string()
                                  + "\n";
            }

        }

        std::ofstream FileToSave(BatFile.string());
        if (!FileToSave.is_open())
        {
            ui->textEditOut->append(QString::fromStdString("Bat File Not Saved"));
        }
        FileToSave << BatFileContent;
        FileToSave.close();
        BatFileContent.clear();
    }

    if(ui->checkBoxCreateTrainingBat->checkState())
    {
        BatFile = BatFolder;
        string prefix;
        if(ui->checkBoxUseSubfolders->checkState())
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString() +
                           ui->lineEditFeatureFamily->text().toStdString() +
                           ui->lineEditImageClass->text().toStdString() +
                           + "Train.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString() +
                     ui->lineEditImageClass->text().toStdString();
        }
        else
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString() +
                          "Train.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString();
        }


        string BatFileContent = "cls\n";
        path FeaturesFile, OptionsFile, TrainingOptionsFile, ClassyfiersFile;

        for(int o = 0; o < optionsCount; o++)
        {
            OptionsFile = OptionsFolder;
            OptionsFile.append(OptionsFileNamesVector[o]);

            FeaturesFile = MzFeaturesOutFolder;

            FeaturesFile.append("t_" + prefix + OptionsFile.stem().string() + ".csv");

            ClassyfiersFile = ClassyfiersFolder;
            ClassyfiersFile.append(prefix + OptionsFile.stem().string() + "Classyfier.txt");
            BatFileContent += MzTrainerPath.string()
                              + " -p " + MzTrainerPluginPath.string()
                              + " -c " + ClassyfiersOptionFile.string()
                              + " -i " + FeaturesFile.string()
                              + " -o " + ClassyfiersFile.string()
                              + "\n";

        }

        std::ofstream FileToSave(BatFile.string());
        if (!FileToSave.is_open())
        {
            ui->textEditOut->append(QString::fromStdString("Training Bat File Not Saved"));
        }
        FileToSave << BatFileContent;
        FileToSave.close();
        BatFileContent.clear();
    }
    if(ui->checkBoxCreatePredictorBat->checkState())
    {
        BatFile = BatFolder;
        string prefix;
        if(ui->checkBoxUseSubfolders->checkState())
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString() +
                           ui->lineEditFeatureFamily->text().toStdString() +
                           ui->lineEditImageClass->text().toStdString() +
                           "Predict.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString() +
                     ui->lineEditImageClass->text().toStdString();
        }
        else
        {
            BatFile.append(ui->lineEditBatFileName->text().toStdString() +
                          "Predict.bat");
            prefix = ui->lineEditOutFilePrefix->text().toStdString();
        }


        string BatFileContent = "cls\n";
        path FeaturesFile, OptionsFile, TrainingOptionsFile, ClassyfiersFile, PredictorOutFile;

        for(int o = 0; o < optionsCount; o++)
        {
            OptionsFile = OptionsFolder;
            OptionsFile.append(OptionsFileNamesVector[o]);

            FeaturesFile = MzFeaturesOutFolder;

            FeaturesFile.append(prefix + OptionsFile.stem().string() + ".csv");

            ClassyfiersFile = ClassyfiersFolder;
            ClassyfiersFile.append(prefix + OptionsFile.stem().string() + "Classyfier.txt");

            PredictorOutFile = PredictorOutputFolder;
            PredictorOutFile.append(prefix + OptionsFile.stem().string() + "Prediction.txt");
            BatFileContent += MzPredictPath.string()
                              + " -c " + ClassyfiersFile.string()
                              + " -i " + FeaturesFile.string()
                              + " -o " + PredictorOutFile.string()
                              + " -v \n";

        }

        std::ofstream FileToSave(BatFile.string());
        if (!FileToSave.is_open())
        {
            ui->textEditOut->append(QString::fromStdString("Prediction Bat File Not Saved"));
        }
        FileToSave << BatFileContent;
        FileToSave.close();
        BatFileContent.clear();
    }
    ReloadPaths();
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
    OpenBatFolder();
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
    OpenClassyfiersFolder();
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
    OpenClassyfiersOptionsFile();
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
    OpenPredictorOutputFotder();
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
    OpenMzFeauresFolder();
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
    OpenQMaZdaFolder();
}

void MainWindow::on_lineEditMzFeaturesOutFolder_returnPressed()
{
    MzFeaturesOutFolder = path(ui->lineEditMzFeaturesOutFolder->text().toStdString());
    OpenMzFeauresFolder();
}

void MainWindow::on_lineEditClassyfiersFolder_returnPressed()
{
    ClassyfiersFolder = path(ui->lineEditClassyfiersFolder->text().toStdString());
    OpenClassyfiersFolder();
}

void MainWindow::on_lineEditClassyfiersOptionsFile_returnPressed()
{
    ClassyfiersOptionFile = path(ui->lineEditClassyfiersOptionsFile->text().toStdString());
    OpenClassyfiersOptionsFile();
}

void MainWindow::on_lineEditPredictorOutputFolder_returnPressed()
{
    PredictorOutputFolder = path(ui->lineEditPredictorOutputFolder->text().toStdString());
    OpenPredictorOutputFotder();
}

void MainWindow::on_lineEditBatFolder_returnPressed()
{
    BatFolder = path(ui->lineEditBatFolder->text().toStdString());
    OpenBatFolder();
}

void MainWindow::on_pushButtonClearOut_clicked()
{
    ui->textEditOut->clear();
}


void MainWindow::on_pushButtonCreateBatFile_clicked()
{
    CreateBat();
}

void MainWindow::on_pushButtonReload_clicked()
{
    ReloadPaths();
}
