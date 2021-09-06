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
    bool isEmpty() { return front == NULL; }	// ť�� ��� �ִ��� üũ

    // ���� ����: ����� ť�� �� �ڿ� ��� ����
    void enqueue(Node* p) {
        if (isEmpty()) front = rear = p; // ���� ���� ����	
        else {	                          // ����� ���� ����
            rear->setLink(p); 	// (1) 
            rear = p;		// (2)	
        }
    }

    // ���� ����
    Node* dequeue() {
        if (isEmpty()) return NULL;
        Node* temp = front;  // (1) 
        front = front->getLink();  // (2) or NULL
        if (front == NULL) rear = NULL;	 // ��� 1���� ���
        return temp;
    }

    // ť�� ���� ù �׸� ��ȯ
    Node* peek() { return front; }

    // ť�� ��� ���� ���÷���
    void display() {
        for (Node* p = front; p != NULL; p = p->getLink())
            p->display();
        cout << endl;
    }

    // ť�� �׸� ���� ��ȯ
    int howmany() {
        int number = 0;
        for (Node* p = front; p != NULL; p = p->getLink())
            number++;
        return number;
    }

    // ť�� number ��° �׸��� ���� ��ȯ
    Node* find(int number)
    {
        Node* p = front;
        for (int i = 1; i < number; i++)  // rear ���� ��� ã��
            p = p->getLink();
        return p;
    }
};

class LinkedDeq : public LinkedQueue
{
public:
    void addRear(Node* p)   // �ڿ� ����
    {
        enqueue(p);
    }
    void deleteFront()      // �ڿ��� ����
    {
        dequeue();
    }
    void addFront(Node* p)  // �տ� ����
    {
        if (isEmpty()) front = rear = p; // ���� ���� ����	
        else {	                         // ����� ���� ����
            p->setLink(front);
            front = p;
        }
    }
    Node* deleteRear()      // �ڿ��� ����
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
            prev->setLink(NULL);                // ���� ����� link�� NULL��
            rear = prev;
        }
        return temp;                            // �����ϴ� ��� ��ȯ
    }

    Node* delete2nd()       // 2��° �׸� ����
    {
        if (isEmpty() || howmany() <2) return NULL;
        Node* prev = find(1);   // find 1st Node
        Node* temp = find(2);   // find 2nd Node

        prev->setLink(temp->getLink());
        return temp;                            // �����ϴ� ��� ��ȯ
    }
};

int main()
{
    LinkedDeq q;
    int n;
    int cm[100];
    int number = 1;

    // ����� �Է�
    cin >> n;
    for (int i = 0; i < n; i++) cin >> cm[i];

    for (int i = 0; i < n; i++)
    {
        switch (cm[i]) {
        case 1:     // ť�� �տ� ����
            q.addFront(new Node(number));
            number++;
            break;
        case 2:     // ť�� �ڿ��� ����
            q.deleteRear();
            break;
        case 3:     // ť�� 2��° �׸� ����
            q.delete2nd();
            break;
        }
    }
    cout << endl;
    q.display();    // ť�� ��� �׸� ���÷���

    return 0;
}

