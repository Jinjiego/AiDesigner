#ifndef BASEDATATABLEWGT_H
#define BASEDATATABLEWGT_H

#include <QTableWidget>
#include<QTextBrowser>
#include<QTextCodec>

class DataTableWgt : public QTableWidget
{
    //提供一个显示数据的表格类，其对象可放在主框架的 CentralShowTabWgt 中显示
    Q_OBJECT

public:
    DataTableWgt(int row,int col);



};

#endif // BASEDATATABLEWGT_H
