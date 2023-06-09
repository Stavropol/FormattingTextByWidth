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

    QString width = argv[1];// Получение ширины текста из аргумента командной строки.
    QString inputFileName = argv[2]; // Получение имени входного файла из аргумента командной строки.

    // Чтение содержимого входного файла
    QString inputText = readTxtFileToString(width.toInt(),inputFileName);
    if (inputText.isEmpty()) {
        return -1;  // Прерываем выполнение программы в случае ошибки
    }

    QString outputFilename = argv[3]; // Получение имени выходного файла из аргумента командной строки.

    QFile outputFile(outputFilename); // Создание объекта файла для записи.

    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл для записи:" << outputFilename;
        return -1;
    }


    QTextStream output(&outputFile);
    QString outputText = FormStringsFromWord(inputText, width.toInt()); // Форматирование текста, расстановка переносов.
    outputText = PutSpacesBetweenWords(outputText,width.toInt()); // Добавление пробелов.
    output << outputText; // Запись отформатированного текста в файл.
    outputFile.close(); // Закрытие файла.


    qInfo()<< "Текст успешно отформатирован и записан в файл:" << outputFilename << endl;

    return 0;
}
