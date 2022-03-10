#include "header.h"
#include <iostream>


Queue::Queue() : first(nullptr), last(nullptr), queue_size(0) { 
}

Queue::Queue(Queue&& other) noexcept { 
    first = other.first;
    last = other.last;
    queue_size = other.queue_size;
}

Queue& Queue::operator=(Queue&& other) noexcept 
{
    if (this != &other) {
        delete first;
        delete last;
        first = other.first;
        last = other.last;
        queue_size = other.queue_size;
        other.first = nullptr;
        other.last = nullptr;
        other.queue_size = 0;
    }
    return *this;
}

Queue::~Queue() {
    delete first;
    delete last;
}

bool Queue::is_empty() const {
    return first == nullptr;
}

void Queue::push_back(int _val, int _prior) {
    Node* p = first;
    Node* prev = first;
    int i = 0;
    while ((p && p->val < _val) || (p && p->val == _val && p->prior < _prior)) {
        prev = p;
        p = p->next;
        ++i;
    }
    if (queue_size == 0) {
        Node* new_elem = new Node(_val);
        new_elem->prior = _prior;
        new_elem->next = last;
        first = new_elem;
        ++queue_size;
        return;
    }
    else if (i == 0) {
        Node* new_elem = new Node(_val);
        new_elem->prior = _prior;
        new_elem->next = first->next;
        first = new_elem;
        last = new_elem;
        ++queue_size;
        return;
    }
    Node* new_elem = new Node(_val);
    new_elem->prior = _prior;
    new_elem->next = p;
    prev->next = new_elem;
    ++queue_size;
}

int Queue::find_quan_with_prior(int _val,
    int _prior) const {
    Node* p = first;
    int k = 0;
    while (p) {
        if (p->val == _val && p->prior == _prior)
            ++k;
        p = p->next;

    }
    return k;
}

int Queue::find_quan(int _val) const {
    Node* p = first;
    int k = 0;
    while (p) {
        if (p->val == _val)
            ++k;
        p = p->next;

    }
    return k;
}

int Queue::get_size() const {
    return queue_size;
}

void Queue::remove(int _val) {
    if (is_empty())
        return;
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != _val) {
        fast = fast->next;
        slow = slow->next;
    }
    if (!fast) {
        std::cout << "This element does not exist" << std::endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
    --queue_size;
}

Node* Queue::get_head_info() const {
    if (is_empty())
        return nullptr;
    Node* p = first;
    for (int i = 0; i < queue_size - 1; i++) {
        p = p->next;
        if (!p)
            return nullptr;
    }
    return p;
}

Queue CreateQueue() {
    Queue r;
    return r;
}


int main() {
    int rear_high = 1;
    int rear_medium = 2;
    int rear_low = 3;
    Queue l; 
    Queue r = CreateQueue(); 
    Queue r1 = r;            
    r1 = CreateQueue();       

    std::cout << l.is_empty() << std::endl; 
    l.push_back(1);
    std::cout << l.get_size() << std::endl; 
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5, rear_high); 
    l.push_back(6, rear_medium); 
    l.push_back(7);
    l.push_back(8, rear_low); 
    std::cout << r.get_size() << std::endl;
    l.remove(8); 
    std::cout << (l.get_head_info())->val << " " << (l.get_head_info())->prior << std::endl; 
    std::cout << l.find_quan(1234) << std::endl;  
    std::cout << l.find_quan_with_prior(6, rear_medium) << std::endl; 
    return 0;
}