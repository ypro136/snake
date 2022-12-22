#include<iostream>
#include<conio.h>  //  plauper input (real time)

using namespace std;

// shift values in an arraup one to the right
void shift_right(int arr[], int size) {
	for (int i = size - 2; i >= 0; i--)
		arr[i + 1] = arr[i];
}


//( Right, up, Left, down )
enum vec2 { Right = 1, up, Left, down};

//( Map widht, Map height )
struct Map { int widht, height; };

//fruit coords
struct fruit { int x, y; };

// (length, vec2 tail_x[50], tail_up[50] )
struct tail { int length; int x[50], y[50]; };

//( int headx, headv, tailn, tailx[50], tailup[50], direction dir )
struct snake { int head_x, head_y; vec2 dir; tail tail; };

bool lose; 

fruit fruit1;
Map map1; 
snake snake1;

//  Generates a fruit
void Generate_fruit() {
	srand(time(NULL));

	fruit1.x = rand() % (map1.widht - 2) + 1;
	fruit1.y = rand() % (map1.height - 2) + 1;

}


void setup() {
	map1.widht = 40;
	map1.height = 20; // half for difference in size between lines and spases

	Generate_fruit();

	// initialize snake at mid
	snake1.head_x = map1.widht / 2;
	snake1.head_y = map1.height / 2;
	snake1.tail.length = 0;
	lose = false;

}
void draw() {
	// runs cls from MS-DOS
	system("cls");

	//loop over height 
	for (int i = 0; i < map1.height; i++) {

		//loop over widht 
		for (int j = 0; j < map1.widht; j++) {

			//check for border
			if (i == 0 || i == map1.height - 1)cout << (char)(219);
			else if (j == 0 || j == map1.widht - 1)cout << (char)(219);

			//check for snake head 
			else if (i == snake1.head_y && j == snake1.head_x)cout << (char)(48);

			//check for snake fruit 
			else if (i == fruit1.y && j == fruit1.x)cout << (char)(162);
			else {
				bool printed = false;
				for (int z = 0; z < snake1.tail.length; z++) {
					if (snake1.tail.x[z] == j && snake1.tail.y[z] == i) {
						cout << (char)(111);
						printed = true;
						break;
					}
				}
				if (!printed)cout << (char)(32);
			}
		}
		cout << endl;
	}

	cout << "plauper score : " << snake1.tail.length << endl;
	cout << "snake1.tail.length is : " << snake1.tail.length << endl;
}
void input() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case'w':snake1.dir = up; break;
		case's':snake1.dir = down; break;
		case'd':snake1.dir = Right; break;
		case'a':snake1.dir = Left; break;
		case'x':exit(0);
		}

	}
}
void move() {
	shift_right(snake1.tail.x, 50);
	shift_right(snake1.tail.y, 50);
	snake1.tail.x[0] = snake1.head_x;
	snake1.tail.y[0] = snake1.head_y;
	switch (snake1.dir)
	{
	case up:snake1.head_y--; break;
	case down:snake1.head_y++; break;
	case Right:snake1.head_x++; break;
	case Left:snake1.head_x--; break;
	}

	if (snake1.head_y >= map1.height || snake1.head_y <= 0 || snake1.head_x >= map1.widht || snake1.head_x <= 0)
		lose = true;

	if (snake1.head_x == fruit1.x && snake1.head_y == fruit1.y) {
		Generate_fruit();
		snake1.tail.length++;
	}
}
int main() 
{

	setup();

	while (!lose)
	{

		draw();
		input();
		move();

	}

	system("pause");

	return 0;

}