#include "Game.h"
#include <utility>
#include <windows.h>
#include <fstream>
#include <string>

void resultToFile(int result, int maxResult, string level)
{
	fstream file;
	file.open("Wyniki.txt", ios::out | ios::app);
	file << "Wynik rozgrywki: " << result << "/" << maxResult << " poziom: " << level << endl;
	file.close();
}

Game::Game()
{
	MENU_TYPE = PROPGAME;
	dimensions = 32;
	result = 0;
	N = 0;
	maxResult = 0;
}

Game::~Game()
{

}

void Game::properGame(RenderWindow& window, Field& field, int N)
{
	string lvl;
	if (N == 10) lvl = "Easy";
	else if (N == 16) lvl = "Medium";
	else lvl = "Hard";
	result = 0;
	this->setMaxResult(field.getMaxResult());
	Texture q;
	q.loadFromFile("images/tiles.jpg");
	Sprite pic(q);
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / dimensions;
		int y = pos.y / dimensions;
		x = abs(x);
		y = abs(y);
		x %= N + 2; // TUTAJ +2 I MOZNA CHODZIC WSZEDZIE
		y %= N + 2; // TUTAJ +2 I MOZNA CHODZIC WSZEDZIE
		bool aoe = false;
		//cout << "x: " << x << " y: " << y << endl;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					field(x, y).setShown(field(x, y).getValue());
					if (field(x, y).getAoe()) aoe = true; // jesli po kliknieciu kliknelismy na pole obok ktorego aoe bomba to aoe = true;
					if ((field(x, y).getShown() > 0 && field(x, y).getShown() < 9) && field(x, y).getShown() != 12) // dodalem zeby nie dodawalo do wyniku 13 czyli aoe bomba
					{
						result += field(x, y).getShown();
					}
				}
				else if (event.key.code == Mouse::Right && field(x, y).getShown() == 11) field(x, y).setShown(10);
				else if (event.key.code == Mouse::Right) field(x, y).setShown(11);
			}
		}


		window.clear(Color::White);


		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (field(x, y).getShown() == 9 || field(x, y).getShown() == 12 || aoe) field(i, j).setShown(field(i, j).getValue()); //  sprawdzam
																							// czy aoe i jesli aoe to konczymy zabawe
				pic.setTextureRect(IntRect(field(i, j).getShown() * dimensions, 0, dimensions, dimensions));
				pic.setPosition(i*dimensions, j*dimensions);
				window.draw(pic);
			}
		}


		window.display();
	}

	resultToFile(result, this->getMax(), lvl);
	RenderWindow next(VideoMode(600, 400), "SAAAAPERR");
	menu0(next);

}

void Game::menu0(RenderWindow& menuWindow)
{
	Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
	//RenderWindow windowTMO(VideoMode(400, 400), "SAPER");
	while (menuWindow.isOpen())
	{

		Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					switch (menu.getPressedItem())
					{
					case 0:
						menuWindow.close();
						menu.choiceDificulty();
						MENU_TYPE = PROPGAME;
						menu1Diff();
						break;
					case 1:
						menuWindow.close();
						menu.choiceDificulty();
						MENU_TYPE = AUTOGAME;
						menu1Diff();
						break;
					case 2:
						menuWindow.close();
						menu.lastResult();
						MENU_TYPE = AUTOGAME;
						menu2LastResult();
						break;
					case 3:
						menuWindow.close();
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				break;
			case Event::Closed:
				menuWindow.close();
				break;
			default:
				break;
			}

		}


		menuWindow.clear();

		menu.draw(menuWindow);

		menuWindow.display();
	}
}

void Game::menu1Diff()
{
	RenderWindow menuWindow(VideoMode(600, 600), "Poziom");
	Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
	menu.choiceDificulty();

	while (menuWindow.isOpen())
	{
		Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					if (menu.getPressedItem() == 0)
					{
						cout << "wybierz poziom" << endl;
					}
					else if (menu.getPressedItem() == 1)
					{
						Field field = gamePreparation(12, 1, 400);
						RenderWindow window(VideoMode(400, 400), "SAPER EZ");
						menuWindow.close();
						if (MENU_TYPE == PROPGAME) properGame(window, field, 10);
						else if (MENU_TYPE == AUTOGAME) solver(window, field, 10);
					}
					else if (menu.getPressedItem() == 2)
					{
						Field field = gamePreparation(18, 2, 600);
						RenderWindow window(VideoMode(600, 600), "SAPER MED");
						menuWindow.close();
						if (MENU_TYPE == PROPGAME) properGame(window, field, 16);
						else if (MENU_TYPE == AUTOGAME) solver(window, field, 16);
					}
					else if (menu.getPressedItem() == 3)
					{
						Field field = gamePreparation(26, 3, 830);
						RenderWindow window(VideoMode(830, 830), "SAPER HARD");
						menuWindow.close();
						if (MENU_TYPE == PROPGAME) properGame(window, field, 24);
						else if (MENU_TYPE == AUTOGAME) solver(window, field, 24);
					}
					else if (menu.getPressedItem() == 4)
					{
						menu.firstWindow();
						menuWindow.close();
						RenderWindow window(VideoMode(400, 400), "SAPER");
						menu0(window);
					}
				default:
					break;
				}
				break;
			case Event::Closed:
				menuWindow.close();
				break;
			default:
				break;
			}
		}

		menuWindow.clear();

		menu.draw(menuWindow);

		menuWindow.display();
	}
}

void Game::menu2LastResult()
{
	RenderWindow menuWindow(VideoMode(600, 400), "Poziom");
	Menu menu(menuWindow.getSize().x, menuWindow.getSize().y);
	menu.lastResult();
	while (menuWindow.isOpen())
	{
		Event event;
		while (menuWindow.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					menu.MoveUp();
					break;
				case Keyboard::Down:
					menu.MoveDown();
					break;
				case Keyboard::Return:
					if (menu.getPressedItem() == 0)
					{
					}
					else if (menu.getPressedItem() == 1)
					{
						menu.firstWindow();
						menuWindow.close();
						RenderWindow window(VideoMode(400, 400), "SAPER");
						menu0(window);
					}
					break;
				default:
					break;
				}
				break;
			case Event::Closed:
				menuWindow.close();
				break;
			default:
				break;
			}

		}

		menuWindow.clear();

		menu.draw(menuWindow);

		menuWindow.display();
	}

}

Field& Game::gamePreparation(int N_, int gigaBombs, int fieldSize) { //// MOZLIWE ZE NIE DZIALA
	int numb;
	int giga;
	this->setN(N_);
	Field f(N_);
	if (N_ == 12) {
		numb = 12;
		giga = 1;
	}
	else if (N_ == 18) {
		numb = 24;
		giga = 2;
	}
	else if (N_ == 26) {
		numb = 50;
		giga = 3;
	}
	f.bombDraw(numb, giga); // rysuje bomby
	maxResult = f.bombPlacment(); // licze ile max res
	for (int i = 0; i < N_; i++) {
		for (int j = 0; j < N_; j++) cout << f.getField(j, i).getValue() << " ";
		cout << endl;
	}
	this->setMaxResult(maxResult); // ustawiam maxRes w game
	return f;
}

void Game::solver(RenderWindow& window, Field& field, int N)
{
	vector <pair <int, int>> solved;
	solved = field.takeClosest(1, 1);
	this->setN(this->getN() - 2);
	Texture q;
	q.loadFromFile("images/tiles.jpg");
	Sprite pic(q);
	int helper = solved.size() - 1;

	while (window.isOpen())
	{
		pair <int, int> curr;
		if (!solved.empty()) {
			curr.first = solved[helper].first;
			curr.second = solved[helper].second;
			solved.pop_back();
		}
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x / dimensions;
		int y = pos.y / dimensions;
		x = abs(x);
		y = abs(y);
		x %= N + 2; // TUTAJ +2 I MOZNA CHODZIC WSZEDZIE
		y %= N + 2; // TUTAJ +2 I MOZNA CHODZIC WSZEDZIE
		bool aoe = false;
		//cout << "x: " << x << " y: " << y << endl;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		field(curr.first, curr.second).setShown(field(curr.first, curr.second).getValue());


		window.clear(Color::White);


		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				pic.setTextureRect(IntRect(field(i, j).getShown() * dimensions, 0, dimensions, dimensions));
				pic.setPosition(i*dimensions, j*dimensions);
				window.draw(pic);
			}
		}

		window.display();
		helper--;
		Sleep(100);
		if (solved.empty()) {
			for (int i = 1; i <= N; i++)
			{
				for (int j = 1; j <= N; j++)
				{
					field(i, j).setShown(field(i, j).getValue());
					pic.setTextureRect(IntRect(field(i, j).getShown() * dimensions, 0, dimensions, dimensions));
					pic.setPosition(i*dimensions, j*dimensions);
					window.draw(pic);
				}
			}
		}
	}

	RenderWindow next(VideoMode(600, 400), "SAAAAPERR");
	menu0(next);
}

void Game::setN(int N_) {
	this->N = N_;
}

void Game::setMaxResult(int R) {
	this->maxResult = R;
}

int Game::getMax() {
	return this->maxResult;
}

int Game::getN() {
	return this->N;
}

