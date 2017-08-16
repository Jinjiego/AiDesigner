#include "BLL-projectsmanagertree.h"




BLLProjectsManagerTree::BLLProjectsManagerTree(QWidget *parent) :
    QTreeWidget(parent)
{

    myProjectDir= "G:\\projects\\Qt\\AiProjects";

    setColumnCount(1);
    //setHeaderLabel(tr("Project Name"));
    setHeaderHidden(true);

    menu= new QMenu();

    menu->addAction(new QAction(tr("close"),this));

    addProject(QString("Project1"));

    addProject(QString("Project2"));

    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(ItemClicked(QTreeWidgetItem *,int)  ));
    connect(this,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),SLOT(ItemDoubleClicked(QTreeWidgetItem*,int) )  );

    //////start();

}


TreeItem * BLLProjectsManagerTree::addChild(QTreeWidgetItem *parent,QString name,QIcon icon,myItemType isLeaf){

       TreeItem * Child=new TreeItem(parent, QStringList(name),isLeaf);
       Child->setIcon(0,icon);
       Child->setExpanded(true);

       parent->addChild(Child);

       return Child;

}


void  BLLProjectsManagerTree:: addProject(  QString ProjectName){

    CreateDir(myProjectDir+ProjectName);


    TreeItem *Project=new  TreeItem(this,  QStringList(ProjectName),Node );
    Projects.append(Project);

    addChild(Project,QString("Data"),QIcon(":/res/Images/folder_close.png"),Node);
    addChild(Project,QString("Model"),QIcon(":/res/Images/folder_close.png"),Node);

    addChild(Project,QString("Results"),QIcon(":/res/Images/folder_close.png"),Node);

    CreateDir(myProjectDir+ProjectName+"\\"+QString("Data"));
    CreateDir(myProjectDir+ProjectName+"\\"+QString("Model"));
    CreateDir(myProjectDir+ProjectName+"\\"+QString("Result"));


}

void  BLLProjectsManagerTree:: ItemClicked(QTreeWidgetItem*Item,int index){

    TreeItem * item=(TreeItem*)Item;

    if( NULL==item->parent()  ){
        //
         cout<< QString(item->text(index) ).toStdString()<<"\n";
    }else if(item->NodeType==Leaf ){
        //QMessageBox::information(NULL, QString("click Promote"  ), QString(item->text(index)  ));

        cout<<item->NodeType<<endl;

    }

}
void BLLProjectsManagerTree:: ItemDoubleClicked(QTreeWidgetItem*Item,int index){

    TreeItem * item=(TreeItem*)Item;
    if(item->NodeType==Leaf ){

         emit ShowDataRequest(myProjectDir+PathCur2Root( Item ),"Text" );

    }


}

void BLLProjectsManagerTree::contextMenuEvent(QContextMenuEvent *event){

      QPoint p=  event->pos();
      RightKeyClickedItem= (TreeItem *)itemAt(p);

     if(RightKeyClickedItem){

        menu->clear();


        QAction * action =new QAction(tr("rename"),this);

        connect(action,SIGNAL(triggered(bool)),SLOT( Rename() ) );
        menu->addAction(action );


        if( RightKeyClickedItem->parent() ==NULL){//if the selected item is Root


        }
        if (RightKeyClickedItem->NodeType==Node){
            QAction * action= new QAction(tr("add a folder"),this);
            connect(action,SIGNAL(triggered(bool)),SLOT(AddaFolder()  ));
            menu->addAction(action);

            action=new QAction(tr("add a csv file"),this);
            connect(action,SIGNAL(triggered(bool)) , SLOT(AddCsv() ));
            menu->addAction(action );

            action=new QAction(tr("add an existing file"),this);
            menu->addAction(action);


        }else{

            QAction * action= new QAction(tr("delete"),this);
            connect(action,SIGNAL(triggered(bool)),SLOT( deleteItem()  ));
            menu->addAction(action);

        }


        event->accept();
        menu->exec(QCursor::pos());

     }
}
void BLLProjectsManagerTree:: deleteItem(){



}


void BLLProjectsManagerTree::AddaFolder(){


     RightKeyClickedItem->setExpanded(true);

     TreeItem * newNode= addChild(RightKeyClickedItem,QString("NewFolder"),QIcon(":/res/Images/folder_close.png"),Node);

     editItem(newNode);


}
void BLLProjectsManagerTree:: Rename(){

    QTreeWidgetItem * selected = currentItem();

    selected->setFlags(selected->flags() | Qt::ItemIsEditable );

    editItem( selected  );

}


void BLLProjectsManagerTree:: closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint){


    QTreeWidgetItem * changeedNode= currentItem();


    QString path(changeedNode->text(0) );

    for(QTreeWidgetItem *root=changeedNode->parent();root;root=root->parent() ){
        path=root->text(0)+"\\"+path;
    }

    CreateDir(myProjectDir+path);


    QTreeWidget:: closeEditor(editor,hint);

}
 QString BLLProjectsManagerTree:: PathCur2Root(QTreeWidgetItem *cur){

     QString path("\\"+cur->text(0) );

     for(QTreeWidgetItem *root=cur->parent();root;root=root->parent() ){
         path="\\"+root->text(0)+path;

     }
     return path;

 }
void  BLLProjectsManagerTree:: AddCsv(){

    TreeItem *seled= (TreeItem * )currentItem();


    TreeItem * file = addChild(seled,QString("NewTxt.csv"),QIcon(),Leaf);

    QFile newTxt(myProjectDir+PathCur2Root(file ));

    cout<<"Create>>>" <<QString(myProjectDir+PathCur2Root(file )).toStdString()<<endl;

    newTxt.open(QFile::Append);


}
