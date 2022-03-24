//
// Created by KK on 2022/3/20.
//


/**
 * Trie 是一种前缀树，也称为字典树。 字典树的每个边代表字母，从根结点到树上某个结点的路径就代表了一个字符串
 */


#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Trie {
public:
  bool insert(const string &word) {
    auto node = this;
    for (char c: word) {
      int pos = c - 'a';
      if (pos < 0 || pos >= 26) return false; // 防止特殊字符造成数组越界
      if (!node->m_children[pos]) node->m_children[pos] = make_shared<Trie>();
      node = node->m_children[pos].get();
    }
    node->m_end = true;
    return true;
  }

  bool search(const string &word) {
    auto node = search_prefix(word);
    return node != nullptr && node->m_end;
  }

  bool has_prefix(const string &word) {
    return search_prefix(word) != nullptr;
  }

private:
  Trie *search_prefix(const string &word) {
    auto node = this;
    if (word.empty()) return nullptr;
    for (char c: word) {
      int pos = c - 'a';
      if (pos < 0 || pos >= 26) return nullptr;
      if (!node->m_children[pos]) return nullptr;
      node = node->m_children[pos].get();
    }
    return node;
  }

  bool m_end{false}; // 表示单词结束
  shared_ptr<Trie> m_children[26]{nullptr}; // 智能指针，可以动态管理在 Trie 内部创建的对象
};


int main() {
  Trie t;
  t.insert("hello");
  t.insert("hi");
  t.insert("world");
  t.insert("helloworld");
  cout << t.search("hello world") << " " << t.search("world") << endl;
  cout << t.has_prefix("hell") << " " << t.has_prefix("ow") << endl;

  return 0;
}