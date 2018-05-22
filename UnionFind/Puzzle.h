#pragma once

class PuzzleImp;
class Puzzle {
public:
	Puzzle(int width, int height);
	~Puzzle();

	void printPuzzle();
private:
	PuzzleImp * mImp;
};