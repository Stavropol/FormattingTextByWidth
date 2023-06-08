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
    QString width = argv[1];

    QString inputFilename = argv[2];

    QFile inputFile(inputFilename);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для чтения:" << inputFilename;
        return -1;
    }

    QString inputText = QString::fromUtf8(inputFile.readAll());
    inputFile.close();

    QString outputFilename = argv[3];

    QFile outputFile(outputFilename);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи:" << outputFilename;
        return -1;
    }

    QTextStream output(&outputFile);
    QString outputText = formatString(inputText, width.toInt());
    output << outputText;
    outputFile.close();

    qInfo()<< "Текст успешно отформатирован и записан в файл:" << outputFilename << endl;

    return 0;
}
