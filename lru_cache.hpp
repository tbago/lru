#ifndef LRU_CACHE_HPP_
#define LRU_CACHE_HPP_

#include <unordered_map>

template <typename K, typename V>
class LRUNode {
public:
    LRUNode() : prev_(nullptr), next_(nullptr) {}
public:
    K key_;
    V value_;
    LRUNode *prev_;
    LRUNode *next_;
};

template <typename K, typename V>
class LRUCache {
public:
    LRUCache(int capacity)
        : capacity_(capacity), head_(nullptr), tail_(nullptr) {}
    ~LRUCache();
public:
    void Add(const K key, const V value);
    bool Search(const K key, V &value);
    int GetCount() const { return map_.size(); }
private:
    void MoveNodeToHead(LRUNode<K, V> *node);
private:
    int capacity_;
    LRUNode<K, V> *head_;
    LRUNode<K, V> *tail_;
    // 通过hashmap来优化查找性能
    std::unordered_map<K, LRUNode<K, V> *> map_;
};  // class LRUCache

template <typename K, typename V>
LRUCache<K, V>::~LRUCache() {
    if (head_ != nullptr) {
        auto index_node = head_;
        while (index_node != nullptr) {
            auto pre_node = index_node;
            index_node = index_node->next_;
            delete pre_node;
        }
        head_ = nullptr;
    }
}

template <typename K, typename V>
void LRUCache<K, V>::Add(const K key, const V value) {
    if (map_.count(key) != 0) {
        auto node = map_[key];
        node->value_ = value;

        // 将节点移动到第一个位置
        MoveNodeToHead(node);
        return;
    }

    // 添加新的节点
    if (map_.size() >= capacity_) {  // 大于存储容量时删除尾节点
        assert(tail_ != nullptr);
        auto node = tail_;
        map_.erase(node->key_);
        tail_ = tail_->prev_;
        if (tail_ != nullptr) {
            tail_->next_ = nullptr;
        }
        delete node;
    }

    auto new_node = new LRUNode<K, V>();
    new_node->key_ = key;
    new_node->value_ = value;
    if (head_ == nullptr) {
        head_ = tail_ = new_node;
    } else {
        new_node->next_ = head_;
        head_->prev_ = new_node;
        head_ = new_node;
    }
    map_[key] = new_node;
}

template <typename K, typename V>
bool LRUCache<K, V>::Search(const K key, V &value) {
    if (map_.count(key) != 0) {
        auto node = map_[key];
        value = node->value_;
        MoveNodeToHead(node);        
        return true;
    }
    return false;
}

template <typename K, typename V>
void LRUCache<K, V>::MoveNodeToHead(LRUNode<K, V> *node) {
    if (node == head_) {
        return;
    }

    if (node == tail_) {
        tail_ = node->prev_;
        tail_->next_ = nullptr;
    } else {
        node->next_->prev_ = node->prev_;
        node->prev_->next_ = node->next_;
    }

    node->next_ = head_;
    node->prev_ = nullptr;
    head_->prev_ = node;
    head_ = node;
}
#endif  // LRU_CACHE_HPP_
