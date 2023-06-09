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

    QString inputFileName = argv[2];

    QString inputText = readTxtFileToString(width.toInt(),inputFileName);
    if (inputText.isEmpty()) {
        return -1;  // Прерываем выполнение программы в случае ошибки
    }

    QString outputFilename = argv[3];

    QFile outputFile(outputFilename);

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи:" << outputFilename;
        return -1;
    }


    QTextStream output(&outputFile);
    QString outputText = FormStringsFromWord(inputText, width.toInt());
    outputText = PutSpacesBetweenWords(outputText,width.toInt());
    //QString outputText = formatString(inputText, width.toInt());
    output << outputText;
    outputFile.close();

    qInfo()<< "Текст успешно отформатирован и записан в файл:" << outputFilename << endl;

    return 0;
}
