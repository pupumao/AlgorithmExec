#pragma once

class UnionFindImp;
class UnionFind{
public:
	UnionFind(int elemNum);
	~UnionFind();

	void UnionTo(int elemA, int elemB);
	bool isUnioned(int elemA, int elemB);
private:
	UnionFindImp * mImp;
};