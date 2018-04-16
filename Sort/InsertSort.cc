#include "ISort.h"

template<typename comparable>
class InsertSort :public ISort<comparable> {
public:
	void Sort(std::vector<comparable>& targetVector) {
		int size = targetVector.size();
		for (int i = 1; i < size; i++) {
			comparable targetValue = targetVector[i];
			for (int j = i - 1; j > -1; j--) {
				if(targetValue >= targetVector[j])
					break;
				comparable curValue = targetVector[j];
				targetVector[j] = targetValue;
				targetVector[j + 1] = curValue;
			}
		}
	}
};