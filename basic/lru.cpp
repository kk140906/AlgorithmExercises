//
// Created by KK on 2022/3/15.
//

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>


using namespace std;

using TimeStamp = chrono::time_point<chrono::system_clock>;

struct Node {
  Node(int k, int v, Node *prev = nullptr, Node *next = nullptr) : key(k), value(v) {
    if (prev) {
      this->prev = prev;
      prev->next = this;
    }
    if (next) {
      this->next = next;
      next->prev = this;
    }
  }

  int key, value;
  TimeStamp time;
  Node *prev, *next;
};

class LRU {
public:
  explicit LRU(int capacity, int expired) : m_cap(capacity), m_expired(expired) {}

  int get(int key) {
    lock_guard<mutex> guard(m_lock);

    remove_expired();

    if (m_cache.find(key) != m_cache.end()) {
      auto node = m_cache[key];
      move_to_head(node);
      return node->value;
    }
    return -1;
  }

  void put(int key, int value) {

    lock_guard<mutex> guard(m_lock);

    remove_expired();

    if (m_cache.find(key) != m_cache.end()) {
      auto node = m_cache[key];
      node->value = value;
      move_to_head(node);
    } else {
      if (m_cache.size() == m_cap) {
        remove_from_tail();
      }
      auto node = new Node(key, value);
      insert_to_head(node);
    }
  }


private:
  void insert_to_head(Node *node) {
    node->next = m_head->next;
    node->prev = m_head;

    m_head->next = node;
    node->next->prev = node;

    if (m_cache.find(node->key) == m_cache.end()) m_cache[node->key] = node;
    node->time = chrono::system_clock::now();
  }

  void remove(Node *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void remove_from_tail() {
    auto node = m_tail->prev;
    remove(node);
    m_cache.erase(node->key);
  }

  void remove_expired() {
    auto now = chrono::system_clock::now();
    auto p = m_tail->prev;
    while (p != m_head) {
      auto expired = p->time + chrono::seconds(m_expired);
      if (now < expired) break;
      p = p->prev;
      remove_from_tail();
    }
  }

  void move_to_head(Node *node) {
    remove(node);
    insert_to_head(node);
  }

  friend ostream &operator<<(ostream &os, const LRU &rhs) {
    auto p = rhs.m_head->next;
    while (p != rhs.m_tail) {
      os << p->value << " ";
      p = p->next;
    }
    return os;
  }

private:
  int m_cap;
  int m_expired; // seconds
  mutex m_lock;
  unordered_map<int, Node *> m_cache;
  Node *m_head{new Node(-1, -1)};
  Node *m_tail{new Node(-1, -1, m_head)};
};


int main() {

  LRU lru(10, 5);


  for (int i = 1; i <= 3; ++i) {
    lru.put(i, i);
  }
  lru.put(9, 9);
  cout << lru << endl;
  cout << "get: " << 2 << " -- " << lru.get(2) << endl;
  cout << lru << endl;
  this_thread::sleep_for(chrono::seconds(2));
  cout << "get: " << 9 << " -- " << lru.get(9) << endl;
  cout << lru << endl;
  this_thread::sleep_for(chrono::seconds(4));
  cout << "get: " << 2 << " -- " << lru.get(2) << endl;
  cout << lru << endl;

  vector<thread> ths;

  for (int i = 1; i <= 25; ++i) {
    ths.emplace_back(&LRU::put, &lru, i, i);
    ths.emplace_back(&LRU::get, &lru, i);
  }

  for (auto &th : ths) {
    th.join();
  }
  cout << lru << endl;
  return 0;
}

