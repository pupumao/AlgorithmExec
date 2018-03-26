#include "UnionFind.h"
#include <vector>
#include <iostream>

class TreeUnionFind : public UnionFind {
public:
	TreeUnionFind(int elemNum);
	~TreeUnionFind();

	//void inputElement(int elem);
	void UnionTo(int elemA, int elemB);
	bool isUnioned(int elemA, int elemB);

private:
	int* mUnions;
	int* mUnionSizes;
	int elemCount;
};

TreeUnionFind::TreeUnionFind(int elemNum) {
	mUnions = new int[elemNum + 1];
	mUnionSizes = new int[elemNum + 1];
	for (int i = 1; i < elemNum + 1; i++) {
		mUnions[i] = i;
		mUnionSizes[i] = 1;
	}
}

TreeUnionFind::~TreeUnionFind() {}

bool TreeUnionFind::isUnioned(int elemA, int elemB) {
	int rootA = elemA;
	int rootB = elemB;

	while (rootA != mUnions[rootA])
		rootA = mUnions[rootA];

	while (rootB != mUnions[rootB])
		rootB = mUnions[rootB];

	return rootA == rootB;
}

void TreeUnionFind::UnionTo(int elemA, int elemB) {
	int rootA = elemA;
	int rootB = elemB;

	while (rootA != mUnions[rootA])
		rootA = mUnions[rootA];
	
	while (rootB != mUnions[rootB])
		rootB = mUnions[rootB];
	
	int sizeA = mUnionSizes[rootA];
	int sizeB = mUnionSizes[rootB];
	if (sizeA > sizeB) {
		mUnions[rootB] = rootA;
		mUnionSizes[rootA] += mUnionSizes[rootB];
	}
	else{
		mUnions[rootA] = rootB;
		mUnionSizes[rootB] += mUnionSizes[rootA];
	}
}

int main() {
	UnionFind* unionFind = new TreeUnionFind(10);
	unionFind->UnionTo(1, 10);
	unionFind->UnionTo(2, 5);
	unionFind->UnionTo(3, 6);
	unionFind->UnionTo(10, 4);
	unionFind->UnionTo(4, 5);

	std::cout << "element 2 and 1 is already unioned? " << 
		unionFind->isUnioned(2, 1) << std::endl;
	system("pause");
	return 0;
}