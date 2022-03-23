//
// Created by KK on 2022/3/16.
//

/**
合并区间, leetcode 56
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。


示例 1：

输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

示例2：
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

提示：

1 <= intervals.length <= 104
intervals[i].length == 2
0 <= starti <= endi <= 104

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/merge-intervals
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


vector<vector<int>> merge_intervals(vector<vector<int>> &intervals) {

  // 合并区间，先按左端点排序
  sort(intervals.begin(), intervals.end());

  vector<vector<int>> res;
  for (auto &v: intervals) {
    int left = v[0], right = v[1];
    // 如果结果是空的，那么说明第一个区间还没加入到结果中，因此可直接加入到结果中
    // 结果的最后一个元素维护了一个动态区间，当最后一个元素的右端点比当前区间的左端点还小时，即两个区间没有交集
    // 说明当前区间无法合并到最后一个元素的区间中，将其添加到结果最后
    if (res.empty() || res.back()[1] < left) {
      res.push_back(v);
    } else {
      // 可合并区间时，取两者右端点的最大值，即实现区间合并
      res.back()[1] = max(res.back()[1], right);
    }
  }
  return res;
}


int main() {
  vector<vector<int>> intervals{
      {1,  3},
      {2,  6},
      {8,  10},
      {15, 18}
  };

  auto res = merge_intervals(intervals);
  for (auto &v: res) {
    for (int val: v) {
      cout << val << " ";
    }
    cout << endl;
  }
}