#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
  vector<int> a;
  a.push_back(11);
  a.push_back(22);
  a.push_back(33);
  a.push_back(44);
  a.push_back(55);
  a.erase(remove_if(a.begin(),a.end(), 
        [](int e){return e%2==1;}),a.end());
}
