#include<iostream>
using namespace std;
int main(int argc, char * argv) {
  struct s {
    int a;
    int *b;
  };
  int v = 8;
  s m;
  m.b = &v;
  m.a = 5;
 
  cout<<sizeof(m)<<endl; // total 16, a 4 ,aligment 4, b 8
  int *p = (int *)&m;
  cout<<m.a<<endl; // get a value
  cout<<*p<<endl; //use p get a value, p point to m and a int type.
  cout<<&m.b<<endl;//get address of m.b
  cout<<p+2<<endl; //get address of m.b using p, p+1 is aligment not used.
  cout<<*(m.b)<<endl;//get value m.b pointed.
  cout<<*(int *)*(long int *)(p+2)<<endl;//get valuse m.b pointed using p. Here v can see p+2 pointed to the start of b. 
  //For b is 8byte, we need to convert p+2 to a 8byte type pointer such as long int *
  // now (long int *)(p+2) is a pointer which pointed to the context m.b, so *(long int *)(p+2) can get the context of b which is same with m.b
  // but when we get the address using *(long int *)(p+2), we didn't it's type ,so we need to convert the type to int *, when we can get the right value
}
