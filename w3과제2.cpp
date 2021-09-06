// Alphabet

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
    bool isItem(int item) {
        bool flag = false;
        for (int i = 0; i <= top; i++) 
            if (data[i] == item) {
                flag = true; 
                break;
            }
        return flag;
    }

};

int main()
{
    int n = 0;
    char ch, max;       // ch: 입력 데이터 
    OperandStack s;     // stack
    char pm[100];       // plus, minus 저장 배열
    int index = 0;      // pm[100] 배열 인덱스

    cin >> n;
    max = 'a'-1;    // max: 현재까지 스택에 들어온 알파벳 중 가장 큰 알파벳

    for (int i = 0; i < n; i++) {
        cin >> ch; 

        for (char c = max+1; c < ch; c++) { // max부터 현재 입력 데이터 바로 이전 알파벳까지 push
            s.push(c);
            pm[index++] = '+';              // 추후 출력을 위해 '+'를 배열에 저장
        }
        if (s.isEmpty() || ch != s.peek()) {   // 현재 입력 데이터가 스택 top 데이터와 다른 경우 push
            if (s.isItem(ch)) {                 // 현재 입력 데이터가 이미 스택에 pop할 수 없는 위치에 있으면 NO 출력
                cout << endl << "NO" << endl; 
                exit(1);
            }
            s.push(ch);
            pm[index++] = '+';              // 추후 출력을 위해 '+'를 배열에 저장
        }
        s.pop();                            // 현재 입력 데이터 출력
        pm[index++] = '-';                  // 추후 출력을 위해 '-'를 배열에 저장

        if (max < ch) max = ch;             // 현재까지 스택에 들어온 가장 큰 알파벳 업데이트
    }
    cout << endl;
    for (int i = 0; i < index; i++) cout << pm[i] << endl;

    return 0;
}

