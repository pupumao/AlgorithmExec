#pragma once

template<typename ElementType>
class SearchTree{
public:
	virtual void insert(ElementType elem) = 0;
	virtual bool remove(ElementType elem) = 0;

	virtual const ElementType& findMax() const = 0;
	virtual const ElementType& findMin() const = 0;

	virtual void makeEmpty() = 0;
	virtual bool isEmpty() const = 0;
	virtual bool contains(const ElementType elem) const= 0;
	virtual void printTree() = 0;
	virtual void printSort() const = 0;
};