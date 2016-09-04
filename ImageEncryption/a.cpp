#include<iostream>
#include<vector>
#include<set>
#include<assert.h>
#include<algorithm>

using namespace std;

bool checkVS(vector<vector<int>>& mA, vector<vector<int>>& mB, int biA, int bjA, int biB, int bjB, int N) {
  vector<int> vA;
  vector<int> vB;
  for(int i=biA; i<biA+N; ++i) {
    for(int j=bjA; j<bjA+N;++j){
      vA.push_back(mA[i][j]);
    }
  }
  for(int i=biB; i<biB+N; ++i) {
    for(int j=bjB; j<bjB+N;++j){
      vB.push_back(mB[i][j]);
    }
  }
  
  sort(vA.begin(),vA.end());
  sort(vB.begin(),vB.end());
 
  for(int i=0; i<vA.size(); ++i) {
    if(vA[i] != vB[i]) {
      return false;
    }
  }
  return true;
}

pair<int, int> getTarRotate(int i, int j, int k, int N) {
  switch(k) {
  case 0:
    return make_pair(i,j);
    break;
  case 1:
    return make_pair(j,N-1-i);
    break;
  case 2:
    return make_pair(N-1-i,N-1-j);
    break;
  case 3:
    return make_pair(N-1-j,i);
    break;
  default:
    assert(false);
  }
}
//encryption
bool checkEnc(vector<vector<int>>& mA, vector<vector<int>>& mB,int biA, int bjA, int biB, int bjB, int N) {

  //values not consistent
  //if(!checkVS(mA, mB, biA, bjA, biB, bjB, N)) {
    //cout<<"Unconsistent Value"<<endl;
   // return false;
  //}
  
  if(N%2==1) {
    //odd, directly check and return
    int cnt = 4;
    for(int k=0; k<4; ++k) {
      bool isExit = false;
      for(int i=0; i<N; ++i) {
        for(int j=0; j<N; ++j) {
          pair<int,int> tar = getTarRotate(i, j, k, N);
          if(mA[biA+i][bjA+j] != mB[biB+tar.first][bjB+tar.second]) {
            //cout<<biA<<" "<<bjA<<" "<<i<<" "<<j<<" "<<tar.first<<" "<<tar.second<<endl;
            cnt--;
            isExit = true;
            break;
          }
        }
        if(isExit)
          break;
      }
    }
    if(cnt)
      return true;
    else 
      return false;

  } else {
    //even recursive call checkEnc
    for(int k=0; k<4; ++k) {
      switch(k) {
      case 0:
        if(  checkEnc(mA, mB, biA,     bjA,     biB,     bjB,             N/2)
          && checkEnc(mA, mB, biA,     bjA+N/2, biB,     bjB+N/2,         N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA+N/2, biB+N/2, bjB+N/2, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA,     biB+N/2, bjB,     N/2)) {
          return true;
        }
        break;
      case 1:
        if(  checkEnc(mA, mB, biA,     bjA,     biB,     bjB+N/2, N/2)
          && checkEnc(mA, mB, biA,     bjA+N/2, biB+N/2, bjB+N/2, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA+N/2, biB+N/2, bjB, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA,     biB,     bjB, N/2)) {
          return true;
        }
        break;
      case 2:
        if(  checkEnc(mA, mB, biA,     bjA,     biB+N/2, bjB+N/2, N/2)
          && checkEnc(mA, mB, biA,     bjA+N/2, biB+N/2, bjB, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA+N/2, biB,     bjB, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA,     biB,     bjB+N/2, N/2)) {
          return true;
        }
        break;
      case 3:
        if(  checkEnc(mA, mB, biA,     bjA,     biB+N/2, bjB, N/2)
          && checkEnc(mA, mB, biA,     bjA+N/2, biB,     bjB, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA+N/2, biB,     bjB+N/2, N/2) 
          && checkEnc(mA, mB, biA+N/2, bjA,     biB+N/2, bjB+N/2, N/2)) {
          return true;
        }
        break;
      default:
        assert(false);
      }
    }
    return false;
  } 
}

int main() {
  int n;
  cin>>n;
  //cout<<n;
  for(int i=0; i<n; ++i) {
    //cout<<i<<endl;
    int N;
    cin>>N;
    //cout<<N;
    vector<vector<int>> mA(N,vector<int>(N, 0));
    for(int j=0; j<N;++j) {
      for(int k=0; k<N; ++k) {
        cin>>mA[j][k];
      }
    }
    vector<vector<int>> mB(N,vector<int>(N, 0));
    for(int j=0; j<N;++j) {
      for(int k=0; k<N; ++k) {
        cin>>mB[j][k];
      }
    }

    if(checkEnc(mA, mB, 0, 0, 0, 0, N))
      cout<<"Yes"<<endl;
    else
      cout<<"No"<<endl;
   /////////
   // for(int i=0;i<4;++i) {
    //  pair<int, int> t = getTargetLoc(0,0,4,i);
      //cout<<t.first<<" "<<t.second<<endl;
    //}

    //cout<<"N "<<N<<endl;
    
  }
  return 0;
}
