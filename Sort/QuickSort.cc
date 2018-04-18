#include "ISort.h"

template<typename comparable>
class QuickSort :public ISort<comparable> {
public:
	void Sort(std::vector<comparable>& targetVector) {
		SortImp(targetVector, 0, targetVector.size()-1);
	}
private:
	void switchElement(comparable& a, comparable& b) {
		if (a == b)
			return;
		comparable temp = a;
		a = b;
		b = temp;
	}
	void sortTwoElement(comparable& a, comparable& b) {
		if (a > b)
			switchElement(a, b);
	}
	void SortImp(std::vector<comparable>& targetVector, int start, int end) {
		int lowIndex = start, highIndex = end-1, targetIndex = start+(end - start) / 2;
		comparable targetValue = targetVector[targetIndex];
		switchElement(targetVector[targetIndex], targetVector[end]);
		while (lowIndex < end&&highIndex >start){
			while (targetVector[lowIndex] < targetValue)
				lowIndex++;
			while (targetVector[highIndex] > targetValue)
				highIndex--;
			if (lowIndex > highIndex -1)
				break;
			switchElement(targetVector[lowIndex], targetVector[highIndex]);
		}
		targetIndex = lowIndex;
		switchElement(targetVector[targetIndex], targetVector[end]);
#ifdef DEBUG
		std::cout << "--------" << std::endl;
		std::cout << "start: " << start << " and end: " << end << std::endl;
		std::cout << "now targetValue: " << targetValue << "----";
		for (int i = start; i < end+1; i++) {
			std::cout << targetVector[i]<<" ";
		}
		std::cout << std::endl;
#endif
		if (targetIndex - start >2)
			SortImp(targetVector, start, targetIndex - 1);
		else if(targetIndex - start==2)
			sortTwoElement(targetVector[start], targetVector[targetIndex - 1]);

		if(end - targetIndex > 2)
			SortImp(targetVector, targetIndex + 1, end);
		else if(end - targetIndex ==2)
			sortTwoElement(targetVector[targetIndex + 1], targetVector[end]);
	}
};