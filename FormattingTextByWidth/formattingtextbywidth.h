#ifndef FORMATTINGTEXTBYWIDTH_H
#define FORMATTINGTEXTBYWIDTH_H
#include <string>
#include <QTextStream>
#include <QRegularExpression>
#include <QFile>
#include <QDebug>

/**
* @brief Считывает текст из входного файла и проверяет правильность введенных пользователем данных.
* @param[in] - width - ширина, с которой будет форматироваться текст.
* @param[in] - inputFileName - имя входного файла.
* @return content - строка, сожержащая все строки входного файла.
* <summary>Пример вызова функции:</summary>
  *\code
    QString inputText = ReadTxtFileToString(width.toInt(),inputFileName);
  *\endcode
*/
QString ReadTxtFileToString(int width, const QString& inputFileName);

/**
* @brief Создает многострочный текст заданной длины из обычной строки.
* @param[in] - inputText - строка, из которой будет создаваться многострочный текст.
* @param[in] - width - ширина, с которой будет форматироваться текст.
* @return result - многострочный текст, полученный в результате форматирования.
* <summary>Пример вызова функции:</summary>
  *\code
    QString outputText = FormStringsFromWord(inputText, width.toInt());
  *\endcode
*/
QString ArrangeHyphenationsLine(const QString& inputText, int width);

/**
* @brief Расставляет пробелы между словами в строках, пока не будет получена необходимая длина при условии, что исходная строка занимает не менее 80% диапазона.
* @param[in] - inputText - строка с расставленными переносами, в которой будут расставлять пробелы.
* @param[in] - width - ширина, с которой будет форматироваться текст.
* @return result - текст, полученный в результате обработки.
* <summary>Пример вызова функции:</summary>
  *\code
     outputText = PutSpacesBetweenWords(outputText,width.toInt());
  *\endcode
*/
QString PutSpacesBetweenWords(const QString& inputText, int width);


#endif // FORMATTINGTEXTBYWIDTH_H
