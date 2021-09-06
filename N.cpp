#include <iostream>
using namespace std;

class HeapNode
{
    int key; // ��� Key ��
public:
    HeapNode(int k = 0) : key(k) { }
    void 	setKey(int k) { key = k; }  	// ��忡 Ű�� �����ϱ�
    int 	getKey() { return key; }		// ��忡�� Ű�� �޾ƿ���
    void 	display() { printf("%4d", key); }// ��� ���÷���
};

#define MAX_ELEMENT 200

class MinHeap
{
    HeapNode node[MAX_ELEMENT];     // HeapNode Ŭ���� Ÿ�� �迭
    int size;                       // �� ��ҵ� ����
public:
    MinHeap() : size(0) { }	    // ó���� ũ�� 0�� �迭
    bool isEmpty() { return size == 0; }		   // ��� �ִ���?
    bool isFull() { return size == MAX_ELEMENT - 1; }// ������ �ִ���

    HeapNode& getParent(int i) { return node[i / 2]; }  // �θ� ���
    HeapNode& getLeft(int i) { return node[i * 2]; }  // ���� �ڽ� ���
    HeapNode& getRight(int i) { return node[i * 2 + 1]; } // ������ �ڽ� ���

    void insert(int key);      	// ���� �Լ�
    HeapNode remove();         	// ���� �Լ�
    HeapNode find() { return node[1]; }	// ��Ʈ ��� ��ȯ

    int howmany();
};

void MinHeap::insert(int key)
{
    // �� ��� ������ �������� �ε����� ���� 
    if (isFull()) return;	// ���� ���� �� ���
    int i = ++size; 		// �� ũ�� 1 ����, i=�ű� ������ �ڸ�

    // �� ��尡 �ִ��� ������ �����ϵ��� UP UP !
    while (i != 1 				// i=1: ��Ʈ ���
        && key < getParent(i).getKey()) {	// �θ𺸴� Ű���� ū ���� �ݺ�
        node[i] = getParent(i);	// �θ� �ڽ� �ڸ��� down
        i /= 2;			// �� ���� ������ �ٽ� ��
    }
    node[i].setKey(key);	          // ���� ������ ��ġ�� �ű� Ű�� ����
}

HeapNode MinHeap::remove() {
    if (isEmpty()) { cout << "empty error !" << endl; exit(-1); }
    HeapNode item = node[1];	 // ��Ʈ ���
    HeapNode last = node[size--]; // ������ ���
    int parent = 1; 		// ��Ʈ ��� �ε���
    int child = 2; 		// ��Ʈ�� ���� �ڽ� �ε���
    // DownHeap : �� ��Ʈ ��带 ���ڸ��� down down ! 
    while (child <= size) {	// �� Ʈ�� ũ�� ������
        if (child < size
            && getLeft(parent).getKey() > getRight(parent).getKey())
            child++;      // ������ �ڽ��� �� ũ�� ���������� �̵�
        if (last.getKey() <= node[child].getKey()) break;
        //�ڽ� ��庸�� ũ�� ok
        node[parent] = node[child]; //�ڽ� ��庸�� ������ change !

        parent = child;		 // �� �ܰ� �Ʒ� ������ �̵�
        child *= 2;
    }
    node[parent] = last;     	// ���� ��ġ�� ������ ��� ����
    return item;             	// ������ ��Ʈ ��� ��ȯ
}
int MinHeap::howmany() { //���� size �˷��ִ� �Լ� ����
    int count = 0;
    for (int i = 1, level = 1; i <= size; i++) {
        if (i == level) {
            level *= 2;
        }
        count++;
    }
    return count;
}


int main() {
    MinHeap mh;
    int n, data;
    cin >> n;


    for (int i = 0; i < n; i++) {
        cin >> data;
        mh.insert(data);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> data;
            mh.insert(data);
        }
        for (int i = 0; i < n; i++) mh.remove();
    }

    cout << '\n' << mh.find().getKey() << '\n';

    return 0;
}

//MaxHeap��� MinHeap ����ؼ� ����.
// n*n���� �� �������� �ʾҰ�, ť�� n���� ���� �����ϵ��� insert/remove �ݺ���.