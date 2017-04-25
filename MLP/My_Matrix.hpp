#ifndef __MY_MATRIX_CPP__
#define __MY_MATRIX_CPP__

#define MY_ALL        -1

class My_Matrix{

  // matlab 연산과 동일한 결과, 에러 검출은 안함
  friend My_Matrix operator+(const My_Matrix &T1, const My_Matrix &T2);// T1 + T2
  friend My_Matrix operator+(const My_Matrix &T, const double num);// T + num
  friend My_Matrix operator+(const double num, const My_Matrix &T);// num + T

  friend My_Matrix operator-(const My_Matrix &T1, const My_Matrix &T2);// T1 - T2
  friend My_Matrix operator-(const My_Matrix &T, const double num);// T - num
  friend My_Matrix operator-(const double num, const My_Matrix &T);// num - T

  friend My_Matrix operator*(const My_Matrix &T1, const My_Matrix &T2);// T1 * T2
  friend My_Matrix operator*(const My_Matrix &T, const double num);// T * num
  friend My_Matrix operator*(const double num, const My_Matrix &T);// num * T

  friend My_Matrix mul(const My_Matrix &T1, const My_Matrix &T2);// T1.*T2
 

  protected :
    double *data;
    int row, column;

  public :

    void init(int y, int x);
    void print(); 

    void gaussian(double average, double stdev);// 가우시안 분포로 변수 생성

    My_Matrix transpose();

    My_Matrix vector(int y, int x);

    double sum(); // 모든 행렬 원소 합
    const double&  operator()(int y, int x) const { return this->data[y*this->row+x]; };
    double&  operator()(int y, int x) { return this->data[y*this->row+x]; };   

    My_Matrix& operator=(const My_Matrix &other); //대입연산자


    My_Matrix();  
    ~My_Matrix();

};


#endif
