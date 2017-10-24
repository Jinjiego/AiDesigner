#ifndef MLXGBOOST_H
#define MLXGBOOST_H
#include "Solvers/Learner.h"
#include "XGBoost/xgboosttest.h"
//主要封装XGBoost 进行数据挖掘的流程
class MLXGBoost:public Learner
{
public:

    MLXGBoost();
    ~MLXGBoost();
    void  setTrainingData(){}
    void setTrainingData(QString fileName);



    int  XGBoostDemo();
private :
    DMatrixHandle h_train[1];
    BoosterHandle h_booster;


};

#endif // MLXGBOOST_H
