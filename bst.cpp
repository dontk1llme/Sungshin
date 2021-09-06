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


class BinaryTree {
protected:
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
	void inorder() { inorder(root); }
	void preorder() { preorder(root); }
	void postorder() { postorder(root); }




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


private:
	//���� ��ȸ
	void inorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			if (node->getLeft() != NULL) inorder(node->getLeft());
			printf("%d", node->getData());
			if (node->getRight() != NULL) inorder(node->getRight());
		}
	}

	//���� ��ȸ
	void preorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			printf("%d", node->getData());
			if (node->getLeft() != NULL) preorder(node->getLeft());
			if (node->getRight() != NULL) preorder(node->getRight());
		}
	}

	// ���� ��ȸ
	void postorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			if (node->getLeft() != NULL) postorder(node->getLeft());
			if (node->getRight() != NULL) postorder(node->getRight());
			printf("%d", node->getData());
		}
	}
};

class BinSrchTree : public BinaryTree
{
public:
	BinSrchTree(void) { }
	~BinSrchTree(void) { }

	BinaryNode* search(int key) {
		BinaryNode* node = search(root, key);  //!!! parent class����: root=> protected
		if (node != NULL)
			cout <<"1"<< endl;
		else
			cout <<"0" << endl;
		return node;
	}

	BinaryNode* search(BinaryNode* n, int key) {
		if (n == NULL) return NULL;
		if (key == n->getData()) return n;
		else if (key < n->getData()) return search(n->getLeft(), key);
		else return search(n->getRight(), key);
	}


	void insert(BinaryNode* n) {
		if (n == NULL) return;
		if (isEmpty()) root = n;
		else insert(root, n);
	}

	void insert(BinaryNode* r, BinaryNode* n) {
		if (n->getData() == r->getData()) return;
		else if (n->getData() < r->getData()) {
			if (r->getLeft() == NULL) r->setLeft(n);
			else insert(r->getLeft(), n);
		}
		else {
			if (r->getRight() == NULL) r->setRight(n);
			else insert(r->getRight(), n);
		}
	}

	void remove(int key) {
		if (isEmpty()) return;

		BinaryNode* parent = NULL;   // ó������ �θ� ���� null
		BinaryNode* node = root;     // root���� ����

		while (node != NULL && node->getData() != key) { // key���� ���� ��� Ž��
			parent = node;           // parent ������Ʈ: node�� parent�� �ǰ�
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}                            // node ������Ʈ: node�� �ڽ� ����
		if (node == NULL) {           // �ܸ����� �����Ͽ��µ� key�� �� ã�� ���
			printf(" Error: key is not in the tree!\n");
			return;
		}
		else remove(parent, node); // key���� ���� ��� ����
	}

	void remove(BinaryNode* parent, BinaryNode* node) {

		// case 1
		if (node->isLeaf()) {
			if (parent == NULL) root = NULL;
			else {
				if (parent->getLeft() == node)
					parent->setLeft(NULL);
				else
					parent->setRight(NULL);
			}
		}

		// case 2
		else if (node->getLeft() == NULL || node->getRight() == NULL) {
			// ���� ��尡 left child�� ������ ���
			BinaryNode* child = (node->getLeft() != NULL)
				? node->getLeft() : node->getRight();
			if (node == root) root = child;   //���� ��尡 root��,
								//root �����ϰ� child�� root�� !
			else {
				if (parent->getLeft() == node)  //�θ� ����� ���� �ڽ� ����
					parent->setLeft(child);
				else 			//�θ� ����� ������ �ڽ� ����
					parent->setRight(child);
			}
		}

		// case 3
		else {// �ѹ� ���������� ���� ��� �������� ���� leftmost node
			BinaryNode* succp = node;
			BinaryNode* succ = node->getRight();
			while (succ->getLeft() != NULL) {
				succp = succ;
				succ = succ->getLeft();
			}

			if (succp->getLeft() == succ)
				succp->setLeft(succ->getRight());
			else
				succp->setRight(succ->getRight());

			node->setData(succ->getData());
			node = succ;  // for deleting the node
		}
		delete node;
	}

};

int main() {
	BinSrchTree tree;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		tree.insert(new BinaryNode(a));
	}

	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int b;
		cin >> b;
		tree.search(b);
	}

	return 0;
}