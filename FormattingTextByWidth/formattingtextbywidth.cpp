#include "formattingtextbywidth.h"


QString readTxtFileToString(int width, const QString& inputFileName)
{

    QFile file(inputFileName);  // Создание объекта файла
       if (!file.exists()) {
           qWarning() << "Файл не найден:" << inputFileName;
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       if (width < 50 || width > 250) {
           qWarning() << "Ширина должна быть в диапазоне от 50 до 250";
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qWarning() << "Не удалось открыть файл для чтения:" << inputFileName;
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       QString content = QString::fromUtf8(file.readAll());  // Чтение содержимого файла в строку
       file.close();  // Закрытие файла после чтения

       if (content.isEmpty()) {
           qWarning() << "Входной файл не содержит текста";
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       QStringList words = content.split(' ', QString::SkipEmptyParts);
       for (const QString& word : words) {
           if (word.length() > width) {
               qWarning() << "Слово превышает допустимую ширину:" << word;
               return QString();  // Возвращаем пустую строку в случае ошибки
           }
       }

       return content;  // Возвращаем содержимое файла

}



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

    QString result; // Результирующая строка

    // Разделяем входной текст на строки по символу новой строки
    QStringList lines = inputText.split('\n', QString::SkipEmptyParts);


        // Перебираем каждую строку
        for (const QString& line : lines)
        {
            // Разделяем строку на слова по пробелам
            QStringList words = line.split(' ', QString::SkipEmptyParts);
            int wordCount = words.size(); // Количество слов в строке
            double requiredLength = width * 0.8; // Необходимая длина строки для применения форматирования

            // Если длина строки меньше 80% от ширины, просто добавляем строку в результат без форматирования
            if (line.length() < requiredLength)
            {
                result += line + '\n';
                continue;
            }

            int totalSpaces = width - line.length() + wordCount - 1; // Общее количество пробелов, которые нужно добавить
            int spacesBetweenWords = totalSpaces / (wordCount - 1); // Количество пробелов между каждыми двумя словами
            int extraSpaces = totalSpaces % (wordCount - 1); // Оставшиеся пробелы, которые нужно добавить после равномерного распределения

            // Добавляем пробелы между словами с учетом равномерного распределения
            for (int i = 0; i < wordCount - 1; ++i)
            {
                result += words[i] + QString(spacesBetweenWords + (i < extraSpaces ? 1 : 0), ' ');
            }

            result += words.last() + '\n'; // Добавляем последнее слово в строку с символом новой строки
        }

        // Возвращаем сформированный текст
        return result;
}
