#include "MY_MLP.hpp"
#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

nueral_layer :: nueral_layer()
{
    index = 0;

    next = NULL;
    prev = NULL; 
}


nueral_layer :: ~nueral_layer()
{
   
}

bool MLP :: Lnext()
{
  if(cur->next != NULL)
  {
    cur = cur->next;
    return true;
  }
  else return false;
}
bool MLP :: Lprev()
{
  if(cur->prev != NULL)
  {
    cur = cur->prev;
    return true;
  }
  else return false;
}



void MLP :: Lfirst()
{
  cur = head;
}

void MLP :: Llast()
{
  cur = tail;
}

bool MLP :: Ldelete()
{
  if(total_layers > 0)
  {
    nueral_layer *del;
    del = cur;
    if(cur == head && cur == tail) 
    {
      //하나만 있는 경우
      head = tail = cur = NULL;
    }
    else if(cur == head)
    {
      //첫번째 레이어를 제거하는 경우
      //cur는 두번째 레이어를 가르킨다.
      head = cur->next;
      head->prev = NULL;
      cur = head;
    }
    else if(cur == tail)
    {
      //마지막 레이어를 제거하는 경우
      //cur는 제거된 레이어 앞을 가르킨다.
      tail = cur->prev;
      tail->next = NULL;
      cur = tail;
    }
    else
    {
      //중간 레이어를 제거하는 경우
      //cur는 제거한 레이어 뒤에것을 가르킨다.
      cur->prev->next = cur->next;
      cur->next->prev = cur->prev;
      cur = cur->next;

    }

    delete del;

    total_layers--;
    return true;
  }
  else return false;
}
void MLP :: Linsert()
{
  nueral_layer *new_layer;

  new_layer = new nueral_layer;

  if(head == NULL)
  {
    head = new_layer;
    tail = new_layer;
    cur = new_layer;
  }
  else
  {
    tail->next = new_layer;
    new_layer->prev = tail;
    tail = new_layer;
    cur = tail;
  }

  total_layers++;
}
void MLP :: add_layer(int nuerals)
{
  Linsert();
  current().index= total_layers;;
  current().nuerals = nuerals;

}

void MLP :: del_layer(int index)
{
  Lfirst();
  do
  {
    if(current().index == index)
    {
      Ldelete();
      do{
        current().index = current().index - 1;
      }while(Lnext());
      break;
    }
  }while(Lnext());
}

void MLP :: check()
{
  Lfirst();
  do
  {
    cout<<"index : "<<current().index<<", nuerals : "<<current().nuerals<<", type : " <<current().type<<endl;
    current().a.print();
    current().z.print();

    current().w.print();
    current().b.print();
  } while(Lnext());
}

void MLP :: network_connect()
{
  Lfirst();
  do
  {
    if(&next() != NULL)
    {
      current().w.init(next().nuerals,current().nuerals);
      current().b.init(1,next().nuerals);
    }
  } while(Lnext());
}

void  MLP :: init_gaussian(double average, double stdev)
{
  Lfirst();
  do
  {
    if(&next() != NULL)
    {
      current().w.gaussian(average,stdev);
      current().b.gaussian(average,stdev);
    }
  } while(Lnext());
}

My_Matrix sigmoid(const My_Matrix &T)
{
  My_Matrix temp;
  temp.init(T.get_column(),T.get_row());
  for(int y = 0 ; y < temp.get_column() ;y++)
  {
    for(int x = 0 ; x < temp.get_row() ; x++)
    {
      temp(y,x) = 1/(1+exp(-T(y,x)));
    }
  }
  return temp;
}


void MLP :: activation()
{
 Lfirst();
  do
  {
    if(&next() != NULL)
    {
      next().a = (current().z * current().w.transpose()) + current().b;
      next().z = sigmoid(next().a);
    }
  } while(Lnext());
}


MLP :: MLP()
{
  total_layers = 0;
  mini_batch = 1;

  head = NULL;
  tail = NULL;
  cur = NULL;
}

MLP :: ~MLP()
{
  if(head != NULL)
  {
    while(Ldelete());
  }
}









