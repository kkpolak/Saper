#pragma once
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Menu.h"
#include <iostream>
#include <utility> 

using namespace std;
using namespace sf;

enum MENUTYPE { PROPGAME, AUTOGAME };


class Game
{
private:
	MENUTYPE MENU_TYPE;
	int dimensions;
	int result;
	int N;
	int maxResult;


public:
	Game();
	~Game();
	void properGame(RenderWindow& window, Field& field, int N);
	void menu0(RenderWindow& menuWindow);
	void menu1Diff();
	void menu2LastResult();
	void setN(int N_);
	Field& gamePreparation(int N_, int gigaBombs, int fieldSize);
	void setMaxResult(int R);
	int getMax();
	int getN();
	void solver(RenderWindow& window, Field& field, int N);
};

