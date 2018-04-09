#include "AVLTree.cc"
#include "ADT.cc"
#include <iostream>
#include <cstdlib>

int main() {
	SearchTree<int>* testTree = new AVLTree<int>;

	int treeSize = 100;
	int elemMax = 200;
	int elemMin = 0;
	int i = 0;
	for (i = 0; i < 20; i++) {
		int cur = rand()*elemMax / (RAND_MAX + 1) + elemMin;
		std::cout <<std::endl<< "Now insert " << cur << " to tree" << std::endl;
		testTree->insert(cur);
		//testTree->printTree();
	}

	testTree->printTree();
	testTree->remove(116);
	std::cout << std::endl;
	testTree->printTree();

	testTree->remove(149);
	std::cout << std::endl;
	testTree->printTree();

	testTree->remove(164);
	std::cout << std::endl;
	testTree->printTree();

	testTree->remove(179);
	std::cout << std::endl;
	testTree->printTree();
	system("pause");
	return 0;
}