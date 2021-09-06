#include <iostream>
using namespace std;

#define MAX_QUEUE_SIZE  100

class CircularQueue {
protected:
    int front; 		// ù ��° ��� ���� ��ġ
    int rear; 		// ������ ��� ��ġ
    int data[MAX_QUEUE_SIZE]; // ����� �迭
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(int val) { // ť�� ����
        if (isFull())
        {
            cout << " error: ť�� ��ȭ�����Դϴ�" << endl;
            exit(-1);
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { 	// ù �׸��� ť���� ���� ��ȯ
        if (isEmpty()) { cout << " Error: ť�� ��������Դϴ�"; exit(-1); }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }
    int peek() { 	// ù �׸��� ť���� ���� �ʰ� ��ȯ
        if (isEmpty()) printf(" Error: ť�� ��������Դϴ�\n");
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    void display() { 	// ť�� ��� ������ ������� ���
        printf("ť ���� : ");
        int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
        for (int i = front + 1; i <= maxi; i++)
            cout << data[i % MAX_QUEUE_SIZE] << " ";
        cout << endl;
    }

    int howmany() {
        int count = 0;
        int maxi = (front < rear) ? rear : rear + MAX_QUEUE_SIZE;
        for (int i = front + 1; i <= maxi; i++)
            count++;
        return count;
    }

};

int main() {
    CircularQueue q;
    int n, k;


    cin >> n >> k;
    for (int i = 0; i < n; i++)
        q.enqueue(i + 1);



    while (q.howmany() > 1) { 
        if (q.howmany() >= k) { 
            for (int i = 0; i < k - 1; i++) {
                q.enqueue(q.peek());
                q.dequeue();
            }
            cout << q.dequeue() << " ";
            cout << q.dequeue() << " ";
        }

    }
    return 0;

}