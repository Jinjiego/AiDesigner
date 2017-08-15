#include "BLL-mesgmanager.h"

BLLMesgManager::BLLMesgManager(QWidget *parent,QString initMessage) :
    QListWidget(parent)
{
      QListWidgetItem*firstMessage=new QListWidgetItem(initMessage,this);

      insertItem(1,firstMessage);


}
