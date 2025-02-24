#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages)
    {
        const QString baseName = "calculator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            QApplication::installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.setWindowTitle("计算器");
    w.show();
    return QApplication::exec();
}
