#include "formattingtextbywidth.h"

// Считывает текст из входного файла и проверяет правильность введенных пользователем данных.
QString ReadTxtFileToString(int width, const QString& inputFileName)
{
    QFile file(inputFileName);  // Создание объекта файла

       // Проверка на наличие файла.
       if (!file.exists()) {
           qWarning() << "Неверно указан файл с входными данными. Возможно, файл не существует." << inputFileName;
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       // Проверка на возможность открытия файла.
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
           qWarning() << "Неверно указан файл с входными данными. Возможно, файл не существует." << inputFileName;
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       QString content = QString::fromUtf8(file.readAll());  // Чтение содержимого файла в строку
       file.close();  // Закрытие файла после чтения

       // Проверка на наличие текста в файле.
       if (content.isEmpty()) {
           qWarning() << "Программа принимает на вход файлы, содержащие не менее 1 строки. Убедитесь, что в исходном файле не менее 1 строки.";
           return QString();  // Возвращаем пустую строку в случае ошибки
       }


       // Проверка на превышение словами заданного диапазона.
       QStringList words = content.split(' ', QString::SkipEmptyParts);
       auto it = std::find_if(words.begin(), words.end(), [width](const QString& word) {
           return word.size() > width;
       });

       if (it != words.end()) {
           qWarning() << "Проверьте правильность расстановки пробелов, количество символов в слове имеет превышение диапазона:" << *it;
           return QString();  // Возвращаем пустую строку в случае ошибки
       }

       return content;  // Возвращаем содержимое файла
}


// Выполняет разбиение текста на строки с заданной шириной, добавляя переносы строк в местах, где слова не помещаются в заданную ширину.
QString ArrangeHyphenationsLine(const QString &inputText, int width)
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

// Расставляет в строках пробелы между словами, пока не будет получена необходимая длина при условии, что исходная строка занимает не менее 80% диапазона
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
