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
    cout<<"--------------------------------"<<endl;
    cout<<"index : "<<current().index<<", nuerals : "<<current().nuerals<<", type : " <<current().type<<endl;
    cout<<"------------- a ----------------"<<endl;
    current().a.print();
    cout<<"------------- z ----------------"<<endl;
    current().z.print();
    cout<<"------------- w ----------------"<<endl;
    current().w.print();
    cout<<"------------- b ----------------"<<endl;
    current().b.print();
    cout<<"------------- delta ----------------"<<endl;
    current().delta.print();
    cout<<"--------------------------------"<<endl;

  } while(Lnext());
  cout<<"------------- y  ----------------"<<endl;
  y.print();
cout<<"w_sum : "<<W<<endl;
 
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
  W = 0;
  do
  {
    if(&next() != NULL)
    {
      next().a = (current().z * current().w.transpose()) + current().b;
      next().z = sigmoid(next().a);

      W = W + mul(current().w,current().w).sum();
    }
  } while(Lnext());
}
double MLP :: get_cost_function()
{
  Llast();

  return mul(y - current().z, y - current().z).sum()/(2*mini_batch) + ramda*W*0.5;
}
void MLP :: back_propagation()
{
  Llast();
  double mb = 1.0/mini_batch;
  My_Matrix delta_w, delta_b;
  current().delta = -1*mul(y-current().z, mul(current().z,1-current().z));
  do
  {
    if(&(prev()) != NULL)
    {
       if(&prev() != head) prev().delta = mul(current().delta * prev().w, mul(prev().z,1-prev().z));
       delta_w.init(current().nuerals,prev().nuerals);
       delta_b.init(1,current().nuerals);

       for(int i = 0 ; i < mini_batch ; i++)
       {
         delta_w = delta_w + current().delta.vector(i,MY_ALL).transpose() * prev().z.vector(i,MY_ALL);
         delta_b = delta_b + current().delta.vector(i,MY_ALL);
       }
       prev().w = prev().w - alpha*(delta_w*mb + ramda*prev().w);
       prev().b = prev().b - alpha*delta_b*mb;

     
    }
  } while(Lprev());

}

MLP :: MLP()
{
  total_layers = 0;
  mini_batch = 1;
  alpha = 0.1; // learning_gain
  ramda = 0.0; // decay_para

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









