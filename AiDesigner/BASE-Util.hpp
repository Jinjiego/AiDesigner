
#ifndef BASEUTIL
#define BASEUTIL



#include<QDir>
#include<iostream>
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

#endif
