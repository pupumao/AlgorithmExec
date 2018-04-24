#pragma once

#define HEAPDLL_API __declspec(dllexport)

#include <vector>

enum HeapType{
	HeapTypeMin = 0x3000,
	HeapTypeMax
};

#define ERRORVALUE 0Xffffff

template<typename comparable>
class HEAPDLL_API BinaryHeap {
public:
	BinaryHeap(const std::vector<comparable>& originElems, HeapType type = HeapTypeMin)
	:mType(type),mCurSize(0) {
		mElems.resize(originElems.size());
		for (auto itr = originElems.begin(); itr!= originElems.end(); itr++) {
			insert(*itr);
		}
	}

	bool isEmpty() const {
		return mCurSize <1;
	}

	const comparable& findTop() const {
		return mElems[0];
	}

	void insert(const comparable& cur) {
		if (mCurSize + 1 > mElems.size())
			mElems.resize(mCurSize * 2);		
		mElems[mCurSize] = cur;
		if (mCurSize == 0) {
			mCurSize++;
			return;
		}

		int sonIndex = mCurSize;
		int parentIndex = (mCurSize-1) / 2;
		//use sonIndex for compare, if sonIndex the first elem, time for loop end
		while (sonIndex && 
			((mType==HeapTypeMin && cur < mElems[parentIndex]) ||
				(mType==HeapTypeMax && cur > mElems[parentIndex]))) {
			mElems[sonIndex] = mElems[parentIndex];
			sonIndex = parentIndex;
			parentIndex = (parentIndex-1) / 2;
		}
		mElems[sonIndex] = cur;
		mCurSize++;
	}

	void deleteTop() {
		comparable tmp;
		deleteTop(tmp);
	}
	void deleteTop(comparable& topElem) {
		if (isEmpty()) {
			topElem = ERRORVALUE;
			return;
		}
		topElem = mElems[0];
		comparable target = mElems[mCurSize-1];
		int index = 0;
		int sonIndex = index * 2+1;
		while (sonIndex < mCurSize){
			if (sonIndex+1 < mCurSize&&
				((mType == HeapTypeMin && mElems[sonIndex] > mElems[sonIndex + 1])||
					(mType == HeapTypeMax && mElems[sonIndex] < mElems[sonIndex+1])))
				sonIndex++;
			if((mType==HeapTypeMin&& mElems[sonIndex] >= target)||
				(mType==HeapTypeMax&& mElems[sonIndex]>= target))
				break;
			mElems[index] = mElems[sonIndex];
			index = sonIndex;
			sonIndex = 2*sonIndex+1;
		}
		mElems[index] = target;
		mCurSize--;
	}

	void makeEmpty() {
		mElems.clear();
		mCurSize = 0;
	}
private:
	std::vector<comparable> mElems;
	int mCurSize;
	HeapType mType;
};