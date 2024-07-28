class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int sum{};
        int ind = 0;
        for(int i = 0; i < nums.size(); ++i){
            sum += nums[i];
            ind += i;
        }

        ind += nums.size();
        return ind - sum;
    }
};
