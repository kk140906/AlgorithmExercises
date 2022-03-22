//
// Created by KK on 2022/3/22.
//

/**
 * 字符串前缀 Hash 是一种特殊的 Hash 方法, 核心问题有两个
 * 1. 如何将字符串转换成整数进而转换成普通的 hash 方法, 这里通常采用 P 进制数转换, 根据经验 p 通常取 131 或者 13331
 * 例如 hash("abcde")  ------> a * p^4 + b * p^3 + c * p^2 + d * p^1 + e * p^0;
 * 2. 如何根据前面字符串计算最终字符串的 hash 值
 * 假设 H[i] 表示以索引 i 结尾的字符形成的字符串的 hash 值
 * 那么 H[0] = a * p^0;
 *     H[1] = H[0] * p + b  ----> a * p^1 + b;
 *     H[2] = H[1] * p + c  ----> a * p^2 + b * p^1 + c;
 *     H[3] = H[2] * p + d  ----> a * p^3 + b * p^2 + c * p^1 + d * p^0;
 * 注意： 不能将一个字母映射成 0 ，否者 A 和 AA .... AAAA ...等字符串将被映射成 0；
 * 由于字符串可以很长，因此最终的数值会比较大，最终的结果需要对某个数取模，通常为 2^64,
 * C++ 中超过 unsigned long long 的将会被自动取模
 * 常见操作：判断某几个区间内的子串是否相等
 *
 *
 * 洛谷 P3370 字符串哈希 https://www.luogu.com.cn/problem/P3370
 * 题目描述
 * 如题，给定 N 个字符串（第 i 个字符串长度为 Mi，字符串内包含数字、大小写字母，大小写敏感），请求出 N 个字符串中共有多少个不同的字符串。
 *
 * 输入格式
 * 第一行包含一个整数 N，为字符串的个数。
 * 接下来 N 行每行包含一个字符串，为所提供的字符串。
 * 输出格式
 * 输出包含一行，包含一个整数，为不同的字符串个数。
 *
 * 输入输出样例
 * 输入
 * 5
 * abc
 * aaaa
 * abc
 * abcc
 * 12345
 * 输出
 * 4
 * 说明/提示
 * 对于 30% 的数据：N ≤ 10，Mi ≈ 6 Mmax ≤ 15。
 * 对于 70% 的数据：N ≤ 1000，Mi ≈ 100，Mmax ≤ 150。
 * 对于 100% 的数据：N ≤ 10000，Mi ≈ 1000，Mmax ≤ 1500。
 */


#include <iostream>
#include <string>
#include <cstring>

using namespace std;
using ULL = unsigned long long;
const int P = 131;
const int N = 30000;
const int NONE = 0x3f3f3f3f;

int H[N];

ULL string_hash(string s) {
  ULL prev = s[0];
  if (static_cast<int>(s[0]) == 0) prev = 1;
  for (int i = 1; i < s.size(); ++i) {
    prev = prev * P + s[i]; // 注意加的 s[i] 不能为 0 否者将会发生冲突
  }
  return prev;
}

int find(int x) {
  int k = (x % N + N) % N;
  while(H[k] != NONE && H[k] != x) {
    k++;
    if (k == N) k = 0;
  }
  return k;
}


int main() {
  memset(H, 0x3f, sizeof H);
  int n;
  cin >> n;
  int res = 0;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    int x = string_hash(s);
    int k = find(x);
    if (H[k] == x) continue;
    H[k] = string_hash(s);
    res++;
  }
  cout << res << endl;
  return 0;
}