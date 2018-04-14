#pragma once

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

struct trie_t {
  map<char, trie_t> children;
  string value;
  bool end;

  explicit trie_t(const string &val = "") : value(val), end(false) {}

  void add(char);
  bool find(const string &);
  void insert(const string &);
  vector<string> all_prefixes();
  vector<string> autocomplete(const string &);
  bool can_find_unambigously(const string &prefix, const string &word);
};

void trie_t::add(char c) {
  if (value == "")
    children[c] = trie_t(string(1, c));
  else
    children[c] = trie_t(value + c);
}

bool trie_t::find(const string &word) {
  trie_t *node = this;
  for (size_t i = 0; i < word.length(); ++i) {
    char c = word[i];
    if (node->children.find(c) == node->children.end())
      return false;
    node = &node->children[c];
  }
  return node->end;
}

void trie_t::insert(const string &word) {
  trie_t *node = this;
  for (size_t i = 0; i < word.length(); ++i) {
    char c = word[i];
    if (node->children.find(c) == node->children.end())
      node->add(c);
    node = &node->children[c];
  }
  node->end = true;
}

vector<string> trie_t::all_prefixes() {
  vector<string> results;
  if (end)
    results.push_back(value);

  if (children.size())
    for (auto iter = children.begin(); iter != children.end(); ++iter) {
      vector<string> nodes = iter->second.all_prefixes();
      results.insert(results.end(), nodes.begin(), nodes.end());
    }

  return results;
}

vector<string> trie_t::autocomplete(const string &prefix) {
  trie_t *node = this;
  vector<string> results;
  for (size_t i = 0; i < prefix.length(); ++i) {
    char c = prefix[i];
    if (node->children.find(c) == node->children.end())
      return results;
    else
      node = &node->children[c];
  }
  return node->all_prefixes();
}

bool trie_t::can_find_unambigously(const string &prefix, const string &word) {
  vector<string> results = autocomplete(prefix);
  return (results.size() == 1 && results[0] == word);
}

