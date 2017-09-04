
#ifndef BASEUTIL
#define BASEUTIL
#include<QDir>
#include<QThread>
#include<QTextStream>
#include<QMessageBox>
#include "baseWgt/BASE-Type.hpp"
#include "baseWgt/BASE-TextDataWgt.h"
#include "baseWgt/BASE-DataTableWgt.h"

#define VNAME(varName)  (#varName)
#define VNAME_D(varName)  QString::fromStdString(string(#varName).substr(15))


bool inline CreateDir(QString fullPath){
    QDir dir(fullPath);
    if(dir.exists() ) return true;
    else {
        dir.mkdir(fullPath);
        std:: cout<<"--->"<<fullPath.toStdString()<<"\n";
        return true;
    }
    return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UtilReadTextFile:public QThread
{
Q_OBJECT
public:
    UtilReadTextFile(){ }
    ~UtilReadTextFile(){ }
    void ReadTextFileFrom(QString fullpath,TextDataWgt  *TextTab)
    {
        fullPath=fullpath;
        textTab=TextTab;
        task=&UtilReadTextFile:: ReadTextFile;
        start();
    }
    void ReadTextAsTable(QString fullpath,DataTableWgt  *tableTab){
                 fullPath=fullpath;
                 anyTab=tableTab;
                 task=&UtilReadTextFile::ParseText2Table;
                 start();
    }
    void ParseText2Table()
    {
        DataTableWgt  *tableTab =(DataTableWgt  *)anyTab;
        QFile TextFile(fullPath);
        QString Text;
        QStringList section;
        if(TextFile.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&TextFile);
            emit ShowMsgRequest("","Thread is runing to parse "+fullPath);

            int i=0;
            Text= stream.readLine();
            section =Text.split(QRegExp("\t") );
            int Col=section.length();

            tableTab->setColumnCount(Col);
            while(!stream.atEnd())
            {
                if(section.length()!=Col   ) {
                      emit ShowMsgRequest("Error:","Parse  as table  failed!");
                      break;
                }else{
                    tableTab->setRowCount(i+1);
                }
                for(int j=0;j<Col;++j)     tableTab->setCellContent(i,j,section.at(j));
                ++i;
                Text= stream.readLine();
                section =Text.split(QRegExp("\t") );
            }
            TextFile.close();
             wait();
        }else{
            QMessageBox::information(NULL, QString("Open Promote"  ), QString("Can't Open "+ fullPath  ));
        }

    }

     void  ReadTextFile()
    {
        QFile TextFile(fullPath);
        QString Text;
        if(TextFile.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&TextFile);
            emit ShowMsgRequest("","Thread is runing to open "+fullPath);
            while(!stream.atEnd())
            {
                Text= stream.readLine();
                textTab->append(Text+"\n");
            }
            TextFile.close();
             wait();

        }else{
            QMessageBox::information(NULL, QString("Open Promote"  ), QString("Can't Open <"+ fullPath +">" ));
        }
    }

signals:
       void ShowMsgRequest(QString Type,QString message);
private:
    QString fullPath;
    TextDataWgt *textTab;
    QWidget *anyTab;
    void (UtilReadTextFile :: *task) ();
public:
    void run()
    {
            if(task)
            {
                cout<<"Thread is runing to open "<<fullPath.toStdString()<<endl;
                (this->*task)  (); //运行任务
                task=nullptr;
            }

    }

};
/////////////////////////////////////////////////////////////////////////////////////////////////
// 带Q_OBJECT 的类声明头文件应该放在.h 文件中
// 避免出现：error: LNK2001: 无法解析的外部符号
//   "public: virtual struct QMetaObject const * __cdecl svmReportor
/////////////////////////////////////////////////////////////////////////////////////////////////
class svmReportor:public QObject
{
 Q_OBJECT
signals:
     void ShowMsgRequest(AiMsg msg);
     void ShowMsgRequest(QString type,QString message);

public:

     svmReportor(){}
     void svmSendMessage(QString type,QString message)
   {
          ShowMsgRequest(type, message);
   }
     void svmSendMessage(AiMsg msg)
   {
           ShowMsgRequest(msg);
           cout<<"fuck!"<<endl;
   }

};


#endif
