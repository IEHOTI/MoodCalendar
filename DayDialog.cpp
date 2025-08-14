#include "DayDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QTextEdit>
#include <QPushButton>
#include <QList>
#include <QColor>
#include <QLocale>

DayDialog::DayDialog(const QDate &date, int *moodPtr, QString *descriptionPtr, bool editable): mood(moodPtr), description(descriptionPtr) {
    setWindowTitle("Один маленький листочек из вашего дерева жизни");
    resize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLocale locale(QLocale::Russian);
    QString dateStr = locale.toString(date, "dddd, d MMMM yyyy");

    QLabel *label = new QLabel("Оценка дня [" + dateStr + "]");
    layout->addWidget(label);

    const QList<QColor> gradient = {
        QColor("#8b0000"), QColor("#c62828"), QColor("#ef5350"),
        QColor("#ff7043"), QColor("#ffa726"), QColor("#ffeb3b"),
        QColor("#cddc39"), QColor("#aed581"), QColor("#81c784"),
        QColor("#4caf50")
    };

    QHBoxLayout *moodLayout = new QHBoxLayout(this);

    QButtonGroup *moodGroup = new QButtonGroup(this);
    for(int i = 1; i < 11; i++) {
        QRadioButton *button = new QRadioButton(QString::number(i),this);
        button->setEnabled(editable);
        QString style = QString("QRadioButton { color: %1; font-weight: bold;}").arg(gradient[i-1].name());
        button->setStyleSheet(style);
        moodGroup->addButton(button,i);
        moodLayout->addWidget(button);
    }
    if(*mood > 0 && *mood < 11) moodGroup->button(*mood)->setChecked(true);
    layout->addLayout(moodLayout);

    QLabel *textLabel = new QLabel("Опишите, почему вы поставили такую оценку.",this);
    layout->addWidget(textLabel);

    QTextEdit *textEdit = new QTextEdit(this);
    textEdit->setText(*description);
    textEdit->setReadOnly(!editable);
    layout->addWidget(textEdit);

    if (editable) {
        QPushButton *saveBtn = new QPushButton("Сохранить");
        layout->addWidget(saveBtn);
        connect(saveBtn, &QPushButton::clicked, this, [=](){
            *mood = moodGroup->checkedId();
            *description = textEdit->toPlainText();
            accept();
        });
    } else {
        QPushButton *closeBtn = new QPushButton("Закрыть");
        layout->addWidget(closeBtn);
        connect(closeBtn, &QPushButton::clicked, this, &QDialog::reject);
    }
}
