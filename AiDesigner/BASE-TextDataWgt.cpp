#include "BASE-TextDataWgt.h"

TextDataWgt::TextDataWgt()
{


    setUtf8(true);
    //setLexer(new QsciLexer());
    zoomIn(4);

    setMarginBackgroundColor(1, QColor("#0000ff"));
    setMarginWidth(1,"000000");

    setMarginLineNumbers(1,true);
    SendScintilla(QsciScintilla::SCI_SETHSCROLLBAR,0);
    setCaretLineVisible(true);


}
void TextDataWgt:: keyPressEvent(QKeyEvent *event)
{
    PressdKey=event->key();
    cout<<PressdKey <<endl;
    QsciScintilla::keyPressEvent(event);//perform slot of its base class

}
 void TextDataWgt:: keyReleaseEvent(QKeyEvent *event){

     PressdKey=INT_MIN;
     QsciScintilla::keyReleaseEvent(event);
 }

void TextDataWgt:: wheelEvent(QWheelEvent *event){
  if(16777249 ==PressdKey )
  {
     if ( event->delta()>0 ){
         zoomIn();
      }else if(event->delta()<0){
        zoomOut();
      }
  }else{
      QsciScintilla::wheelEvent(event);

  }
}

