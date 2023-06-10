#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "formattingtextbywidth.h"


/*!
*\file
*\brief Файл содержит вызываемые функции программы, а также управляющую функцию.
*\mainpage Документация для программы "FormattingTextByWidth"
Программа должна формировать многострочный текст по ширине с расстановкой переносов и также минимизацией добавляемых пробелов.

Для функционирования программы необходима операционная система Windows 8 или выше.
Программа будет разработана на языке С++ с применением библиотек <string>, <QTextStream>, <QRegularExpression>, <QFile>, <QDebug>, <QCoreApplication>. Дополнительного программного обеспечения не требуется.
Входные файлы должны быть подготовлены в редакторе Блокнот. Выходные файлы могут быть прочитаны с его помощью.

Программа должна получать три параметра командной строки: ширину для форматирования текста, имя входного файла с исходным текстом и имя файла для записи текста.

Пример команды запуска программы:
*\code
FormattingTextByWidth.exe 100 C:\input.txt  C:\output.txt
*\endcode
*\author Теликов Кирилл Евгеньевич
*\date Июнь 2023 года
*\version 1.0
*/


/**
* @brief Обеспечивает запись в выходной файл, вывод в консоль ошибок, если они есть, вызов функций, решающих задачу.
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "rus");
    QTextStream in(stdin);
    QTextStream out(stdout);

    QString width = argv[1];// Получение ширины текста из аргумента командной строки.
    QString inputFileName = argv[2]; // Получение имени входного файла из аргумента командной строки.

    // Чтение содержимого входного файла
    QString inputText = ReadTxtFileToString(width.toInt(),inputFileName);
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
