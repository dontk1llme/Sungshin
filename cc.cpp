#include <iostream>
using namespace std;

#define MAX_VTXS    100

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
                fprintf(fp, " %3d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};
// 탐색 기능이 추가된 인접행렬 기반 그래프 클래스
class SrchAMGraph : public AdjMatGraph
{
protected:
    bool visited[MAX_VTXS];	 // 정점의 방문 정보
public:
    void resetVisited() {	 // 모든 정점을 방문하지 않았다고 초기화
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    // 깊이 우선 탐색 함수
    void DFS(int v) {
        visited[v] = true;	         // 현재 정점을 방문함
        printf("%c ", getVertex(v));      // 정점의 이름 출력

        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);	     // 연결 + 방문X => 순환호출
    }
};
class ConnectedComponentGraph : public SrchAMGraph {  // 클래스 상속
    int label[MAX_VTXS]; 	// CC 색상 (동일 CC에 동일 색상)
public:
    void labelDFS(int v, int color) { // 색상 레이블링
        visited[v] = true; 	// 노드 v 방문 여부 기록
        label[v] = color; 	// 노드 v의 색상
        for (int w = 0; w < size; w++)  // 모든 노드에 대해서
            if (isLinked(v, w) && visited[w] == false)
                labelDFS(w, color); // 연결되어있고, 방문안한 노드 DFS
    }
    void findConnectedComponent() {
        int count = 0;		   // 연결성분 개수 초기화
        for (int i = 0; i < size; i++)  // 모든 노드에 대해서
            if (visited[i] == false)  // 방문안한 노드이면
                labelDFS(i, ++count); // 이 노드에서 DFS시작
                              // CC개수 증가
        printf("%d\n", count);
        //for (int i = 0; i < size; i++)// 모든 노드에 대해서
        //    printf("%c=%d ", getVertex(i), label[i]); // vertex=label 출력
        printf("\n");				      // A=1 B=1 C=1 D=2 E=2
    }
};

int main() {
    int n;
    cin >> n;

    char m[100][100];
    ConnectedComponentGraph cc;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            cin >> m[i][j];
            if (m[i][j] >= 'A') {
                cc.insertVertex(m[i][j]);
            }
            else if (m[i][j] == '1') {
                cc.insertEdge(i, j - 1);
            }
        }
    }
    cout <<'\n';
    cc.resetVisited();
    cc.findConnectedComponent();


    return 0;

}