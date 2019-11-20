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
    boost::filesystem::path OutFolder;
    boost::filesystem::path BatFolder;

    std::string OutFilePrefix;
    std::string BatFileName;
    std::string FilePattern;

    std::vector<std::string> ImageFileNamesVector;
    std::vector<std::string> RoiFileNamesVector;
    std::vector<std::string> OptionsFileNamesVector;



    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButtonOpenQMaZdaFolder_clicked();

    void on_pushButtonUpenImageFolder_clicked();

    void on_pushButtonOpenRoiFolder_clicked();

    void on_pushButtonOpenOptionsFolder_clicked();

    void on_pushButtonOpenOutFolder_clicked();

    void on_pushButtonOpenBatFolder_clicked();

    void on_lineEditFilePattern_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
