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

//��带 �޴� ����ť

#define MAX_QUEUE_SIZE 100
class CircularQueue {
protected:
	int front; 		// ù ��° ��� ���� ��ġ
	int rear; 		// ������ ��� ��ġ
	BinaryNode* data[MAX_QUEUE_SIZE]; // ����� �迭
public:
	CircularQueue() { front = rear = 0; }
	bool isEmpty() { return front == rear; }
	bool isFull() { return (rear + 1) % MAX_QUEUE_SIZE == front; }

	void enqueue(BinaryNode* n) { // ť�� ����
		if (isFull())
		{
			cout << " error: ť�� ��ȭ�����Դϴ�" << endl;  exit(-1);
		}
		else {
			rear = (rear + 1) % MAX_QUEUE_SIZE;
			data[rear] = n;
		}
	}
	BinaryNode* dequeue() { 	// ù �׸��� ť���� ���� ��ȯ
		if (isEmpty()) { cout << " Error: ť�� ��������Դϴ�"; exit(-1); }
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

	// �ܸ� ��� ����
	int getLeafCount(BinaryNode* node) {
		if (node == NULL) return 0;
		if (node->isLeaf()) return 1;
		else return getLeafCount(node->getLeft()) + getLeafCount(node->getRight());
	}

	//Ʈ���� ����
	int getHeight(BinaryNode* node) {
		if (node == NULL) return 0;
		int hLeft = getHeight(node->getLeft());
		int hRight = getHeight(node->getRight());
		return (hLeft > hRight) ? 1 + hLeft : 1 + hRight;
	}

	//��ȭ ����Ʈ�� ����
	//true -> YES, false -> NO
	bool isFull(BinaryNode* node) { //BinaryTree::
		if (node == NULL) return true;	//�� ��� �������
		if (node->left == NULL && node->right == NULL) { 	//�� ��� �ڽ� ��� ����, ��������
			if (getCount(node) == (pow(2, getHeight(node) - 1))) {
				return true;
			}
			else {
				return false;
			}
		}
		if (node->left != NULL && node->right != NULL)	//�ڽ� ��� �� �� ����
			return isFull(node->left) and isFull(node->right);
		else return false;
	}

	//��������Ʈ�� ����
	//true -> YES, false -> NO
	bool isComplete(BinaryNode* n, unsigned int index, unsigned int nNodes)
	{
		if (n == NULL) return true;
		// �ε����� ��ü ��� ������ �Ѿ�� false
		if (index >= nNodes) return false;

		// left & right subtree�� ��� complete�̸� ��ü tree�� complete
		// left, right subtree�� root index�� ����ؼ� ����
		// complete��� index�� ��ü ��� ���� �ȿ� �־�� ��.
		return (isComplete(n->left, 2 * index + 1, nNodes) &&
			isComplete(n->right, 2 * index + 2, nNodes));
	}


	//Ư�� ����� ���� ���
	int calcLevel(BinaryNode* node, int n, int level) { //BinaryTree::
		if (node == NULL) return 0;
		if (node->data == n) return level;
		int ll = calcLevel(node->left, n, level + 1);
		if (ll != 0) return ll;
		ll = calcLevel(node->right, n, level + 1);
		return ll;
	}

	//���� ��ȸ

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
	//���� ��ȸ
	void inorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			if (node->getLeft() != NULL) inorder(node->getLeft());
			printf("%c", node->getData());
			if (node->getRight() != NULL) inorder(node->getRight());
		}
	}

	//���� ��ȸ
	void preorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			printf("%c", node->getData());
			if (node->getLeft() != NULL) preorder(node->getLeft());
			if (node->getRight() != NULL) preorder(node->getRight());
		}
	}

	// ���� ��ȸ
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
