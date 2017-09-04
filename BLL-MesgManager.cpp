#include "BLL-mesgmanager.h"

BLLMesgManager::BLLMesgManager(QWidget *parent,QString initMessage) :
    QListWidget(parent)
{
      MessageItem=new QListWidgetItem(initMessage,this);
      insertItem(1,MessageItem);
}
void BLLMesgManager::RecvAMessage(QString type,QString message){
            addItem(message);
}


 void BLLMesgManager::RecvAMessage(AiMsg msg)
 {
        cout<<" RecvAMessage(AiMsg msg)"<<endl;
         if(msg.Type==MSG_TYPE_TEXT) //接受一个文本消息
         {
                addItem( "The curent thread : "+QString::number( (long) msg.senderId ) );
                for( auto c:msg.Content)
                {
                    addItem(c);
                }
         }

 }
