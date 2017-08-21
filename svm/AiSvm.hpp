#ifndef AISVM_H
#define AISVM_H
#include"svm/svm.h"
#include "CplusHeader.h"
#include <QThread>
#include "baseWgt/BASE-Util.hpp"
#include "baseWgt/BASE-Type.hpp"

using namespace libsvm;
class AiSVM:public QThread
{
  Q_OBJECT
 public:
    AiSVM(){
        libsvm::svm_Reportor=new svmReportor;
    }
    ~AiSVM(){ freeMemory();}
    STATUS  setTrainingData(string fileName)
    {
        svmProb=new svm_problem;
        svmParams=new svm_parameter;
        ///////////////////////////////////////////////////////////////////////
        ifstream fin(fileName);
         if (!fin){
                cout << "Error in opening file <" << fileName << ">. ABORT!";
                //emit ShowMsgRequest("Error","Error in opening file <" + QString(fileName) +">. ABORT!");
                return Error;
          }
           string line;
           int i = 0;
           vector<vector<double>> Data;
            while (fin.good() )
            {
                getline(fin, line);
                istringstream sin(line);
                string Xi;
                vector<double> row;
                while (!sin.eof())
                {
                    sin >> Xi;
                    row.push_back(atof(Xi.c_str()));
                }
                if (Data.size()==0 || Data[0].size()==row.size() )  Data.push_back(row);
            }
            fin.close();
            /////////////////////////////////////////
            int M = Data.size();
            int n = Data[0].size();
            svmProb->l = M;
            svmProb->y = new double[svmProb->l];
            svmProb->x = new svm_node*[svmProb->l];
            for (int i = 0; i < svmProb->l; ++i){
                svmProb->x[i] = new svm_node[n];
            }
            for (int i = 0, j; i < M; ++i)
            {
                for (j = 0; j < Data[i].size() - 1; ++j)
                {
                    svmProb->x[i][j].index = j+1;
                    svmProb->x[i][j].value = Data[i][j];
                }
                svmProb->x[i][j].index = -1;//不知为何要多分配一个单元
                svmProb->y[i] = Data[i][j];
            }
        return Ok;
    }
    void initDefaultParams()
    {
          //参数初始化，参数调整部分在这里修改即可
            // 默认参数
            svmParams->svm_type = C_SVC;        //算法类型
            svmParams->kernel_type = LINEAR;    //核函数类型
            svmParams->degree = 3;    //多项式核函数的参数degree
            svmParams->coef0 = 0;    //多项式核函数的参数coef0
            svmParams->gamma = 0.5;    //1/num_features，rbf核函数参数
            svmParams->nu = 0.5;        //nu-svc的参数
            svmParams->C = 10;        //正则项的惩罚系数
            svmParams->eps = 1e-3;    //收敛精度
            svmParams->cache_size = 100;    //求解的内存缓冲 100MB
            svmParams->p = 0.1;
            svmParams->shrinking = 1;
            svmParams->probability = 1;    //1表示训练时生成概率模型，0表示训练时不生成概率模型，用于预测样本的所属类别的概率
            svmParams->nr_weight = 0;    //类别权重
            svmParams->weight = NULL;    //样本权重
            svmParams->weight_label = NULL;    //类别权重

    }
    void train()
    {
        start();
    }
    void run(){

        svmModel= svm_train(svmProb,svmParams);

    }
    void freeMemory()
    {
        if (svmModel)  svm_free_and_destroy_model(&svmModel);
        if (svmParams)  svm_destroy_param(svmParams);
        if(svmProb)
        {
            if(svmProb->y) delete [] svmProb->y;
            if(svmProb->x)  delete [] svmProb->x;
            delete svmProb;
        }
    }
signals:
     void ShowMsgRequest(QString Type,QString message);
private:
    svm_problem *svmProb;
    svm_parameter *svmParams;
    svm_model *svmModel;



};



#endif // AISVM_H
