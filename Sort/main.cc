#include "InsertSort.cc"
#include "MergeSort.cc"
#include <iostream>

void generateSourceVector(std::vector<int>& sourceVector, int size, int ulimit) {
	sourceVector.clear();
	sourceVector.resize(size);
	for (int i = 0; i < size; i++) {
		int curValue = 1 + std::rand() / ((RAND_MAX + 1u) / ulimit);
		sourceVector[i] = curValue;
	}
}

template<typename comparable>
void printSourceVector(const std::vector<comparable>& sourceVector) {
	for (auto ite = sourceVector.begin(); ite != sourceVector.end(); ite++) {
		std::cout << *ite << " ";
	}
	std::cout << std::endl;
}

int main() {
	ISort<int>* sortMethod = new MergeSort<int>;
	int sourceSize = 20;
	int uLimit = 10000;
	std::vector<int> sourceVector;
	generateSourceVector(sourceVector, sourceSize, uLimit);
	printSourceVector<int>(sourceVector);
	sortMethod->Sort(sourceVector);
	printSourceVector<int>(sourceVector);
	delete sortMethod;
	system("pause");
	return 0;
}