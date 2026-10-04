#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution{
public:
    vector<int> TwoNumAdd(vector<int>& nums, int target){

        unordered_map<int, int> num_map;
        for(int i = 0; i < nums.size(); i++){
            int value = target - nums[i];
            if(num_map.find(value) != num_map.end()){
                return {num_map[value], i}; 
            }
            num_map.insert(pair<int, int>{nums[i], i});
        }
        return {};
    }
};

int main(){
    vector<int> nums = {2, 7, 9, 11};
    int target = 9;
    Solution solution;
    vector<int> result = solution.TwoNumAdd(nums, target);
    
    for(int i = 0; i < result.size(); i++){
        cout << result[i] << " ";
    }
}