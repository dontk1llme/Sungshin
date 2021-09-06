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
        maxArr[idx++] = top + 1;  // push�� ������ ������ �׸�� ����, top�� 0���� �����̹Ƿ� +1
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
    char ch, max;       // ch: �Է� ������ 
    OperandStack s;     // stack
    char pm[100];       // plus, minus ���� �迭
    int index = 0;      // pm[100] �迭 �ε���

    cin >> n;
    max = 'a'-1;    // max: ������� ���ÿ� ���� ���ĺ� �� ���� ū ���ĺ�

    for (int i = 0; i < n; i++) {
        cin >> ch; 

        for (char c = max+1; c < ch; c++) { // max���� ���� �Է� ������ �ٷ� ���� ���ĺ����� push
            s.push(c);
            pm[index++] = '+';              // ���� ����� ���� '+'�� �迭�� ����
        }
        if (s.isEmpty() || ch != s.peek()) {   // ���� �Է� �����Ͱ� ���� top �����Ϳ� �ٸ� ��� push
            if (s.isItem(ch)) {                 // ���� �Է� �����Ͱ� �̹� ���ÿ� pop�� �� ���� ��ġ�� ������ NO ���
                cout << endl << "NO" << endl; 
                exit(1);
            }
            s.push(ch);
            pm[index++] = '+';              // ���� ����� ���� '+'�� �迭�� ����
        }
        s.pop();                            // ���� �Է� ������ ���
        pm[index++] = '-';                  // ���� ����� ���� '-'�� �迭�� ����

        if (max < ch) max = ch;             // ������� ���ÿ� ���� ���� ū ���ĺ� ������Ʈ
    }
    cout << endl;
    for (int i = 0; i < index; i++) cout << pm[i] << endl;

    return 0;
}

