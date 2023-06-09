#include <QtTest>
#include <../FormattingTextByWidth/formattingtextbywidth.cpp>


class FormStringsFromWord_tests : public QObject
{
    Q_OBJECT


private slots:
    void wordsExceedTheLengthThereAreNoHyphenations();
    void theLengthIsExceededThereAreNoTransfers();
    void theWordsDoNotExceedTheLengthThereAreCustomHyphenations();
    void wordsExceedTheLengthThereAreCustomHyphenations();
};



void FormStringsFromWord_tests::wordsExceedTheLengthThereAreNoHyphenations()
{
    int width = 50;
    QString textToFormat = "Форматирование текста по ширине с расстановкой переносов. Пример текста для переноса с диапазоном пятьдесят символов, а также тут используется";
    QString requiredResult = "Форматирование текста по ширине с расстановкой\nпереносов. Пример текста для переноса с диапазоном\nпятьдесят символов, а также тут используется\n";
    QString obtainedResult = FormStringsFromWord(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

void FormStringsFromWord_tests::theLengthIsExceededThereAreNoTransfers()
{
    int width = 250;
    QString textToFormat = "Форматирование текста по ширине с расстановкой переносов. Пример текста для переноса с диапазоном пятьдесят символов, а также тут";
    QString requiredResult = "Форматирование текста по ширине с расстановкой переносов. Пример текста для переноса с диапазоном пятьдесят символов, а также тут\n";
    QString obtainedResult = FormStringsFromWord(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

void FormStringsFromWord_tests::theWordsDoNotExceedTheLengthThereAreCustomHyphenations()
{
    int width = 250;
    QString textToFormat = "Форматирование текста по ширине с расстановкой переносов.\nПример текста для переноса с диапазоном пятьдесят символов,\nа также тут используется";
    QString requiredResult = "Форматирование текста по ширине с расстановкой переносов.\nПример текста для переноса с диапазоном пятьдесят символов,\nа также тут используется\n";
    QString obtainedResult = FormStringsFromWord(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

void FormStringsFromWord_tests::wordsExceedTheLengthThereAreCustomHyphenations()
{
    int width = 50;
    QString textToFormat = "Форматирование\nтекста по ширине с расстановкой переносов. Пример текста для переноса с диапазоном пятьдесят символов, а также тут используется";
    QString requiredResult = "Форматирование\nтекста по ширине с расстановкой переносов. Пример\nтекста для переноса с диапазоном пятьдесят\nсимволов, а также тут используется\n";
    QString obtainedResult = FormStringsFromWord(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

QTEST_APPLESS_MAIN(FormStringsFromWord_tests)

#include "tst_formstringsfromword_tests.moc"
