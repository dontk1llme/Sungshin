#include <iostream>
using namespace std;

#define MAX_VTXS 1002
#define MAX_QUEUE_SIZE 100

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

class CircularQueue {
protected:
    int front; 		// ù ��° ��� ���� ��ġ
    int rear; 		// ������ ��� ��ġ
    int data[MAX_QUEUE_SIZE]; // ����� �迭
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(int val) { // ť�� ����
        if (isFull())
        {
            cout << " error: ť�� ��ȭ�����Դϴ�" << endl;
            exit(-1);
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { 	// ù �׸��� ť���� ���� ��ȯ
        if (isEmpty()) { cout << " Error: ť�� ��������Դϴ�"; exit(-1); }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }
    int peek() { 	// ù �׸��� ť���� ���� �ʰ� ��ȯ
        if (isEmpty()) printf(" Error: ť�� ��������Դϴ�\n");
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    void display() { 	// ť�� ��� ������ ������� ���
        printf("ť ���� : ");
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

class AdjMatGraph {
protected:
    int    size;
    int    vertices[MAX_VTXS];
    int    adj[MAX_VTXS][MAX_VTXS];
public:
    AdjMatGraph() { reset(); }
    int getVertex(int i) { return vertices[i]; }
    int  getEdge(int i, int j) { return adj[i][j]; }
    void setEdge(int i, int j, int val)
    {
        adj[i][j] = val;
    }
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
    void insertVertex(int name) {
        if (!isFull())
        {
            for (int i = 0; i < MAX_VTXS; i++)
            {
                if (vertices[i] == name)
                    return;
            }
            vertices[name - 1] = name;
            size++;
        }
        else printf("Error: �׷��� ���� ���� �ʰ�\n");
    }
    // ���� ����: ������ �׷����� �����. 
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }
    // �׷��� ���� ��� (ȭ���̳� ���Ͽ� ���)
    void display(FILE* fp = stdout) {
        for (int i = 0; i < size; i++) {		// �� ���� ���� ���
            fprintf(fp, "%d ", getVertex(i));	// ������ �̸� ���
            fprintf(fp, "\n");
        }
    }
};

class AdjListGraph {
protected:
    int size;                // ������ ����
    int vertices[MAX_VTXS]; // ���� ����
    Node* adj[MAX_VTXS];     // �� ������ ���� ����Ʈ
public:
    AdjListGraph() : size(0) { }
    ~AdjListGraph() {  }
    void reset(void) {
        for (int i = 0; i < size; i++)
            if (adj[i] != NULL) delete adj[i];
        size = 0;
    }
    void insertVertex(int val) {      // ���� ���� ����
        if (!isFull()) {

            for (int i = 0; i < MAX_VTXS; i++)
            {
                if (vertices[i] == val)
                    return;
            }
            vertices[val - 1] = val;
            adj[val - 1] = NULL;
            size++;
        }
        else printf("Error: �׷��� ���� ���� �ʰ�\n");
    }
    //void insertEdge(int u, int v) {    // ���� ���� ����
    //    adj[u] = new Node(v, adj[u]); // ���� ����Ʈ�� �߰�
    //}
    void insertEdge(int u, int v)
    {    // ���� ���� ����
        if (adj[u] == NULL)
            adj[u] = new Node(v, adj[u]);
        else
        {
            Node* curNode = adj[u];
            while (curNode->getLink() != NULL)
                curNode = curNode->getLink();
            curNode->setLink(new Node(v, NULL));
        }
    }
    void insertEdgeB(int u, int v)
    {    // ���� ���� ����
        adj[u] = new Node(v, adj[u]);
        adj[v] = new Node(u, adj[v]);
    }
    void display() {
        printf("%d\n", size);                // ������ ���� ���
        for (int i = 0; i < MAX_VTXS; i++) {      // �� ���� ���� ���
            printf("%d ", getVertex(i));         // ������ �̸� ���
            for (Node* v = adj[i]; v != NULL; v = v->getLink())
                printf(" %d", getVertex(v->getId()));
            printf("\n");
        }
    }
    Node* adjacent(int v) { return adj[v]; }
    bool isEmpty() { return size == 0; }
    bool isFull() { return size >= MAX_VTXS; }
    int getVertex(int i) { return vertices[i]; }

}; 

class SrchAMGraph : public AdjMatGraph
{
    bool visited[MAX_VTXS];	 // ������ �湮 ����
public:
    void resetVisited() {	 // ��� ������ �湮���� �ʾҴٰ� �ʱ�ȭ
        for (int i = 0; i < MAX_VTXS; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    // ���� �켱 Ž�� �Լ�
    void DFS(int v) {
        visited[v] = true;	         // ���� ������ �湮��
        printf("%d ", getVertex(v));      // ������ �̸� ���

        for (int w = 0; w < MAX_VTXS; w++)
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);	     // ���� + �湮X => ��ȯȣ��
    }
};

class SrchALGraph : public AdjListGraph
{
    bool visited[MAX_VTXS];
public:
    void resetVisited()
    {
        for (int i = 0; i < MAX_VTXS; i++)
            visited[i] = false;
    }

    bool isLinked(int u, int v)
    {
        for (Node* p = adj[u]; p != NULL; p = p->getLink())
            if (p->getId() == v) return true;
        return false;
    }


    void BFS(int v) {
        visited[v] = true; // ���� ������ �湮��
        printf("%d ", getVertex(v)); // ������ �̸� ���

        CircularQueue que; 
        que.enqueue(v); // ���� ������ ť�� ����
        while (!que.isEmpty()) {
            int v = que.dequeue();
            for (Node* w = adj[v]; w != NULL; w = w->getLink())
            {
                int id = w->getId();
                if (!visited[id]) {
                    visited[id] = true;
                    printf("%d ", getVertex(id));
                    que.enqueue(id);
                }
            }
        }
    }
}; //BFS


int main() {

    int n, m, v;
    cin >> n >> m >> v;

    //
    SrchAMGraph g;
    SrchALGraph g2;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g.insertVertex(a);
        g.insertVertex(b);
        g.insertEdge(a - 1, b - 1);

        g2.insertVertex(a);
        g2.insertVertex(b);
        g2.insertEdgeB(a - 1, b - 1);
    }
    g.resetVisited();		// ��� ������ �湮���� ���� ������ �ʱ�ȭ
    g.DFS(v - 1);
    printf("\n");


    g2.resetVisited();		// ��� ������ �湮���� ���� ������ �ʱ�ȭ
    g2.BFS(v - 1);
    printf("\n");

    return 0;
}
