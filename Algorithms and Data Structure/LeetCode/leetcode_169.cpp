class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int ele=nums[0];
        int count = 0;
        for(int i = 0; i < nums.size(); i++){
            if(ele == nums[i]){
                count++;
            }
            else if(ele != nums[i]){
                count--;
            }
            if(count == 0){
                ele = nums[i+1];
            }
        }
        return ele;
    }
};
