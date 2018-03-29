#include "SearchTree.h"

template<typename ElementType>
class AVLTree :public SearchTree<ElementType> {
public:
	AVLTree() :mTreeRoot(nullptr) {}

	~AVLTree() {
		makeEmpty();
	}

	void insert(ElementType elem) {
		AVLNode* node = new AVLNode(elem, nullptr, nullptr, 1);
		if (!insert(mTreeRoot, node))
			delete node;
	}
	bool remove(ElementType elem) {
		AVLNode* node = new AVLNode(elem, nullptr, nullptr, 1);
		bool ret = remove(mTreeRoot, node);
		delete node;
		return ret;
	}

	const ElementType& findMax() const {
		return findMax(mTreeRoot)->curElem;
	}
	const ElementType& findMin() const {
		return findMin(mTreeRoot)->curElem;
	}

	void makeEmpty() {
		makeEmpty(mTreeRoot);
	}

	bool isEmpty() const {
		return nullptr == mTreeRoot;
	}

	bool contains(const ElementType elem) const {
		return true;
	}

	void printTree() const {
		printTree(mTreeRoot);
	}
private:
	struct AVLNode{
		AVLNode* leftChild;
		AVLNode* rightChild;
		ElementType curElem;
		int curDepth;

		AVLNode(ElementType elem, AVLNode* left, AVLNode* right, int depth) :
			curElem(elem), leftChild(left), rightChild(right), curDepth(depth) {}
	}*mTreeRoot;

	bool insert(AVLNode*& root, AVLNode* cur) {
		if (!cur)
			return false;
		if (!root) {
			root = cur;
			return true;
		}
		bool ret;
		if (root->curElem > cur->curElem) {
			ret = insert(root->leftChild, cur);
			if (depthOfNode(root->leftChild) - depthOfNode(root->rightChild) == 2) {
				if (depthOfNode(root->leftChild->leftChild) > depthOfNode(root->leftChild->rightChild))
					rotationLeftLeft(root);
				else
					rotationLeftRight(root);
			}
		}
		else if (root->curElem < cur->curElem) {
			ret = insert(root->rightChild, cur);
			if (depthOfNode(root->rightChild) - depthOfNode(root->leftChild) == 2) {
				if (depthOfNode(root->rightChild->leftChild) > depthOfNode(root->rightChild->rightChild))
					rotationRightLeft(root);
				else
					rotationRightRight(root);
			}
		}
		else
			return false;

		updateDepth(root);
		return ret;
	}

	void updateDepth(AVLNode* cur) {
		if (!cur)
			return;
		cur->curDepth = maxNum(depthOfNode(cur->leftChild), depthOfNode(cur->rightChild)) + 1;
	}

	int depthOfNode(AVLNode* cur) {
		if (!cur)
			return 0;
		return cur->curDepth;
	}

	int maxNum(int num1, int num2) {
		return num1 > num2 ? num1 : num2;
	}

	void rotationLeftLeft(AVLNode*& root) {
		AVLNode* candidate = root->leftChild;
		AVLNode* acceptance = root;
		if (acceptance) {
			acceptance->leftChild = nullptr;
			updateDepth(acceptance);
		}
		insert(acceptance, candidate->rightChild);
		candidate->rightChild = acceptance;
		root = candidate;
	}

	void rotationLeftRight(AVLNode*& root) {
		AVLNode* candidate = root->leftChild->rightChild;
		AVLNode* acceptanceLeft = root->leftChild;
		AVLNode* acceptanceRight = root;
		if (acceptanceLeft) {
			acceptanceLeft->rightChild = nullptr;
			updateDepth(acceptanceLeft);
		}
		if (acceptanceRight) {
			acceptanceRight->leftChild = nullptr;
			updateDepth(acceptanceRight);
		}
		insert(acceptanceLeft, candidate->leftChild);
		insert(acceptanceRight, candidate->rightChild);
		candidate->leftChild = acceptanceLeft;
		candidate->rightChild = acceptanceRight;
		root = candidate;
	}

	void rotationRightLeft(AVLNode*& root) {
		AVLNode* candidate = root->rightChild->leftChild;
		AVLNode* acceptanceLeft = root;
		AVLNode* acceptanceRight = root->rightChild;
		if (acceptanceLeft) {
			acceptanceLeft->rightChild = nullptr;
			updateDepth(acceptanceLeft);
		}
		if (acceptanceRight) {
			acceptanceRight->leftChild = nullptr;
			updateDepth(acceptanceRight);
		}
		insert(acceptanceLeft, candidate->leftChild);
		insert(acceptanceRight, candidate->rightChild);
		candidate->leftChild = acceptanceLeft;
		candidate->rightChild = acceptanceRight;
		root = candidate;
	}

	void rotationRightRight(AVLNode*& root) {
		AVLNode* candidate = root->rightChild;
		AVLNode* acceptance = root;
		if (acceptance) {
			acceptance->rightChild = nullptr;
			updateDepth(acceptance);
		}
		insert(acceptance, candidate->leftChild);
		candidate->leftChild = acceptance;
		root = candidate;
	}

	bool remove(AVLNode*& root, const AVLNode* cur) {
		if (!root)
			return false;
		if (root->curElem > cur->curElem) {
			remove(root->leftChild, cur);
			if (depthOfNode(root->rightChild) - depthOfNode(root->leftChild) == 2) {
				if (depthOfNode(root->rightChild->leftChild) > depthOfNode(root->rightChild->rightChild))
					rotationRightLeft(root);
				else
					rotationRightRight(root);
			}
		}
		else if(root->curElem < cur->curElem){
			remove(root->rightChild, cur);
			if (depthOfNode(root->leftChild) - depthOfNode(root->rightChild) == 2) {
				if (depthOfNode(root->leftChild->leftChild) > depthOfNode(root->leftChild->rightChild))
					rotationLeftLeft(root);
				else
					rotationLeftRight(root);
			}
		}
		else{
			if (depthOfNode(root->rightChild) > depthOfNode(root->leftChild)) {
				const AVLNode* candidate = findMin(root->rightChild);
				root->curElem = candidate->curElem;
				remove(root->rightChild, candidate);
			}
			else if (root->leftChild) {
				const AVLNode* candidate = findMax(root->leftChild);
				root->curElem = candidate->curElem;
				remove(root->leftChild, candidate);
			}
			delete root;
			root = nullptr;
		}
		updateDepth(root);
	}

	const AVLNode* findMax(AVLNode* root) const {
		if (!root)
			return root;
		AVLNode* searchNode = root;
		while (searchNode->rightChild) {
			searchNode = searchNode->rightChild;
		}
		return searchNode;
	}
	const AVLNode* findMin(AVLNode* root) const {
		if (!root)
			return root;
		AVLNode* searchNode = root;
		while (searchNode->leftChild) {
			searchNode = searchNode->leftChild;
		}
		return searchNode;
	}

	void makeEmpty(AVLNode*& root) {
		if (!root)
			return;
		makeEmpty(root->leftChild);
		makeEmpty(root->rightChild);
		delete(root);
		root = nullptr;
	}

	void printTree(AVLNode* root) const {
		if (!root)
			return;
		printTree(root->leftChild);
		std::cout << root->curElem << " ";
		printTree(root->rightChild);
	}
};