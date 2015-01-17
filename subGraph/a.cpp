#include<vector>
#include<iostream>

using namespace std;

int main() {
  int n;
  cin>>n;
  vector<vector<pair<int,int> > > array;
  for(;n>0;--n) {
    int h,w;
    cin>>h>>w;
    vector<pair<int,int> > pic;
    for(int i=0;i<h;i++) {
      string s;
      cin>>s;
      for(int j=0;j<w;j++) {
        if(s[j] == '#') {
          pic.push_back(make_pair(i,j));
        }
      }
    }
    //the last one save h,w
    pic.push_back(make_pair(h,w));
    array.push_back(pic);
  }
  //read sky
  int h,w;
  cin>>h>>w;
  vector<pair<int,int> > sky;
  for(int i=0;i<h;++i) {
    string s;
    cin>>s;
    for(int j=0;j<w;++j) {
      if(s[j] == '#') {
        sky.push_back(make_pair(i,j));
      }
    }
  }
  sky.push_back(make_pair(h,w));
  
  //echo sky to cache for check.
  vector<char> line(sky[sky.size()-1].second,'.');
  vector<vector<char> > outArr(sky[sky.size()-1].first,line);
  for(int i=0;i<(int)sky.size()-1;++i) {
    outArr[sky[i].first][sky[i].second] = '#';
  }
  int H=(int)outArr.size();
  int W=(int)outArr[0].size();

  //check spot

  for(int n=0;n<array.size();++n) {


//    for(int xx=0; xx<(int)tmpPicStar.size(); ++xx) {
//      cout<<tmpPicStar[xx].first<<" "<<tmpPicStar[xx].second<<endl;
//    }

    bool yes = false;
    for(int k=0;k<(int)sky.size()-1;++k) {
      //transfor the last one to the max point
      vector<pair<int,int> > tmpPicStar = array[n];
      tmpPicStar[tmpPicStar.size()-1].first-=1;
      tmpPicStar[tmpPicStar.size()-1].second-=1;
      //get offset
      int offsetX = sky[k].first-tmpPicStar[0].first;
      int offsetY = sky[k].second-tmpPicStar[0].second;
      if(tmpPicStar[tmpPicStar.size()-1].first+offsetX > H-1 || tmpPicStar[tmpPicStar.size()-1].second+offsetY > W-1) {
        continue;
      }
      if(offsetX<0 || offsetY<0) {
        continue;
      }
      bool skipCur = false;
      for(int i=0;i<(int)tmpPicStar.size()-1;++i) {
        tmpPicStar[i].first+=offsetX;
        tmpPicStar[i].second+=offsetY;
        //cout<<tmpPicStar[i].first<<" "<<tmpPicStar[i].second<<endl;
        if(tmpPicStar[i].first>H-1 || tmpPicStar[i].second>W-1) {
          skipCur = true;
          break;
        }
        if(outArr[tmpPicStar[i].first][tmpPicStar[i].second] != '#') {
          skipCur = true;
          break;
        }
      }
      if(skipCur) { continue; }
      yes = true;
      break;
    }
    if(yes) {cout<<"Yes"<<endl;} else {cout<<"No"<<endl;} 

  }
//  //echo pics for debug
//  for(int n=0;n<array.size();++n) {
//    vector<char> line(array[n][array[n].size()-1].second,'.');
//    vector<vector<char> > outArr(array[n][array[n].size()-1].first, line);
//    for(int i=0;i<(int)array[n].size()-1;++i) {
//      outArr[array[n][i].first][array[n][i].second] = '#';
//    }
//    cout<<array[n][array[n].size()-1].first<<" "<<array[n][array[n].size()-1].second<<endl;
//    for(int i=0;i<array[n][array[n].size()-1].first;++i) {
//      for(int j=0;j<array[n][array[n].size()-1].second;++j) {
//        cout<<outArr[i][j];
//      }
//      cout<<endl;
//    }
//  }
//
//
//  cout<<sky[sky.size()-1].first<<" "<<sky[sky.size()-1].second<<endl;
//  for(int i=0;i<sky[sky.size()-1].first;++i) {
//    for(int j=0;j<sky[sky.size()-1].second;++j) {
//      cout<<outArr[i][j];
//    }
//    cout<<endl;
//  }

}
