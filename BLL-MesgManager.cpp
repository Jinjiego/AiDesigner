#include "BLL-mesgmanager.h"

BLLMesgManager::BLLMesgManager(QWidget *parent,QString initMessage) :
    QListWidget(parent)
{
      MessageItem=new QListWidgetItem(initMessage,this);
      insertItem(1,MessageItem);
}

void  BLLMesgManager:: RecvAMessage(QString type,QString message){


      addItem(message);

}
