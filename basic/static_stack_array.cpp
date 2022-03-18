//
// Created by KK on 2022/3/18.
//


#include <iostream>

/**
 * 通过数组来模拟静态的栈
 */

using namespace std;

const int N = 1e6 + 10;

int stack[N], topPos = -1;

inline void push (int val) {
  stack[++topPos] = val;
}

inline void pop() {
  --topPos;
}

inline bool empty() {
  return topPos == -1;
}

inline int top() {
  return stack[topPos];
}

int main() {
  int arr[] = {10,2,0,15,16,52,66,78,2};
  for (int i : arr) push(i);
  while (!empty()) {
    cout << top() << " ";
    pop();
  }
  return 0;
}