#include "SearchTree.h"
#include <iostream>
#include <cstdlib>

template<typename ElementType>
class ADT :public SearchTree<ElementType> {
public:
	ADT():mTreeRoot(NULL){}

	~ADT() {
		makeEmpty();
	}

	void insert(ElementType elem) {
		ElemNode* node = new ElemNode(elem, NULL, NULL);
		if (!insert(mTreeRoot, node))
			delete node;
	}
	bool remove(ElementType elem) {
		ElemNode* node = new ElemNode(elem, NULL, NULL);
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
	struct ElemNode {
		ElemNode* leftChild;
		ElemNode* rightChild;
		ElementType curElem;
		ElemNode(ElementType elem, ElemNode* left, ElemNode* right):
			curElem(elem), leftChild(left), rightChild(right) {}
	}*mTreeRoot;

	bool insert(ElemNode*& root, ElemNode* cur) {
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

	bool remove(ElemNode*& root, ElemNode* cur) {
		bool ret = false;
		if (!root)
			return ret;
		if (root->curElem > cur->curElem)
			ret = remove(root->leftChild, cur);
		else if (root->curElem < cur->curElem)
			ret = remove(root->rightChild, cur);
		else {
			ElemNode* origin = root;
			if (root->rightChild) {
				ElemNode* acceptance = root->leftChild;
				ElemNode* candidate = root->rightChild;
				insert(acceptance, candidate->leftChild);
				candidate->leftChild = acceptance;
				root = candidate;

			}
			else if (root->leftChild) {
				root = root->leftChild;
			}
			delete origin;
			ret = true;
		}
		return ret;
	}

	const ElemNode* findMax(ElemNode* root) const {
		if (!root)
			return root;
		ElemNode* searchNode = root;
		while (searchNode->rightChild) {
			searchNode = searchNode->rightChild;
		}
		return searchNode;
	}
	const ElemNode* findMin(ElemNode* root) const {
		if (!root)
			return root;
		ElemNode* searchNode = root;
		while (searchNode->leftChild){
			searchNode = searchNode->leftChild;
		}
		return searchNode;
	}

	void makeEmpty(ElemNode* root) {
		if (!root)
			return;
		makeEmpty(root->leftChild);
		makeEmpty(root->rightChild);
		delete(root);
	}

	void printTree(ElemNode* root) const {
		if (!root)
			return;
		printTree(root->leftChild);
		std::cout << root->curElem << " ";
		printTree(root->rightChild);
	}
};

int main() {
	SearchTree<int>* ADTtree = new ADT<int>;

	int treeSize = 10;
	int elemMax = 20;
	int elemMin = 0;
	for (int i = 0; i < treeSize; i++) {
		int cur = rand()*elemMax / (RAND_MAX + 1) + elemMin;
		std::cout << "Now insert " << cur << " to ADT tree" << std::endl;
		ADTtree->insert(cur);
	}
	ADTtree->printTree();
	system("pause");
	return 0;
}