#ifndef DAYBUTTON_H
#define DAYBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QDate>
#include <QString>
#include <QColor>

class DayButton : public QPushButton
{
    Q_OBJECT
public:
    DayButton(const QDate &m_date, int m_mood = 0, const QString &m_description = "");

    void calculateColor();
    void setColorButton();
    void saveInfo(QJsonObject &root);
    void onButtonClick();
private:
    QDate date;
    int mood;
    QColor color;
    QString description;
    bool editable;
};

#endif // DAYBUTTON_H
