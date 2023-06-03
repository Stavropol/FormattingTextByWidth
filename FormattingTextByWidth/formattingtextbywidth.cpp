#include "formattingtextbywidth.h"

// Функция, которая форматирует строку по ширине с расстановкой переносов
QString formatString(const QString& inputText, int width) {

    QString result = FormStringsFromWord(inputText, width);
    QString formattedText = PutSpacesBetweenWords(result, width);

   return formattedText;
}

QString FormStringsFromWord(const QString &inputText, int width)
{
    QString result;
    QString currentLine;
    QString str =    inputText;
            str.replace(QRegularExpression(" +"), " ");
            QStringList lines = str.split('\n', QString::SkipEmptyParts);

               for (const QString& line : lines) {
                   QStringList words = line.split(' ', QString::SkipEmptyParts);
                   for (const QString& word : words) {
                       if (currentLine.length() + word.length() + 1 <= width) {
                           if (!currentLine.isEmpty()) {
                               currentLine.append(' ');
                           }
                           currentLine.append(word);
                       } else {
                           result.append(currentLine + '\n');
                           currentLine = word;
                       }
                   }
                   result.append(currentLine + '\n');
                   currentLine.clear();
               }

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
