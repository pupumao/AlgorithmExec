#include "Heap.cc"
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
	std::vector<int> sourceVector;
	BinaryHeap<int> testHeap(sourceVector);
	printSourceVector<int>(sourceVector);
	while (!testHeap.isEmpty()){
		int curMin = -1;
		testHeap.deleteMin(curMin);
		std::cout << curMin << " ";
	}
	std::cout << std::endl;
	system("pause");
}