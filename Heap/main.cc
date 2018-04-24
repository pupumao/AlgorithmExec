#include "Heap.h"
#include <iostream>
#include <cassert>

void generateSourceVector(std::vector<int>& sourceVector, int size, int ulimit) {
	sourceVector.clear();
	sourceVector.resize(size);
	for (int i = 0; i < size; i++) {
		int curValue = 1 + std::rand() / ((RAND_MAX + 1u) / ulimit);
		sourceVector[i] = curValue;
	}
}

template<typename comparable>
void printSourceVector(const std::vector<comparable>& sourceVector, bool verify = false) {
	comparable last = *sourceVector.begin();
	for (auto ite = sourceVector.begin(); ite != sourceVector.end(); ite++) {
		if (verify)
			assert(*ite >= last);
		std::cout << *ite << " ";
		last = *ite;
	}
	std::cout << std::endl;
}

int main() {
	int testSize = 20;
	int ulimit = 1000;
	std::vector<int> sourceVector;
	generateSourceVector(sourceVector, testSize, ulimit);
	BinaryHeap<int> testHeap(sourceVector);
	printSourceVector<int>(sourceVector);
	while (!testHeap.isEmpty()){
		int curMin = -1;
		testHeap.deleteTop(curMin);
		std::cout << curMin << " ";
	}
	std::cout << std::endl;
	system("pause");
}