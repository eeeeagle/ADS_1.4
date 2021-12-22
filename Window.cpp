#include "window.h"

bool fileExists(QString path);

Settings::Settings()
{
    inter = new QLineEdit();
    auto labelInter = new QLabel();
    labelInter->setText("Path to the Python interpreter");
    auto buttonInter = new QPushButton("Locate");
    connect(buttonInter, &QPushButton::clicked, this, &Settings::locateInter);

    script = new QLineEdit();
    auto labelScript = new QLabel();
    labelScript->setText("Path to Python script (.py)");
    auto buttonScript = new QPushButton("Locate");
    connect(buttonScript, &QPushButton::clicked, this, &Settings::locateScript);

    auto buttonDone = new QPushButton("Close");
    connect(buttonDone, &QPushButton::clicked, this, &Settings::close);

    auto layout = new QGridLayout();

    layout->addWidget(labelInter, 0, 0);
    layout->addWidget(inter, 0, 1);
    layout->addWidget(buttonInter, 0, 2);

    layout->addWidget(labelScript, 1, 0);
    layout->addWidget(script, 1, 1);
    layout->addWidget(buttonScript, 1, 2);

    layout->addWidget(buttonDone, 2, 2);

    setLayout(layout);

    setWindowTitle(tr("Settings"));
    setWindowIcon(QIcon("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\settings.png"));
}

void Settings::locateInter()
{
    auto text = QFileDialog::getOpenFileName(this, "Loacte path to the Python interpreter...", "C:\\");
    inter->setText(text);
}

void Settings::locateScript()
{
    auto text = QFileDialog::getOpenFileName(this, "Loacte path to .py file...", "C:\\");
    script->setText(text);
}

MainWindow::MainWindow()
{
    QPixmap settingsPic("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\settings.png");
    auto actionSettings = new QAction(settingsPic, tr("&Settings"), this);
    connect(actionSettings, &QAction::triggered, this, &MainWindow::showSettings);
    
    QPixmap exitPic("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\exit.png");
    auto actionExit = new QAction(exitPic, tr("&Exit"), this);
    connect(actionExit, &QAction::triggered, this, &QWidget::close);

    auto fileMenu = new QMenu(tr("&File"));
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(actionSettings);
    fileMenu->addSeparator();
    fileMenu->addAction(actionExit);

    input = new QLineEdit();
    auto labelInput = new QLabel();
    labelInput->setText("Path to input file");
    auto buttonInput = new QPushButton("Locate");
    connect(buttonInput, &QPushButton::clicked, this, &MainWindow::locateInput);

    output = new QLineEdit();
    auto labelOutput = new QLabel();
    labelOutput->setText("Path to output file");
    auto buttonOutput = new QPushButton("Locate");
    connect(buttonOutput, &QPushButton::clicked, this, &MainWindow::locateOutput);

    auto buttonValidate = new QPushButton("Validate");
    connect(buttonValidate, &QPushButton::clicked, this, &MainWindow::validate);

    auto layout = new QGridLayout();
   
    layout->addWidget(labelInput, 1, 0);
    layout->addWidget(input, 1, 1);
    layout->addWidget(buttonInput, 1, 2);

    layout->addWidget(labelOutput, 2, 0);
    layout->addWidget(output, 2, 1);
    layout->addWidget(buttonOutput, 2, 2);

    layout->addWidget(buttonValidate, 3, 2);

    QWidget* window = new QWidget();
    window->setLayout(layout);
    setCentralWidget(window);
  
    setWindowTitle(tr("Validator"));
    setWindowIcon(QIcon("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\icon.png"));
    QPixmap backgroundPic("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\background.jpg");
    backgroundPic = backgroundPic.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Window, backgroundPic);
    setAutoFillBackground(true);
    setPalette(palette);
}

void MainWindow::validate()
{
    if ((settings.inter->text()).isEmpty() || (settings.script->text()).isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Unspecified path to Python interpretator or .py file\nCheck File->Settings");
        return;
    }
    if ((input->text()).isEmpty() || (output->text()).isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Unspecified path to input or output file");
        return;
    }
    if (!fileExists((settings.inter)->text()) || !fileExists((settings.script)->text()))
    {
        QMessageBox::warning(this, "Warning", "Python interpretator or .py file do not exist\nCheck File->Settings");
        return;
    }
    
    if(!fileExists(input->text()))
    {
        QMessageBox::warning(this, "Warning", "Input file do not exist");
        return;
    }
    QProcess process(this);
    QStringList arguments;
    arguments << (settings.script->text());
    arguments << (input->text());
    arguments << (output->text());
    process.start(QString(settings.inter->text()), arguments);

    auto err = process.readAllStandardError();
    if (err.size() != 0)
        QMessageBox::critical(this, "Error", err);
    if (process.waitForFinished())
        QMessageBox::information(this, "100%", "Validating is over");
}

void MainWindow::locateInput()
{
    auto text = QFileDialog::getOpenFileName(this, "Loacte path to input file...", "C:\\");
    input->setText(text);
}

void MainWindow::locateOutput()
{
    auto text = QFileDialog::getOpenFileName(this, "Loacte path to output file...", "C:\\");
    output->setText(text);
}

void MainWindow::showSettings()
{
    settings.setWindowModality(Qt::ApplicationModal);
    settings.show();
}

bool fileExists(QString path) 
{
    QFileInfo check_file(path);
    return check_file.isFile() && check_file.exists();
}