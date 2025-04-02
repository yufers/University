#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMovie>
#include <QDebug>  // Для отладки

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), counter1(SmartPtr<int>(new int(0))), counter2(SmartPtr<int>(new int(0))), counter3(SmartPtr<int>(new int(0))), counter4(SmartPtr<int>(new int(0))) {  // Инициализация counter
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QMovie *movie = new QMovie("D:/University.code/OOP/Lab10/sticker.gif");

    if (!movie->isValid()) {
        qDebug() << "Ошибка загрузки GIF!";
    }

    QGraphicsPixmapItem *gifItem = new QGraphicsPixmapItem();
    scene->addItem(gifItem);

    connect(movie, &QMovie::frameChanged, [=](int) {
        gifItem->setPixmap(movie->currentPixmap());
    });

    movie->start();

    QString buttonStyle = "background-color: white; color: dark; font-size: 16px;";
    ui->pushButton->setStyleSheet(buttonStyle);
    ui->pushButton_2->setStyleSheet(buttonStyle);
    ui->pushButton_3->setStyleSheet(buttonStyle);
    ui->pushButton_4->setStyleSheet(buttonStyle);

    ui->textBrowser->setStyleSheet("font-size: 15px;");
    ui->textBrowser->append("Прыжки на месте – 2 минуты\nБёрпи – 3 подхода по 1 минут\nВысокие колени – 3 подхода по по 1 минут\n"
                            "Прыжки в сторону (конькобежец) – 3 подхода по по 1 минут\nСкакалка (или имитация) – 2 минуты\nПланка с переходами на локти – 1 минута");

    ui->textBrowser_2->setStyleSheet("font-size: 15px;");
    ui->textBrowser_2->append("Приседания – 3 подхода по 15 раз\nВыпады вперед и назад – 3 подхода по 10 раз на каждую ногу\nЯгодичный мост – 3 подхода по 20 раз\n"
                              "Отжимания (классические или с колен) – 3 подхода по 12 раз\nТяга к груди (гантели, бутылки с водой) – 3 подхода по 15 раз\nПланка с подтягиванием коленей – 3 подхода по по 1 минут\n"
                              "Скручивания – 3 подхода по 20 раз");

    ui->textBrowser_3->setStyleSheet("font-size: 15px;");
    ui->textBrowser_3->append("Наклоны вперед (растяжка задней поверхности бедра) – 1 минута\nРастяжка квадрицепса стоя – 1 минута на каждую ногу\nРастяжка спины (поза ребёнка) – 1 минута\n"
                              "Поза голубя (ягодицы и бедра) – 1 минута на каждую сторону\nРастяжка грудных мышц у стены – 1 минута");

    ui->textBrowser_4->setStyleSheet("font-size: 15px;");
    ui->textBrowser_4->append("Прыжки на месте – 1 минута\nВращения руками и плечами – 1 минута\nВысокие колени – по 1 минут\nБёрпи – по 1 минут\n"
                              "Приседания – 3 подхода по 15 раз\nОтжимания – 3 подхода по 10 раз\nНаклоны вперед – 1 минута");

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::increaseCounter1);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::increaseCounter2);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::increaseCounter3);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &MainWindow::increaseCounter4);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MainWindow::resetCounters);

    ui->time_stat1->setText("Выполненно упражнений: " + QString::number(*counter1));
    ui->time_stat2->setText("Выполненно упражнений: " + QString::number(*counter2));
    ui->time_stat3->setText("Выполненно упражнений: " + QString::number(*counter3));
    ui->time_stat4->setText("Выполненно упражнений: " + QString::number(*counter4));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::increaseCounter1()
{
    counter1 += 12;
    ui->time_stat1->setText("Выполненно упражнений: " + QString::number(*counter1));
}

void MainWindow::increaseCounter2()
{
    counter2 += 21;
    ui->time_stat2->setText("Выполненно упражнений: " + QString::number(*counter2));
}

void MainWindow::increaseCounter3()
{
    counter3 += 5;
    ui->time_stat3->setText("Выполненно упражнений: " + QString::number(*counter3));
}

void MainWindow::increaseCounter4()
{
    counter4 += 11;
    ui->time_stat4->setText("Выполненно упражнений: " + QString::number(*counter4));
}

void MainWindow::resetCounters()
{
    (*counter1) = 0;
    (*counter2) = 0;
    (*counter3) = 0;
    (*counter4) = 0;

    ui->time_stat1->setText("Выполненно упражнений: " + QString::number(*counter1));
    ui->time_stat2->setText("Выполненно упражнений: " + QString::number(*counter2));
    ui->time_stat3->setText("Выполненно упражнений: " + QString::number(*counter3));
    ui->time_stat4->setText("Выполненно упражнений: " + QString::number(*counter4));
}
