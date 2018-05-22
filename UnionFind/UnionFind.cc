#include "UnionFind.h"
#include <vector>
#include <iostream>
#include <cassert>

class UnionFindImp{
public:
	UnionFindImp(int elemNum) {
		for (int i = 0; i < elemNum; i++) {
			mUnions.push_back(i);
			mUnionSizes.push_back(1);
		}
	}
	~UnionFindImp(){}

	//void inputElement(int elem);
	void UnionTo(int elemA, int elemB) {
		int size = mUnions.size();
		assert(elemA < size);
		assert(elemB < size);

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
		else {
			mUnions[rootA] = rootB;
			mUnionSizes[rootB] += mUnionSizes[rootA];
		}
	}
	bool isUnioned(int elemA, int elemB) {
		int size = mUnions.size();
		assert(elemA < size);
		assert(elemB < size);

		int rootA = elemA;
		int rootB = elemB;

		while (rootA != mUnions[rootA])
			rootA = mUnions[rootA];

		while (rootB != mUnions[rootB])
			rootB = mUnions[rootB];

		return rootA == rootB;
	}

private:
	std::vector<int> mUnions;
	std::vector<int> mUnionSizes;
};

UnionFind::UnionFind(int elemNum) {
	mImp = new UnionFindImp(elemNum);
}

UnionFind::~UnionFind() {
	delete mImp;
	mImp = nullptr;
}

void UnionFind::UnionTo(int elemA, int elemB) {
	mImp->UnionTo(elemA, elemB);
}

bool UnionFind::isUnioned(int elemA, int elemB) {
	return mImp->isUnioned(elemA, elemB);
}