#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <iostream>
#include <ctime>
#include <windows.h>

struct photo { // we make structures to track the score, we cannot compare Texture/Sprite to each other
	int number;
	sf::Texture data;
};

sf::Sprite Piece[16];
photo arr[16];
unsigned int position = 15; // we always start in bottom right corner, we are tracking the position to get right swap

std::string intToString(int i) // simple convertion from int to string, element of puzzle are from 1.jpg ..... 15.jpg
{
	std::stringstream ss;
	ss << i + 1;
	std::string x = ss.str();
	x += ".jpg";
	return x;
}

bool winCondition() // checking if the pieces are in right order, if yes - you won
{
	return (arr[0].number == 0) && (arr[1].number == 1) && (arr[2].number == 2) && (arr[3].number == 3) && (arr[4].number == 4) &&
		(arr[5].number == 5) && (arr[6].number == 6) && (arr[7].number == 7) && (arr[8].number == 8) && (arr[9].number == 9) &&
		(arr[10].number == 10) && (arr[11].number == 11) && (arr[12].number == 12) && (arr[13].number == 13) && (arr[14].number == 14);
}

void assignAndShuffle(photo *arr)
{
	for (int i = 0; i < 16; i++) // assigning pictures to Tektures and set number to order of element
	{
		std::string x = intToString(i);
		arr[i].data.loadFromFile(x.c_str());
		arr[i].number = i;
	}
	for (int i = 0; i < 15; i++) // swaping Textures randomly to generate puzzle
	{
		int x = rand() % 15;
		std::swap(arr[i], arr[x]);
	}

	for (int i = 0; i < 16; i++) // making Sprites
	{
		Piece[i].setTexture(arr[i].data);
	}

}

void setPosition(sf::Sprite *Piece) //setting good position for each Sprite, it makes matrix such as
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			Piece[i * 4 + j].setPosition(j * 100, i * 100);
		}
}

void programControl(sf::Event &e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) // if right key move right, checking if you are not get out or border
	{
		if (position != 3 && position != 7 && position != 11 && position != 15)
		{
			std::swap(arr[position], arr[position + 1]);
			std::swap(Piece[position], Piece[position + 1]);
			position++;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // if left key move left, checking if you are not get out or border
	{
		if (position != 0 && position != 4 && position != 8 && position != 12)
		{
			std::swap(arr[position], arr[position - 1]);
			std::swap(Piece[position], Piece[position - 1]);
			position--;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) // if up key move up, checking if you are not get out or border
	{
		if (position != 0 && position != 1 && position != 2 && position != 3)
		{
			std::swap(arr[position], arr[position - 4]);
			std::swap(Piece[position], Piece[position - 4]);
			position = position - 4;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) // if down key move down, checking if you are not get out or border
	{
		if (position != 12 && position != 13 && position != 14 && position != 15)
		{
			std::swap(arr[position], arr[position + 4]);
			std::swap(Piece[position], Piece[position + 4]);
			position = position + 4;
		}
	}
}

void cleanSpace() // hiding console window && setting rnd to generate rando number
{
	ShowWindow(::GetConsoleWindow(), SW_HIDE); 
	srand(time(NULL)); 
}

void drawPuzzle(sf::RenderWindow &win) { // drawing and displaying
	for (int i = 0; i < 16; i++) //drawning Sprites in window
	{
		win.draw(Piece[i]);
	}
	win.display(); // show window
}

int main()
{	
	cleanSpace(); 
	MessageBoxA(NULL, "Complete picture using arrows. Good Luck!", "Puzzle", MB_OK); // creating window with message
	sf::RenderWindow window;
	window.create(sf::VideoMode(400, 400, 32), "Puzzle", sf::Style::Default); // creating window for game
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	assignAndShuffle(arr);
	setPosition(Piece);

	while (window.isOpen()) //while window is open
	{
		sf::Event e; //create event
		while (window.pollEvent(e)) // choose action acording to event
		{
			if (e.type == sf::Event::Closed)
				window.close();
			if (e.type == sf::Event::KeyPressed)
				programControl(e);

			drawPuzzle(window); // drawing and displaying

			if (winCondition()) //checking if you are winning
			{
				MessageBoxA(NULL, "You won. Congratulations!", "Victory!", MB_OK);
				window.close();
			}
		}
	}

	return 0;
}
