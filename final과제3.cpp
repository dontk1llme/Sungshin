#include <iostream>
#include <algorithm>
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

int* tmparr = new int[MAX_VTXS];
int* arr2 = new int[MAX_VTXS];
int* fianlarr = new int[MAX_VTXS];
char* vtxs = new char[MAX_VTXS];
char* num1 = new char[MAX_VTXS];

// Dijkstra�˰����� �ִ� ��� Ž�� ����� �߰��� �׷���
class WGraphDijkstra : public WGraph {
    int	  dist[MAX_VTXS];	// ���۳��κ����� �ִܰ�� �Ÿ�
    bool found[MAX_VTXS];	// �湮�� ���� ǥ�� -> ���� S
public:
    int chooseVertex() {   // ���� ��� ���� �̹湮 ������ ��ȯ
        int min = INF;
        int minpos = -1;
        for (int i = 0; i < size; i++)
            if (dist[i] < min && !found[i]) {
                min = dist[i];
                minpos = i;
            }
        return minpos;
    }
    void printDistance() { //��� �������� dist[] �� ���
        for (int i = 0; i < size; i++)
            printf("%5d", dist[i]);
        printf("\n");
    }
    void saveDistance() { //��� �������� dist[]�� ����.
        for (int i = 0; i < size; i++) {
            tmparr[i] = dist[i];
        }
    }

    // Dijkstra�� �ִ� ��� �˰���: start �������� ������.
    void ShortestPath(int start) {
        for (int i = 0; i < size; i++) {  //�ʱ�ȭ: dist[], found[]
            dist[i] = getEdge(start, i); //������� �� ��ȯ(���� ����ġ)
            found[i] = false;           //ó���� S������ �������.
        }
        found[start] = true;	// S�� ����
        vtxs[0] = getVertex(start);
        dist[start] = 0;      // ���� �Ÿ�
        for (int i = 0; i < size; i++) {
            //    printf("Step%2d:", i + 1);
            //    printDistance();        // ��� dist[] �迭�� ���
            saveDistance();//��� dist[]�迭���� tmparr[]�� ������.
            if (i == 3) {//4���� �߰��� �ܰ�!
                memcpy(arr2, tmparr, sizeof(int) * size);
            }
            if (i == size - 1) {//������ �ִ� ���
                memcpy(fianlarr, tmparr, sizeof(int) * size);
            }
            int u = chooseVertex(); // S�� ������ ���� ��� ���� ���� ���� ��ȯ
            found[u] = true;        // ���� S�� ����
            vtxs[i + 1] = getVertex(u);
            if (i == 3) {
                memcpy(num1, vtxs, sizeof(char) * size);
            }
            for (int w = 0; w < size; w++) {
                if (found[w] == false)//S�� ������ �ʴ� ��� w�� dist�� ����
                    if (dist[u] + getEdge(u, w) < dist[w])
                        dist[w] = dist[u] + getEdge(u, w);
            }       // u�� ���İ��� ���� �ִ� �Ÿ��̸� dist[] ����
        }
    }

};

int main() {
    WGraphDijkstra sp;

    //�Է�
    int n;
    cin >> n;         // ������ ��ü ����
    for (int i = 0; i < n; i++) {
        char str;
        int val;

        cin >> str;        // ������ �̸�
        sp.insertVertex(str);        // ���� ����

        for (int j = 0; j < n; j++) {
            cin >> val;   // ���� ����
            sp.insertEdge(i, j, val);     // ���� ����          
        }
    }

    sp.ShortestPath(0);
    cout << endl;

    //1�� ���
    sort(num1, num1 + 3); //������� ����
    for (int i = 0; i < 4; i++) {
        cout << num1[i] << " ";
    }
    cout << endl;

    //2�� ���
    for (int i = 0; i < n; i++) {
        cout << arr2[i] << " ";
    }
    cout << endl;

    //3�����
    cout << "3�� pass" << endl;

    //4�� ���
    for (int i = 0; i < n; i++) {
        cout << fianlarr[i] << " ";
    }
    cout << endl;

    //5�����
    cout << "5�� pass" << endl;

    return 0;

}
