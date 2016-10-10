#include<vector>
#include<iostream>
using namespace std;
class Solution {
  public:
    int removeDuplicates(vector<int>& nums) {
      int cnt=0;
      vector<int> newNums;
      newNums.push_back(nums[0]);
      for(unsigned i=1;i<nums.size();++i) {
        if(nums[i-1]==nums[i]) {
          cnt++;
        } else {
          cnt=0;
        }
        if(cnt<2) {
          newNums.push_back(nums[i]);
        }

      }
      nums.swap(newNums);
      return nums.size();
    }
};

int main(){
  vector<int> nums={1,1,1,2,2,3};
  Solution s;
  cout<<s.removeDuplicates(nums);
}
