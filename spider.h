#ifndef SPIDER_H
#define SPIDER_H
#include <QNetworkReply>
#include <QMainWindow>

namespace Ui {
class Spider;
}

class Spider : public QMainWindow
{
    Q_OBJECT

public:
    explicit Spider(QWidget *parent = 0);
    ~Spider();

private slots:
    void on_pushButton_clicked();
    void replyFinished(QNetworkReply*);
    void on_toolButton_clicked();

private:
    Ui::Spider *ui;
    QNetworkAccessManager *manager;
    QString dir;
};

#endif // SPIDER_H
