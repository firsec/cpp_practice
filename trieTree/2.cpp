#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Node {
  public:    
    Node(basic_string<char> s):self(s[0]),asChildNr(0) {
      insert(s);
      //cout<<"New a Node: with "<<s<<endl;
    }
    bool insert(basic_string<char> s) {      
      if(self!=s[0]) { return false;}
      if(s.size()==1) {
        asChildNr++;
        //cout<<"child "<<asChildNr<<endl;
        return true;
      }
      bool inserted = false;
      //try to insert into sub tree;
      for(unsigned int i=0;i<child_.size();++i) {
        if(child_[i].insert(s.substr(1,s.size()-1))) {
          inserted = true;
          asChildNr++;
          break;
        }
      }

      //make a new branch
      if(!inserted) {
        child_.push_back(Node(s.substr(1,s.size()-1)));
        inserted = true;
        asChildNr++;
      }
      return inserted;
    }

    unsigned int getToHereAsPreStrNr() {
      unsigned int total = asChildNr;
      for(unsigned int i=0;i<child_.size();++i) {
        total+=child_[i].getToHereAsPreStrNr();
      }
      return total;
    }
    unsigned int getComPreStrNr(basic_string<char> s) {
      if(self != s[0]) {
        //cout<<s<<" but "<<self<<endl;
        return 0;
      }
      if(s.size()==1) {
        return asChildNr;
      } else {
        unsigned int total=0;
        for(unsigned int i=0;i<child_.size();++i) {
          total += child_[i].getComPreStrNr(s.substr(1,s.size()-1));
        }
        return total;
      }
    }

  private:
    char self;
    unsigned int asChildNr;
    vector<Node> child_;
};

class Tree {
  public:
    void insert(basic_string<char> s) {
      for(unsigned int i=0;i<subTree_.size();++i) {
        if(subTree_[i].insert(s)) {
          return;
        }
      }
      Node node(s);
      subTree_.push_back(node);
    }
    unsigned int getComPreStrNr(basic_string<char> s) {
      //cout<<"Checking string: "<<s<<endl;
      unsigned int totalComPreStrNr = 0;
      for(unsigned int i=0;i<subTree_.size();++i) {
        totalComPreStrNr += subTree_[i].getComPreStrNr(s);
      }
      return totalComPreStrNr;
    }
  private:
    vector<Node> subTree_;

};

int main() {
  int n;
  cin>>n;
  Tree ss;
  for(;n>0;--n) {
    basic_string<char> s;
    cin>>s;
    //cout<<s<<endl;
    ss.insert(s);
  }
  cin>>n;
  for(;n>0;--n){
    basic_string<char> s;
    cin>>s;
    //cout<<s<<endl;
    cout<<ss.getComPreStrNr(s)<<endl;
  }

}
