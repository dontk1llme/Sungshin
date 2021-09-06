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
					printf("%d ", n->getData());

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
			printf("%d", node->getData());
			if (node->getRight() != NULL) inorder(node->getRight());
		}
	}

	//전위 순회
	void preorder(BinaryNode* node) {//BinaryTree::
		if (node != NULL) {
			printf("%d", node->getData());
			if (node->getLeft() != NULL) preorder(node->getLeft());
			if (node->getRight() != NULL) preorder(node->getRight());
		}
	}

	// 후위 순회
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
		BinaryNode* node = search(root, key);  //!!! parent class변수: root=> protected
		if (node != NULL)
			cout << "탐색 성공 : 키 값이 " << node->getData()
			<< "인 노드 = 0x" << node << endl;
		else
			cout << "탐색 실패 : 키값이 " << key << "인 노드 없음" << endl;
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

		BinaryNode* parent = NULL;   // 처음에는 부모 노드는 null
		BinaryNode* node = root;     // root에서 시작

		while (node != NULL && node->getData() != key) { // key값을 갖는 노드 탐색
			parent = node;           // parent 업데이트: node가 parent가 되고
			node = (key < node->getData()) ? node->getLeft() : node->getRight();
		}                            // node 업데이트: node의 자식 노드로
		if (node == NULL) {           // 단말까지 도달하였는데 key를 못 찾은 경우
			printf(" Error: key is not in the tree!\n");
			return;
		}
		else remove(parent, node); // key값을 갖는 노드 제거
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
			// 삭제 노드가 left child를 가지는 경우
			BinaryNode* child = (node->getLeft() != NULL)
				? node->getLeft() : node->getRight();
			if (node == root) root = child;   //삭제 노드가 root면,
								//root 삭제하고 child를 root로 !
			else {
				if (parent->getLeft() == node)  //부모 노드의 왼쪽 자식 제거
					parent->setLeft(child);
				else 			//부모 노드의 오른쪽 자식 제거
					parent->setRight(child);
			}
		}


		//	 case 3
		else {
		// 한번 오른쪽으로 가서 계속 왼쪽으로 가면 leftmost node(원래거)
		// 한번 왼쪽으로 가서 계속 오른쪽으로 가면 rightmost node(추가한것)
		// 두개 값과 삭제값 비교해서 차이가 적은 걸 올리게 구현해야 함!
			BinaryNode* succp = node;
			BinaryNode* succ = node->getRight();
			while (succ->getLeft() != NULL) {//leftmost찾기
				succp = succ;
				succ = succ->getLeft();
			}

			BinaryNode* rmstp = node;
			BinaryNode* rmst = node->getLeft();
			while (rmst->getRight() != NULL) {//rightmost 찾기
				rmstp = rmst;
				rmst = rmst->getRight();
			}

			//삭제값과 leftmost, rightmost의 차이 비교 위한 int형 변수들
			int dm = node->getData();
			int lm = succ->getData();
			int rm = rmst->getData();

			if ((lm - dm) <= (dm - rm)) {
				//leftmost와 값의 차이가 rightmost와 값의 차이보다 작거나 같을 때
				if (succp->getLeft() == succ)
					succp->setLeft(succ->getRight());
				else
					succp->setRight(succ->getRight());
				node->setData(succ->getData());
				node = succ;  // for deleting the node
			}
			else {
				//leftmost와 값의 차이가 rightmost와 값의 차이보다 클 때
				if (rmstp->getLeft() == rmst)
					rmstp->setLeft(rmst->getRight());
				else
					rmstp->setRight(rmst->getRight());
				node->setData(rmst->getData());
				node = rmst;  // for deleting the node
			}
		}
		
		delete node;
	}
};

int main() {
	BinSrchTree	tree;
	
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a;
		cin >> a;
		tree.insert(new BinaryNode(a));
	}

	int b;
	cin >> b;
	tree.remove(b);

	tree.levelorder();

	return 0;
}