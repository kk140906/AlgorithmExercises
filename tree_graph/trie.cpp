//
// Created by KK on 2022/3/20.
//


/**
 * Trie ��һ��ǰ׺����Ҳ��Ϊ�ֵ����� �ֵ�����ÿ���ߴ�����ĸ���Ӹ���㵽����ĳ������·���ʹ�����һ���ַ���
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
      if (pos < 0 || pos >= 26) return false; // ��ֹ�����ַ��������Խ��
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

  bool m_end{false}; // ��ʾ���ʽ���
  shared_ptr<Trie> m_children[26]{nullptr}; // ����ָ�룬���Զ�̬������ Trie �ڲ������Ķ���
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