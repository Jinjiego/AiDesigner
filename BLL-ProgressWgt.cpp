#include "BLL-ProgressWgt.h"

BLLProgressWgt::BLLProgressWgt(QWidget *parent):QTreeWidget(parent)
{
    setColumnCount(1);
    setHeaderHidden(true);
    activatedProjectTree=new RuningProgress(this,"Project1" );
    activatedProjectRoot=activatedProjectTree->activatedProject;

    setItemWidget(activatedProjectTree->progressItem,0,activatedProjectTree->progressBar );

    activatedProjectRoot=activatedProjectTree->activatedProject;

   // Project->addChild();



}
void  BLLProgressWgt::RecvAMessage(QString type, QString message){
      if(type=="Progress"){

             activatedProjectTree->progressBar->setValue(message.toInt() );
      }
}
