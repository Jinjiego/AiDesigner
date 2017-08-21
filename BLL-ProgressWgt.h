#ifndef BLLPROGRESSWGT_H
#define BLLPROGRESSWGT_H
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QProgressBar>

//typedef  void (QTreeWidget::*setItemWidget)(QTreeWidgetItem*,int,QWidget*);

class RuningProgress:public QObject
{
public:
    QTreeWidgetItem* activatedProject;
    RuningProgress(QTreeWidget*parent, QString activatedProjectName) //,setItemWidget fun )
    {

        activatedProject=new QTreeWidgetItem(parent, QStringList(activatedProjectName));
        MessageItem=new QTreeWidgetItem(QStringList("Parparing ..."));
        progressItem=new QTreeWidgetItem();
        progressBar=new QProgressBar();
        progressBar->setMaximumWidth(300);

        progressBar->setMaximumHeight(20);
        //(*fun)(progressItem,0,progressBar);
        ShowStatus();

    }
    void ShowStatus()
    {
         activatedProject->addChild(MessageItem);
         activatedProject->addChild(progressItem);

    }
    void ClearStatus()
    {


    }

    void UapdateStatus(QString message,int progress)
    {
           MessageItem->setText(0,message);
           progressBar->setValue(progress);
    }
public:
       QTreeWidgetItem *MessageItem;
       QTreeWidgetItem *progressItem;
       QProgressBar *progressBar;

};



class BLLProgressWgt : public  QTreeWidget
{

    Q_OBJECT
public:
     BLLProgressWgt(QWidget *parent=nullptr);


signals:
public slots:
     void RecvAMessage(QString type, QString message);


private :
     QTreeWidgetItem * activatedProjectRoot;
     RuningProgress * activatedProjectTree;
};

#endif // BLLPROGRESSWGT_H
