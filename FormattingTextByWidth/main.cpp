#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "rus");
    QTextStream in(stdin);
    QTextStream out(stdout);
    int width = 40;
    QString outputText;

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

    QString currentLine;
    QStringList words = inputText.split(' ');

       for (const QString& word : words) {
           if (currentLine.length() + word.length() + 1 <= width) {
               if (!currentLine.isEmpty()) {
                   currentLine.append(' ');
               }
               currentLine.append(word);
           } else {
               outputText.append(currentLine + '\n');
               currentLine = word;
           }
       }

       outputText.append(currentLine);

       // Расстановка пробелов в каждой строке, если достигнут порог 80% от ширины
       QString result2;
           QStringList lines = outputText.split('\n', QString::SkipEmptyParts);

           for (const QString& line : lines)
           {
               QStringList words = line.split(' ', QString::SkipEmptyParts);
               int wordCount = words.size();

               int totalSpaces = width - line.length() + wordCount - 1;
               int spacesBetweenWords = totalSpaces / (wordCount - 1);
               int extraSpaces = totalSpaces % (wordCount - 1);

               for (int i = 0; i < wordCount - 1; ++i)
               {
                   result2 += words[i] + QString(spacesBetweenWords + (i < extraSpaces ? 1 : 0), ' ');
               }

               result2 += words.last() + '\n';
           }


    output << result2;
    outputFile.close();

    qInfo()<< "Текст успешно отформатирован и записан в файл:" << outputFilename << endl;

    return a.exec();
}
