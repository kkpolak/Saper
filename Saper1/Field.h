#pragma once
#include "Cell.h"
#include <vector>
#include <utility>
using namespace std;
class Field
{
private:
	Cell** field;
	int result;
	int maxResult;
	int N;

public:
	Field(int N);
	Field();
	~Field();
	//void resultToFile(int result, int maxResult);
	int bombPlacment();
	void bombDraw(int numb, int giga);
	Cell& getField(int i, int j);
	Cell & operator () (int i, int j);
	Field & operator = (const Field& f); //TODO
	bool checkGigaBomb(int i, int j);
	vector <pair <int, int>> takeClosest(int i, int j);
	int getMaxResult();
	//Cell operator () (int i, int j);
};

