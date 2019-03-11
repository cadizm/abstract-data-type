#ifndef ORDERED_SYMBOL_TABLE_H_
#define ORDERED_SYMBOL_TABLE_H_

#include <map>
#include <vector>
#include <iterator>

template<class K, class T>
class OrderedSymbolTable {
 public:
  using iterator = typename std::map<K, T>::iterator;

  // Put key-value pair into symbol table
  void put(K key, T value) {
    if (table.find(key) != table.end()) {
      table.at(key) = value;
    } else {
      table.emplace(key, value);
    }
  }

  // Get value paired with key
  T* get(K key) {
    if (table.find(key) != table.end())
      return &table.at(key);

    return nullptr;
  }

  // Remove key and its value from table
  int remove(K key) {
    return table.erase(key);
  }

  // Is there a value paired with key
  bool contains(K key) {
    return table.find(key) != table.end() ? true : false;
  }

  // Number of key-value paris
  int size() {
    return table.size();
  }

  // Is the symbol table empty
  bool isEmpty() {
    return table.empty();
  }

  // Smallest key
  const K* min() {
    if (isEmpty())
      return nullptr;

    return &table.begin()->first;
  }

  // Largest key
  const K* max() {
    if (isEmpty())
      return nullptr;

    return &(--table.end())->first;
  }

  // Largest key less than or equal to key
  const K* floor(K key) {
    if (isEmpty())
      return nullptr;

    // lower_bound returns iterator to first element not less than key
    auto candidate = table.lower_bound(key);
    if (candidate == table.begin())
      return &candidate->first;

    return &(--candidate)->first;
  }

  // Smallest key greater than or equal to key
  const K* ceiling(K key) {
    if (isEmpty())
      return nullptr;

    // upper_bound returns iterator to the first element greater than key
    return &table.upper_bound(key)->first;
  }

  // Number of keys less than key
  // i == rank(select(i)) for all 0 <= i <= size() - 1
  int rank(K key) {
    return std::distance(table.begin(), table.lower_bound(key));
  }

  // Key of rank k
  // key == select(rank(key)) for all keys in table
  const K* select(int k) {
    int low = 0;
    int high = size() - 1;

    // binary search
    while (low <= high) {
      auto it = table.begin();
      int mid = low + ((high - low) / 2);

      std::advance(it, mid);
      int rank = std::distance(table.begin(), it);

      if (rank < k) {
        low = mid + 1;  // look to the right
      } else if (rank > k) {
        high = mid - 1;  // look to the left
      } else {
        return &it->first;
      }
    }

    return nullptr;
  }

  // Number of keys in [low, high]
  int size(K low, K high) {
    auto begin = table.lower_bound(low);
    auto end = table.upper_bound(high);

    return std::distance(begin, end);
  }

  // Keys in [low, high], in sorted order
  std::vector<K> keys(K low, K high) {
    auto begin = table.lower_bound(low);
    auto end = table.upper_bound(high);

    std::vector<K> res;
    for (auto it = begin; it != end; ++it) {
      res.push_back(it->first);
    }

    return res;
  }

  // All keys in table, in sorted order
  std::vector<K> keys() {
    std::vector<K> res;

    for (auto it = table.begin(); it != table.end(); ++it) {
      res.push_back(it->first);
    }

    return res;
  }

 private:
  std::map<K, T> table;
};

#endif  // ORDERED_SYMBOL_TABLE_H_
