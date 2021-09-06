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
                fprintf(fp, " %3d", getEdge(i, j));
            fprintf(fp, "\n");
        }
    }
};
// Ž�� ����� �߰��� ������� ��� �׷��� Ŭ����
class SrchAMGraph : public AdjMatGraph
{
protected:
    bool visited[MAX_VTXS];	 // ������ �湮 ����
public:
    void resetVisited() {	 // ��� ������ �湮���� �ʾҴٰ� �ʱ�ȭ
        for (int i = 0; i < size; i++)
            visited[i] = false;
    }
    bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

    // ���� �켱 Ž�� �Լ�
    void DFS(int v) {
        visited[v] = true;	         // ���� ������ �湮��
        printf("%c ", getVertex(v));      // ������ �̸� ���

        for (int w = 0; w < size; w++)
            if (isLinked(v, w) && visited[w] == false)
                DFS(w);	     // ���� + �湮X => ��ȯȣ��
    }
};
class ConnectedComponentGraph : public SrchAMGraph {  // Ŭ���� ���
    int label[MAX_VTXS]; 	// CC ���� (���� CC�� ���� ����)
public:
    void labelDFS(int v, int color) { // ���� ���̺�
        visited[v] = true; 	// ��� v �湮 ���� ���
        label[v] = color; 	// ��� v�� ����
        for (int w = 0; w < size; w++)  // ��� ��忡 ���ؼ�
            if (isLinked(v, w) && visited[w] == false)
                labelDFS(w, color); // ����Ǿ��ְ�, �湮���� ��� DFS
    }
    void findConnectedComponent() {
        int count = 0;		   // ���Ἲ�� ���� �ʱ�ȭ
        for (int i = 0; i < size; i++)  // ��� ��忡 ���ؼ�
            if (visited[i] == false)  // �湮���� ����̸�
                labelDFS(i, ++count); // �� ��忡�� DFS����
                              // CC���� ����
        printf("%d\n", count);
        //for (int i = 0; i < size; i++)// ��� ��忡 ���ؼ�
        //    printf("%c=%d ", getVertex(i), label[i]); // vertex=label ���
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