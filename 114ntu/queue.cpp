#include <iostream>
using namespace std;
class Queue {
public:
    Queue() : backPtr(NULL) {}
    void enqueue(int x); // 在 queue 尾加入 item x
    int dequeue();   // 空回 -1，不空回 front 的 item
    int length();    // 回傳節點數
    void reverse();  // 將整個 queue 反轉

private:
    struct QueueNode {
        int item;
        QueueNode* next;
    };

    QueueNode* backPtr; // 指向最後一個節點
};

int Queue::length() {
    // 空佇列
    if (backPtr == NULL)
        return 0;

    int count = 1;
    QueueNode* current = backPtr->next; // front node

    // 環狀串列：從 front 開始數，直到回到 front
    while (current != backPtr) {
        current = current->next;
        count++;
    }

    return count;
}


int Queue::dequeue() {
    // 空佇列
    if (backPtr == NULL)
        return -1;

    QueueNode* front = backPtr->next; // front 為 backPtr->next
    int value = front->item;

    // 情況 1：只有一個節點
    if (front == backPtr) {
        delete front;
        backPtr = NULL; // queue 變空
    }
    // 情況 2：多個節點
    else {
        backPtr->next = front->next; // 略過 front 節點
        delete front;
    }

    return value;
}


void Queue::enqueue(int x) {
    QueueNode* newNode = new QueueNode;
    newNode->item = x;

    // Case 1：queue 原本是空的
    if (backPtr == NULL) {
        backPtr = newNode;
        newNode->next = newNode;  // 自己指向自己，形成環
    }
    // Case 2：queue 非空
    else {
        newNode->next = backPtr->next; // 新節點指向 front
        backPtr->next = newNode;       // 舊 back 指向新節點
        backPtr = newNode;             // backPtr 更新成新節點
    }
}


void Queue::reverse() {
    // 空或只有一個節點：無需反轉
    if (backPtr == NULL || backPtr->next == backPtr)
        return;

    QueueNode* front = backPtr->next;  // 起點
    QueueNode* prev = backPtr;         // 一開始 prev 指向 back
    QueueNode* curr = front;           // 從 front 開始
    QueueNode* next = NULL;

    // 反轉整個環，直到回到 front
    do {
        next = curr->next;
        curr->next = prev;  // reverse
        prev = curr;
        curr = next;
    } while (curr != front);

    // 最終調整 backPtr：
    // 原本 front → 變成新的 back
    backPtr = front;
}


int main(){
    Queue q;
    cout << "Length of queue: " << q.length() << endl;
    cout << "enqueue 10" << endl;
    q.enqueue(10);
    cout << "Length of queue: " << q.length() << endl;
    cout << "enqueue 20" << endl;
    q.enqueue(20);
    cout << "Length of queue: " << q.length() << endl;
    cout << "reverse the queue" << endl;
    q.reverse();
    cout << "Length of queue: " << q.length() << endl;
    cout << "dequeue: " ;
    cout << q.dequeue() << endl;
    cout << "Length of queue: " << q.length() << endl;
    cout << "enqueue 30" << endl;
    q.enqueue(30);
    cout << "Length of queue: " << q.length() << endl;
    cout << "dequeue: " ;
    cout << q.dequeue() << endl;
    cout << "Length of queue: " << q.length() << endl;
    cout << "reverse the queue" << endl;
    q.reverse();
    cout << "Length of queue: " << q.length() << endl;
    cout << "dequeue: " ;
    cout << q.dequeue() << endl;
    cout << "Length of queue: " << q.length() << endl;
    cout << "dequeue: " ;
    cout << q.dequeue() << endl; // empty queue
    cout << "Length of queue: " << q.length() << endl;
    cout << "reverse the queue" << endl;
    q.reverse();
    cout << "Length of queue: " << q.length() << endl;
}