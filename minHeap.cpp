#include <iostream>
#include <string>
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

string output;

int main() {
    int n;
    cin >> n;
    int* input = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> input[i];
    }

    MinHeap minHeap;

    for (int i = 0; i < n; i++) {
        int x = input[i];
        if (x == 0) {
            if (minHeap.isEmpty()) {
                output += "0  \n";
            }
            else {
                int root = minHeap.find().getKey();
                output += to_string(root) + "\n";
                minHeap.remove();
            }
        }
        else minHeap.insert(x);
    }
    cout << endl;
    cout << output;
    return 0;

}

