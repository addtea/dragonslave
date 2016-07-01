#include <algorithm>
#include <memory>
#include <vector>

namespace dragonslave {


template <typename TData>
struct PriorityQueueNode 
{
    TData* data = nullptr;
    int    index = -1;
    double priority = 0.f;

    PriorityQueueNode(TData* data)
      : data {data}
    { }
};


template <typename TData>
class PriorityQueue
{
public:
    PriorityQueue() { }
    virtual ~PriorityQueue() { }

    TData* get_front() const;

    PriorityQueueNode<TData>* enqueue(TData* data);
    void dequeue();
    void update(PriorityQueueNode<TData>* node);
    void clear();

private:
    std::vector<std::unique_ptr<PriorityQueueNode<TData> > > heap_;
};


template <typename TData>
TData* PriorityQueue<TData>::get_front() const
{
    if (heap_.is_empty()) {
        return nullptr;
    }
    return heap_.front()->data;
}


template <typename TData>
PriorityQueueNode<TData>* PriorityQueue<TData>::enqueue(TData* data)
{
    heap_.push_back(std::make_unique<PriorityQueueNode<TData> >(data));
    PriorityQueueNode<TData>* node = heap_.back().get();
    node->index = heap_.size() - 1;
    update(node);
    return node;
}


template <typename TData>
void PriorityQueue<TData>::dequeue()
{
    heap_.front().swap(heap_.back());
    heap_.pop_back();
    PriorityQueueNode<TData>* node = heap_.front().get();
    node->index = 0;
    while (2 * node->index + 1 < heap_.size()) {
        PriorityQueueNode<TData>* left = heap_[2 * node->index + 1].get();
        PriorityQueueNode<TData>* max_child = left;
        if (2 * node->index + 2 < heap_.size()) {
            PriorityQueueNode<TData>* right = heap_[2 * node->index + 2].get();
            if (right->priority > left->priority) {
                max_child = right;
            }
        }
        if (node->priority >= max_child->priority) break;
        heap_[node->index].swap(heap_[max_child->index]);
        std::swap(node->index, max_child->index);
    }
}


template <typename TData>
void PriorityQueue<TData>::update(PriorityQueueNode<TData>* node)
{
    while (node->index) {
        PriorityQueueNode<TData>* parent = heap_[node->index / 2].get();
        if (parent->priority >= node->priority) break;
        heap_[node->index].swap(heap_[parent->index]);
        std::swap(node->index, parent->index);
    }
}


template <typename TData>
void PriorityQueue<TData>::clear()
{
    heap_.clear();
}


}
