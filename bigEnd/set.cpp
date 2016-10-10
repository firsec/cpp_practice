#include<set>
#include<iostream>
using namespace std;
int main(int argc, char* argv) {
  set<int> a;
  a.insert(1);
  a.insert(2);
  a.insert(3);
  set<int>::iterator pos = a.begin();
  for(;pos != a.end();pos++) {
    cout<<*pos<<endl;
  }
}
