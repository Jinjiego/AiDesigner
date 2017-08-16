#ifndef BLLMESGMANAGER_H
#define BLLMESGMANAGER_H

#include <QListWidget>
class BLLMesgManager : public QListWidget
{
    Q_OBJECT
public:
         explicit BLLMesgManager(QWidget *parent = 0,QString initMessage="");

signals:



public slots:

     void RecvAMessage(QString message);
private:
     QListWidgetItem*MessageItem;

};

#endif // BLLMESGMANAGER_H
