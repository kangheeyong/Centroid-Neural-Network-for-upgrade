#include "My_Matrix.hpp"
#include <iostream>
#include <math.h>
#include <stdlib.h>



using namespace std;

My_Matrix mul(const My_Matrix &T1, const My_Matrix &T2)
{
  My_Matrix temp;

  temp.init(T2.column, T2.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = T1(y,x) * T2(y,x);
    }
  }

  return temp;
}
 


My_Matrix operator+(const My_Matrix &T1, const My_Matrix &T2)
{
  My_Matrix temp;

  if(T1.column == 1 && T2.column != 1)
  {
    temp.init(T2.column, T2.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(0,x) + T2(y,x);
      }
    }
  }

  else if(T1.column != 1 && T2.column == 1)
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) + T2(0,x);
      }
    }
  }
  else if(T1.row == 1 && T2.row != 1)
  {
    temp.init(T2.column, T2.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,0) + T2(y,x);
      }
    }
  }

  else if(T1.row != 1 && T2.row == 1)
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) + T2(y,0);
      }
    }
  }
  else
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) + T2(y,x);
      }
    }
  }

  return temp;
}

My_Matrix operator+(const My_Matrix &T, const double num)
{
  My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = T(y,x) + num;
    }
  }
  return temp;

}

My_Matrix operator+(const double num, const My_Matrix &T)
{
   My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = num + T(y,x);
    }
  }
  return temp;

}

My_Matrix operator-(const My_Matrix &T1, const My_Matrix &T2)
{
  My_Matrix temp;

  if(T1.column == 1 && T2.column != 1)
  {
    temp.init(T2.column, T2.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(0,x) - T2(y,x);
      }
    }
  }

  else if(T1.column != 1 && T2.column == 1)
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) - T2(0,x);
      }
    }
  }
  else if(T1.row == 1 && T2.row != 1)
  {
    temp.init(T2.column, T2.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,0) - T2(y,x);
      }
    }
  }

  else if(T1.row != 1 && T2.row == 1)
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) - T2(y,0);
      }
    }
  }
  else
  {
    temp.init(T1.column, T1.row);
    for(int y = 0 ; y < temp.column ;y++)
    {
      for(int x = 0 ; x < temp.row ; x++)
      {
        temp(y,x) = T1(y,x) - T2(y,x);
      }
    }
  }

  return temp;
}

My_Matrix operator-(const My_Matrix &T, const double num)
{
  My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = T(y,x) - num;
    }
  }
  return temp;

}

My_Matrix operator-(const double num, const My_Matrix &T)
{
   My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = num - T(y,x);
    }
  }
  return temp;

}




My_Matrix operator*(const My_Matrix &T1, const My_Matrix &T2)
{
  My_Matrix temp;

  temp.init(T1.column, T2.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      for(int i = 0 ; i < T1.row ; i++)
      {
        temp(y,x) = temp(y,x) + T1(y,i)*T2(i,x);
      }
    }
  }
  return temp;

}


My_Matrix operator*(const My_Matrix &T, const double num)
{
  My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = T(y,x) * num;
    }
  }
  return temp;

}

My_Matrix operator*(const double num, const My_Matrix &T)
{
   My_Matrix temp;

  temp.init(T.column, T.row);
  for(int y = 0 ; y < temp.column ;y++)
  {
    for(int x = 0 ; x < temp.row ; x++)
    {
      temp(y,x) = num * T(y,x);
    }
  }
  return temp;

}




double gaussianRandom(double average, double stdev) 
{
  double v1, v2, s, temp;

  do {
    v1 =  2 * ((double) rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
    v2 =  2 * ((double) rand() / RAND_MAX) - 1;      // -1.0 ~ 1.0 까지의 값
    s = v1 * v1 + v2 * v2;
  } while (s >= 1 || s == 0);

  s = sqrt( (-2 * log(s)) / s );

  temp = v1 * s;
  temp =( stdev*temp) + average;


  return temp;
}


void My_Matrix :: gaussian(double average, double stdev)
{
 for(int i = 0 ; i < this->column ; i++)
  {
    for(int j = 0 ; j < this->row ; j++)
    {
      this->data[i*this->row + j] = gaussianRandom(average,stdev); 
    }
  }

}
My_Matrix My_Matrix :: vector(int y, int x)
{
  My_Matrix temp;
  if(y == MY_ALL)
  {
    temp.init(this->column,1);
    for(int i = 0 ; i < this->column ; i++)
    {
      temp(i,0) = this->data[i*this->row + x];
    }
  }
  else
  {
    temp.init(1,this->row);
    for(int i = 0 ; i < this->row ; i++)
    {
      temp(0,i) =  this->data[y*this->row + i];
    }
  }
  return temp;
}


double My_Matrix :: sum()
{
  double temp = 0.0;
 for(int i = 0 ; i < this->column ; i++)
  {
    for(int j = 0 ; j < this->row ; j++)
    {
      temp = temp + this->data[i*this->row + j]; 
    }
  }

  return temp;
}


void My_Matrix :: init(int y, int x)
{
  if(this->data != NULL) delete data;
  this->data = new double[x*y];
  this->row = x;
  this->column = y;

}


void My_Matrix :: print()
{
  if(this->data == NULL) cout<<"empty"<<endl;
  else
  {
    cout<<endl;
    cout<<"column : "<<this->column<<", row : "<<this->row<<endl;

    if(this->column < 21)
    {
      for(int i = 0 ; i < this->column ; i++)
      {
        for(int j = 0 ; j < this->row ; j++)
        {
          cout << this->data[i*this->row + j]<<" ";
        }
        cout<<endl;
      }
    }
    else
    {
      for(int i = 0 ; i < 10 ; i++)
      {
        for(int j = 0 ; j < this->row ; j++)
        {
          cout << this->data[i*this->row + j]<<" ";
        }
        cout<<endl;
      }
      cout<<"..."<<endl;
      for(int i = this->column-10 ; i < this->column ; i++)
      {
        for(int j = 0 ; j < this->row ; j++)
        {
          cout << this->data[i*this->row + j]<<" ";
        }
        cout<<endl;
      }
    }
    cout<<endl;
  }

}


My_Matrix& My_Matrix :: operator=(const My_Matrix &other) //대입연산자
{
  
  this->init(other.column, other.row);

  for(int i = 0 ; i < this->column ; i++)
  {
    for(int j = 0 ; j < this->row ; j++)
    {
      this->data[i*this->row + j] = other.data[i*this->row + j];
    }
  }

  return *this;

}


My_Matrix My_Matrix :: transpose()
{
  My_Matrix temp;
  temp = *this;
  temp.row = this->column;
  temp.column = this->row;
  return temp;
}


My_Matrix :: My_Matrix()
{
  this->data = NULL;
  this->row = 0;
  this->column = 0;
}


My_Matrix :: ~My_Matrix()
{
  if(this->data != NULL) delete data;
}
