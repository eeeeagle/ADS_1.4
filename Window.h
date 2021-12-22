#pragma once
#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QProcess>
#include <QProgressDialog>
#include <QPushButton>
#include <QStringList>
#include <QWidget>

class Settings : public QDialog
{
    QLineEdit* inter;
    QLineEdit* script;

    void locateInter();
    void locateScript();
public:
    Settings();
    friend class MainWindow;
};

class MainWindow : public QMainWindow
{
    QLineEdit* input;
    QLineEdit* output;
    Settings settings;

    void validate();

    void locateInput();
    void locateOutput();

    void showSettings();
public:
    MainWindow();
};