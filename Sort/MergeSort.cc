#include "ISort.h"

template<typename comparable>
class MergeSort :public ISort<comparable> {
public:
	void Sort(std::vector<comparable>& targetVector) {
		int size = targetVector.size();
		mLocalVector.resize(size);
		sortVector(targetVector, 0, targetVector.size());
	}
private:
	void copyToLocal(std::vector<comparable>& targetVector, int start, int end) {
		for (int i = start; i < end; i++) {
			mLocalVector[i] = targetVector[i];
		}
	}
	void sortVector(std::vector<comparable>& targetVector, int start, int end) {
		int middle = (start + end) / 2;
		if(middle-start >1)
			sortVector(targetVector, start, middle);
		if(end - middle >1)
			sortVector(targetVector, middle, end);
		copyToLocal(targetVector, start, end);
		int index = start;
		int sub1 = start;
		int sub2 = middle;
		for (; sub1 < middle&& sub2<end; ) {
			if (mLocalVector[sub1] < mLocalVector[sub2]) {
				targetVector[index] = mLocalVector[sub1];
				sub1++;
			}
			else {
				targetVector[index] = mLocalVector[sub2];
				sub2++;
			}
			index++;
		}
		for (; sub1 < middle; sub1++, index++)
			targetVector[index] = mLocalVector[sub1];
		for (; sub2 < end; sub2++, index++)
			targetVector[index] = mLocalVector[sub2];
	}
	std::vector<comparable> mLocalVector;
};