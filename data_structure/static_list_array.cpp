//
// Created by KK on 2022/3/18.
//

#include <iostream>

using namespace std;

const int N = 1e6 + 10;

// Node[i] 表示第 i 个结点的值
// Next[i] 表示第 i 个结点的下一个结点的索引
// Prev[i] 表示第 i 个结点的上一个结点的索引
// cur 表示当前已经操作到的索引
// head 表示头结点索引
// tail 表示尾结点索引
int Node[N], Next[N], Prev[N], cur, head, tail;

void init_list() {
  head = 0;
  tail = 1;
  cur = 2;
  Prev[head] = -1;
  Next[head] = tail;
  Prev[tail] = head;
  Next[tail] = -1;
}


/**
 *
 * @param k   第 k 个位置后面插入数据， k 从 1 开始计数
 * @param val 被插入的数据
 */
void insert(int k, int val) {
  int p = head;
  while (k && p != tail) {
    p = Next[p];
    k--;
  }

  if (k && p == tail) {
    cout << "插入结点位置溢出" << endl;
    return;
  }

  Node[cur] = val;
  Next[cur] = Next[p];
  Prev[cur] = p;
  Prev[Next[p]] = cur;
  Next[p] = cur;
  cur++;
}

/**
 * @details 在链表的头部插入数据
 * @param val 被插入的数据
 */
void insert_head(int val) {
  insert(head, val);
}

/**
 * @details 在链表的尾部插入数据
 * @param val 被插入的数据
 */
void insert_tail(int val) {
  Node[cur] = val;
  Next[cur] = tail;
  Prev[cur] = Prev[tail];
  Next[Prev[tail]] = cur;
  Prev[tail] = cur;
  cur++;
}

/**
 * @param k 移除第 k 个位置的结点， k 从 1 开始计数
 */
void remove(int k) {
  int p = head;
  while(k && p != tail) {
    p = Next[p];
    k--;
  }
  if (p == tail || p == head) {
    cout << "删除结点位置溢出" << endl;
    return;
  }

  Next[Prev[p]] = Next[p];
  Prev[Next[p]] = Prev[p];
}


void print_list() {
  int p = Next[head];
  while (p != tail) {
    cout << Node[p] << " ";
    p = Next[p];
  }
  cout << endl;
}



int main() {
  init_list();
  int arr[] = {12,5,4,7,8,84,5,7,8,54};
  cout << "头插法：" << endl;
  for(int i : arr) insert_head(i);
  print_list();

  cout << "尾插法:" << endl;
  for(int i : arr) insert_tail(i);
  print_list();

  cout << "依次移除第1个位置的结点" << endl;
  for (int i = 0; i < 20; i++) {
    print_list();
    remove(1);
  }

  return 0;
}