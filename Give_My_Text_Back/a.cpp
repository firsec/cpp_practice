#include<iostream>
#include <ctype.h>

using namespace std;

int main() {
  string a;
  while(getline(cin,a)) {
    a[0] = (char)toupper(a[0]);

    cout<<a[0];
    for(int i=1; i<a.size(); ++i) {

      if(a[i] != ' ') {
        cout<<(char)tolower(a[i]);
      } else {
        while(a[i] == ' ') {
          i++;
        }
        if(a[i] != ',' && a[i] != '.') {
          cout<<' '<<(char)tolower(a[i]);
        } else {
          cout<<a[i];
        }
      }

    }
    cout<<endl;
  }
}
