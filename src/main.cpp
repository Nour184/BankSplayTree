#include "BankSplayTree.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString styleSheet; // 1. Declare the string here so 'w' can see it later
    QFile styleFile("C:/Users/lenovo thinkpad E15/Desktop/fundamentals c++/SplayTreeDemo/styles/styles.qss");

    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream ts(&styleFile);
        styleSheet = ts.readAll(); // 2. Store the file content in the string

        if (styleSheet.isEmpty()) {
        //    QMessageBox::warning(nullptr, "Warning", "File found, but it is EMPTY!");
        }
        else {
            // This sets the style for the WHOLE application
            a.setStyleSheet(styleSheet);
          //  QMessageBox::information(nullptr, "Debug", "Content: " + styleSheet.left(50));
        }
        styleFile.close();
    }
    else {
        QMessageBox::critical(nullptr, "Error", "Could not open: " + styleFile.errorString());
    }

    BankSplayTree w;

    w.setStyleSheet(styleSheet);

    w.show();
    return a.exec();
}
