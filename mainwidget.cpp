#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QString>
#include <QFile>
#include <QTextStream>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(true);

    QString qss;
    QFile file(":/style.css");

    if (file.open(QFile::ReadOnly)) {
        // 用QTextStream读取样式文件不用区分文件编码 带bom也行
        QStringList list;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line;
            in >> line;
            list << line;
        }

        file.close();
        qss = list.join("\n");
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(paletteColor));
        // 用时主要在下面这句
        qApp->setStyleSheet(qss);
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

