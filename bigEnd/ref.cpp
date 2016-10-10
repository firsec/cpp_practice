#include<iostream>
using namespace std;

int main(int argc,char * argv) {
  float a = 1.0f;
  int *p = (int *)&a;
  cout << hex <<*p<<endl;
  cout << sizeof(float) <<endl;
  cout << sizeof(int) <<endl;
  cout << (int)a << endl;
  cout << (int&)a << endl;
  cout << boolalpha << ( (int)a == (int&)a ) << endl;
  float b = 0.0f;
  cout << (int)b << endl;
  cout << (int&)b << endl;
  cout << boolalpha << ( (int)b == (int&)b ) << endl; 

}
