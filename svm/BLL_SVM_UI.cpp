#include "BLL_SVM_UI.h"

BLL_SVM_UI::BLL_SVM_UI(QWidget *parent) : GuiLearner(parent)
{

         svm=nullptr;



}
void BLL_SVM_UI::init(){

     cellfont =new QFont("Times New Roman",12);

      initTrainingDatasetItem(0);
     initParamTable();
     initTrainDataTable();
     initTestDataTable();
     cout<< " The current object of type BLL_SVM_UI is at " <<QThread::currentThreadId()<<endl;
     //*********create model tree****************
     QTreeWidget  * centralWidget= new QTreeWidget(this);
     centralWidget->setHeaderHidden(true);

     QTreeWidgetItem *  svmModel =new QTreeWidgetItem(centralWidget,QStringList()<<"svm Model");
     svmModel->setFont(0,QFont("Times New Roman",13) );
     QTreeWidgetItem *  TrainDataPar =new QTreeWidgetItem(svmModel,QStringList()<<"training Data set");
     TrainDataPar->setFont(0,QFont("Times New Roman",13)  );
     QTreeWidgetItem *  TrainDataNode =new QTreeWidgetItem(TrainDataPar);

     QTreeWidgetItem *  TestDataParent =new QTreeWidgetItem(svmModel,QStringList()<<"Test Data");
       TestDataParent->setFont(0,QFont("Times New Roman",13)  );
     QTreeWidgetItem *  TestDataNode  =new  QTreeWidgetItem(TestDataParent);
     QTreeWidgetItem *  paraTbParent =new QTreeWidgetItem(svmModel,QStringList()<< "Parameters");
     paraTbParent->setFont(0,QFont("Times New Roman",13)  );
     QTreeWidgetItem *  paraTbNode =new QTreeWidgetItem(paraTbParent);

     QTreeWidgetItem *  evalWgtPar =new QTreeWidgetItem(svmModel,QStringList()<<"Model Evalution");
      evalWgtPar->setFont(0,QFont("Times New Roman",13)  );
     QTreeWidgetItem *  evalWgtNode =new QTreeWidgetItem(evalWgtPar);

     svmModel->setExpanded(true);
     //*********set model tree****************
     centralWidget->setItemWidget(TrainDataNode,0,TrainingDataTable);
     centralWidget->setItemWidget(paraTbNode,0,paramsTable   );
     centralWidget->setItemWidget(TestDataNode, 0 ,TestDataTable );

     evalWgt= new  ModelEvaluator_UI();
     centralWidget->setItemWidget(evalWgtNode,0,evalWgt);
       //*********add model tree into the window****************

     setCentralWidget(centralWidget);

     //********** 显示模型的评测结果************************
     qRegisterMetaType<vector<vector<double> > >("vector<vector<double> >");
     qRegisterMetaType<vector<double> >("vector<double>");

     connect(svm,SIGNAL(SendEvalutionData(vector<vector<double> >,vector<double>)),
                   evalWgt,SLOT(receive_evalData(vector<vector<double> >,vector<double>)  )  );



}

void BLL_SVM_UI::init2()
{
    //zoomTable=new zoomAbleTableWgt(this);
}

void BLL_SVM_UI:: initTrainingDatasetItem(int row)
{
       emit getActivateProjectTreeLeafRequest( 0 );

}
void BLL_SVM_UI:: receive_trainingData(QString dir, QStringList path)
{
        Dir=dir;
        trainingDataItem =new AiQComboBox();
        trainingDataItem->addItems(path);
        TestDataItems=new AiQComboBox();
        TestDataItems->addItems(path);
}

void BLL_SVM_UI:: initTestDataTable()
{
    TestDataTable=new DataTableWgt(1,3);
    TestDataTable->setColumnWidth(0,200);
    TestDataTable->setColumnWidth(1,300);
    TestDataTable->setColumnWidth(2,600);
    TestDataTable->setMaximumHeight(100);
    TestDataTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );
    // initTrainingDatasetItem( 0 );
    if(TestDataItems)
    {
        QTableWidgetItem * var =new QTableWidgetItem("Test data");
        QTableWidgetItem * Comment =new QTableWidgetItem("Test Data set");
        addTableRow(TestDataTable, 0,var,TestDataItems,Comment);
    }
    setTableAttributes(TestDataTable);
}
void BLL_SVM_UI:: initTrainDataTable()
{
    TrainingDataTable=new DataTableWgt(1,3);
    TrainingDataTable->setColumnWidth(0,200);
    TrainingDataTable->setColumnWidth(1,300);
    TrainingDataTable->setColumnWidth(2,600);
    TrainingDataTable->setMaximumHeight(100);
    TrainingDataTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );
    if(trainingDataItem)
    {
        QTableWidgetItem * var =new QTableWidgetItem("Training data");
        QTableWidgetItem * Comment =new QTableWidgetItem("Training Data set");
        addTableRow(TrainingDataTable, 0,var,trainingDataItem,Comment);
    }
    setTableAttributes(TrainingDataTable);
}

void BLL_SVM_UI:: initParamTable()
{

    paramsTable=new DataTableWgt();
    paramsTable->setMinimumHeight(450);
    int start=0;
    paramsTable->setColumnCount(3);
    paramsTable->setRowCount(start+ 12);
    paramsTable->setHorizontalHeaderLabels(QStringList()<<"Parameters Name"<<"Values"<<"Comment" );
    //  paramsTable->horizontalHeader()->setVisible(false);

    paramsTable->setColumnWidth(0,200);
     paramsTable->setColumnWidth(1,300);
      paramsTable->setColumnWidth(2,600);
  //  paramsTable->horizontalHeader()->setStretchLastSection(true);
 //   paramsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    // paramsTable->setSpan(0,0,0,2);
    ///************************************
    ///  0 设置训练集
    /// *************************************


    ///************************************
    ///  1 求解问题类型
    /// *************************************
    QTableWidgetItem * var =new QTableWidgetItem(VNAME_D(svm_parameter::svm_type));
    svm_type_comb =new AiQComboBox();

    svm_type_comb->setBackgroundRole(QPalette::ColorRole::Light);
    svm_type_comb->addItems( QStringList () <<"C_SVC"<<" NU_SVC"<<" ONE_CLASS"<<"EPSILON_SVR"<<"NU_SVR" );
    QTableWidgetItem * Comment =new QTableWidgetItem("type of svm algorithm");
    addTableRow(paramsTable,start+0,var,svm_type_comb,Comment);

    ///************************************
    /// 2  核函数类型
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::kernel_type));
    kernel_type_comb =new AiQComboBox();
    kernel_type_comb->setBackgroundRole(QPalette::ColorRole::Light);
    kernel_type_comb->addItems( QStringList () << VNAME(LINEAR)<<VNAME(POLY)<<VNAME(RBF)<<VNAME(SIGMOID)<<VNAME(PRECOMPUTED ));

    Comment =new QTableWidgetItem("type of svm kernel");
    addTableRow(paramsTable,start+1,var,kernel_type_comb,Comment);

    ///************************************
    /// 3  多项式核函数度
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::degree));
    degree_linedit =new QLineEdit();
    degree_linedit->setText("3");
    Comment =new QTableWidgetItem("The degree of polynomial  kernel");
    addTableRow(paramsTable,start+2,var,degree_linedit,Comment);


    ///************************************
    ///   4 多项式核函数的参数coef0
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::coef0 ));
    coef0_linedit =new QLineEdit();
    coef0_linedit->setText("0");

    Comment =new QTableWidgetItem("The coef0 of polynomial  kernel");
    addTableRow(paramsTable,start+3,var,coef0_linedit,Comment);

    ///************************************
    ///   5.    1/num_features，rbf核函数参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::gamma ) );
    gamma_linedit =new QLineEdit();
    gamma_linedit->setText("0.5");

    Comment =new QTableWidgetItem("The γ of polynomial  kernel, for kernel rbf ");
    addTableRow(paramsTable,start+4,var,gamma_linedit,Comment);

    ///************************************
    ///    6  nu-svc的参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::nu ) );
    nu_linedit =new QLineEdit();
    nu_linedit->setText("0.5");
    Comment =new QTableWidgetItem(tr("The parameter of  svc for svm_type=svc ") );
    addTableRow(paramsTable,start+5,var,nu_linedit,Comment);

    ///************************************
    ///    nu-svc的参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::C ) );
    C_linedit =new QLineEdit();
    C_linedit->setText("10");

    Comment =new QTableWidgetItem(tr("The punishment coefficients of regularization ") );
    addTableRow(paramsTable,start+6,var,C_linedit,Comment);
    ///************************************
    ///   eps 收敛精度
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::eps ) );
    eps_linedit =new QLineEdit();
    eps_linedit->setText("1e-3");

    Comment =new QTableWidgetItem(tr("convergence precision ") );
    addTableRow(paramsTable,start+7,var,eps_linedit,Comment);


    ///************************************
    ///  求解的内存缓冲 100MB
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::cache_size ) );
    cache_size_comb =new AiQComboBox();
    cache_size_comb->addItems(QStringList()<<"100MB"<<"80MB"<<"50MB");

    Comment =new QTableWidgetItem(tr("cache size of  memory ") );
    addTableRow(paramsTable,start+8,var,cache_size_comb,Comment);
    ///************************************
    ///  p
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::p ) );
    p_linedit =new QLineEdit();
    p_linedit->setText("0.1");

    Comment =new QTableWidgetItem(tr(" for EPSILON_SVR") );
    addTableRow(paramsTable,start+9,var,p_linedit,Comment);

    ///************************************
    ///  shrinking
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::shrinking ) );
    shrinking_linedit =new QLineEdit();
    shrinking_linedit->setText("1");


    Comment =new QTableWidgetItem(tr(" use the shrinking heuristics ") );
    addTableRow(paramsTable,start+10,var,shrinking_linedit,Comment);

    ///************************************
    ///  probability: //1表示训练时生成概率模型，0表示训练时不生成概率模型，用于预测样本的所属类别的概率
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::probability ) );
    probability_comb =new AiQComboBox();
     probability_comb->addItems(QStringList()<<"0"<<"1");

    Comment =new QTableWidgetItem(tr(" 1 denotes  that svm will  generating probability model and 0 denotes will not ") );
    addTableRow(paramsTable,start+11,var,probability_comb,Comment);

    ///************************************
    ///  nr_weight 类别权重
    /// ************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::nr_weight ) );
    nr_weight_linedit =new QLineEdit();
    nr_weight_linedit->setText("0");

    Comment =new QTableWidgetItem(tr(" type wight ") );
    addTableRow(paramsTable, start+12,var,nr_weight_linedit,Comment);

    // svmParams->weight = NULL;    //样本权重
    // svmParams->weight_label = NULL;    //类别权重

    //*********************************************
    //** set font
    //*********************************************
    setTableAttributes(paramsTable);


}
void BLL_SVM_UI::setTableAttributes( DataTableWgt * Table){

     int m= Table->rowCount();
     int n=Table->columnCount();

    for(int i=0;i<m;++i)
        for(int j=0;j<n;++j){
             QTableWidgetItem *itemWgt= Table->item(i,j);
             if(itemWgt){
                      itemWgt->setTextAlignment(Qt::AlignLeft);
                      itemWgt->setFont(*cellfont);
             }
        }
    Table->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(0)->setFont(*cellfont);
    Table->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(1)->setFont(*cellfont);
    Table->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
    Table->horizontalHeaderItem(2)->setFont(*cellfont);

}



void BLL_SVM_UI::addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment )
{
      table->setItem(row,0,var);
      table->setItem(row,1,val);
      table->setItem(row,2,comment);

}
void BLL_SVM_UI::addTableRow(DataTableWgt * table,int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment )
{
      table->setItem(row,0,var);
      table->setCellWidget(row,1,val);
      table->setItem(row,2,comment);

}

void  BLL_SVM_UI:: updateParamFromUI()
{
             if(svm && svm->svmParams){
                    svm->setrainningAble(0);
                    svm->trainingDataSetPath=Dir+ trainingDataItem->currentText();
                    svm->predictDataSetPath=Dir+TestDataItems->currentText();

                    //*******************************************
                    svm->svmParams->svm_type = svm_type_comb->currentIndex();
                    svm->svmParams->cache_size=cache_size_comb->currentText().mid(0,2).toDouble();
                    svm->svmParams->C =C_linedit->text().toDouble();
                    svm->svmParams->coef0 =coef0_linedit->text().toDouble();
                    svm->svmParams->degree= degree_linedit->text().toInt();
                    svm->svmParams->eps=eps_linedit->text().toDouble();
                    svm->svmParams->gamma=gamma_linedit->text().toDouble();
                    svm->svmParams->kernel_type=kernel_type_comb->currentIndex();
                    svm->svmParams->nu=nu_linedit->text().toDouble();
                    svm->svmParams->probability=probability_comb->currentIndex();
                    svm->svmParams->shrinking=shrinking_linedit->text().toDouble();
                    svm->svmParams->nr_weight=nr_weight_linedit->text().toDouble();
                    svm->svmParams->weight=NULL;
                    svm->svmParams->weight_label=NULL;
                    QString message ="Update parameters of svm model successfully! ";
                    ShowMsgRequest(AiMsg(Ok,MSG_TYPE_TEXT,0,message) );

             }else{
                   QString message="The svm instance has not been allocated yet! ";
                   ShowMsgRequest( AiMsg(Error,MSG_TYPE_TEXT,0 ,message ) );
             }
 }







