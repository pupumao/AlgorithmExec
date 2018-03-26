#pragma once

class UnionFind{
public:
	//virtual void inputElement(int elem) = 0;
	virtual void UnionTo(int elemA, int elemB) = 0;
	virtual bool isUnioned(int elemA, int elemB) = 0;
};