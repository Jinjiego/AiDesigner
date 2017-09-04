#ifndef LEARNER_H
#define LEARNER_H
#include <QThread>
#include <QMainWindow>
#include "baseWgt/BASE-Type.hpp"
class Learner:public  QThread  //学习器基类
{
    Q_OBJECT
signals:
     void ShowMsgRequest(AiMsg msg);

  protected:
     int trainningAble;

public:
      virtual  void  train(){};
      virtual void  setTrainingData(){ };

};

class GuiLearner :public QMainWindow{

     Q_OBJECT
signals:
         void ShowMsgRequest(AiMsg msg);

public:
    GuiLearner(){}
    GuiLearner(QWidget*parent):QMainWindow(parent){}
    virtual void   updateParamFromUI(){};

    Learner *learner;


};


struct LearnerUI
{

     GuiLearner *Ui;
     LearnerUI(QMainWindow *ui=nullptr ){

         Ui=(GuiLearner * )ui;
     }

};



#endif
