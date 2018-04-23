#pragma once
#include <vector>
template<typename comparable>
class BinaryHeap {
public:
	BinaryHeap(int capacity = 100) {
		mElems.resize(capacity + 1);
	}

	BinaryHeap(const std::vector<comparable>& originElems) {
		mCurSize = 0;
		mElems.resize(originElems.size() + 1);
		for (auto itr = originElems.begin(); itr!= originElems.end(); itr++) {
			insert(*itr);
		}
	}

	bool isEmpty() const {
		return mCurSize > 0;
	}

	const comparable& findMin() const {
		return mElems[1];
	}

	void insert(const comparable& cur) {
		if (mCurSize + 2 > mElems.size())
			mElems.resize(mElems.size() * 2);
		
		mElems[++mCurSize] = cur;
		int sonIndxe = mCurSize;
		int parentIndex = mCurSize / 2;
		while (parentIndex && cur < mElems[parentIndex]) {
			mElems[sonIndxe] = mElems[parentIndex];
			sonIndxe = parentIndex;
			parentIndex /= 2;
		}
		mElems[sonIndxe] = cur;
	}

	void deleteMin() {
		comparable tmp;
		deleteMin(tmp);
	}
	void deleteMin(comparable& minElem) {
		if (isEmpty()) {
			minElem = -1;
			return;
		}
		minElem = mElems[1];
		comparable target = mElems[mCurSize--];
		int index = 1;
		int sonIndex = index * 2;
		while (sonIndex < mCurSize){
			if (mElems[sonIndex] > mElems[sonIndex + 1])
				sonIndex++;
			if(mElems[sonIndex] >= target)
				break;
			mElems[index] = mElems[sonIndex];
			index = sonIndex;
			sonIndex *= 2;
		}
		mElems[index] = target;
	}

	void makeEmpty() {
		mElems.clear();
		mCurSize = 0;
	}
private:
	std::vector<comparable> mElems;
	int mCurSize;
};