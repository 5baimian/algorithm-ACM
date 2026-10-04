#include <iostream>
#include <vector> 

using namespace std;

class Solution{
public:
    void moveZeroes(vector<int>& nums){
        //使用双指针进行移动0
        //left 用于指向下一个可能已送的整数位置，right 用于遍历数组，找到非0的元素
        int left = 0;
        for(int right = 0; right < nums.size();right++){
            if(nums[right] != 0){
                swap(nums[left], nums[right]);
                left++;
            }
        }
    }
};

int main(){
    vector<int> nums = {0, 1, 0, 3,12};
    Solution solution;
    solution.moveZeroes(nums);

    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }

    return 0;
}