#ifndef DAYDIALOG_H
#define DAYDIALOG_H

#include <QDialog>
#include <QObject>
#include <QDate>
#include <QString>

class DayDialog : public QDialog
{
    Q_OBJECT
public:
    DayDialog(const QDate &date, int *moodPtr, QString *descriptionPtr, bool editable);

private:
    int *mood;
    QString *description;
};

#endif // DAYDIALOG_H
