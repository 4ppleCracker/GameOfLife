#include "gGraphics.h"
#include "PrivateFuncs.h"
#include <iostream>
#include <ctime>

using namespace std; using namespace sf;
int WindowHeight = 800;
int WindowLength = 800;
RenderWindow window(VideoMode(WindowHeight, WindowLength), "Game Of Life");
int GridHeight = 100;
int GridLength = 100;
vector<vector<int>> grid;
gGraphics graphics(window);
int framerate = 15;
int fps = 0;
int t = time(0);
int RenderHeight = WindowHeight / GridHeight;
int RenderLength = WindowLength / GridLength;

RectangleShape square;

int GridAround(int row, int column) {
	int tmp = 0;
	int oldr = row;
	int oldc = column;
	if (row != 0) row--;
	if (column != 0) column--;
	for (int i = 0; i < (oldr == 0 || oldr == GridHeight - 1 ? 2 : 3); i++) {
		for (int k = 0; k < (oldc == 0 || oldc == GridLength - 1 ? 2 : 3); k++) {
			if (!(row + i == (oldr) && column + k == (oldc))) {
				if (grid[row + i][column + k] == 1) {
					tmp++;
				}
			}
		}
	}
	return tmp;
}


int main() {
	grid = vector<vector<int>>(GridHeight, vector<int>(GridLength, 0));
	square = RectangleShape(Vector2f(RenderHeight - 2, RenderLength - 2));
	window.setFramerateLimit(framerate);
	srand(time(0) * 0.99382);
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid[0].size(); k++) {
			grid[i][k] = rand() % 10 == 1 ? 1 : 0;
		}
	}
	t = time(0);
	while (window.isOpen()) {
		graphics.Render();
	}
	return 0;
}

void gGraphics::WindowRender() {
	if (time(0) == t) fps++;
	else {
		cout << fps << endl;
		t = time(0);
		fps = 0;
	}
	for (int i = 0; i < grid.size(); i++) {
		for (int k = 0; k < grid[0].size(); k++) {
			int amount = GridAround(i, k);
			int toset = grid[i][k];
			if (amount < 2 || amount > 3 || (rand() % 12) == 1) toset = 0;
			if (amount == 3) toset = 1;
			grid[i][k] = toset;
			if (toset == 1) {
				
				square.setPosition(i * RenderHeight, k * RenderLength);
				square.setFillColor(Color::White);
				window.draw(square);
			}
		}
	}
}

void gGraphics::Poll(Event e) {
		if (e.key.code == Keyboard::Up) {
			framerate += 1;
			window.setFramerateLimit(framerate);
			cout << framerate << endl;
		}
		if (e.key.code == Keyboard::Down) {
			framerate -= 1;
			window.setFramerateLimit(framerate);
			cout << framerate << endl;
		}
		if (e.type == Event::Closed) {
			window.close();
		}
}


/*

The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells,
each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated".
Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or diagonally adjacent.
At each step in time, the following transitions occur:

Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

The initial pattern constitutes the seed of the system. 
The first generation is created by applying the above rules simultaneously to every cell in the seed—births and deaths occur simultaneously,
and the discrete moment at which this happens is sometimes called a tick (in other words, each generation is a pure function of the preceding one).
The rules continue to be applied repeatedly to create further generations.

*/