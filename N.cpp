#include <iostream>
using namespace std;

class HeapNode
{
    int key; // 노드 Key 값
public:
    HeapNode(int k = 0) : key(k) { }
    void 	setKey(int k) { key = k; }  	// 노드에 키값 저장하기
    int 	getKey() { return key; }		// 노드에서 키값 받아오기
    void 	display() { printf("%4d", key); }// 노드 디스플레이
};

#define MAX_ELEMENT 200

class MinHeap
{
    HeapNode node[MAX_ELEMENT];     // HeapNode 클래스 타입 배열
    int size;                       // 힙 요소들 개수
public:
    MinHeap() : size(0) { }	    // 처음엔 크기 0인 배열
    bool isEmpty() { return size == 0; }		   // 비어 있는지?
    bool isFull() { return size == MAX_ELEMENT - 1; }// 가득차 있는지

    HeapNode& getParent(int i) { return node[i / 2]; }  // 부모 노드
    HeapNode& getLeft(int i) { return node[i * 2]; }  // 왼쪽 자식 노드
    HeapNode& getRight(int i) { return node[i * 2 + 1]; } // 오른쪽 자식 노드

    void insert(int key);      	// 삽입 함수
    HeapNode remove();         	// 삭제 함수
    HeapNode find() { return node[1]; }	// 루트 노드 반환

    int howmany();
};

void MinHeap::insert(int key)
{
    // 새 노드 삽입할 ‘마지막 인덱스’ 결정 
    if (isFull()) return;	// 힙이 가득 찬 경우
    int i = ++size; 		// 힙 크기 1 증가, i=신규 삽입할 자리

    // 새 노드가 최대힙 성질을 만족하도록 UP UP !
    while (i != 1 				// i=1: 루트 노드
        && key < getParent(i).getKey()) {	// 부모보다 키값이 큰 동안 반복
        node[i] = getParent(i);	// 부모를 자식 자리로 down
        i /= 2;			// 한 레벨 위에서 다시 비교
    }
    node[i].setKey(key);	          // 최종 적합한 위치에 신규 키값 저장
}

HeapNode MinHeap::remove() {
    if (isEmpty()) { cout << "empty error !" << endl; exit(-1); }
    HeapNode item = node[1];	 // 루트 노드
    HeapNode last = node[size--]; // 마지막 노드
    int parent = 1; 		// 루트 노드 인덱스
    int child = 2; 		// 루트의 왼쪽 자식 인덱스
    // DownHeap : 새 루트 노드를 제자리로 down down ! 
    while (child <= size) {	// 힙 트리 크기 내에서
        if (child < size
            && getLeft(parent).getKey() > getRight(parent).getKey())
            child++;      // 오른쪽 자식이 더 크면 오른쪽으로 이동
        if (last.getKey() <= node[child].getKey()) break;
        //자식 노드보다 크면 ok
        node[parent] = node[child]; //자식 노드보다 작으면 change !

        parent = child;		 // 한 단계 아래 레벨로 이동
        child *= 2;
    }
    node[parent] = last;     	// 최종 위치에 마지막 노드 저장
    return item;             	// 삭제한 루트 노드 반환
}
int MinHeap::howmany() { //힙의 size 알려주는 함수 만듦
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

//MaxHeap대신 MinHeap 사용해서 구현.
// n*n개의 수 정렬하지 않았고, 큐에 n개의 수만 유지하도록 insert/remove 반복함.