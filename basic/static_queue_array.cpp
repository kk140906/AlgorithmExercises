//
// Created by KK on 2022/3/18.
//

#include <iostream>

using namespace std;

const int N = 1e6 + 10;
int queue[N], head = 0, tail = -1;

void push(int val) {
  queue[++tail] = val;
}

void pop() {
  ++head;
}

bool empty() {
  return head > tail;
}

int front() {
  return queue[head];
}


int main() {
  int arr[] = {10,15,16,22,12,11,2,5,7,8,4,5,757,16};
  for (int i : arr) push(i);
  while(!empty()) {
    cout << front() << " ";
    pop();
  }
  return 0;
}