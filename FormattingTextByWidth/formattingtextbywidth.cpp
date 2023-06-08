#include "formattingtextbywidth.h"

QString FormStringsFromWord(const QString &inputText, int width)
{
    QString result; // Результирующая строка
    QString currentLine; // Текущая строка, которая будет формироваться
    QString str = inputText; // Полученная строка

            // Удаляем повторяющиеся пробелы, заменяя их на один пробел
            str.replace(QRegularExpression(" +"), " ");

            // Разделяем текст на строки по символу новой строки
            QStringList lines = str.split('\n', QString::SkipEmptyParts);

               // Перебираем каждую строку
               for (const QString& line : lines) {

                   // Разделяем строку на слова по пробелам
                   QStringList words = line.split(' ', QString::SkipEmptyParts);

                   // Перебираем каждое слово в строке
                   for (const QString& word : words) {

                       // Если добавление текущего слова к текущей строке не превышает заданную ширину
                       if (currentLine.length() + word.length() + 1 <= width) {

                           // Если текущая строка не пуста, добавляем пробел перед текущим словом
                           if (!currentLine.isEmpty()) {
                               currentLine.append(' ');
                           }

                           // Добавляем текущее слово к текущей строке
                           currentLine.append(word);
                       } else {

                           // Если добавление текущего слова превышает заданную ширину,
                           // добавляем текущую строку в результат и начинаем новую строку с текущим словом
                           result.append(currentLine + '\n');
                           currentLine = word;
                       }
                   }

                   // Добавляем оставшуюся часть текущей строки в результат
                   result.append(currentLine + '\n');
                   currentLine.clear();
               }

    // Возвращаем сформированный текст
    return result;
}

QString PutSpacesBetweenWords(const QString &inputText, int width)
{
    // Расстановка пробелов в каждой строке, если достигнут порог 80% от ширины
    QString result;
        QStringList lines = inputText.split('\n', QString::SkipEmptyParts);

        for (const QString& line : lines)
        {
            QStringList words = line.split(' ', QString::SkipEmptyParts);
            int wordCount = words.size();
            double requiredLength = width * 0.8;

            if (line.length() < requiredLength)
            {
                result += line + '\n';
                continue;
            }

            int totalSpaces = width - line.length() + wordCount - 1;
            int spacesBetweenWords = totalSpaces / (wordCount - 1);
            int extraSpaces = totalSpaces % (wordCount - 1);

            for (int i = 0; i < wordCount - 1; ++i)
            {
                result += words[i] + QString(spacesBetweenWords + (i < extraSpaces ? 1 : 0), ' ');
            }

            result += words.last() + '\n';
        }

        return result;
}
