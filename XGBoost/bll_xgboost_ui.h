#ifndef BLL_XGBOOST_UI_H
#define BLL_XGBOOST_UI_H
#include "Solvers/Learner.h"

class BLL_XGBoost_UI:public GuiLearner
{

public:


    BLL_XGBoost_UI();
    void initParamTable();
};

#endif // BLL_XGBOOST_UI_H
