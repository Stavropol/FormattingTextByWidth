#ifndef FORMATTINGTEXTBYWIDTH_H
#define FORMATTINGTEXTBYWIDTH_H
#include <string>
#include <QTextStream>
#include <QRegularExpression>
#include <QFile>
#include <QDebug>

QString readTxtFileToString(int width, const QString& inputFileName);
QString FormStringsFromWord(const QString& inputText, int width);
QString PutSpacesBetweenWords(const QString& inputText, int width);


#endif // FORMATTINGTEXTBYWIDTH_H
