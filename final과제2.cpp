#include <iostream>
#include <string>
using namespace std;

#define INF 9999              // INF이면 간선없음
#define MAX_VTXS 100

class Node {
protected:
    int id; 	// 정점의 id
    Node* link; 	// 다음 노드의 포인터
public:
    Node(int i, Node* l = NULL) : id(i), link(l) { }
    ~Node() {
        if (link != NULL) delete link;
    }
    int   getId() { return id; }
    Node* getLink() { return link; }
    void  setLink(Node* l) { link = l; }
};

class AdjMatGraph {
protected:
    int    size;
    char   vertices[MAX_VTXS];
    int    adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    char getVertex(int i) { return vertices[i]; }
    int  getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val) { adj[i][j] = val; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }

    // 그래프 초기화 ==> 공백 상태의 그래프
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    // 정점 삽입
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    // 간선 삽입: 무방향 그래프의 경우임. 
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }
    // 그래프 정보 출력 (화면이나 파일에 출력)
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);		// 정점의 개수 출력
        for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
            fprintf(fp, "%c ", getVertex(i));	// 정점의 이름 출력
            for (int j = 0; j < size; j++)	// 간선 정보 출력
                fprintf(fp, " %5d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

// 가중치 그래프를 표현하는 클래스
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

};


class HeapNode {
    int	key;    // Key 값: 간선의 가중치
    int	v1;     // 정점 1
    int	v2;     // 정점 2
public:
    HeapNode(int k = 0, int u = 0, int v = 0) : key(k), v1(u), v2(v) { }
    void setKey(int k) { key = k; }
    void  setKey(int k, int u, int v) {
        key = k;   v1 = u;  v2 = v;
    }
    int getKey() { return key; }
    int getV1() { return v1; }
    int getV2() { return v2; }
    void display() { printf("\t(%2d-%2d) -- %d\n", v1, v2, key); }
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

    void insert(int key, int u, int v);      	// 삽입 함수
    HeapNode remove();         	// 삭제 함수
    HeapNode find() { return node[1]; }	// 루트 노드 반환
};

void MinHeap::insert(int key, int u, int v)
{
    if (isFull()) return;
    int i = ++size;
    while (i != 1 && key < getParent(i).getKey()) {
        node[i] = getParent(i);
        i /= 2;
    }
    node[i].setKey(key, u, v);
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

// 정점 집합 클래스
class VertexSets {
    int        parent[MAX_VTXS];	// 부모 정점의 id
    int        nSets;		// 집합의 개수

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;	// 초기에 모든 정점이 고유의 집합에 속함
    }
    bool isRoot(int i) { return parent[i] < 0; }  // -1이면 root
    int findSet(int v) {	    	// v가 속한 집합을 찾아 root 반환
        while (!isRoot(v)) v = parent[v]; // v가 속한 집합의 루트를 찾음
        return v;
    }
    void unionSets(int s1, int s2) { // 집합 s1을 집합 s2와 합침
        parent[s1] = s2;  	// s1의 parent를 s2로 설정
        nSets--;          	// 2개의 집합을 합쳐서 집합 개수는 1 감소
    }
    int getnSets() { return nSets; }


};

string* num4 = new string[MAX_VTXS];
string* num5 = new string[MAX_VTXS];
constexpr int CHAR_LENGTH = 1;
int cntedge = 0;

class WGraphMST : public WGraph {
    int unionnum = 0; //1번을 위한 union 연산 발생 개수
    int finalroot = 0; //2번을 위한
    int cnt = 0; //5번 저장을 위한
    char ch1[10];
public:
    void Kruskal() {     // kruskal의 최소 비용 신장 트리 프로그램
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j); // 모든 간선 삽입
        VertexSets set(size);		// size개의 집합을 만듦
        int edgeAccepted = 0;		// 선택된 간선의 수
        while (edgeAccepted < size - 1) { 	// 4.(n-1)개의 edge가 삽입될때까지
            HeapNode e = heap.remove(); // 2.가장 작은 edge 선택
            int uset = set.findSet(e.getV1()); // v1이 속한 집합의 루트 반환
            int vset = set.findSet(e.getV2()); // v2가 속한 집합의 루트 반환
            if (uset != vset) {          // 3.사이클 생기지 않으면 MST삽입
                /*printf("간선 추가 : %c - %c (비용:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());*/
                    //5번
                string str1(CHAR_LENGTH, getVertex(e.getV1()));
                string str2(CHAR_LENGTH, getVertex(e.getV2()));
                string str3 = to_string(e.getKey());
                num5[cnt] = str1.append(" ").append(str2).append(" ").append(str3);
                cnt++;
                set.unionSets(uset, vset);       // 두개의 집합을 합함.
                edgeAccepted++;
                unionnum++; //1번
                if (set.getnSets() == 3) { //3번
                    //각 집합의 루트를 오름차순으로 출력.
                }
            }
            else {
                string str4 = to_string(e.getKey());
                num4[cntedge] = str4;
                cntedge++;
            }
            finalroot = max(set.findSet(uset), set.findSet(vset));
        }

    }
    int getUnionnum() { return unionnum; } //1번
    int getFinalroot() { return finalroot+1; } //2번

};


int main() {

    WGraphMST mst;

    //입력
    int n;
    cin >> n;         // 정점의 전체 개수
    for (int i = 0; i < n; i++) {
        char str;
        int val;

        cin >> str;        // 정점의 이름
        mst.insertVertex(str);        // 정점 삽입

        for (int j = 0; j < n; j++) {
            cin >> val;   // 간선 정보
            mst.insertEdge(i, j, val);     // 간선 삽입          
        }
    }

    cout << endl;

    mst.Kruskal();


    //1번 union 연산 발생 개수 출력. 
    cout << mst.getUnionnum() << endl;

    //2번 u-f알고리즘 완료시 집합의 루트 출력. 
    cout << mst.getFinalroot()  << endl;


    //3번 집합 개수 3개일 때 각 집합의 루트를 오름차순으로 출력
    cout << "3번 pass" << endl;
    //집합의 루트를 뽑는 것을 어떻게 해야 하는지 모르겠습니다.

    //4번 사이클 생겨서 mst에 포함 안 된 edge 개수와 가중치 순서대로 출력
    cout << cntedge << " ";
    for (int i = 0; i < n; i++) {
        cout << num4[i] << " ";
    }
    cout << endl;


    //5번, MST 결과 출력
    for (int i = 0; i < n; i++) {
        cout << num5[i] << endl;
    }

}
