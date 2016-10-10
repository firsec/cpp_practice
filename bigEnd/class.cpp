#include<iostream>
using namespace std;

class s{
  public:
    s():a(1),b(2),x(3){
      cout<<"construct s"<<endl;
    }
    long int b;
    int a;
    int x;
};

class m:public s{
  public:
    m(int v):a(v),b(2),x(3){
      cout<<"construct m"<<endl;
    }
    int x;
  private:
    int a;
    int b;
};

int main(int argc, char* argv) {
  m o;
  s o1;
//  int *p=(int *)&;
  cout<<sizeof(o1)<<endl;
  cout<<sizeof(o)<<endl;
  cout<<*(((int *)(&o)))<<endl;
  cout<<*(((int *)(&o)) + 1)<<endl;
  cout<<*(((int *)(&o)) + 2)<<endl;
}
