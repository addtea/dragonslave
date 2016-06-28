#pragma once

namespace dragonslave {


template <typename TData>
class LinkedList;


template <typename TData>
struct LinkedListNode
{
    TData* data = nullptr;
    LinkedListNode* next = nullptr;
    LinkedListNode* prev = nullptr;

    LinkedListNode(TData* data)
      : data (data)
    { }
};


template<typename TData>
class LinkedList
{
public:
    LinkedList() { }
    virtual ~LinkedList() { }

    LinkedListNode<TData>* get_head() const { return head_; }

    void add(LinkedListNode<TData>* node);
    void remove(LinkedListNode<TData>* node);

    void clear();

private:
    LinkedListNode<TData>* head_ = nullptr;
    LinkedListNode<TData>* tail_ = nullptr;
};


template <typename TData>
void LinkedList<TData>::add(LinkedListNode<TData>* node)
{
    if (!head_) {
        node->next = nullptr;
        node->prev = nullptr;
        head_ = node;
        tail_ = node;
    } else {
        tail_->next = node;
        node->prev = tail_;
        node->next = nullptr;
        tail_ = node;
    }
}


template <typename TData>
void LinkedList<TData>::remove(LinkedListNode<TData>* node)
{
    if (head_ == node) {
        head_ = node->next;
    }
    if (tail_ == node) {
        tail_ = node->prev;
    }
    if (node->prev) {
        node->prev->next = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->next = nullptr;
    node->prev = nullptr;
}


template <typename TData>
void LinkedList<TData>::clear()
{
    LinkedListNode<TData>* it = head_;
    while (it) {
        it->next = nullptr;
        it->prev = nullptr;
        it = it->next;
    }
    head_ = nullptr;
    tail_ = nullptr;
}


}
