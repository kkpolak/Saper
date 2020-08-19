#include "Menu.h"

Menu::Menu(float width_, float height_)
{
	width = width_;
	height = height_;
	buttonsQuantity = MENU1;
	firstButton = 0;

	font.loadFromFile("arial.ttf");
	firstWindow();
}

Menu::~Menu()
{

}

void Menu::firstWindow()
{
	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("PLAY");
	menu[0].setPosition(sf::Vector2f(50, height / (MENU1 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("AUTO-SOLVE");
	menu[1].setPosition(sf::Vector2f(50, height / (MENU1 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("LOAD LAST RESULT");
	menu[2].setPosition(sf::Vector2f(50, height / (MENU1 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("EXIT");
	menu[3].setPosition(sf::Vector2f(50, height / (MENU1 + 1) * 4));
	buttonsQuantity = MENU1;
	selectedItemIndex = 0;
	firstButton = 0;
}

void Menu::lastResult()
{
	menu[0].setFont(font);
	menu[0].setFillColor(Color::White);
	menu[0].setString(loadLastResult());
	menu[0].setPosition(Vector2f(60, height / (MENU3 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("BACK");
	menu[1].setPosition(Vector2f(50, height / (MENU3 + 1) * 2));

	buttonsQuantity = MENU3;
	firstButton = 1;
	selectedItemIndex = 0;
}

string Menu::loadLastResult()
{
	string result = "Brak wyniku";
	string line = "";
	fstream file;
	file.open("Wyniki.txt", ios::in);
	while (getline(file, line))
	{
		if (line != "" && line != " " && line != "\n")
		{
			result = line;
		}
	}

	return result;
}

void Menu::choiceDificulty()
{
	font.loadFromFile("arial.ttf");

	menu[0].setFont(font);
	menu[0].setFillColor(Color::Red);
	menu[0].setString("Select the level of difficulty: ");
	menu[0].setPosition(Vector2f(30, height / (MENU2 + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(Color::White);
	menu[1].setString("EASY");
	menu[1].setPosition(Vector2f(50, height / (MENU2 + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(Color::White);
	menu[2].setString("MEDIUM");
	menu[2].setPosition(Vector2f(50, height / (MENU2 + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(Color::White);
	menu[3].setString("HARD");
	menu[3].setPosition(Vector2f(50, height / (MENU2 + 1) * 4));

	menu[4].setFont(font);
	menu[4].setFillColor(Color::White);
	menu[4].setString("BACK");
	menu[4].setPosition(Vector2f(30, 40 + (height / (MENU2 + 1) * 5)));

	buttonsQuantity = MENU2;
	firstButton = 1;
	selectedItemIndex = 0;
}

void Menu::draw(sf::RenderWindow &window)
{

	for (int i = 0; i < buttonsQuantity; i++) {
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= firstButton)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < buttonsQuantity)
	{
		menu[selectedItemIndex].setFillColor(Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(Color::Red);
	}
}
