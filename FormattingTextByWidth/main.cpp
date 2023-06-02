#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "formattingtextbywidth.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "rus");
    QTextStream in(stdin);
    QTextStream out(stdout);
    int width = 40;

    qInfo() << "Введите путь к файлу для чтения: ";
    QString inputFilename = in.readLine();

    QFile inputFile(inputFilename);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для чтения:" << inputFilename;
        return -1;
    }

    QString inputText = QString::fromUtf8(inputFile.readAll());
    inputFile.close();

    qInfo() << "Введите путь к файлу для записи: ";
    QString outputFilename = in.readLine();

    QFile outputFile(outputFilename);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи:" << outputFilename;
        return -1;
    }

    QTextStream output(&outputFile);
    QString outputText = formatString(inputText, width);
    output << outputText;
    outputFile.close();

    qInfo()<< "Текст успешно отформатирован и записан в файл:" << outputFilename << endl;

    return a.exec();
}
