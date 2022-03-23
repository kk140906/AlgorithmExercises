//
// Created by KK on 2022/3/21.
//

/**
 * hash 算法常见的方式是对一个质数取模, 由于取模操作本质是将一个大范围的数值映射到一个相对较小范围的数值，
 * 因此可能发生 Hash 冲突，对于 Hash 冲突，常用的方式有两种，
 * 一种是拉链法，即当冲突时将所有冲突的元素形成一条链表；
 * 另一种是开放地址法，即一旦发现冲突，然后依次扫描后面的所有位置，一旦发现发现空的位置，将元素放置到这个空的位置上
 * 对于开放地址法，通常需要 bucket 的数量是需要处理的数量级的 2 ~ 3 倍
 *
 * 洛谷 P4305 不重复的数字 https://www.luogu.com.cn/problem/P4305
 * 题目描述
 * 给定 n 个数，要求把其中重复的去掉，只保留第一次出现的数。
 *
 * 输入格式
 * 本题有多组数据。
 * 第一行一个整数 T，表示数据组数。
 * 对于每组数据：
 * 第一行一个整数 n。
 * 第二行 n 个数，表示给定的数。
 *
 * 输出格式
 * 对于每组数据，输出一行，为去重后剩下的数，两个数之间用一个空格隔开。
 *
 * 输入输出样例
 * 输入
 * 2
 * 11
 * 1 2 18 3 3 19 2 3 6 5 4
 * 6
 * 1 2 3 4 5 6
 * 输出
 * 1 2 18 3 19 6 5 4
 * 1 2 3 4 5 6
 *
 * 说明/提示
 * 对于 30% 的数据，n ≤ 100，给出的数 n ∈ [0,100]。
 * 对于 60% 的数据，n ≤ 10^4，给出的数 n ∈ [0,10^4]。
 * 对于 100% 的数据，1 ≤ T ≤ 50，1 ≤ n ≤ 5×10^4,给出的数在 32 位有符号整数范围内。
 *
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;
using LL = long long;

void prime(int n) {
  for (int i = n; i < INT_MAX; ++i) {
    bool flag = true;
    for (int j = 2; j * j < i; ++j) {
      if (i % j == 0) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << i << endl;
      break;
    }
  }
}

//#define OPEN_ADDRESS

#ifdef OPEN_ADDRESS
const int N = 1e5 + 3; // 数据量的 2 - 3 倍
const LL NONE = LONG_LONG_MAX; // 数据集在 int 范围，NONE 标记需要使用 int 范围之外的数据

vector<LL> H(N, NONE);

int find(int x) {
  int k = (x % N + N) % N;
  while (H[k] != NONE && H[k] != x) {
    k++;
    if (k == N) k = 0;
  }
  return k;
}

void solve() {
  int t, n;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    scanf("%d", &n);
    vector<int> a(n);
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[j]);
      int k = find(a[j]);
      if (H[k] == a[j]) continue;
      printf("%d ", a[j]);
      H[k] = a[j];
    }
    puts("");
    H = vector<LL>(N, NONE);
  }
}

#else

const int N = 50021;
const int NONE = -1;
int idx = 0;
vector<int> H(N, NONE), p(N), q(N);

int find(int x) {
  int k = (x % N + N) % N;
  int index = H[k];
  while (index != NONE) {
    if (p[index] == x) return index; // 找到 x 返回找到的 index
    index = q[index];
  }
  return NONE;
}

bool insert(int x) {
  int index = find(x);
  if (index != NONE) return false;

  int k = (x % N + N) % N;
  p[idx] = x;
  q[idx] = H[k];
  H[k] = idx;
  idx++;

  return true;
}

void solve() {

  int t, n;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    scanf("%d", &n);
    vector<int> a(n);
    for (int j = 0; j < n; ++j) {
      scanf("%d", &a[j]);
      if (insert(a[j])) printf("%d ", a[j]);
    }
    puts("");
    H = vector<int>(N, NONE);
    p = vector<int>(N);
    q = vector<int>(N);
    idx = 0;
  }
}

#endif


int main() {
  solve();
  return 0;
}

