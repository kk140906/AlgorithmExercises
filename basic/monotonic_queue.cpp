//
// Created by KK on 2022/3/19.
//

// 单调队列: 洛谷 P1886: 滑动窗口 https://www.luogu.com.cn/problem/P1886

/**
 * 题目描述
 * 有一个长为 nn 的序列 aa，以及一个大小为 kk 的窗口。现在这个从左边开始向右滑动，每次滑动一个单位，求出每次滑动后窗口中的最大值和最小值。
 *
 * 输入格式
 * 输入一共有两行，第一行有两个正整数 n,kn,k。 第二行 nn 个整数，表示序列 aa
 *
 * 输出格式
 * 输出共两行，第一行为每次窗口滑动的最小值
 * 第二行为每次窗口滑动的最大值
 *
 * 输入输出样例
 *
 *  输入
 * 8 3
 * 1 3 -1 -3 5 3 6 7
 *
 *  输出
 * -1 -3 -3 -3 3 3
 * 3 3 5 5 6 7
 *
 * 说明/提示
 * 【数据范围】
 * 对于 50% 的数据，1 ≤ n ≤ 10^5;
 * 对于 100% 的数据，1 ≤ k ≤ n ≤ 10^6, ，a[i] ∈ [-2^31,2^31)
 */


#include <cstdio>
#include <functional>

using namespace std;

const int N = 1e6 + 10;
int n, k;
int a[N];

// h 表示队首， t 表示队尾
int h = 1, t = 0;
// q[i] 表示单调队列，保存原数组的下标， res 保存最终的结果
int q[N], res[N];

void monotonic_queue(const function<bool(int lhs, int rhs)>& comp) {
  h = 1, t = 0; // 初始化队首，队尾
  for (int i = 1; i <= n; ++i) {
    // 单调队列与单调栈不同的地方是单调队列需要同时考虑队首和队尾的出队情况
    while (h <= t && q[h] + k <= i) h++;
    while (h <= t && comp(a[i], a[q[t]])) t--;
    q[++t] = i;
    if (i >= k) res[i - k + 1] = a[q[h]];
    printf("i = %d : ----- ", i);
    for(int j = h; j <= t; ++j) {
      printf("%d ", a[q[j]]);
    }
    puts("");
  }
  for (int i = 1; i <= n - k + 1; ++i) printf("%d ", res[i]);
  puts("");
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  // 单调递增队列，保证队首永远是最小值即可
  monotonic_queue([](int lhs, int rhs) {return lhs <= rhs;});

  // 单调递减队列，保证队首永远是最大值即可
  monotonic_queue([](int lhs, int rhs) {return lhs >= rhs;});

  return 0;
}