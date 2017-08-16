
#ifndef BASEUTIL
#define BASEUTIL



#include<QDir>
#include<QThread>
#include<QTextStream>
#include<iostream>
#include<QMessageBox>


using namespace std;


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

class UtilReadTextFile:public QThread

{
public:
   QString *Text;

   UtilReadTextFile(){

   }
   ~UtilReadTextFile(){
         terminate();

   }
   void ReadTextFileFrom(QString fullpath,QString *content){
        fullPath=fullpath;
        Text=content;

        start();

    }
   void run(){

       QFile TextFile(fullPath);

       if(TextFile.open(QIODevice::ReadOnly)){
            QTextStream stream(&TextFile);
            cout<<"Reading file from: "<< fullPath.toStdString() <<endl;
             *Text=stream.readAll();
            cout<<"Content: "<<Text->toStdString()<<endl;
            TextFile.close();
       }else{
          QMessageBox::information(NULL, QString("Open Promote"  ), QString("Can't Open "+ fullPath  ));
       }
   }
private:

   QString fullPath;
};


#endif
