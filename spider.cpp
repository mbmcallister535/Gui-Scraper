#include "spider.h"
#include "ui_spider.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <iostream>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

Spider::Spider(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Spider)
{
    ui->setupUi(this);
}

Spider::~Spider()
{
    delete ui;
}

void Spider::on_pushButton_clicked()
{
    QLineEdit *line_edit = findChild<QLineEdit*>("lineEdit");
    QString url = line_edit->text();
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    manager->get(QNetworkRequest(QUrl(url)));
}
void Spider::replyFinished(QNetworkReply *p)
{
    if(p->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {

        QString file_path = dir + "/index.html";
        qDebug() << file_path;
        QFile file(file_path);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                qDebug() <<"Error occured here "<<endl;
            else
            {
                qDebug() << "In the else statement"<<endl;
                QTextStream out(&file);
                QString html_data = p->readAll();
                out << html_data;
            }
       file.close();
       QMessageBox msg;
    }
    else
    {
        qDebug() <<"Not supported "<<endl;
    }

}

void Spider::on_toolButton_clicked()
{
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    QLineEdit *path_edit = findChild<QLineEdit*>("pathEdit");
    path_edit->setText(dir);

}
