#include "MainWindow.h"
#include "DayDialog.h"
#include "DayButton.h"
#include <QVBoxLayout>
#include <QStringList>
#include <QScreen>
#include <QRect>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QGuiApplication>
#include <QIODevice>
#include <QLocale>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setWindowTitle("Календарь настроения");
    setCentralWindow(1024,468);
    setFixedSize(1024,468);
    widget = new QWidget(this);
    setCentralWidget(widget);

    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *nameCalendar = new QLabel("Календарь вашего настроения на " + QString::number(QDate::currentDate().year()) + " год.");
    nameCalendar->setAlignment(Qt::AlignCenter);
    nameCalendar->setFont(QFont("Tahoma",14));
    grid = new QGridLayout;
    layout->addWidget(nameCalendar);
    layout->addLayout(grid);

    QStringList monthNames = {
        "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    };

    // Заголовки дней (строка 0)
    for (int day = 1; day <= 31; ++day) {
        QLabel *label = new QLabel(QString::number(day));
        label->setAlignment(Qt::AlignCenter);
        label->setFixedWidth(30);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        grid->addWidget(label, 0, day);
    }

    // Заголовки месяцев (столбец 0)
    for (int month = 1; month <= 12; ++month) {
        QLabel *label = new QLabel(monthNames.at(month - 1));
        label->setAlignment(Qt::AlignCenter);
        label->setFixedWidth(60);
        label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        grid->addWidget(label, month, 0);
    }
    loadData(QString::number(QDate::currentDate().year()) +" year.json");
}

MainWindow::~MainWindow(){
    saveData(QString::number(QDate::currentDate().year()) +" year.json");
}

void MainWindow::setCentralWindow(int width, int height){
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();

    int x = (screenGeometry.width() - width) / 2;
    int y = (screenGeometry.height() - height) / 2;

    this->move(x, y);
}

void MainWindow::loadData(const QString &path) {
    QFile file(path);
    QJsonObject root;

    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
        root = doc.object();
    }

    int year = QDate::currentDate().year();

    for (int month = 1; month <= 12; ++month) {
        for (int day = 1; day <= 31; ++day) {
            QDate date(year, month, day);
            if (!date.isValid()) continue;

            int mood = 0;
            QString description = "";

            QString key = date.toString("yyyy-MM-dd");
            if (root.contains(key)) {
                QJsonObject obj = root[key].toObject();
                mood = obj["mood"].toInt(1);
                description = obj["description"].toString("");
            }

            DayButton *btn = new DayButton(date, mood, description);
            connect(btn, &QPushButton::clicked, btn, &DayButton::onButtonClick);
            grid->addWidget(btn, month, day);
        }
    }
    grid->setSpacing(0);
    grid->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::saveData(const QString &path) {
    QJsonObject root;

    for (int col = 1; col <= 12; ++col) {
        for (int row = 1; row <= 31; ++row) {
            QWidget *w = grid->itemAtPosition(col, row) ? grid->itemAtPosition(col, row)->widget() : nullptr;
            if (DayButton *btn = qobject_cast<DayButton*>(w)) {
                btn->saveInfo(root);
            }
        }
    }

    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(root);
        file.write(doc.toJson(QJsonDocument::Indented));
    }
}

