#pragma once

template<typename T>
class LinkedList {
public:  
    struct Node {
        T value{};
        Node* prev{nullptr};
        Node* next{nullptr};
    };
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
        // sentinetals
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

    LinkedList(const LinkedList& other) {
        auto it = other.begin();
        while (it != other.end()) {
            pushBack(*it);
            ++it;
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        auto it = other.begin();
        while (it != other.end()) {
            pushBack(*it);
            ++it;
        }
        return *this;
    }

    LinkedList(LinkedList&& other) {
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }

    LinkedList& operator=(LinkedList&& other) {
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
        return *this;
    }

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

    Iterator begin() const { return Iterator(head->next); }

    Iterator end() const { return Iterator(tail); }

    Iterator find(T value) {
        auto it = begin();
        while (it != end() && *it != value) {
            ++it;
        }
        return it;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }
private:
    Node* head;
    Node* tail;
    size_t size_;
};