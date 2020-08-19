#pragma once
class Cell
{
private:
	int value;
	int shwon;
	bool aoe;
public:
	Cell(int v, int s);
	~Cell();
	Cell();
	int getValue();
	void setValue(int v);
	int getShown();
	void setShown(int s);
	bool getAoe();
	void setAoe();
};

