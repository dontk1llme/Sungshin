#include <iostream>
using namespace std;

#define MAX_VTXS 1002
#define MAX_QUEUE_SIZE 100

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

class CircularQueue {
protected:
    int front; 		// 첫 번째 요소 앞의 위치
    int rear; 		// 마지막 요소 위치
    int data[MAX_QUEUE_SIZE]; // 요소의 배열
public:
    CircularQueue() { front = rear = 0; }
    bool isEmpty() { return front == rear; }
    bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

    void enqueue(int val) { // 큐에 삽입
        if (isFull())
        {
            cout << " error: 큐가 포화상태입니다" << endl;
            exit(-1);
        }
        else {
            rear = (rear + 1) % MAX_QUEUE_SIZE;
            data[rear] = val;
        }
    }
    int dequeue() { 	// 첫 항목을 큐에서 빼서 반환
        if (isEmpty()) { cout << " Error: 큐가 공백상태입니다"; exit(-1); }
        else {
            front = (front + 1) % MAX_QUEUE_SIZE;
            return data[front];
        }
    }
    int peek() { 	// 첫 항목을 큐에서 빼지 않고 반환
        if (isEmpty()) printf(" Error: 큐가 공백상태입니다\n");
        else
            return data[(front + 1) % MAX_QUEUE_SIZE];
    }
    void display() { 	// 큐의 모든 내용을 순서대로 출력
        printf("큐 내용 : ");
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

    // 그래프 초기화 ==> 공백 상태의 그래프
    void reset() {
        size = 0;
        for (int i = 0; i < MAX_VTXS; i++)
            for (int j = 0; j < MAX_VTXS; j++)
                setEdge(i, j, 0);
    }
    // 정점 삽입
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
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    // 간선 삽입: 무방향 그래프의 경우임. 
    void insertEdge(int u, int v) {
        setEdge(u, v, 1);
        setEdge(v, u, 1);
    }
    // 그래프 정보 출력 (화면이나 파일에 출력)
    void display(FILE* fp = stdout) {
        for (int i = 0; i < size; i++) {		// 각 행의 정보 출력
            fprintf(fp, "%d ", getVertex(i));	// 정점의 이름 출력
            fprintf(fp, "\n");
        }
    }
};

class AdjListGraph {
protected:
    int size;                // 정점의 개수
    int vertices[MAX_VTXS]; // 정점 정보
    Node* adj[MAX_VTXS];     // 각 정점의 인접 리스트
public:
    AdjListGraph() : size(0) { }
    ~AdjListGraph() {  }
    void reset(void) {
        for (int i = 0; i < size; i++)
            if (adj[i] != NULL) delete adj[i];
        size = 0;
    }
    void insertVertex(int val) {      // 정점 삽입 연산
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
        else printf("Error: 그래프 정점 개수 초과\n");
    }
    //void insertEdge(int u, int v) {    // 간선 삽입 연산
    //    adj[u] = new Node(v, adj[u]); // 인접 리스트에 추가
    //}
    void insertEdge(int u, int v)
    {    // 간선 삽입 연산
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
    {    // 간선 삽입 연산
        adj[u] = new Node(v, adj[u]);
        adj[v] = new Node(u, adj[v]);
    }
    void display() {
        printf("%d\n", size);                // 정점의 개수 출력
        for (int i = 0; i < MAX_VTXS; i++) {      // 각 행의 정보 출력
            printf("%d ", getVertex(i));         // 정점의 이름 출력
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
    bool visited[MAX_VTXS];	 // 정점의 방문 정보
public:
    void resetVisited() {	 // 모든 정점을 방문하지 않았다고 초기화
        for (int i = 0; i < MAX_VTXS; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    // 깊이 우선 탐색 함수
    void DFS(int v) {
        visited[v] = true;	         // 현재 정점을 방문함
        printf("%d ", getVertex(v));      // 정점의 이름 출력

        for (int w = 0; w < MAX_VTXS; w++)
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);	     // 연결 + 방문X => 순환호출
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
        visited[v] = true; // 현재 정점을 방문함
        printf("%d ", getVertex(v)); // 정점의 이름 출력

        CircularQueue que; 
        que.enqueue(v); // 시작 정점을 큐에 저장
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
    g.resetVisited();		// 모든 정점을 방문하지 않은 것으로 초기화
    g.DFS(v - 1);
    printf("\n");


    g2.resetVisited();		// 모든 정점을 방문하지 않은 것으로 초기화
    g2.BFS(v - 1);
    printf("\n");

    return 0;
}
