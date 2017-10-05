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
#include "baseWgt/BASE-AiQComboBox.h"
#include "ModelEvalution/BLL-ModelEvaluator_UI.h"
class BLL_SVM_UI : public GuiLearner
{
    Q_OBJECT
public:
        explicit BLL_SVM_UI(QWidget *parent = nullptr);

        DataTableWgt * paramsTable,*TrainingDataTable ,*TestDataTable, *EvalutionTable;
        ModelEvaluator_UI  *evalWgt;
        zoomAbleTableWgt *zoomTable;

        AiSVM * getSVMInstance(){return svm;}
         void addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment );
         void addTableRow( DataTableWgt * table ,  int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment );
         void setTableAttributes( DataTableWgt * Table);

        void setLearner(Learner *learner)
        {
            this->learner=learner;
            this->svm=(AiSVM*)learner  ;

        }
        void init();
        void init2();
        void train(){ if(svm) svm->train();    }
        void updateParamFromUI();


signals:
        void getActivateProjectTreeLeafRequest(int id);

public slots:
         void receive_trainingData(QString dir,QStringList path);

private:
         AiQComboBox * svm_type_comb,*kernel_type_comb ,*cache_size_comb,*probability_comb;

         QLineEdit  * degree_linedit,*coef0_linedit,*gamma_linedit,*nu_linedit,*C_linedit,*eps_linedit,*p_linedit,*shrinking_linedit,*nr_weight_linedit;

         AiQComboBox * trainingDataItem,*TestDataItems;
         QString Dir;

        AiSVM * svm;   //这是一个辅助指针,基类中有一个Learner 指针
        QFont  *cellfont;
        void initTrainingDatasetItem(int row);
        void initParamTable();
        void initTestDataTable();
        void initTrainDataTable();


};

#endif // BLL_SVM_UI_H
