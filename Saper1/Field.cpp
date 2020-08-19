#include "Field.h"
#include "Cell.h"
#include <iostream>
#include <utility> 
#include <vector>
// <fstream>
//#include <time.h>

using namespace std;

Field::Field(int N_)
{
	cout << "TWORZY GIT";
	N = N_;
	field = new Cell*[N];
	for (int i = 0; i < N; i++)
	{
		field[i] = new Cell[N];
	}
	result = 0;
	maxResult = 0;
}

Field::Field()
{
	N = 12;
	field = new Cell*[N];
	for (int i = 0; i < N; i++)
	{
		field[i] = new Cell[N];
	}
	result = 0;
	maxResult = 0;
}

Field::~Field()
{

}

Cell& Field::getField(int i, int j)
{
	//if (i < 1 || i > 10 || j < 1 || j>10) cout << "Blad Indeksow" << endl;
	return this->field[i][j];
}

Cell& Field::operator()(int i, int j)
{
	return field[i][j];
}

Field & Field::operator=(const Field & f)
{
	return *this;
}

int Field::bombPlacment() { // przy bomb placement setuje od razu AOE bombe i wliczam zeby ja tez liczylo do cyferek ile bomb
	int maxResult = 0;
	for (int i = 1; i <= N - 2; i++)
	{
		for (int j = 1; j <= N - 2; j++)
		{
			int counter = 0;
			if (field[i][j].getValue() == 9 || field[i][j].getValue() == 12) {
				continue;
			}
			if (field[i + 1][j].getValue() == 9 || field[i + 1][j].getValue() == 12) counter++;
			if (field[i + 1][j].getValue() == 12) field[i][j].setAoe();
			if (field[i][j + 1].getValue() == 9 || field[i][j + 1].getValue() == 12) counter++;
			if (field[i][j + 1].getValue() == 12) field[i][j].setAoe();
			if (field[i - 1][j].getValue() == 9 || field[i - 1][j].getValue() == 12) counter++;
			if (field[i - 1][j].getValue() == 12) field[i][j].setAoe();
			if (field[i][j - 1].getValue() == 9 || field[i][j - 1].getValue() == 12) counter++;
			if (field[i][j - 1].getValue() == 12) field[i][j].setAoe();
			if (field[i + 1][j + 1].getValue() == 9 || field[i + 1][j + 1].getValue() == 12) counter++;
			if (field[i + 1][j + 1].getValue() == 12) field[i][j].setAoe();
			if (field[i - 1][j - 1].getValue() == 9 || field[i - 1][j - 1].getValue() == 12) counter++;
			if (field[i - 1][j - 1].getValue() == 12) field[i][j].setAoe();
			if (field[i - 1][j + 1].getValue() == 9 || field[i - 1][j + 1].getValue() == 12) counter++;
			if (field[i - 1][j + 1].getValue() == 12) field[i][j].setAoe();
			if (field[i + 1][j - 1].getValue() == 9 || field[i + 1][j - 1].getValue() == 12) counter++;
			if (field[i + 1][j - 1].getValue() == 12) field[i][j].setAoe();
			if (!(field[i][j].getAoe())) field[i][j].setValue(counter);
			if (!(field[i][j].getAoe())) maxResult += counter;
		}
	}
	this->maxResult = maxResult;
	return maxResult;
}

void Field::bombDraw(int numb, int giga) {
	bool gigabomb = false;
	int numbTMP = numb * 2;
	int* arr = new int[numb * 2];
	//int arr[numbTMP];

	for (int i = 0; i < 2 * numb; i += 2) {
		arr[i] = (rand() % (N - 2)) + 1;
		arr[i + 1] = (rand() % (N - 2)) + 1;
	}

	for (int i = 1; i <= N - 2; i++)
	{
		cout << "N-2 " << endl;
		for (int j = 1; j <= N - 2; j++)
		{
			field[i][j].setShown(10);
		}
	}

	for (int i = 0; i < 2 * numb; i += 2) {
		field[arr[i]][arr[i + 1]].setValue(9);
	}

	for (int i = 0; i < giga; i++) {
		int x = (rand() % (N - 2)) + 1;
		int y = (rand() % (N - 2)) + 1;
		field[x][y].setValue(12);
	}


}

vector <pair <int, int>> Field::takeClosest(int i, int j) {
	vector <pair <int, int>> result;
	for (int i = 1; i <= N - 2; i++) {
		for (int j = 1; j <= N - 2; j++) {
			if (field[i][j].getValue() != 12 && field[i][j].getValue() != 9 && !field[i][j].getAoe() && field[i][j].getShown() == 10) {
				result.push_back(make_pair(i, j));
			}
		}
	}
	return result;
}

int Field::getMaxResult() {
	return this->maxResult;
}




