#ifndef FORMATTINGTEXTBYWIDTH_H
#define FORMATTINGTEXTBYWIDTH_H
#include <string>
#include <QTextStream>
#include <QRegularExpression>

QString FormStringsFromWord(const QString& inputText, int width);
QString PutSpacesBetweenWords(const QString& inputText, int width);


#endif // FORMATTINGTEXTBYWIDTH_H
