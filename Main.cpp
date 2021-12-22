#include "window.h"
#include <QSettings>

void SetWindowConfig(MainWindow& window)
{
    QSettings config("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\config.ini", QSettings::IniFormat);
    
    config.beginGroup("Position");
    int x = config.value("x", -1).toInt();
    int y = config.value("y", -1).toInt();
    int width = config.value("width", -1).toInt();
    int height = config.value("height", -1).toInt();
    config.endGroup();

    if (x > 0 && y > 0 && width > 0 && height > 0) 
    {
        window.setGeometry(x, y, width, height);
    }
}

void SaveWindowConfig(const MainWindow& window)
{
    QSettings config("C:\\Users\\DK\\source\\repos\\AlDS_1.4\\config.ini", QSettings::IniFormat);

    config.beginGroup("Position");
    config.setValue("x", window.x());
    config.setValue("y", window.y());
    config.setValue("width", window.width());
    config.setValue("height", window.height());
    config.endGroup();
}

int main(int argc, char** argv) 
{
    QApplication app(argc, argv);

    MainWindow window;
    SetWindowConfig(window);
    
    window.show();
    int res = app.exec();
    SaveWindowConfig(window);

    return res;
}