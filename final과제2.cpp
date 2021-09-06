#include <iostream>
#include <string>
using namespace std;

#define INF 9999              // INF�̸� ��������
#define MAX_VTXS 100

class Node {
protected:
    int id; 	// ������ id
    Node* link; 	// ���� ����� ������
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

    // �׷��� �ʱ�ȭ ==> ���� ������ �׷���
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    // ���� ����
    void insertVertex(char name) {
        if (!isFull()) vertices[size++] = name;
        else printf("Error: �׷��� ���� ���� �ʰ�\n");
    }
    // ���� ����: ������ �׷����� �����. 
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }
    // �׷��� ���� ��� (ȭ���̳� ���Ͽ� ���)
    void display(FILE* fp = stdout) {
        fprintf(fp, "%d\n", size);		// ������ ���� ���
        for (int i = 0; i < size; i++) {		// �� ���� ���� ���
            fprintf(fp, "%c ", getVertex(i));	// ������ �̸� ���
            for (int j = 0; j < size; j++)	// ���� ���� ���
                fprintf(fp, " %5d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};

// ����ġ �׷����� ǥ���ϴ� Ŭ����
class WGraph : public AdjMatGraph {
public:
    void insertEdge(int u, int v, int weight) {
        if (weight > INF) weight = INF;
        setEdge(u, v, weight);
    }
    bool hasEdge(int i, int j) { return (getEdge(i, j) < INF); }

};


class HeapNode {
    int	key;    // Key ��: ������ ����ġ
    int	v1;     // ���� 1
    int	v2;     // ���� 2
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
    HeapNode node[MAX_ELEMENT];     // HeapNode Ŭ���� Ÿ�� �迭
    int size;                       // �� ��ҵ� ����
public:
    MinHeap() : size(0) { }	    // ó���� ũ�� 0�� �迭
    bool isEmpty() { return size == 0; }		   // ��� �ִ���?
    bool isFull() { return size == MAX_ELEMENT - 1; }// ������ �ִ���

    HeapNode& getParent(int i) { return node[i / 2]; }  // �θ� ���
    HeapNode& getLeft(int i) { return node[i * 2]; }  // ���� �ڽ� ���
    HeapNode& getRight(int i) { return node[i * 2 + 1]; } // ������ �ڽ� ���

    void insert(int key, int u, int v);      	// ���� �Լ�
    HeapNode remove();         	// ���� �Լ�
    HeapNode find() { return node[1]; }	// ��Ʈ ��� ��ȯ
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

// ���� ���� Ŭ����
class VertexSets {
    int        parent[MAX_VTXS];	// �θ� ������ id
    int        nSets;		// ������ ����

public:
    VertexSets(int n) : nSets(n) {
        for (int i = 0; i < nSets; i++)
            parent[i] = -1;	// �ʱ⿡ ��� ������ ������ ���տ� ����
    }
    bool isRoot(int i) { return parent[i] < 0; }  // -1�̸� root
    int findSet(int v) {	    	// v�� ���� ������ ã�� root ��ȯ
        while (!isRoot(v)) v = parent[v]; // v�� ���� ������ ��Ʈ�� ã��
        return v;
    }
    void unionSets(int s1, int s2) { // ���� s1�� ���� s2�� ��ħ
        parent[s1] = s2;  	// s1�� parent�� s2�� ����
        nSets--;          	// 2���� ������ ���ļ� ���� ������ 1 ����
    }
    int getnSets() { return nSets; }


};

string* num4 = new string[MAX_VTXS];
string* num5 = new string[MAX_VTXS];
constexpr int CHAR_LENGTH = 1;
int cntedge = 0;

class WGraphMST : public WGraph {
    int unionnum = 0; //1���� ���� union ���� �߻� ����
    int finalroot = 0; //2���� ����
    int cnt = 0; //5�� ������ ����
    char ch1[10];
public:
    void Kruskal() {     // kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
        MinHeap heap;
        for (int i = 0; i < size - 1; i++)
            for (int j = i + 1; j < size; j++)
                if (hasEdge(i, j))
                    heap.insert(getEdge(i, j), i, j); // ��� ���� ����
        VertexSets set(size);		// size���� ������ ����
        int edgeAccepted = 0;		// ���õ� ������ ��
        while (edgeAccepted < size - 1) { 	// 4.(n-1)���� edge�� ���Եɶ�����
            HeapNode e = heap.remove(); // 2.���� ���� edge ����
            int uset = set.findSet(e.getV1()); // v1�� ���� ������ ��Ʈ ��ȯ
            int vset = set.findSet(e.getV2()); // v2�� ���� ������ ��Ʈ ��ȯ
            if (uset != vset) {          // 3.����Ŭ ������ ������ MST����
                /*printf("���� �߰� : %c - %c (���:%d)\n",
                    getVertex(e.getV1()), getVertex(e.getV2()), e.getKey());*/
                    //5��
                string str1(CHAR_LENGTH, getVertex(e.getV1()));
                string str2(CHAR_LENGTH, getVertex(e.getV2()));
                string str3 = to_string(e.getKey());
                num5[cnt] = str1.append(" ").append(str2).append(" ").append(str3);
                cnt++;
                set.unionSets(uset, vset);       // �ΰ��� ������ ����.
                edgeAccepted++;
                unionnum++; //1��
                if (set.getnSets() == 3) { //3��
                    //�� ������ ��Ʈ�� ������������ ���.
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
    int getUnionnum() { return unionnum; } //1��
    int getFinalroot() { return finalroot+1; } //2��

};


int main() {

    WGraphMST mst;

    //�Է�
    int n;
    cin >> n;         // ������ ��ü ����
    for (int i = 0; i < n; i++) {
        char str;
        int val;

        cin >> str;        // ������ �̸�
        mst.insertVertex(str);        // ���� ����

        for (int j = 0; j < n; j++) {
            cin >> val;   // ���� ����
            mst.insertEdge(i, j, val);     // ���� ����          
        }
    }

    cout << endl;

    mst.Kruskal();


    //1�� union ���� �߻� ���� ���. 
    cout << mst.getUnionnum() << endl;

    //2�� u-f�˰��� �Ϸ�� ������ ��Ʈ ���. 
    cout << mst.getFinalroot()  << endl;


    //3�� ���� ���� 3���� �� �� ������ ��Ʈ�� ������������ ���
    cout << "3�� pass" << endl;
    //������ ��Ʈ�� �̴� ���� ��� �ؾ� �ϴ��� �𸣰ڽ��ϴ�.

    //4�� ����Ŭ ���ܼ� mst�� ���� �� �� edge ������ ����ġ ������� ���
    cout << cntedge << " ";
    for (int i = 0; i < n; i++) {
        cout << num4[i] << " ";
    }
    cout << endl;


    //5��, MST ��� ���
    for (int i = 0; i < n; i++) {
        cout << num5[i] << endl;
    }

}
