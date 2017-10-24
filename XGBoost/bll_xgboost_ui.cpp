#include "bll_xgboost_ui.h"

BLL_XGBoost_UI::BLL_XGBoost_UI()
{

   initParamTable();
  this->init();

}
void BLL_XGBoost_UI::initParamTable(){
    paramsTable=new DataTableWgt();
    paramsTable->setStyleSheet("border:none;");
    int start=0;
    paramsTable->setColumnCount(3);
    paramsTable->setRowCount(start+ 8);
    paramsTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );
    //  paramsTable->horizontalHeader()->setVisible(false);

    paramsTable->setColumnWidth(0,200);
    paramsTable->setColumnWidth(1,300);
    paramsTable->setColumnWidth(2,600);



}
