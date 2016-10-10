#include <iostream>
#include <list>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

//----------------> y
//| 1,1 1,2 ...
//| 2,1 ...
//| ...
//|
//|
//V
//x



class Orienteering {
  public:
    void main();
    bool parseData();
    void printDataArray();
    void wavePropagate(pair<int, int> &pos, int checkPointPos);
    int getShortestPath();
    void initDataArrTags();
    void initArray(int width, int height);
  private:
    
    struct dataUnit {
      dataUnit():tag(false),initValue_(0){}
      int initValue_;
      vector<int> distanceVec_;
      bool tag;
    };
    vector<vector<dataUnit> > dataArray_; //pair<value,tag>
    vector<pair<int,int> > checkPoints_; //the 1st and 2nd is S and G, others are real checkpoints.
};

void Orienteering::initArray(int width, int height) {
  dataUnit tmpDataUnit;
  vector<dataUnit> tmpDataUnitVec(width,tmpDataUnit); 
  for(int i = 0; i < height; ++i) {
    dataArray_.push_back(tmpDataUnitVec);
  }
}

int Orienteering::getShortestPath() {
}

void Orienteering::initDataArrTags() {
  int height = dataArray_.size();
  int width = dataArray_[0].size();
  for(int i = 0; i< height; ++i) {
    for(int j = 0; j<width; ++j) {
      dataArray_[i][j].tag = false;
    }
  }
}

void Orienteering::wavePropagate(pair<int, int> &pos,int checkPointPos) {
  list<pair<int,int> > queue;
  list<int> curValueList;
  initDataArrTags();
  //BFS
  queue.push_back(pos);
  curValueList.push_back(0);
  dataArray_[pos.first][pos.second].distanceVec_.push_back(0);
  dataArray_[pos.first][pos.second].tag = true;
  for(;!queue.empty();) {
    pair<int,int> curPos = queue.front();
//    cout<<curPos.first<<" "<<curPos.second<<endl;
    int curValue = curValueList.front();
    ++curValue;
    if(dataArray_[curPos.first][curPos.second-1].initValue_ != -1 && !dataArray_[curPos.first][curPos.second-1].tag) {
      dataArray_[curPos.first][curPos.second - 1].distanceVec_.push_back(curValue);
      dataArray_[curPos.first][curPos.second - 1].tag = true;
      queue.push_back(make_pair(curPos.first, curPos.second - 1));
      curValueList.push_back(curValue);
    }
    if(dataArray_[curPos.first-1][curPos.second].initValue_ != -1 && !dataArray_[curPos.first-1][curPos.second].tag) {
      dataArray_[curPos.first-1][curPos.second].distanceVec_.push_back(curValue);
      dataArray_[curPos.first-1][curPos.second].tag = true;
      queue.push_back(make_pair(curPos.first-1, curPos.second));
      curValueList.push_back(curValue);
    }
    if(dataArray_[curPos.first][curPos.second+1].initValue_ != -1 && !dataArray_[curPos.first][curPos.second+1].tag) {
      dataArray_[curPos.first][curPos.second + 1].distanceVec_.push_back(curValue);      
      dataArray_[curPos.first][curPos.second+1].tag = true;
      queue.push_back(make_pair(curPos.first, curPos.second+1));
      curValueList.push_back(curValue);
    }
    if(dataArray_[curPos.first+1][curPos.second].initValue_ != -1 && !dataArray_[curPos.first+1][curPos.second].tag) {
      dataArray_[curPos.first+1][curPos.second].distanceVec_.push_back(curValue); 
      dataArray_[curPos.first+1][curPos.second].tag = true;
      queue.push_back(make_pair(curPos.first+1, curPos.second));
      curValueList.push_back(curValue);
    }
    queue.pop_front();
    curValueList.pop_front();
  }
    
  cout<<"after wave propagation from ("<<pos.first<<", "<<pos.second<<")"<<endl;
  printDataArray();

}

void Orienteering::printDataArray() {
  int height = dataArray_.size();
  int width = dataArray_[0].size();
  cout<<"init data:"<<endl;
  for(int i = 0; i< height; ++i) {
    for(int j = 0; j<width; ++j) {
      cout<<setw(5)<<dataArray_[i][j].initValue_;
    }
    cout<<endl;
  }
  cout<<"check points: (1st S, 2nd G)"<<endl;
  for(int i = 0; i < checkPoints_.size(); ++i) {
    cout<<"("<<checkPoints_[i].first<<", "<<checkPoints_[i].second<<") ";
  }
  for(int ii = 0;ii < dataArray_[0][0].distanceVec_.size();++ii) {
    cout<<"No."<<ii + 1<<"wave propagatation array:"<<endl;
    for(int i = 0; i< height; ++i) {
      for(int j = 0; j<width; ++j) {
        cout<<setw(5)<<dataArray_[i][j].distanceVec_[ii];
      }
      cout<<endl;
    }
  }

  cout<<endl;
}

bool Orienteering::parseData() {
  int width, height;
  cin>>width>>height;
  if(!(width > 0 && height >0)) {
    cout<<"Error: bad width or height"<<endl;
    return false;
  }
  cout<<"width "<<width<<", height "<<height<<endl;
  initArray(width, height);
  checkPoints_.clear();
  checkPoints_.push_back(make_pair(-1,-1)); //checkPoints_[0]  S
  checkPoints_.push_back(make_pair(-1,-1)); //checkPoints_[1]  G

  for(int i = 0; i<height; ++i) {
    string line;
    cin>>line;
    cout<<"line "<<i<<" is: "<<line<<endl;
    string::iterator strPos = line.begin();
    if(line.compare(0, 1, "#") != 0 || line.compare(line.size()-1, 1, "#") != 0 || line.size() != width)
      return false;
    for(int j = 0; j < line.size(); ++j) {
      if(i == 0 || i == height - 1) {
        if(line.compare(j, 1, "#") !=0)
          return false;
      }
      if(line.compare(j,1,"#") == 0) {
        dataArray_[i][j].initValue_ = -1;
      } else if(line.compare(j,1,"@") == 0) {
        checkPoints_.push_back(make_pair(i,j));
      } else if(line.compare(j,1,"S") == 0) {
        checkPoints_[0].first = i;
        checkPoints_[0].second = j;
//        checkPoints_[0].swap(make_pair(i,j));
      } else if(line.compare(j,1,"G") == 0) {
        checkPoints_[1].first = i;
        checkPoints_[1].second = j;
//        checkPoints_[1].swap(make_pair(i,j));
      }
    }      
  }
  if(checkPoints_[0] == make_pair(-1,-1) || checkPoints_[1] == make_pair(-1,-1))
    return false;
  return true;
}

void Orienteering::main() {
  //implementation

  if(!parseData()) {
    cout<<"Data input Error!"<<endl;
//    return -1;
  }
  printDataArray();
  for(int i = 0; i < checkPoints_.size(); ++i) {
    cout<<"haoyu"<<endl;
    wavePropagate(checkPoints_[i],i);
  }
//  cout<<getShortestPath()<<endl;;
  return;
}
