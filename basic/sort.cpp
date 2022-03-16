#pragma ide diagnostic ignored "misc-no-recursion"
//
// Created by KK on 2022/3/9.
//

#include <iostream>
#include <random_data_sets.hpp>

using namespace std;

// 左闭，右闭区间
// 从小到大排序
/**
 * @detail 选择锚点，根据锚点值进行划分，使得锚点左侧的值不大于锚点值，锚点右侧的值不小于锚点值，然后递归的对左右两侧进行快速排序
 *
 * @param nums 待排序的数组
 * @param left 需要排序的起始索引
 * @param right 需要排序的结束索引
 */
void quick_sort(vector<int> &nums, int left, int right) {
  if (left >= right) return;

  int pivot = nums[left];
  int i = left - 1, j = right + 1;

  while (i < j) {
    while (nums[++i] < pivot);
    while (nums[--j] > pivot);
    if (i < j) swap(nums[i], nums[j]);
  }

  quick_sort(nums, left, j);
  quick_sort(nums, j + 1, right);
}

// 左闭 右闭区间
/**
 * @details 先划分区域，直至区域无法被划分后开始递归的对左右两个区域进行排序
 *
 * @param nums 待排序的数据
 * @param left 区域的左边界
 * @param right 区域的右边界
 * @param tmp 临时存储区，用于存储已被排序的区域数据
 */
void merge_sort(vector<int> &nums, int left, int right, vector<int> &tmp) {
  if (left >= right) return;
  int mid = left + ((right - left) >> 1);
  merge_sort(nums, left, mid, tmp);
  merge_sort(nums, mid + 1, right, tmp);

  int i = left, j = mid + 1;
  int k = 0;
  while (i <= mid && j <= right) {
    if (nums[i] <= nums[j]) { // 等号保证排序的稳定性
      tmp[k++] = nums[i++];
    } else {
      tmp[k++] = nums[j++];
    }
  }

  while (i <= mid) {
    tmp[k++] = nums[i++];
  }

  while (j <= right) {
    tmp[k++] = nums[j++];
  }

  for (int m = 0, n = left; m < k; ++m, ++n) {
    nums[n] = tmp[m];
  }
}


/**
 * @details 堆有序化，从堆根向下有序化，先假设最大结点在根结点，然后分别从左右两个子结点选取最大值作为下一次迭代的根结点
 * @param nums
 * @param low
 * @param high
 */
void heapify(vector<int> &nums, int low, int high) {
  while (low <= high) {
    int left = 2 * low + 1, right = 2 * low + 2;
    int maxIndex = low;
    if (left <= high && nums[left] > nums[maxIndex]) maxIndex = left;
    if (right <= high && nums[right] > nums[maxIndex]) maxIndex = right;
    if (maxIndex == low) break;
    swap(nums[maxIndex], nums[low]);
    low = maxIndex;
  }
}

/**
 * @details 先对待排序数据进行一轮堆有序化，使其成为一个堆，然后交换堆顶和堆最后一个位置，
 *          这样最后的一个位置就是最大的，然后对剩余的数据进行堆有序化即可
 * @param nums 待排序的数据
 */
void heap_sort(vector<int> &nums) {
  int n = static_cast<int>(nums.size() - 1);
  for (int i = n >> 1; i >= 0; --i) heapify(nums, i, n);
  for (int i = n; i > 0; --i) {
    swap(nums[0], nums[i]);
    heapify(nums, 0, i - 1);
  }
}


int main() {
//  vector<int> res{23, 44, 60, 60, 100, 79};
  auto res = random_dataset(0, 10000, 1000000);
  int n = static_cast<int>(res.size());
  cout << "排序前: " << endl;
  if (n <= 50) {
    for (int c: res) cout << c << " ";
    cout << endl;
  }

  vector<int> tmp(res.size());
  quick_sort(res, 0, n - 1);
  merge_sort(res, 0, n - 1, tmp);
  heap_sort(res);

  cout << "排序后: " << endl;
  int last = -1;
  for (int c: res) {
    if (n <= 50) cout << c << " ";
    if (last <= c) last = c;
    else cout << "jk";
  }

  return 0;
}
