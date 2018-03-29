#include "SearchTree.h"

template<typename ElementType>
class ADT :public SearchTree<ElementType> {
public:
	ADT():mTreeRoot(NULL){}

	~ADT() {
		makeEmpty();
	}

	void insert(ElementType elem) {
		ADTNode* node = new ADTNode(elem, NULL, NULL);
		if (!insert(mTreeRoot, node))
			delete node;
	}
	bool remove(ElementType elem) {
		ADTNode* node = new ADTNode(elem, NULL, NULL);
		bool ret =remove(mTreeRoot, node);
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
		return NULL == mTreeRoot;
	}

	bool contains(const ElementType elem) const {
		return true;
	}

	void printTree() const {
		printTree(mTreeRoot);
	}
private:
	struct ADTNode {
		ADTNode* leftChild;
		ADTNode* rightChild;
		ElementType curElem;
		ADTNode(ElementType elem, ADTNode* left, ADTNode* right):
			curElem(elem), leftChild(left), rightChild(right) {}
	}*mTreeRoot;

	bool insert(ADTNode*& root, ADTNode* cur) {
		bool ret = false;
		if (!root) {
			root = cur;
			return true;
		}
		if (root->curElem > cur->curElem) {
			ret = insert(root->leftChild, cur);
		}
		else if (root->curElem < cur->curElem) {
			ret = insert(root->rightChild, cur);
		}
		else {
			return false;
		}
		return ret;
	}

	bool remove(ADTNode*& root, ADTNode* cur) {
		bool ret = false;
		if (!root)
			return ret;
		if (root->curElem > cur->curElem)
			ret = remove(root->leftChild, cur);
		else if (root->curElem < cur->curElem)
			ret = remove(root->rightChild, cur);
		else {
			ADTNode* origin = root;
			if (root->rightChild) {
				ADTNode* acceptance = root->leftChild;
				ADTNode* candidate = findMin(root->rightChild);
				root->curElem = candidate->curElem;
				remove(root->rightChild, candidate);
			}
			else if (root->leftChild) {
				root = root->leftChild;
			}
			delete origin;
			ret = true;
		}
		return ret;
	}

	const ADTNode* findMax(ADTNode* root) const {
		if (!root)
			return root;
		ADTNode* searchNode = root;
		while (searchNode->rightChild) {
			searchNode = searchNode->rightChild;
		}
		return searchNode;
	}
	const ADTNode* findMin(ADTNode* root) const {
		if (!root)
			return root;
		ADTNode* searchNode = root;
		while (searchNode->leftChild){
			searchNode = searchNode->leftChild;
		}
		return searchNode;
	}

	void makeEmpty(ADTNode*& root) {
		if (!root)
			return;
		makeEmpty(root->leftChild);
		makeEmpty(root->rightChild);
		delete(root);
		root = NULL;
	}

	void printTree(ADTNode* root) const {
		if (!root)
			return;
		printTree(root->leftChild);
		std::cout << root->curElem << " ";
		printTree(root->rightChild);
	}
};