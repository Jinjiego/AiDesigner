#include "BLL_SVM_UI.h"

BLL_SVM_UI::BLL_SVM_UI(QWidget *parent) : GuiLearner(parent)
{

}
void BLL_SVM_UI::init()
{

    cellfont =new QFont("Times New Roman",15);
    svm=nullptr;

     cout<< " The current object of type BLL_SVM_UI is at " <<QThread::currentThreadId()<<endl;

    QWidget * centralWidget=new QWidget(this);
    QVBoxLayout * mainLayout =new QVBoxLayout();

    initParamTable();
    mainLayout->addWidget(paramsTable);

    centralWidget->setLayout(mainLayout);
    //zoomTable=new zoomAbleTableWgt(this);

    QWidget *t=new QWidget();
    t->addAction(new QAction("TEST"));
    setCentralWidget(centralWidget);
}

void BLL_SVM_UI:: initTrainingDatasetItem(int row){
      if(paramsTable){
          QTableWidgetItem * var =new QTableWidgetItem("training Data set");
          trainingDataItem =new QComboBox();

          emit getActivateProjectTreeLeafRequest( 0 );

          QTableWidgetItem * Comment =new QTableWidgetItem("set training data set ");
          connect(trainingDataItem,SIGNAL(currentIndexChanged(QString)),this,SLOT(  set_trainingData(QString) )   );

           addTableRow(0,var,trainingDataItem,Comment);

      }
}

void BLL_SVM_UI:: initParamTable()
{

    paramsTable=new DataTableWgt();

    int start=1;
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
     initTrainingDatasetItem(0);

    //paramsTable->verticalHeader()->setVisible(false);
    ///************************************
    ///  1 求解问题类型
    /// *************************************
    QTableWidgetItem * var =new QTableWidgetItem(VNAME_D(svm_parameter::svm_type));
    svm_type_comb =new QComboBox();

    svm_type_comb->setBackgroundRole(QPalette::ColorRole::Light);
    svm_type_comb->addItems( QStringList () <<"C_SVC"<<" NU_SVC"<<" ONE_CLASS"<<"EPSILON_SVR"<<"NU_SVR" );

     connect(svm_type_comb,SIGNAL(currentIndexChanged(int)),this,SLOT(  receive_svm_type(int) ) );

    QTableWidgetItem * Comment =new QTableWidgetItem("type of svm algorithm");
    addTableRow(start+0,var,svm_type_comb,Comment);

    ///************************************
    /// 2  核函数类型
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::kernel_type));
    kernel_type_comb =new QComboBox();
    kernel_type_comb->setBackgroundRole(QPalette::ColorRole::Light);

     connect(  kernel_type_comb,SIGNAL(currentIndexChanged(int)),this,SLOT(receive_kernel_type(int))  );

     kernel_type_comb->addItems( QStringList () << VNAME(LINEAR)<<VNAME(POLY)<<VNAME(RBF)<<VNAME(SIGMOID)<<VNAME(PRECOMPUTED ));

     Comment =new QTableWidgetItem("type of svm kernel");
    addTableRow(start+1,var,kernel_type_comb,Comment);

    ///************************************
    /// 3  多项式核函数度
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::degree));
    degree_linedit =new QLineEdit();
    degree_linedit->setText("3");
    connect(degree_linedit,SIGNAL(textEdited(QString)),this,SLOT(receive_degree(QString)));

    Comment =new QTableWidgetItem("The degree of polynomial  kernel");
    addTableRow(start+2,var,degree_linedit,Comment);


    ///************************************
    ///   4 多项式核函数的参数coef0
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::coef0 ));
    coef0_linedit =new QLineEdit();
    coef0_linedit->setText("0");
    connect(coef0_linedit,SIGNAL(textEdited(QString) ),this,SLOT( receive_coef0(QString)) );
    Comment =new QTableWidgetItem("The coef0 of polynomial  kernel");
    addTableRow(start+3,var,coef0_linedit,Comment);

    ///************************************
    ///   5.    1/num_features，rbf核函数参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::gamma ) );
    gamma_linedit =new QLineEdit();
    gamma_linedit->setText("0.5");
    connect(gamma_linedit,SIGNAL(textChanged(QString)),this,SLOT( receive_gamma(QString ) ) );
    Comment =new QTableWidgetItem("The γ of polynomial  kernel, for kernel rbf ");
    addTableRow(start+4,var,gamma_linedit,Comment);

    ///************************************
    ///    6  nu-svc的参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::nu ) );
    nu_linedit =new QLineEdit();
    nu_linedit->setText("0.5");

    connect( nu_linedit,SIGNAL(textChanged(QString)),this,SLOT(receive_nu_svc(QString))  );
    Comment =new QTableWidgetItem(tr("The parameter of  svc for svm_type=svc ") );
    addTableRow(start+5,var,nu_linedit,Comment);

    ///************************************
    ///    nu-svc的参数
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::C ) );
    C_linedit =new QLineEdit();
    C_linedit->setText("10");

    Comment =new QTableWidgetItem(tr("The punishment coefficients of regularization ") );
    addTableRow(start+6,var,C_linedit,Comment);
    ///************************************
    ///   eps 收敛精度
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::eps ) );
    eps_linedit =new QLineEdit();
    eps_linedit->setText("1e-3");
    connect(eps_linedit,SIGNAL(textChanged(QString)),this,SLOT(receive_eps(QString )));
    Comment =new QTableWidgetItem(tr("convergence precision ") );
    addTableRow(start+7,var,eps_linedit,Comment);


    ///************************************
    ///  求解的内存缓冲 100MB
    /// *************************************

    var =new QTableWidgetItem(VNAME_D(svm_parameter::cache_size ) );
    cache_size_comb =new QComboBox();
    cache_size_comb->addItems(QStringList()<<"100MB"<<"80MB"<<"50MB");
    connect(cache_size_comb,SIGNAL(currentTextChanged(QString)),this,SLOT(receive_cache_size(QString ) ) );

    Comment =new QTableWidgetItem(tr("cache size of  memory ") );
    addTableRow(start+8,var,cache_size_comb,Comment);
    ///************************************
    ///  p
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::p ) );
    p_linedit =new QLineEdit();
    p_linedit->setText("0.1");
    connect(p_linedit,SIGNAL(textChanged(QString)),this,SLOT(receive_p(QString )));
    Comment =new QTableWidgetItem(tr(" for EPSILON_SVR") );
    addTableRow(start+9,var,p_linedit,Comment);

    ///************************************
    ///  shrinking
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::shrinking ) );
    shrinking_linedit =new QLineEdit();
    shrinking_linedit->setText("1");
    connect(shrinking_linedit,SIGNAL(textChanged(QString)),this,SLOT(receive_shrinking(QString )  ));

    Comment =new QTableWidgetItem(tr(" use the shrinking heuristics ") );
    addTableRow(start+10,var,shrinking_linedit,Comment);

    ///************************************
    ///  probability: //1表示训练时生成概率模型，0表示训练时不生成概率模型，用于预测样本的所属类别的概率
    /// *************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::probability ) );
    probability_comb =new QComboBox();
     probability_comb->addItems(QStringList()<<"0"<<"1");
    connect(probability_comb,SIGNAL( currentIndexChanged(int)),this,SLOT( receive_probability(int)  ));

    Comment =new QTableWidgetItem(tr(" 1 denotes  that svm will  generating probability model and 0 denotes will not ") );
    addTableRow(start+11,var,probability_comb,Comment);

    ///************************************
    ///  nr_weight 类别权重
    /// ************************************
    var =new QTableWidgetItem(VNAME_D(svm_parameter::nr_weight ) );
    nr_weight_linedit =new QLineEdit();
    nr_weight_linedit->setText("0");

    Comment =new QTableWidgetItem(tr(" type wight ") );
    addTableRow(start+12,var,nr_weight_linedit,Comment);


    // svmParams->weight = NULL;    //样本权重
    // svmParams->weight_label = NULL;    //类别权重

    //*********************************************
    //** set font
    //*********************************************

    for(int i=0;i<start+13;++i)
        for(int j=0;j<3;++j){
             QTableWidgetItem *itemWgt= paramsTable->item(i,j);
             if(itemWgt){
                      itemWgt->setTextAlignment(Qt::AlignLeft);
                      itemWgt->setFont(*cellfont);
             }
        }
    paramsTable->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    paramsTable->horizontalHeaderItem(0)->setFont(*cellfont);
    paramsTable->horizontalHeaderItem(1)->setTextAlignment(Qt::AlignLeft);
    paramsTable->horizontalHeaderItem(1)->setFont(*cellfont);
    paramsTable->horizontalHeaderItem(2)->setTextAlignment(Qt::AlignLeft);
    paramsTable->horizontalHeaderItem(2)->setFont(*cellfont);


}


void BLL_SVM_UI::addTableRow(int row,QTableWidgetItem*var,QTableWidgetItem*val,QTableWidgetItem*comment )
{
      paramsTable->setItem(row,0,var);
      paramsTable->setItem(row,1,val);
      paramsTable->setItem(row,2,comment);

}
void BLL_SVM_UI::addTableRow(int row,QTableWidgetItem*var,QWidget *val,QTableWidgetItem*comment )
{
      paramsTable->setItem(row,0,var);
      paramsTable->setCellWidget(row,1,val);
      paramsTable->setItem(row,2,comment);

}
 void BLL_SVM_UI:: receive_trainingData(QString dir, QStringList path){
       if( trainingDataItem  )
       {
           Dir=dir;
           trainingDataItem->addItems(path);
       }
}
void  BLL_SVM_UI:: updateParamFromUI()
{
             if(svm && svm->svmParams){
                    svm->trainingDataSetPath=Dir+ trainingDataItem->currentText();

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

void BLL_SVM_UI:: set_trainingData(QString dataRelativePath)
{
    if(svm ){
            svm->trainingDataSetPath = Dir+ dataRelativePath ;
            cout<< svm->trainingDataSetPath.toStdString() << endl;
      }
}

void BLL_SVM_UI::receive_svm_type(int svm_type){
     cout<<"Test"<<endl;
     if(svm ){
           cout<<"svm"<<endl;
             svm->svmParams->svm_type=svm_type;
       }
}
void BLL_SVM_UI::receive_kernel_type(int kernel_type){
       if(svm &&svm->svmParams  ){

             svm->svmParams->kernel_type=kernel_type;
       }
}
void BLL_SVM_UI::receive_degree(QString d){
       if(svm &&svm->svmParams  ){
            svm->svmParams->degree=d.toInt();
       }
}
void BLL_SVM_UI:: receive_coef0(QString coef0){
    if(svm &&svm->svmParams  )
    {
         svm->svmParams->coef0=coef0.toDouble();
    }
}
 void  BLL_SVM_UI::receive_gamma(QString gama) {
     if(svm &&svm->svmParams  )
     {
          svm->svmParams->gamma=gama.toDouble();
     }
 }
void  BLL_SVM_UI::receive_nu_svc(QString nu) {
    if(svm &&svm->svmParams  )
    {
         svm->svmParams->nu=nu.toDouble();
    }
}
void BLL_SVM_UI:: receive_eps(QString eps){
    if(svm &&svm->svmParams  )
    {
         svm->svmParams->eps=eps.toDouble();
    }
}
void BLL_SVM_UI:: receive_cache_size(QString cache_size){
    if(svm &&svm->svmParams  )
         svm->svmParams->cache_size=cache_size.mid(0,2).toInt();
         cout<< svm->svmParams->cache_size<<endl;
}
 void  BLL_SVM_UI:: receive_p(QString p){
        if(svm &&svm->svmParams  )
             svm->svmParams->p=p.toDouble();
}
void BLL_SVM_UI::  receive_shrinking(QString shrinking) {
    if(svm &&svm->svmParams  )
         svm->svmParams->shrinking=shrinking.toInt();
}
void BLL_SVM_UI:: receive_probability(int  probability)
{
    if(svm &&svm->svmParams  )
          svm->svmParams->probability=probability;
 }






