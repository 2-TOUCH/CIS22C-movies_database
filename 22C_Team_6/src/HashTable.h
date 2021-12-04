#pragma once

#include <functional>
#include <vector>

#include "LinkedList.h"

/**
 * Hash table implementation.
 * Collission resolution is done by linked list
 * @param Key the type of the key
 * @param Value the type of the entry
 */
template <typename Key, typename Value>
class HashTable {
  public:
    using Hasher = std::function<uint64_t(const Key&)>;
    /**
     * Constructor
     * @param hasher the hash function that receives Key type and returns uint64_t value
     * @param bucketsCount the initial bucket count
     */
    HashTable(const Hasher& hasher, size_t bucketsCount)
        : hasher(hasher), bucketsCount(bucketsCount), buckets(new LinkedList<Item>[bucketsCount]) {
    }

    /**
     * Destructor
     */
    ~HashTable() {
        delete[] buckets;
    }

    /**
     * Copy constructor
     * It copies all the values from scratch. O(n)
     */
    HashTable(const HashTable& other)
        : bucketsCount(other.bucketsCount), buckets(new LinkedList<Item>[other.bucketsCount]), numberOfCollisions(other.numberOfCollisions), filledBuckets(other.filledBuckets) {
        for (int i = 0; i < other.bucketsCount; i++) {
            buckets[i] = other.buckets[i];
        }
    }

    /**
     * Copy assignment operator
     * It copies all the values from scratch. O(n)
     */
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

    /**
     * Move constructor
     * It does not copy all the values but only copies the pointers. O(1)
     */
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

    /**
     * Move assignmnet operator
     * It does not copy all the values but only copies the pointers. O(1)
     */
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

    /**
     * Inserts a new entry into the table.
     * @param key the key of the entry
     * @param value the value of the entry
     */
    void add(const Key& key, const Value& value) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({ key });
        if (it != bucket.end()) {
            (*it).value = value;
        } else {
            if (bucket.empty()) {
                filledBuckets++;
            } else {
                numberOfCollisions++;
            }
            bucket.pushBack({ key, value });
        }
    }

    /**
     * Removes a entry from the table.
     * @param key the key of the entry
     */
    void remove(const Key& key) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({ key });
        if (it == bucket.end()) {
            return;
        }
        bucket.remove(it);
        if (bucket.empty()) {
            filledBuckets--;
        }
    }

    /**
     * Removes a entry from the table, and copies the removed value to the output reference.
     * @param key the key of the entry
     * @param value the output reference that receives the value of the entry
     * @return true if the entry was found, false otherwise
     */
    bool remove(const Key& key, Value& value) {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({ key });
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

    /**
     * Finds a entry in the table.
     * @param key the key of the entry
     * @param value the output reference that receives the value of the entry
     * @return true if the entry was found, false otherwise
     */
    bool find(const Key& key, Value& value) const {
        auto hash = hashKey(key);
        auto& bucket = buckets[hash];
        auto it = bucket.find({ key });
        if (it == bucket.end()) {
            return false;
        }
        value = (*it).value;
        return true;
    }

    /**
     * List every entry in the table
     * @return vector of entries
     */
    std::vector<Value> list() const {
        std::vector<Value> result{};
        for (int i = 0; i < bucketsCount; i++) {
            auto& bucket = buckets[i];
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                result.push_back((*it).value);
            }
        }
        return result;
    }

    /**
     * Get load factor of the buckets
     * @return load factor
     */
    double getLoadFactor() const {
        return static_cast<double>(filledBuckets) / bucketsCount;
    }

    /**
     * Get number of collisions so far after the last rehashing
     * @return number of collisions
     */
    size_t getNumberOfCollisions() const {
        return numberOfCollisions;
    }

    /**
     * Get number of buckets
     * @return number of buckets
     */
    size_t getBucketsCount() const {
        return bucketsCount;
    }

    /**
     * Rehash the table with the specifid bucket count
     * @param newBucketsCount the new bucket count
     */
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
    size_t bucketsCount{ 0 };
    LinkedList<Item>* buckets{ nullptr };
    size_t numberOfCollisions{ 0 };
    size_t filledBuckets{ 0 };
};
