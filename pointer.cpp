#include <iostream>
using namespace std;

class Node {
    int data;
    Node* link;
public:
    Node(int val) { data = val; link = NULL; }
    Node* getLink() { return link; }
    void  setLink(Node* next) 
    {
        link = next;
    }
    void display() {
        cout << data << endl;
    }
};

class LinkedQueue {
protected:
    Node* front;
    Node* rear;
public:
    LinkedQueue() : front(NULL), rear(NULL) { }
    ~LinkedQueue() { while (!isEmpty()) delete dequeue(); }
    bool isEmpty() { return front == NULL; }	// 큐가 비어 있는지 체크

    // 삽입 연산: 연결된 큐의 맨 뒤에 노드 삽입
    void enqueue(Node* p) {
        if (isEmpty()) front = rear = p; // 공백 상태 삽입	
        else {	                          // 비공백 상태 삽입
            rear->setLink(p); 	// (1) 
            rear = p;		// (2)	
        }
    }

    // 삭제 연산
    Node* dequeue() {
        if (isEmpty()) return NULL;
        Node* temp = front;  // (1) 
        front = front->getLink();  // (2) or NULL
        if (front == NULL) rear = NULL;	 // 노드 1개인 경우
        return temp;
    }

    // 큐의 앞의 첫 항목 반환
    Node* peek() { return front; }

    // 큐의 모든 내용 디스플레이
    void display() {
        for (Node* p = front; p != NULL; p = p->getLink())
            p->display();
        cout << endl;
    }

    // 큐의 항목 갯수 반환
    int howmany() {
        int number = 0;
        for (Node* p = front; p != NULL; p = p->getLink())
            number++;
        return number;
    }

    // 큐의 number 번째 항목을 노드로 반환
    Node* find(int number)
    {
        Node* p = front;
        for (int i = 1; i < number; i++)  // rear 이전 노드 찾기
            p = p->getLink();
        return p;
    }
};

class LinkedDeq : public LinkedQueue
{
public:
    void addRear(Node* p)   // 뒤에 삽입
    {
        enqueue(p);
    }
    void deleteFront()      // 뒤에서 제거
    {
        dequeue();
    }
    void addFront(Node* p)  // 앞에 삽입
    {
        if (isEmpty()) front = rear = p; // 공백 상태 삽입	
        else {	                         // 비공백 상태 삽입
            p->setLink(front);
            front = p;
        }
    }
    Node* deleteRear()      // 뒤에서 제거
    {
        if (isEmpty()) return NULL;
        Node* temp = rear;             
        Node* prev = front;
        int number = howmany();
        if (number == 1)
        {
            front = rear = NULL;
        }
        else
        {
            prev = find(number - 1);
            prev->setLink(NULL);                // 이전 노드의 link를 NULL로
            rear = prev;
        }
        return temp;                            // 제거하는 노드 반환
    }

    Node* delete2nd()       // 2번째 항목 제거
    {
        if (isEmpty() || howmany() <2) return NULL;
        Node* prev = find(1);   // find 1st Node
        Node* temp = find(2);   // find 2nd Node

        prev->setLink(temp->getLink());
        return temp;                            // 제거하는 노드 반환
    }
};

int main()
{
    LinkedDeq q;
    int n;
    int cm[100];
    int number = 1;

    // 사용자 입력
    cin >> n;
    for (int i = 0; i < n; i++) cin >> cm[i];

    for (int i = 0; i < n; i++)
    {
        switch (cm[i]) {
        case 1:     // 큐의 앞에 삽입
            q.addFront(new Node(number));
            number++;
            break;
        case 2:     // 큐의 뒤에서 삭제
            q.deleteRear();
            break;
        case 3:     // 큐의 2번째 항목 삭제
            q.delete2nd();
            break;
        }
    }
    cout << endl;
    q.display();    // 큐의 모든 항목 디스플레이

    return 0;
}

