#ifndef AISVM_H
#define AISVM_H
#include"svm/svm.h"
#include "CplusHeader.h"
#include <QThread>
#include "baseWgt/BASE-Util.hpp"
#include "baseWgt/BASE-Type.hpp"
#include "Solvers/Learner.hpp"
#define TRAINDATA_SET  1
#define  PARAM_SET 2
#define  SOLVED  4

using namespace libsvm;
class AiSVM:public Learner
{
  Q_OBJECT
 public:
    AiSVM(){
        ModelStatus=0;
        svmProb=new svm_problem;
        svmParams=new svm_parameter;
        trainningAble=0;
        libsvm::svm_Reportor=new svmReportor;
    }
    ~AiSVM(){ freeMemory();}
    STATUS  setTrainingData(string fileName);
    void initDefaultParams();
    void freeMemory();

    void train();

    void  setTrainingData();

    void run()
    {
       if(trainningAble==0) /// everything is ok then to run!
             svmModel= svm_train(svmProb,svmParams);
       else
            emit ShowMsgRequest(AiMsg(Error,MSG_TYPE_TEXT,0,QString("Not Ready! ") ));
    }
signals:

public:

    int ModelStatus;

    QString trainingDataSetPath;
    svm_problem *svmProb;
    svm_parameter *svmParams;
    svm_model *svmModel;


};


#endif // AISVM_H
