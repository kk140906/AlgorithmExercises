//
// Created by KK on 2022/3/23.
//

/**
 * union find (并查集) 是在近乎 O(1) 时间复杂度下快速判断两个元素是否属于同一个集合或者完成两个集合合并的数据结构
 * 并查集数据的存储形式是树，树根表示集合的编号
 * 当需要判断某个元素是否在某个集合中时，只需要不停的向上查找父结点，直至最终的根结点即可，
 * 但是从树的某个结点向上查找根结点的时间复杂度并不是 O(1),因此并查集做了两个优化
 * 1. 路径压缩：查找的过程中将某个元素的父结点直接指向根结点，从而实现查找路径的压缩
 * 2. 按秩合并：将树高度低的集合合并到高度高的集合中(优化有限，一般不常用)
 */

/**
 * 洛谷 P3367 并查集 https://www.luogu.com.cn/problem/P3367
 * 题目描述
 * 如题，现在有一个并查集，你需要完成合并和查询操作。
 *
 * 输入格式
 * 第一行包含两个整数 N,M,表示共有 N 个元素和 M 个操作。
 * 接下来 M 行，每行包含三个整数 Zi,Xi,Yi
 * 当 Zi = 1 时，将 Xi 与 Yi 所在的集合合并。
 * 当 Zi = 2 时，输出 Xi 与 Yi 是否在同一集合内，是的输出 Y ；否则输出 N 。
 *
 * 输出格式
 * 对于每一个 Zi=2 的操作，都有一行输出，每行包含一个大写字母，为 Y 或者 N 。
 *
 * 输入输出样例
 * 输入
 * 4 7
 * 2 1 2
 * 1 1 2
 * 2 1 2
 * 1 3 4
 * 2 1 4
 * 1 2 3
 * 2 1 4
 * 输出
 * N
 * Y
 * N
 * Y
 * 说明/提示
 * 对于 30% 的数据，N ≤ 10，M ≤ 20。
 * 对于 70% 的数据，N ≤ 100，M ≤ 10^3。
 * 对于 100% 的数据，1 ≤ N ≤ 10^4, 1 ≤ M ≤ 2×10^5, 1 ≤ Xi,Yi ≤ N，Zi ∈ {1,2}。
 */



#include <iostream>
#include <string>

using namespace std;

const int N = 100010;

// p[i] 存储的是元素 i 的父结点编号
int p[N];

void init() {
  for (int i = 0; i < N; ++i) p[i] = i; // 初始化每个元素都是一个单独的集合
}

// 查找树的根结点
int find(int a) {
  // 除了根结点以外， p[a] != a
  if (p[a] != a) p[a] = find(p[a]); // 路径压缩的过程, 递归返回的是根结点，直接将结点 a 的父结点指向根结点
  return p[a];
}

void union_set(int a, int b) {
  int s1 = find(a), s2 = find(b);
  if (s1 == s2) return;
  p[s1] = s2; // 将集合 s1 合并到集合 s2中
}


int main() {
  init();
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 1) union_set(b, c);
    else if (a == 2) find(b) == find(c) ? puts("Y") : puts("N");
  }

  return 0;
}