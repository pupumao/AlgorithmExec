#include "AVLTree.cc"
#include <iostream>
#include <cstdlib>

int main() {
	SearchTree<int>* testTree = new AVLTree<int>;

	int treeSize = 10000;
	int elemMax = 20000;
	int elemMin = 0;
	int i = 0;
	for (i = 0; i < 10; i++) {
		int cur = rand()*elemMax / (RAND_MAX + 1) + elemMin;
		std::cout <<std::endl<< "Now insert " << cur << " to tree" << std::endl;
		testTree->insert(cur);
		//testTree->printTree();
	}
	testTree->printTree();
	testTree->makeEmpty();
	testTree->printTree();
	system("pause");
	return 0;
}