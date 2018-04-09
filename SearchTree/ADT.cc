#include "SearchTree.h"
#include <vector>

template<typename ElementType>
class ADT :public SearchTree<ElementType> {
public:
	ADT():mTreeRoot(NULL){}

	~ADT() {
		makeEmpty();
	}

	void insert(ElementType elem) {
		insert(mTreeRoot, elem);
	}
	bool remove(ElementType elem) {
		return remove(mTreeRoot, elem);
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

	void printSort() const {
		printSort(mTreeRoot);
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

	bool insert(ADTNode*& root, ElementType elem) {
		bool ret = false;
		if (!root) {
			root = new ADTNode(elem, NULL, NULL);
			return true;
		}
		if (root->curElem > elem) {
			ret = insert(root->leftChild, elem);
		}
		else if (root->curElem < elem) {
			ret = insert(root->rightChild, elem);
		}
		else {
			return false;
		}
		return ret;
	}

	bool remove(ADTNode*& root, ElementType elem) {
		bool ret = false;
		if (!root)
			return ret;
		if (root->curElem > elem)
			ret = remove(root->leftChild, elem);
		else if (root->curElem < elem)
			ret = remove(root->rightChild, elem);
		else {
			ADTNode* origin = root;
			if (root->rightChild) {
				ADTNode* acceptance = root->leftChild;
				ADTNode* candidate = findMin(root->rightChild);
				root->curElem = candidate->curElem;
				remove(root->rightChild, candidate->curElem);
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

	void printSort(ADTNode* root) const {
		if (!root)
			return;
		printTree(root->leftChild);
		std::cout << root->curElem << " ";
		printTree(root->rightChild);
	}
	
	void printLevel(std::vector<ADTNode*>& curLevel, std::vector<ADTNode*>& nextLevel) {
		nextLevel.clear();
		for (int index = 0; index < curLevel.size(); index++) {
			ADTNode* curNode = curLevel[index];
			if (curNode) {
				std::cout << curLevel[index]->curElem << " ";
				nextLevel[2 * index] = curLevel[index]->leftChild;
				nextLevel[2 * index + 1] = curLevel[index]->rightChild;
			}
			else{
				std::cout << -1 << " ";
			}
		}
		std::cout << std::endl;
	}

	void printTree(ADTNode* root) const {
		if (!root)
			return;
		std::vector<ADTNode*> curLevel;
		std::vector<ADTNode*> nextLevel;
		curLevel.push_back(root);
		while (!curLevel.empty()){
			printLevel(curLevel, nextLevel);
			curLevel.clear();
			curLevel = nextLevel;
		}
	}
};