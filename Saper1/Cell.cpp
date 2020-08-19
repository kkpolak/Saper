#include "Cell.h"

Cell::Cell(int v, int s)
{
	value = v;
	shwon = s;
	aoe = false; // nowe pole do zapamietywania aoe bomby
}

Cell::Cell()
{
	value = 0;
	shwon = 0;
	aoe = false;
}

Cell::~Cell()
{

}

int Cell::getValue()
{
	return value;
}

int Cell::getShown()
{
	return shwon;
}

bool Cell::getAoe()
{
	return aoe;
}

void Cell::setAoe()
{
	aoe = true;
}

void Cell::setValue(int v)
{
	value = v;
}

void Cell::setShown(int s)
{
	shwon = s;
}
