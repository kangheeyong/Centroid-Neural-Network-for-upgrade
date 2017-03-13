#ifndef __MY_TYPES_CPP__
#define __MY_TYPES_CPP__

#define BUFF_SIZE     4096   

class PR1_DATA{

  private:

    double *data;
    int row;
    int column;

    double *t_table;
    int t_row;
    int t_column;

    void table_make();
    void Swap(double arr[], int idx1,int idx2);
    int Partition(double arr[], int left, int right);
    void QuickSort(double arr[], int left, int right);

  public:

    void init(); //초기화 data table

    void init(int y); // data값에 따라  table도 초기화
    void init(int y, int x);
    void print();
    void random(); //data 값의 랜덤
    void random(double min, double max);
    void suffle(); //data의 row단위로 섞는다.
    void suffle(int num); //data의 row단위로 섞는다.

    const int get_row() {return row;};
    const int get_column() {return column;};

    void table_init(); //table값을 초기화
    void table_insert(int y, double value);
    void table_ascending();
    double get_table(int y,int x);
    double table(int ordered_y, int x);
    void table_print();

    bool fread(const char *fname); //텍스트 읽기
    bool table_fwrite(const char *fname); //table 텍스트 쓰기
    bool fwrite(const char *fname); //텍스트 쓰기

    const double&  operator()(int y) const { return this->data[y]; };
    double&  operator()(int y) { return this->data[y]; };
    const double&  operator()(int y, int x) const { return this->data[y*this->row+x]; };
    double&  operator()(int y, int x) { return this->data[y*this->row+x]; };   

    PR1_DATA& operator=(const PR1_DATA &other); //대입연산자

    PR1_DATA();
    ~PR1_DATA();
};

typedef PR1_DATA       Data;

class Node
{
  public :
    Data data;
    class Node *next;
};

class PR1_QUEUE
{
  private :

    Node *front;
    Node *rear;

  public :
    bool IsEmpty();
    PR1_QUEUE& operator<<(const Data &data); //Enqueue
    PR1_QUEUE& operator>>(Data &data); //Dequeue
    void lwrite(const char *lname);
    PR1_QUEUE();
    ~PR1_QUEUE();
};

#endif
