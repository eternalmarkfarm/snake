#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <vector>

const int row = 16;
const int col = 30;

int one = 5;
int two = 11;
char move = 'r';
int r1 = 0;
int r2 = 0;
int count = 1;

std::vector<int> iPos; // Store x-coordinates of all body parts
std::vector<int> yPos; // Store y-coordinates of all body parts







void generateFood() {
	std::random_device rd; // Инициализация генератора случайных чисел
	std::mt19937 gen(rd());

	// Генерация случайных координат для еды
	int min = 2;
	int maxRow = 14;
	int maxCol = 28;
	std::uniform_int_distribution<> disRow(min, maxRow);
	std::uniform_int_distribution<> disCol(min, maxCol);

	r1 = disRow(gen);
	r2 = disCol(gen);
}

int one_u() {
	return --one;
}
int two_r() {

	return ++two;
}
int one_d() {

	return ++one;
}
int two_l() {

	return --two;
}



void changVecI(std::vector<int>& iPos) {
	
	if (move == 'u') {
		one = one_u();		
	}
	else if(move == 'd')
	{
		one = one_d();	
	}	
	iPos.push_back(one);
	if (iPos.size() > count + 1)
		iPos.erase(iPos.begin());	
}

void changVecY(std::vector<int>& yPos) {
	if (move == 'r') {
		two = two_r();		
	}
	else if (move == 'l')
	{
		two = two_l();		
	}		
	yPos.push_back(two);
	if (yPos.size() > count + 1)
		yPos.erase(yPos.begin());		
}

void draw(const int row, const int col) {
	
	for (int i = 0; i < row; ++i) {
		for (int y = 0; y < col; ++y)
		{
			bool isSnakeBody = false;
			for (int k = 0; k < iPos.size(); ++k) {
				if (i == iPos[k] && y == yPos[k])
				{
					isSnakeBody = true;
					break;
				}
			}

			if (isSnakeBody || i == 0 || i == 15 || y == 0 || y == 29)
			{
				std::cout << 0;
			}
			else if (i == r1 && y == r2)
			{
				std::cout << 0;				
			}
			else
				std::cout << " ";

		}
		std::cout << std::endl;
	}
}





void choise() {
	if (_kbhit())
	{
		char key = _getch();
		switch (key) {
		case 'w': // Движение вверх
			move = 'u';
			break;
		case 's': // Движение вниз
			move = 'd';
			break;
		case 'a': // Движение влево
			move = 'l';
			break;
		case 'd': // Движение вправо
			move = 'r';
			break;
		}
	}
}

void updateGame() {
	choise();
	changVecI(iPos);
	changVecY(yPos);
	if (two > 29 || two < 0 || one < 0 || one > 15) {
		std::cout << "Game Over!";
		exit(0);
	}
	if (one == r1 && two == r2) {
		++count;
		generateFood();
	}
}

int show() {
	generateFood();
	for (;;) {	
		updateGame();
		draw(row, col);
		Sleep(300);		
		system("cls");
	}
	
}
int main() {
	show();
	return 0;
}