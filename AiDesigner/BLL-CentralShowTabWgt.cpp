#include "BLL-CentralShowTabWgt.h"
#include "BASE-DataTableWgt.h"


CentralShowTabWgt::CentralShowTabWgt()
{
    Plot* plot= new Plot();
    TabList.append(plot);

    plot->start();

    addTab(plot," figure ");
    setTabsClosable(true);

    addTab(new DataTableWgt(10,10)," Data Table ");
    QMainWindow * aTab=new QMainWindow(this);

    TabList.append(aTab);
    aTab->setCentralWidget(new TextDataWgt());
    addTab(aTab ,"Text");
    connect(this,SIGNAL(tabCloseRequested(int)),SLOT(CloseTab(int) ) );


}
void CentralShowTabWgt:: CloseTab(int index){
      removeTab(index);

}







