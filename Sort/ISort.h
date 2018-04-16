#pragma once
#include <vector>
template<typename comparable>
class ISort {
public:
	virtual void Sort(std::vector<comparable>& targetVector) = 0;
};