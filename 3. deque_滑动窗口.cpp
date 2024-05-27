#include <iostream>
#include <deque>
#include <vector>

void slidingWindowMaximum(const std::vector<int>& nums, int k) {
    std::deque<int> window;
    
    for (size_t i = 0; i < nums.size(); ++i) {
        // 移除窗口左边界之外的元素
        if (!window.empty() && window.front() == i - k) {
            window.pop_front();
        }
        
        // 保持 `deque` 的递减顺序(单调队列)
        while (!window.empty() && nums[i] > nums[window.back()]) {
            window.pop_back();
        }
        
        // 添加当前元素的索引
        window.push_back(i);
        
        // 从窗口开始时输出最大值
        if (i >= k - 1) {
            std::cout << nums[window.front()] << " ";
        }
    }
    std::cout << std::endl;
}

int main(){
    std::vector<int> nums = {4, 6, 3, 5, 1, 0, 9};

    slidingWindowMaximum(nums, 3);

}