#ifndef BASETYPE_H
#define BASETYPE_H
#include<QWidget>
enum STATUS{Ok,Error,Warning};


struct TabData{
     QWidget *wgt;
     QString ID;
     QString Label;
     TabData(QWidget* w=0,QString id="",QString label=""):wgt(w),ID(id),Label(label){}
};
enum MsgType{MsgType_Text,MsgType_Progress,};

class Msg{
public:

        MsgType Type;
};



#endif // BASETYPE_H
