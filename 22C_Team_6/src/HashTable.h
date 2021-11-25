#pragma once

#include <vector>
#include <functional>
#include "LinkedList.h"

template<typename Key, typename Value>
class HashTable {
public:
    using Hasher = std::function<uint64_t(const Key&)>;
    HashTable(const Hasher& hasher, size_t bucketsCount) : 
        hasher(hasher), 
        bucketsCount(bucketsCount), 
        buckets(new LinkedList<Item>[bucketsCount]) {
    }
    ~HashTable() {
        delete buckets;
    }

    HashTable(const HashTable& other) :
        bucketsCount(other.bucketsCount),
        buckets(new LinkedList<Item>[other.bucketsCount]),
        numberOfCollisions(other.numberOfCollisions),
        filledBuckets(other.filledBuckets) {
        for (int i = 0; i < other.bucketsCount; i++) {
            buckets[i] = other.buckets[i];
        }
    }

    HashTable& operator=(const HashTable& other) {
        delete buckets;
        bucketsCount = other.bucketsCount;
        buckets = new LinkedList<Item>[other.bucketsCount];
        numberOfCollisions = other.numberOfCollisions;
        filledBuckets = other.filledBuckets;
        for (int i = 0; i < other.bucketsCount; i++) {
            buckets[i] = other.buckets[i];
        }
        return *this;
    }

    HashTable(HashTable&& other) {
        bucketsCount = other.bucketsCount;
        buckets = other.buckets;
        numberOfCollisions = other.numberOfCollisions;
        filledBuckets = other.filledBuckets;
        other.bucketsCount = 0;
        other.buckets = nullptr;
        other.numberOfCollisions = 0;
        other.filledBuckets = 0;
    }

    HashTable& operator=(HashTable&& other) {
        bucketsCount = other.bucketsCount;
        buckets = other.buckets;
        numberOfCollisions = other.numberOfCollisions;
        filledBuckets = other.filledBuckets;
        other.bucketsCount = 0;
        other.buckets = nullptr;
        other.numberOfCollisions = 0;
        other.filledBuckets = 0;
        return *this;
    }

    void add(const Key& key, const Value& value) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        if (bucket.empty()) {
            filledBuckets++;
        } else {
            numberOfCollisions++;
        }
        bucket.pushBack({key, value});
    }

    void remove(const Key& key) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({key});
        if (it == bucket.end()) {
            return;
        }
        bucket.remove(it);
        if (bucket.empty()) {
            filledBuckets--;
        }
    }

    bool remove(const Key& key, Value& value) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({key});
        if (it == bucket.end()) {
            return false;
        }
        value = (*it).value;
        bucket.remove(it);
        if (bucket.empty()) {
            filledBuckets--;
        }
        return true;
    }

    bool find(const Key& key, Value& value) const {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({key});
        if (it == bucket.end()) {
            return false;
        }
        value = (*it).value;
        return true;
    }

    double getLoadFactor() const {
        return static_cast<double>(filledBuckets) / bucketsCount;
    }

    size_t getNumberOfCollisions() const {
        return numberOfCollisions;
    }
    
    size_t getBucketsCount() const {
        return bucketsCount;
    }

    void rehash(size_t newBuckets) {
        auto oldBuckets = buckets;
        size_t oldBucketsCount = bucketsCount;
        buckets = new LinkedList<Item>[newBuckets];
        bucketsCount = newBuckets;
        numberOfCollisions = 0;
        filledBuckets = 0;
        
        for (size_t i = 0; i < oldBucketsCount; i++) {
            auto& bucket = oldBuckets[i];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                add((*it).key, (*it).value);
            }
        }
    }
private:
    struct Item {
        Key key;
        Value value;
        bool operator==(const Item& other) const {
            return key == other.key;
        }
        bool operator!=(const Item& other) const {
            return key != other.key;
        }
    };

    size_t hashKey(const Key& key) const {
        return hasher(key) % bucketsCount;
    }

    Hasher hasher;
    size_t bucketsCount{0};
    LinkedList<Item>* buckets{nullptr};
    size_t numberOfCollisions{0};
    size_t filledBuckets{0};
};