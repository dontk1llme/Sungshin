#include <iostream>
using namespace std;

#define MAX_QUEUE_SIZE  100

class CircularQueue {
protected:
    int front; 		// 첫 번째 요소 앞의 위치
    int rear; 		// 마지막 요소 위치
    int data[MAX_QUEUE_SIZE]; // 요소의 배열
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(int val) { // 큐에 삽입
        if (isFull())
        {
            cout << " error: 큐가 포화상태입니다" << endl;
            exit(-1);
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { 	// 첫 항목을 큐에서 빼서 반환
        if (isEmpty()) { cout << " Error: 큐가 공백상태입니다"; exit(-1); }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }
    int peek() { 	// 첫 항목을 큐에서 빼지 않고 반환
        if (isEmpty()) printf(" Error: 큐가 공백상태입니다\n");
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    void display() { 	// 큐의 모든 내용을 순서대로 출력
        printf("큐 내용 : ");
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