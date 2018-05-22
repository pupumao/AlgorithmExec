#include "Puzzle.h"
#include "UnionFind.h"
#include <iostream>
#include <random>

class PuzzleImp {
public:
	PuzzleImp(int width, int height):mWidth(width), mHeight(height) {
		mUnionBase = new UnionFind(width*height);
		generatePuzzle();
	}

	~PuzzleImp() {
		delete mUnionBase;
	}

	void printPuzzle() {
		std::cout << std::endl;
		for (int i = 0; i < mHeight; i++) {
			for (int j = 0; j < mWidth-1; j++) {
				std::cout << "  ";
				std::cout << (hasRightWall(j, i) ? "|" : " ");
			}
			std::cout << std::endl;
			if(i == mHeight-1)
				break;
			for (int j = 0; j < mWidth; j++) {
				std::cout << (hasUnderWsll(j, i) ? "--" : "  ");
				std::cout << " ";
			}
			std::cout << std::endl;
		}
	}
private:
	void generatePuzzle() {
		std::default_random_engine generator;
		std::uniform_int_distribution<int> horizontalDistribution(0, mWidth-1);
		std::uniform_int_distribution<int> verticalDistribution(0, mHeight - 1);
		std::uniform_int_distribution<int> directionDistribution(0, 1);
		while (!mUnionBase->isUnioned(0, mWidth* mHeight-1)){
			int hIndex = horizontalDistribution(generator);
			int vIndex = verticalDistribution(generator);
			int elemIndex = vIndex * mWidth + hIndex;

			int direct = directionDistribution(generator);
			switch (direct) {
			case 0:
				if (hasLeftWall(hIndex, vIndex)) {
					mUnionBase->UnionTo(elemIndex, elemIndex - 1);
				}
				break;
			case 1:
				if (hasOverWall(hIndex, vIndex)) {
					mUnionBase->UnionTo(elemIndex, elemIndex - mWidth);
				}
				break;
			default:
				break;
			}
			//printPuzzle();
		}
	}
	bool hasLeftWall(int horizontalIndex, int verticalIndex) {
		int elemIndex = verticalIndex * mWidth + horizontalIndex;
		int leftNeighbor = elemIndex - 1;
		if (elemIndex > mWidth* mHeight - 1|| leftNeighbor<0)
			return false;
		return !mUnionBase->isUnioned(elemIndex, leftNeighbor);
	}
	bool hasOverWall(int horizontalIndex, int verticalIndex) {
		int elemIndex = verticalIndex * mWidth + horizontalIndex;
		int overNeighbor = elemIndex - mWidth;
		if (elemIndex > mWidth* mHeight - 1 || overNeighbor < 0)
			return false;
		return !mUnionBase->isUnioned(elemIndex, overNeighbor);
	}
	bool hasRightWall(int horizontalIndex, int verticalIndex) {
		int elemIndex = verticalIndex * mWidth + horizontalIndex;
		int rightNeighbor = elemIndex + 1;
		if (elemIndex > mWidth* mHeight - 1)
			return false;
		return !mUnionBase->isUnioned(elemIndex, rightNeighbor);
	}
	bool hasUnderWsll(int horizontalIndex, int verticalIndex) {
		int elemIndex = verticalIndex * mWidth + horizontalIndex;
		int underNeighbor = elemIndex + mWidth;
		if (elemIndex > mWidth* mHeight - 1)
			return false;
		return !mUnionBase->isUnioned(elemIndex, underNeighbor);
	}
private:
	UnionFind * mUnionBase;
	int mWidth;
	int mHeight;
};

Puzzle::Puzzle(int width, int height) {
	mImp = new PuzzleImp(width, height);
}

Puzzle::~Puzzle() {
	delete mImp;
	mImp = nullptr;
}

void Puzzle::printPuzzle() {
	mImp->printPuzzle();
}