#include <iostream>
#include <algorithm>
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

int* tmparr = new int[MAX_VTXS];
int* arr2 = new int[MAX_VTXS];
int* fianlarr = new int[MAX_VTXS];
char* vtxs = new char[MAX_VTXS];
char* num1 = new char[MAX_VTXS];

// Dijkstra알고리즘의 최단 경로 탐색 기능이 추가된 그래프
class WGraphDijkstra : public WGraph {
    int	  dist[MAX_VTXS];	// 시작노드로부터의 최단경로 거리
    bool found[MAX_VTXS];	// 방문한 정점 표시 -> 집합 S
public:
    int chooseVertex() {   // 가장 비용 적은 미방문 정점을 반환
        int min = INF;
        int minpos = -1;
        for (int i = 0; i < size; i++)
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        return minpos;
    }
    void printDistance() { //모든 정점들의 dist[] 값 출력
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }
    void saveDistance() { //모든 정점들의 dist[]값 저장.
        for (int i = 0; i < size; i++) {
            tmparr[i] = dist[i];
        }
    }

    // Dijkstra의 최단 경로 알고리즘: start 정점에서 시작함.
    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {  //초기화: dist[], found[]
            dist[i] = getEdge(start, i); //인접행렬 값 반환(간선 가중치)
            found[i] = false;           //처음에 S집합은 비어있음.
        }
        found[start] = true;	// S에 포함
        vtxs[0] = getVertex(start);
        dist[start] = 0;      // 최초 거리
        for (int i = 0; i < size; i++) {
            //    printf("Step%2d:", i + 1);
            //    printDistance();        // 모든 dist[] 배열값 출력
            saveDistance();//모든 dist[]배열값을 tmparr[]에 저장함.
            if (i == 3) {//4개가 추가된 단계!
                memcpy(arr2, tmparr, sizeof(int) * size);
            }
            if (i == size - 1) {//마지막 최단 경로
                memcpy(fianlarr, tmparr, sizeof(int) * size);
            }
            int u = chooseVertex(); // S에 속하지 않은 비용 가장 작은 정점 반환
            found[u] = true;        // 집합 S에 포함
            vtxs[i + 1] = getVertex(u);
            if (i == 3) {
                memcpy(num1, vtxs, sizeof(char) * size);
            }
            for (int w = 0; w < size; w++) {
                if (found[w] == false)//S에 속하지 않는 노드 w의 dist값 갱신
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
            }       // u를 거쳐가는 것이 최단 거리이면 dist[] 갱신
        }
    }

};

int main() {
    WGraphDijkstra sp;

    //입력
    int n;
    cin >> n;         // 정점의 전체 개수
    for (int i = 0; i < n; i++) {
        char str;
        int val;

        cin >> str;        // 정점의 이름
        sp.insertVertex(str);        // 정점 삽입

        for (int j = 0; j < n; j++) {
            cin >> val;   // 간선 정보
            sp.insertEdge(i, j, val);     // 간선 삽입          
        }
    }

    sp.ShortestPath(0);
    cout << endl;

    //1번 출력
    sort(num1, num1 + 3); //순서대로 정렬
    for (int i = 0; i < 4; i++) {
        cout << num1[i] << " ";
    }
    cout << endl;

    //2번 출력
    for (int i = 0; i < n; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    //3번출력
    cout << "3번 pass" << endl;

    //4번 출력
    for (int i = 0; i < n; i++) {
        cout << fianlarr[i] << " ";
    }
    cout << endl;

    //5번출력
    cout << "5번 pass" << endl;

    return 0;

}
