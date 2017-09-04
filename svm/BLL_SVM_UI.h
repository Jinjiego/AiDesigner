#ifndef BLL_SVM_UI_H
#define BLL_SVM_UI_H

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include "AiSvm.h"
#include "baseWgt/BASE-Util.hpp"
#include "baseWgt/BASE-DataTableWgt.h"
#include "baseWgt/BASE-zoomAbleTableWgt.h"
#include <QTableView>
#include <QHeaderView>
#include <QFont>
#include <QGridLayout>
#include <QAction>
#include "BLL-ProjectsManagerTree.h"


class BLL_SVM_UI : public GuiLearner
{
    Q_OBJECT
public:
      explicit BLL_SVM_UI(QWidget *parent = nullptr);


       AiSVM * getSVMInstance(){return svm;}
        void addTableRow(int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment );
        void addTableRow(int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment );

        DataTableWgt * paramsTable;
        zoomAbleTableWgt *zoomTable;
        void setLearner(Learner *learner)
        {
            this->learner=learner;
            this->svm=(AiSVM*)learner  ;

        }
        void init();
        void train(){ if(svm) svm->train();    }
        void updateParamFromUI();


signals:
        void getActivateProjectTreeLeafRequest(int id);

public slots:

        void receive_svm_type(int svm_type);
        void receive_kernel_type(int kernel_type);
        void receive_degree(QString d);
        void  receive_coef0(QString coef0);
        void  receive_gamma(QString gama);
        void  receive_nu_svc(QString nu);
        void  receive_eps(QString eps);
        void  receive_cache_size(QString cache_size);
        void  receive_p(QString p);

        void  receive_shrinking(QString shrinking);

        void  receive_probability(int  probability) ;
        void receive_trainingData(QString dir,QStringList path);
        void set_trainingData(QString dataRelativePath);


private:
         QComboBox * svm_type_comb,*kernel_type_comb ,*cache_size_comb,*probability_comb;

         QLineEdit  * degree_linedit,*coef0_linedit,*gamma_linedit,*nu_linedit,*C_linedit,*eps_linedit,*p_linedit,*shrinking_linedit,*nr_weight_linedit;

         QComboBox * trainingDataItem;
         QString Dir;

        AiSVM * svm;   //这是一个辅助指针,基类中有一个Learner 指针
        QFont  *cellfont;
        void initTrainingDatasetItem(int row);
        void initParamTable();
};

#endif // BLL_SVM_UI_H
