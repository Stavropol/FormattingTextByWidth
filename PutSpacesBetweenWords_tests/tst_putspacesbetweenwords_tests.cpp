#include <QtTest>
#include <../FormattingTextByWidth/formattingtextbywidth.cpp>


class PutSpacesBetweenWords_tests : public QObject
{
    Q_OBJECT

private slots:
    void threeLinesForPlacementSpacesDoNotNeedToBePlaced();
    void threeLinesForPlacementSpacesInTheFirstAndSecond();
    void twoLinesForPlacementOneToIgnoreSpacesInTheFirstAndSecond();

};





void PutSpacesBetweenWords_tests::threeLinesForPlacementSpacesDoNotNeedToBePlaced()
{
    int width = 50;
    QString textToFormat = "форматирование текста по ширине с расстановкой123,\nПример текста для переноса с диапазоном пятьдесят1\nПример текста для переноса с диапазоном пятьдесят1\n";
    QString requiredResult = "форматирование текста по ширине с расстановкой123,\nПример текста для переноса с диапазоном пятьдесят1\nПример текста для переноса с диапазоном пятьдесят1\n";
    QString obtainedResult = PutSpacesBetweenWords(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

void PutSpacesBetweenWords_tests::threeLinesForPlacementSpacesInTheFirstAndSecond()
{
    int width = 50;
    QString textToFormat = "форматирование текста по ширине с расстановкой,\nПример текста для переноса с диапазоном пятьдесят\nПример текста для переноса с диапазоном пятьдесят.\n";
    QString requiredResult = "форматирование  текста  по  ширине с расстановкой,\nПример  текста для переноса с диапазоном пятьдесят\nПример текста для переноса с диапазоном пятьдесят.\n";
    QString obtainedResult = PutSpacesBetweenWords(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

void PutSpacesBetweenWords_tests::twoLinesForPlacementOneToIgnoreSpacesInTheFirstAndSecond()
{
    int width = 50;
    QString textToFormat = "форматирование текста по ширине с расстановкой,\nПример текста для переноса с диапазоном пятьдесят\nПример текста";
    QString requiredResult = "форматирование  текста  по  ширине с расстановкой,\nПример  текста для переноса с диапазоном пятьдесят\nПример текста\n";
    QString obtainedResult = PutSpacesBetweenWords(textToFormat, width);
    QCOMPARE(requiredResult,obtainedResult);
}

QTEST_APPLESS_MAIN(PutSpacesBetweenWords_tests)

#include "tst_putspacesbetweenwords_tests.moc"
