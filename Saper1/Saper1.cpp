#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Menu.h"
#include "Cell.h"
#include "Field.h"
#include "Game.h"

using namespace sf;
using namespace std;


int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(600, 400), "Saper-MENU");

	Game saper;
	saper.menu0(window);


	return 0;

}
