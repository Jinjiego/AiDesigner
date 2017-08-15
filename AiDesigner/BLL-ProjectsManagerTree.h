#ifndef BLLPROJECTSMANAGERTREE_H
#define BLLPROJECTSMANAGERTREE_H

#include <QTreeWidget>
#include <QVector>
#include<QMessageBox>
#include<QMenu>
#include <QtEvents>
#include<iostream>
#include"BASE-Util.hpp"
#include<QThread>

using namespace std;

enum  myItemType {Node,Leaf} ;


//**********************************************
class TreeItem : public QTreeWidgetItem
{

public:

    myItemType NodeType;
    TreeItem(QTreeWidgetItem *parent, const QStringList &strings,myItemType type):
        QTreeWidgetItem(parent,strings)
    {
         NodeType=type;
    }
    TreeItem(QTreeWidget *parent, const QStringList &strings,myItemType type):
        QTreeWidgetItem(parent,strings)
    {
         NodeType=type;

    }


};


//**********************************************


class BLLProjectsManagerTree : public QTreeWidget
{
    Q_OBJECT


private:
    QMenu * menu;
    QString myProjectDir;

public:
    explicit BLLProjectsManagerTree(QWidget *parent);
    void  addProject(QString ProjectName);

    TreeItem * addChild(QTreeWidgetItem *parent,QString name,QIcon icon,myItemType type);

signals:

public slots:

    void ProjectClicked(QTreeWidgetItem*,int);
    void AddaFolder();
    void AddCsv();
    void Rename();
    void deleteItem();


protected :

   void run();
   virtual void contextMenuEvent(QContextMenuEvent *);
   void closeEditor(QWidget *editor, QAbstractItemDelegate::EndEditHint hint);
private:
              QVector<QTreeWidgetItem*>  Projects;
              TreeItem * RightKeyClickedItem;
               QString PathCur2Root(QTreeWidgetItem *cur);


};
///////////////////////////////////////////////////
// QString BLLProjectsManagerTree::myProjectDir("./");




#endif // BLLPROJECTSMANAGERTREE_H
