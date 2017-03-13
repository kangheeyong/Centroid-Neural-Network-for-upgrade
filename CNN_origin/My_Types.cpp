#include "My_Types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

void PR1_DATA :: init() //초기화
{
  srand(time(NULL));
  if(this->data != NULL) delete this->data;
  this->row = 0;
  this->column = 0;
  this->data = NULL;
  if(this->t_table != NULL) delete this->t_table;
  this->t_row = 0;
  this->t_column = 0;
  this->t_table = NULL; 
}
   
void PR1_DATA :: table_make()
{
  this->t_row = 2;
  this->t_column = this->column;
  this->t_table = new double[2*this->t_column];
  for(int i = 0 ; i < 2*this->t_column ; i++) this->t_table[i] = 0.0;
}


void PR1_DATA :: init(int y)
{
  this->init(y,1);
}
void PR1_DATA :: init(int y, int x)
{
  this->init();
  this->data = new double[x*y];
  this->row = x;
  this->column = y;
  for(int i = 0 ; i < x*y ; i++) this->data[i] = 0.0;
  
  this->table_make();
 
}
void PR1_DATA :: print()
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
void PR1_DATA :: random() //data 값의 랜덤
{
  this->random(-1,1);

}
void PR1_DATA :: random(double min, double max)
{
  int temp = (max - min) *100000;

  for(int i = 0 ; i < this->column ; i++)
  {
    for(int j = 0 ; j < this->row ; j++)
    {
      this->data[i * this->row + j] = (double)(rand()%temp)/100000 + min;
    }
  }

}
void PR1_DATA :: suffle() //data의 row단위로 섞는다.
{
  double *temp = new double[this->row];
  int num;
  for(int i = 0 ; i < this->column ; i++)
  {
    num = rand()%this->column;
    for(int j = 0 ; j < this->row ; j++)
    {
      temp[j] = this->data[i * this->row + j];
      this->data[i * this->row + j] = this->data[num * this->row + j];
      this->data[num * this->row + j] = temp[j];
    }
  }

  delete temp;

}
void PR1_DATA :: suffle(int num) //data의 row단위로 섞는다.
{
  srand(num);
  this->suffle();
}

void PR1_DATA :: table_init()
{
  if(this->data == NULL)
  {
    cout<<"data is empty"<<endl;
  }
  else
  {
    if(this->t_table != NULL) delete this->t_table;
    this->t_row = 2;
    this->t_column = this->column;
    this->t_table = new double[2*this->t_column];
    for(int i = 0 ; i < 2*this->t_column ; i++) this->t_table[i] = 0.0;
  }
}
void PR1_DATA :: table_insert( int y, double value)
{
  this->t_table[y*2] = value;
  this->t_table[y*2+1] = y;
}

void PR1_DATA :: Swap(double arr[], int idx1,int idx2)
{
  double t_value = arr[idx1*2];
  double t_y = arr[idx1*2 + 1];

  arr[idx1*2] = arr[idx2*2];
  arr[idx1*2+1] = arr[idx2*2+1];
  
  arr[idx2*2] = t_value;
  arr[idx2*2+1] = t_y;
}

int PR1_DATA :: Partition(double arr[], int left, int right)
{
  double pivot = arr[left*2]; // 피벗의 위치는 가장 왼쪽!
  int low = left + 1;
  int high = right;
  
  while(low <= high) // 교차되지 않을 때까지 반복
  {
    //피벗보다 큰 값을 찾는 과정
    while(pivot >= arr[low*2] && low <=right)
    {
      low++;
    }
    //피벗보다 작은 값을 찾는 과정
    while(pivot <= arr[high*2] && high >= (left + 1))
    {
      high--;
    }

    //교차 되지 않은 상태라면 Swap 실행
    if(low <= high)
    {
      Swap(arr,low,high);
    }
  }

  Swap(arr,left,high); //피벗과 high가 가리키는 대상 교환
  return high;          //옮겨진 피벗의 위치정보 반환
}

void PR1_DATA :: QuickSort(double arr[], int left, int right)
{
  if(left <= right)
  {
    int point_pivot = Partition(arr,left,right);
    QuickSort(arr,left,point_pivot-1);
    QuickSort(arr,point_pivot+1, right);
  }
}


void PR1_DATA :: table_ascending()
{
  if(this->t_table != NULL)
    this->QuickSort(this->t_table,0,this->t_column-1);
}
double PR1_DATA :: get_table(int y, int x)
{
  return this->t_table[y*2+x];
}
double PR1_DATA :: table(int ordered_y,int x)
{
  return this->data[ (int)(this->t_table[ordered_y*2 + 1]) * this->row + x];
}
void PR1_DATA :: table_print()
{
  if(this->t_table == NULL) cout<<"empty"<<endl;
  else
  {
    cout<<endl;
    cout<<"table => column : "<<this->t_column<<endl;

    if(this->column < 21)
    {
      for(int i = 0 ; i < this->t_column ; i++)
      {
        for(int j = 0 ; j < 2 ; j++)
        {
          cout << this->t_table[i*2 + j]<<" ";
        }
        cout<<endl;
      }
    }
    else
    {
      for(int i = 0 ; i < 10 ; i++)
      {
        for(int j = 0 ; j < 2 ; j++)
        {
          cout << this->t_table[i*2 + j]<<" ";
        }
        cout<<endl;
      }
      cout<<"..."<<endl;
      for(int i = this->t_column-10 ; i < this->t_column ; i++)
      {
        for(int j = 0 ; j < 2 ; j++)
        {
          cout << this->t_table[i*2 + j]<<" ";
        }
        cout<<endl;
      }
    }
    cout<<endl;
  }
}


bool PR1_DATA :: fread(const char* fname) //텍스트 읽기
{
   FILE *fp;

  this->init();

   if(fp = fopen( fname, "r"))
   {
     char buf[BUFF_SIZE];

     while( fgets( buf, BUFF_SIZE, fp)) // 가로와 세로의 개수 구하기
     {
       bool delta[2] = {0,0};
       for(int i = 0; i < BUFF_SIZE ; i++)
       {
         if(buf[i] == '\n') break;

         else if(buf[i] == '.'||buf[i] == '+'||buf[i] == '-'||(buf[i] >= '0' && buf[i] <= '9') )
         {
           delta[0] = delta[1];
           delta[1] = 1;
         }
         else
         {
           delta[0] = delta[1];
           delta[1] = 0;
         }
         if(delta[0] == 0 && delta[1] == 1) this->row++;

       }
       this->column++;

     }
     this->row = this->row / this->column; // 열(row)의 개수는 일정해야함
     rewind( fp);   // 파일 읽기/쓰기 위치를 처음 위치로 이동
     this->data = new double[this->row*this->column]; //동적할당 받기 1차원 배열을 2차원 배열처럼 쓰자

     double temp;
     for(int i = 0 ; i < this->column ; i++)
     {
       for(int j = 0 ; j < this->row ; j++)
       {
         fscanf(fp,"%lf",&temp);
         this->data[i * this->row + j] = temp; //값 읽기 오로지 공백으로만 검출
       }
     }
     fclose(fp);
     this->table_make();
     return 1;
   }
   else
   {
     cout<<"fail to read"<<endl;
     return -1;
   }
}
bool PR1_DATA :: table_fwrite(const char *fname) //TABLE 텍스트 쓰기
{
  FILE *fp;
  if(fp = fopen( fname, "w"))
  {
    for(int i = 0 ; i < this->t_column ; i++)
    {
      for(int j = 0 ; j < this->t_row ; j++)
      {
        fprintf(fp,"%18.15f ",this->t_table[i * this->t_row + j]);
      }
      fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
  }
  else
  {
    cout<<"fail to table write"<<endl;
    return -1;
  }

}
bool PR1_DATA :: fwrite(const char *fname) //텍스트 쓰기
{
  FILE *fp;
  if(fp = fopen( fname, "w"))
  {
    for(int i = 0 ; i < this->column ; i++)
    {
      for(int j = 0 ; j < this->row ; j++)
      {
        fprintf(fp,"%18.15f ",this->data[i * this->row + j]);
      }
      fprintf(fp,"\n");
    }
    fclose(fp);
    return 1;
  }
  else
  {
    cout<<"fail to write"<<endl;
    return -1;
  }

}
PR1_DATA& PR1_DATA :: operator=(const PR1_DATA &other) //대입연산자
{
  
  this->init(other.column, other.row);

  for(int i = 0 ; i < this->column ; i++)
  {
    for(int j = 0 ; j < this->row ; j++)
    {
      this->data[i*this->row + j] = other.data[i*this->row + j];
    }
  }

  this->table_init();

  return *this;

}

PR1_DATA :: PR1_DATA()
{
  this->row = 0;
  this->column = 0;
  this->data = NULL;
  this->t_row = 0;
  this->t_column = 0;
  this->t_table = NULL;

}

PR1_DATA :: ~PR1_DATA()
{
  this->init();
}

bool PR1_QUEUE :: IsEmpty()
{
  if(this->front == NULL) return true;
  else return false;
}

PR1_QUEUE& PR1_QUEUE :: operator<<(const Data &data)
{ 
  Node *newNode = new Node;
  newNode->next = NULL;
  newNode->data = data;
  if(this->IsEmpty())
  {
    this->front = newNode;
    this->rear = newNode;
  }
  else
  {
    this->rear->next = newNode;
    this->rear = newNode;
  }
}

PR1_QUEUE& PR1_QUEUE :: operator>>(Data &data)
{
  Node *delNode;
  if(this->IsEmpty())
  {
    data.init();
  }
  else
  {
    delNode = this->front;
    data = delNode->data;
    this->front = this->front->next;
    delete delNode;
  }
}

void PR1_QUEUE :: lwrite(const char *lname)
{
  char buff[100];
  int i = 0;
  Data  temp;
  while(!this->IsEmpty())
  {
    sprintf(buff,"%s_%d.txt",lname,i++);
    *this>>temp;
    temp.fwrite(buff);
  }
}

PR1_QUEUE :: PR1_QUEUE()
{
  this->front = NULL;
  this->rear = NULL;
}

PR1_QUEUE ::~PR1_QUEUE()
{
  Node *delNode;

  while(!this->IsEmpty())
  {
    delNode = this->front;
    this->front = this->front->next;
    delete delNode;
  }  
}

