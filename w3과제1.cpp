// Stack

#include <iostream>
using namespace std;

#define MAX_STACK_SIZE 20

inline void error(char* message) {
    cout << message;
    exit(1);
}

class OperandStack
{
    int top;
    int maxArr[100], idx = 0;
    double data[MAX_STACK_SIZE];

public:
    OperandStack() { top = -1; }
    ~OperandStack() {}

    bool isEmpty() { return top == -1; }
    bool isFull() { return top == MAX_STACK_SIZE - 1; }

    void push(double e) {
        if (isFull()) error((char*)"stack overflow !");
        data[++top] = e;
        maxArr[idx++] = top + 1;  // push할 때마다 현재의 항목수 저장, top은 0부터 시작이므로 +1
    }
    double pop() {
        if (isEmpty()) error((char*)"stack empty !");
        return data[top--];
    }
    double peek() {
        if (isEmpty()) error((char*)"stack empty !");
        return data[top];
    }
    void display() {
        for (int i = top; i >= 0; i--) cout << data[i] << endl;
        cout << endl;
    }
    int evalSum() {
        int sum = 0;
        for (int i = 0; i <= top; i++) sum += data[i];
        return sum;
    }
};

int main()
{
    int n = 0;
    int data;
    OperandStack s, t;

    cin >> n;
   

    for (int i = 0; i < n; i++) {
        cin >> data;
        if (data == 0) {
            if (!s.isEmpty()) t.push(s.pop());
        }
        else if (data == -1) {
            if (!t.isEmpty()) s.push(t.pop());
        }
        else if (data == -2) {
            if (!s.isEmpty()) t.push(s.pop());
            if (!s.isEmpty()) t.push(s.pop());
        }
        else s.push(data);
    }
    cout << endl << s.evalSum() << endl;

    return 0;
}

