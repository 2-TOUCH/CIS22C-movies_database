#pragma once

/**~*~*
 * Linked list implementation internally used by HashTable
*~**/
template<typename T>
class LinkedList {
public:  
    struct Node {
        T value{};
        Node* prev{nullptr};
        Node* next{nullptr};
    };

    // Iterator class
    class Iterator {
    public:
        Iterator(Node* node) : node(node) {}
        T& operator*() { return node->value; }
        Iterator& operator++() { node = node->next; return *this; }
        bool operator==(const Iterator& other) { return node == other.node; }
        bool operator!=(const Iterator& other) { return node != other.node; }
        Node* node;
    };

    LinkedList() : size_(0) {
        // head and tail sentinetals
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
    }

    ~LinkedList() {
        auto it = begin();
        // when head = nullptr && tail == nullptr, this will be noop
        while (it != end()) {
            it = remove(it);
        }
        delete tail;
    }

    /**~*~*
     * Copy constructor
     * It copies all the values from scratch. O(n)
    *~**/
    LinkedList(const LinkedList& other) {
        auto it = other.begin();
        while (it != other.end()) {
            pushBack(*it);
            ++it;
        }
    }

    /**~*~*
     * Copy assignment operator
     * It copies all the values from scratch. O(n)
    *~**/
    LinkedList& operator=(const LinkedList& other) {
        auto it = other.begin();
        while (it != other.end()) {
            pushBack(*it);
            ++it;
        }
        return *this;
    }

    /**~*~*
     * Move constructor
     * It does not copy all the values but only copies the pointers. O(1)
    *~**/
    LinkedList(LinkedList&& other) {
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }

    /**~*~*
     * Move assignmnet operator
     * It does not copy all the values but only copies the pointers. O(1)
    *~**/
    LinkedList& operator=(LinkedList&& other) {
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
        return *this;
    }

    /**~*~*
     * Inserts a new entry at the back
     * @param value the entry to add
    *~**/
    void pushBack(T value) {
        auto node = new Node();
        node->value = value;

        auto prev = tail->prev;
        node->next = tail;
        node->prev = prev;

        prev->next = node;
        tail->prev = node;
        size_++;
    }

    /**~*~*
     * Remove the entry at the specified iterator point and returns the next iterator
     * @param it the iterator point to remove
    *~**/
    Iterator remove(const Iterator& it) {
        auto node = it.node;
        auto next = node->next;
        auto prev = node->prev;

        prev->next = next;
        next->prev = prev;
        
        delete node;

        size_--;
        return Iterator(next);
    }

    /**~*~*
     * Returns the iterator pointing to the first element
     * @return begin iterator
    *~**/
    Iterator begin() const { return Iterator(head->next); }

    /**~*~*
     * Returns the iterator pointing to the tail sentinetal node
     * @return end iterator
    *~**/
    Iterator end() const { return Iterator(tail); }

    /**~*~*
     * Find the iterator pointing to the element with the specified value
     * @return iterator pointing to the element if found, end() otherwise
    *~**/
    Iterator find(T value) {
        auto it = begin();
        while (it != end() && *it != value) {
            ++it;
        }
        return it;
    }

    /**~*~*
     * Returns the number of elements in the list
     * @return number of elements
     *~**/
    size_t size() const {
        return size_;
    }

    /**~*~*
     * Is this list empty?
     * @return true if empty, false otherwise
     *~**/
    bool empty() const {
        return size_ == 0;
    }
private:
    Node* head;
    Node* tail;
    size_t size_;
};