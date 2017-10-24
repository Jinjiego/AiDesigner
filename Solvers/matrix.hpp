#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
using namespace std;
template <typename E>


class Matrix
{
public:
    int rows,cols,length;

    Matrix(int _m,int _n);
     Matrix(const Matrix<E> &M) ;
    ~Matrix();
   Matrix<E> &  operator+(Matrix<E> &M);
   Matrix<E> &  operator-(Matrix<E> &M);
   Matrix<E> &  operator=(const Matrix<E> &M);
   Matrix<E> &  T();

    E& operator()(int i,int j)
    {
          if ( (i>=0 && i<rows) &&(j>=0 && j<cols ) ){
              return basePtr[i*cols+j];
          }else {
              cout<<"subscript over bounded!"<<endl;
              exit(0);
          }
    }
private:
     E* basePtr;

};


/*
   模板类的声明与定义不能分开为两个文件，只有部分编译器支持声明与实现分开。
 */
template <typename E>
Matrix<E>::Matrix(int _m,int _n)
{
    rows=_m;cols=_n;
    if( !(rows==0 || cols==0 )){
          length=rows*cols;
          basePtr =new E[length];
    }
    else cout<<"Error!"<<endl;
}

template <typename E>
Matrix<E>::~Matrix(){
         if(basePtr) delete[] basePtr;
}
template <typename E>
Matrix<E>& Matrix<E>:: operator+(Matrix<E> &M)
{
        if( M.rows == rows && M.cols==cols){
            Matrix<E> * res= new Matrix<E>(rows,cols);
            #pragma omp parallel for
            for(int i=0;i<length;++i){
                   res->basePtr[i]=basePtr[i]+M.basePtr[i];
            }
            return *res;
        }else {
             cout<< "Matrix in operator+ are in different size"<<endl;
             return *this;
        }
}
template <typename E>
Matrix<E> & Matrix<E> :: operator-(Matrix<E> &M)
{
    if( M.rows == rows && M.cols==cols){
        Matrix<E> * res= new Matrix<E>(rows,cols);
        #pragma omp parallel for
        for(int i=0;i<length;++i){
               res->basePtr[i]=basePtr[i]-M.basePtr[i];
        }
        return *res;
    }else {
         cout<< "Matrix in operator+ are in different size"<<endl;
         exit(0);
    }
}
template <typename E>
Matrix<E> :: Matrix(const Matrix<E> &M)
{
         rows=M.rows;
         cols=M.cols;
         length = M.length;
         basePtr =new E[length];
      //   #pragma omp parallel for
         for(int i=0;i<length;++i)
         {
             basePtr[i] =M.basePtr[i];
         }
}
/**
 *
 */

template<typename E>
Matrix<E> & Matrix<E> :: operator=(const Matrix<E> &M)
{
       if(this==&M) return *this;
       if(basePtr) delete[] basePtr;
       rows=M.rows;
       cols=M.cols;
       length=M.length;
       basePtr =new E[length];
       for(int i=0;i<length;++i) basePtr[i]=M.basePtr[i];
       return *this;
}
template<typename E>
Matrix<E> & Matrix<E> :: T()
{
       Matrix<E> *result= new  Matrix<E>(cols,rows);
       result->length =length;
       int i,j;
       for(int k=0;k<length;++k)
       {
            i=k/cols;
            j=k-i*cols;
            result->basePtr[j*rows+i] =basePtr[k];
       }
        return *result;
}




#endif // MATRIX_H
