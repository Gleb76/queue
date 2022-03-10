#pragma once

struct Node {
    int val; 
    Node* next; 
    int prior; 
    explicit Node(int _val) : val(_val), next(nullptr), prior(0) {
    }
};

class Queue {
public:
    Queue();
    ~Queue();
    Queue(Queue&& other) noexcept; 
    Queue& operator=(Queue&& other) noexcept; 
    Queue(const Queue& other) = default; 
    bool is_empty() const; 
    void push_back(int _val, int _prior = 0); 
    int find_quan_with_prior(int _val,
        int _prior) const; 
    int find_quan(int _val) const; 
    int get_size() const; 
    void remove(int _val); 
    Node* get_head_info() const;
    friend Queue CreateQueue();

private:
    Node* first; 
    Node* last; 
    int queue_size;
};