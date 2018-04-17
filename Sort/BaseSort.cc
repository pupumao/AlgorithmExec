#include "ISort.h"

template<typename comparable>
class BaseSort :public ISort<comparable> {
public:
	BaseSort() {
		mVectorBase.resize(10);
	}
	void Sort(std::vector<comparable>& targetVector) {
		bool hasValue = false;
		int base = 10;
		do{
			for (auto itr = targetVector.begin(); itr != targetVector.end(); itr++) {
				int baseValue = *itr%base;
				baseValue /= (base / 10);
				if (baseValue)
					hasValue = true;
				mVectorBase[baseValue].push_back(*itr);
			}
			if(!hasValue)
				break;
			targetVector.clear();
			for (auto itr = mVectorBase.begin(); itr != mVectorBase.end(); itr++) {
				for (auto itrComp = (*itr).begin(); itrComp != (*itr).end(); itrComp++) {
					targetVector.push_back(*itrComp);
				}
				(*itr).clear();
			}
			base *= 10;
			hasValue = false;
		} while (true);
	}
private:
	std::vector<std::vector<comparable>> mVectorBase;
};