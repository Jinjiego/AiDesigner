#ifndef BLLCENTRALSHOWTABWGT_H
#define BLLCENTRALSHOWTABWGT_H
#include <QTabWidget>
#include <QList>
#include "BASE-Plot.h"
#include "BASE-DataTableWgt.h"
#include "BASE-TextDataWgt.h"
#include<iostream>
using namespace std;

class CentralShowTabWgt : public QTabWidget
{
    //这个类的对象放到主框架的中心DockWidget 中

    Q_OBJECT

public:
    CentralShowTabWgt();
protected:
public slots:

    void  CloseTab(int index);

private:
    QList <QWidget *> TabList;

};

#endif // BLLCENTRALSHOWTABWGT_H
