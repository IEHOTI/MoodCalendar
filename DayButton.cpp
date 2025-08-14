#include "DayButton.h"
#include "DayDialog.h"
#include <QList>
#include <QJsonObject>

DayButton::DayButton(const QDate &m_date, int m_mood, const QString &m_description)
    : date(m_date), mood(m_mood), description(m_description)
{
    if(m_date != QDate::currentDate()) editable = false;
    else editable = true;
    calculateColor();
    setColorButton();
    setFixedSize(30,30);
}

void DayButton::calculateColor() {
    if ((mood < 1) || (mood > 10)) {
        color = Qt::white;
        return;
    }

    const QList<QColor> gradient = {
        QColor("#8b0000"), QColor("#c62828"), QColor("#ef5350"),
        QColor("#ff7043"), QColor("#ffa726"), QColor("#ffeb3b"),
        QColor("#cddc39"), QColor("#aed581"), QColor("#81c784"),
        QColor("#4caf50")
    };
    color = gradient[mood - 1];
}

void DayButton::setColorButton() {
    QString style = QString("background-color: %1;").arg(color.name());
    this->setStyleSheet(style);
}

void DayButton::onButtonClick() {
    DayDialog dlg(date,&mood,&description,editable);
    if (dlg.exec() == QDialog::Accepted) {
        calculateColor();
        setColorButton();
    }
}

void DayButton::saveInfo(QJsonObject &root) {
    QJsonObject moodObj;
    moodObj["mood"] = mood;
    moodObj["description"] = description;
    root[date.toString("yyyy-MM-dd")] = moodObj;
}


