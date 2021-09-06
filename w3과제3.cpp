// Postfix

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
    bool isFull() { return top == MAX_STACK_SIZE - 1;  }

    void push(double e) {
        if (isFull()) error((char*)"stack overflow !");
        data[++top] = e;
        maxArr[idx++] = top+1;  // push할 때마다 현재의 항목수 저장, top은 0부터 시작이므로 +1
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
    void copy(OperandStack s) { // 스택 내용 복사
        top = s.top;
        for (int i = 0; i <= top; i++) data[i] = s.data[i];
    }
    int getMax() {          // 항목수 중에 Max값 찾아서 출력
        int m = 0;
        for (int i = 0; i < idx; i++) {
            if (m < maxArr[i]) m = maxArr[i];
        }
        return m;
    }
    int countMax() {        // Max Count 세어서 출력
        int count = 0;
        int m = getMax();
        for (int i = 0; i < idx; i++) {
            if (m == maxArr[i]) count++;
        }
        return count;
    }
};

double calcPostfixExpr(FILE* fp = stdin) {
    char c;
    double val;
    OperandStack st, pt;
    int count = 0;

    while ((c = getc(fp)) != '\n') {                            // 파일에서 expr 한 문자 씩 읽어서
        if (c == '+' || c == '-' || c == '*' || c == '/') {     //연산자이면 
            count++;
            if (count == 3) pt.copy(st);
            double val2 = st.pop();                             //피연산자 2개 pop하여   
            double val1 = st.pop();	                            //계산
            switch (c) {
            case '+' : st.push(val1 + val2); break;             // 계산결과를
            case '-' : st.push(val1 - val2); break;             // 다시 스택에
            case '*' : st.push(val1 * val2); break;             // 저장
            case '/' : st.push(val1 / val2); break;
            }
        }
        else if (c >= '0' && c <= '9') {                        // 피연산자이면 스택에 push
            ungetc(c, fp);                                      // 읽어 들인 문자 한 개를 반납
            fscanf_s(fp, "%lf", &val);                          // 피연산자를 실수로 read
            st.push(val);	                                    // 피연산자를 스택에 push
        }
    }
    cout << endl << st.getMax() << endl;
    cout << st.countMax() << endl;
    cout << "______________________" << endl;

    pt.display();
    cout << "______________________" << endl;

    return (st.pop());	                                        // 스택에 최종 남아있는 값은 전체 계산결과
}

int main()
{
    cout << "수식입력(postfix) = ";
    double res = calcPostfixExpr();
    cout << res << endl;        // 계산 결과 출력
    return 0;
}


