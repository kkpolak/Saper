#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;
using namespace sf;

#define MENU1 4
#define MENU2 5
#define MENU3 2

class Menu
{
private:
	int selectedItemIndex;
	int firstButton;
	float width;
	float height;
	int buttonsQuantity;
	sf::Font font;
	sf::Text menu[5];

public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int getPressedItem() { return selectedItemIndex; }
	void choiceDificulty();
	void firstWindow();
	void lastResult();
	string loadLastResult();
};

