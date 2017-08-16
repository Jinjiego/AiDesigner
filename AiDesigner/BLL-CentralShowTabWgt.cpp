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
void CentralShowTabWgt::ShowData(QString fullpath,QString type){


  if("Text"==type){
       QMainWindow * aTab=new QMainWindow(this);
       TabList.append(aTab);

       TextDataWgt * TextTab= new TextDataWgt();

       UtilReadTextFile reader;
       QString Text;
       reader.ReadTextFileFrom(fullpath,&Text);


       cout<<"Got: "<<Text.toStdString()<<endl;

       TextTab->setText( Text );
       aTab->setCentralWidget(TextTab);
       addTab(aTab ,"Text");
       setCurrentWidget(aTab);



  }else if("Table"==type){


  }


}








