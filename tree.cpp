#include <iostream>
using namespace std;

class BinaryNode {
public:
	int data;
	BinaryNode* left;
	BinaryNode* right;

	BinaryNode(int val = 0, BinaryNode* l = NULL, BinaryNode* r = NULL)
		: data(val), left(l), right(r) {}
	~BinaryNode() {}

	void setData(int val) { data = val; }
	void setLeft(BinaryNode* l) { left = l; }
	void setRight(BinaryNode* r) { right = r; }

	int getData() { return data; }
	BinaryNode* getLeft() { return left; }
	BinaryNode* getRight() { return right; }

	bool isLeaf() { return left == NULL && right == NULL; }
};

//노드를 받는 원형큐

#define MAX_QUEUE_SIZE 100
class CircularQueue {
protected:
	int front; 		// 첫 번째 요소 앞의 위치
	int rear; 		// 마지막 요소 위치
	BinaryNode* data[MAX_QUEUE_SIZE]; // 요소의 배열
public:
	CircularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

	void enqueue(BinaryNode* n) { // 큐에 삽입
		if (isFull())
		{
			cout << " error: 큐가 포화상태입니다" << endl;  exit(-1);
		}
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() { 	// 첫 항목을 큐에서 빼서 반환
		if (isEmpty()) { cout << " Error: 큐가 공백상태입니다"; exit(-1); }
		else {
			front = (front + 1) % MAX_QUEUE_SIZE;
			return data[front];
		}
	}
};

class BinaryTree {
	BinaryNode* root;
public:
	BinaryTree() :root(NULL) {}
	~BinaryTree() {}

	void setRoot(BinaryNode* node) { root = node; }
	BinaryNode* getRoot() { return root; }
	bool isEmpty() { return root == NULL; }

	int getCount() { return isEmpty() ? 0 : getCount(root); }
	int getLeafCount() { return isEmpty() ? 0 : getLeafCount(root); }
	int getHeight() { return isEmpty() ? 0 : getHeight(root); }
	int isFull() { return isEmpty() ? true : isFull(root); }//BinaryTree::
	bool isComplete() {
		bool ret = isComplete(root, 0, getCount(root));
		return ret;
	}
	int calcLevel(int n) { return isEmpty() ? 0 : calcLevel(root, n, 1); }//BinaryTree::
	void inorder() {   inorder(root); }
	void preorder() {   preorder(root); }
	void postorder() {   postorder(root); }




	int getCount(BinaryNode* node) {
		if (node == NULL) return 0;
		return 1 + getCount(node->getLeft()) + getCount(node->getRight());
	}

	// 단말 노드 개수
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) return 0;
		if (node->isLeaf()) return 1;
		else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}

	//트리의 높이
	int getHeight(BinaryNode* node) {
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? 1 + hLeft : 1 + hRight;
	}

	//포화 이진트리 여부
	//true -> YES, false -> NO
	bool isFull(BinaryNode* node) { //BinaryTree::
		if (node == NULL) return true;	//이 노드 비어있음
		if (node->left == NULL && node->right == NULL) { 	//이 노드 자식 노드 없음, 질의응답
			if (getCount(node) == (pow(2, getHeight(node) - 1))) {
				return true;
			}
			else {
				return false;
			}
		}
		if (node->left != NULL && node->right != NULL)	//자식 노드 둘 다 있음
			return isFull(node->left) and isFull(node->right);
		else return false;
	}

	//완전이진트리 여부
	//true -> YES, false -> NO
	bool isComplete(BinaryNode* n, unsigned int index, unsigned int nNodes)
	{
		if (n == NULL) return true;
		// 인덱스가 전체 노드 개수를 넘어가면 false
		if (index >= nNodes) return false;

		// left & right subtree가 모두 complete이면 전체 tree는 complete
		// left, right subtree의 root index를 계산해서 전달
		// complete라면 index는 전체 노드 개수 안에 있어야 함.
		return (isComplete(n->left, 2 * index + 1, nNodes) &&
			isComplete(n->right, 2 * index + 2, nNodes));
	}


	//특정 노드의 레벨 계산
	int calcLevel(BinaryNode* node, int n, int level) { //BinaryTree::
		if (node == NULL) return 0;
		if (node->data == n) return level;
		int ll = calcLevel(node->left, n, level + 1);
		if (ll != 0) return ll;
		ll = calcLevel(node->right, n, level + 1);
		return ll;
	}

	//레벨 순회

	void levelorder() { //BinaryTree::
	//	printf("\n levelorder: ");
		if (!isEmpty()) {
			CircularQueue q;
			q.enqueue(root);
			while (!q.isEmpty()) {
				BinaryNode* n = q.dequeue();
				if (n != NULL) {
					printf("%c", n->getData());
					q.enqueue(n->getLeft());
					q.enqueue(n->getRight());
				}
			}
		}
		printf("\n");
	}

private:
	//중위 순회
	void inorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			if (node->getLeft() != NULL) inorder(node->getLeft());
			printf("%c", node->getData());
			if (node->getRight() != NULL) inorder(node->getRight());
		}
	}

	//전위 순회
	void preorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			printf("%c", node->getData());
			if (node->getLeft() != NULL) preorder(node->getLeft());
			if (node->getRight() != NULL) preorder(node->getRight());
		}
	}

	// 후위 순회
	void postorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			if (node->getLeft() != NULL) postorder(node->getLeft());
			if (node->getRight() != NULL) postorder(node->getRight());
			printf("%c", node->getData());
		}
	}


};
 
struct Node {
	char data, left, right;
};


int main() {
	int n;
	BinaryTree tree;
	Node nodeList[26];
	BinaryNode* bnList[26] = { 0, };
	char d, l, r;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> d >> l >> r;
		nodeList[d - 'A'] = { d,l,r };
	}
	for (int i = n-1; i > -1; i--) {
		
		if (nodeList[i].right == '.' && nodeList[i].left == '.') {
			bnList[i] = new BinaryNode(nodeList[i].data, NULL, NULL);
		}
		else if (nodeList[i].left == '.') {
			bnList[i] = new BinaryNode(nodeList[i].data, NULL, bnList[nodeList[i].right - 'A']);
		}
		else if (nodeList[i].right == '.') {
			bnList[i] = new BinaryNode(nodeList[i].data, bnList[nodeList[i].left - 'A'], NULL);
		}
		else {
			bnList[i] = new BinaryNode(nodeList[i].data, bnList[nodeList[i].left - 'A'], bnList[nodeList[i].right - 'A']);
		}
	}
	
	tree.setRoot(bnList[0]);

	tree.preorder(); cout << endl;
	tree.inorder(); cout << endl;
	tree.postorder(); cout << endl;
	tree.levelorder(); 
	cout << tree.getLeafCount() << endl;
	cout << tree.getHeight() << endl;
	if (tree.isFull()) { printf("YES\n"); }
	else { printf("NO\n"); }
	if (tree.isComplete()) { printf("YES\n"); }
	else { printf("NO\n"); }
	cout << tree.calcLevel(n / 2 + 'A' - 1) << endl;

	return 0;
}
