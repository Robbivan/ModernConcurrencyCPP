#include <iostream>
#include <mutex>


class ForwardList{
    struct Node{
        Node* next;
    };
public:

    void Push(){

        // лучше не использовать unique_lock
        // RAII только lock, unlock в lock_guard
        std::lock_guard guard(mutex_);
        Node* new_node = new Node();
        new_node->next = head_;
        head_ = new_node;

        // для такого кода лучше делать отдельные новые скопы, если они
        // не совпадают с окончанием метода(функции)
        {}
        // также можно регулировать lock_guard

    }

    //Race Condition - общая проблема // Data race - одна ячейка
    void Pop(){
        Node * head = head_;
        head_ = head->next;
        delete head;
    }
private:

    Node*head_{nullptr}; // в clang есть GUARDED_BY(mutex)
    std::mutex mutex_
};
int main(){

}
