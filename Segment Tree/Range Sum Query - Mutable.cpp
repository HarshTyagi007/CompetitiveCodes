//https://leetcode.com/problems/range-sum-query-mutable/
/*
Given an integer array nums, handle multiple queries of the following types:

Update the value of an element in nums.
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
void update(int index, int val) Updates the value of nums[index] to be val.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).
 

Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8
 

Constraints:

1 <= nums.length <= 3 * 104
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
At most 3 * 104 calls will be made to update and sumRange.
*/

class NumArray {
public:
    vector<int> segTree;
    int low,high;
    
    NumArray(vector<int>& nums) {
        int n=nums.size();
        //max size for segment tree would be 4*N
        segTree.resize(4*n,0);//Initializing all with zeroes
        low=0;
        high=n-1;
        buildSegTree(0,low,high,nums);
    }
    
    void buildSegTree(int idx,int low,int high,vector<int> &nums){
        if(low==high)
        {
            segTree[idx]=nums[high];
            return ;
        }
        int mid=(low+high)/2;
        buildSegTree(2*idx+1,low,mid,nums);
        buildSegTree(2*idx+2,mid+1,high,nums);
        segTree[idx]=segTree[2*idx+1]+segTree[2*idx+2];
    }
    
    void updateSegTree(int idx,int low,int high,int i,int val){
        if(low==high)
        {
            segTree[idx]=val;
            return;
        }
        int mid=(low+high)/2;
        if(i<=mid)//means elements is on left side of segment Tree
         updateSegTree(2*idx+1,low,mid,i,val);
        else updateSegTree(2*idx+2,mid+1,high,i,val);
        segTree[idx]=segTree[2*idx+1]+segTree[2*idx+2];
    }
    
    void update(int index, int val) {
        updateSegTree(0,low,high,index,val);
    }
    
    int findQuery(int idx,int low,int high,int left,int right){
        //no overlap
        if(left > high or right < low)
            return 0;
        //complete overlap
        if(left<=low and right>=high)
            return segTree[idx];
        //partial wala case
        int mid=(low+high)/2;
        int leftAns=findQuery(2*idx+1,low,mid,left,right);
        int rightAns=findQuery(2*idx+2,mid+1,high,left,right);
        return (leftAns+rightAns);
    }
    
    int sumRange(int left, int right) {
        return findQuery(0,low,high,left,right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
