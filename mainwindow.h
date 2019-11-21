#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <boost/filesystem.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    boost::filesystem::path QMaZdaFolder;
    boost::filesystem::path ImageFolder;
    boost::filesystem::path ROIFolder;
    boost::filesystem::path OptionsFolder;
    boost::filesystem::path MzFeaturesOutFolder;
    boost::filesystem::path ClassyfiersFolder;
    boost::filesystem::path ClassyfiersOptionFile;
    boost::filesystem::path PredictorOutputFolder;
    boost::filesystem::path BatFolder;

    //std::string OutFilePrefix;
    //std::string BatFileName;
    //std::string FilePattern;

    std::vector<std::string> ImageFileNamesVector;
    std::vector<std::string> ROIFileNamesVector;
    std::vector<std::string> OptionsFileNamesVector;



    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void ReloadPaths();
    void OpenQMaZdaFolder();
    void OpenImageFolder();
    void OpenROIFolder();
    void OpenOptionsFolder();

private slots:

    void on_pushButtonOpenQMaZdaFolder_clicked();

    void on_pushButtonUpenImageFolder_clicked();

    void on_pushButtonOpenRoiFolder_clicked();

    void on_pushButtonOpenOptionsFolder_clicked();

    void on_pushButtonOpenBatFolder_clicked();

    void on_pushButtonOpenClassyfiersFolder_clicked();

    void on_pushButtonOpenClassyfiersOptionsFile_clicked();

    void on_pushButtonOpenPredictorOutputFolder_clicked();

    void on_pushButtonOpenMzFeaturesOutFolder_clicked();

    void on_lineEditImageFilePattern_returnPressed();

    void on_lineEditOptionsFilePattern_returnPressed();

    void on_lineEditROIFilePattern_returnPressed();

    void on_lineEditImageFolder_returnPressed();

    void on_lineEditROIFolder_returnPressed();

    void on_lineEditOptionsFolder_returnPressed();

    void on_lineEditMaZdaFolder_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
