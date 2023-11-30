#include "../Inc/Play.h"


#include <iostream>
#include <vector>


#include "../Inc/Cub.h"
#include "../Inc/Board.h"


Play::Play(int size_x, int size_y)
{
	Board board(size_x, size_y);
	srand(time(NULL));

	int shape;
	int color;
	int previous_color = 1;
	std::vector<std::vector<bool>> cubs;

	do {

		shape = (std::rand() % 10) + 0;

		do {color = (std::rand() % 6) + 2;} while (color == previous_color);

		switch (shape)
		{
			case 0:
				cubs = { {1,1,1},{1,1,1},{1,1,1} };
				break;
			case 1:
				cubs = { {1,1,1},{1,1,1},{0,0,0} };
				break;
			case 2:
				cubs = { {0,0,0},{1,1,1},{0,0,0} };
				break;
			case 3:
				cubs = { {0,1,1},{0,1,1},{0,0,0} };
				break;
			case 4:
				cubs = { {0,0,0},{0,1,1},{0,0,0} };
				break;
			case 5:
				cubs = { {0,1,0},{1,1,0},{0,0,0} };
				break;
			case 6:
				cubs = { {0,0,1},{0,0,1},{1,1,1} };
				break;
			case 7:
				cubs = { {0,1,0},{1,1,1},{0,1,0} };
				break;
			case 8:
				cubs = { {1,0,0},{1,1,0},{0,1,1} };
				break;
			case 9:
				cubs = { {0,1,0},{1,1,1},{0,0,0} };
				break;
		}

		Cub cub(cubs, { 8,2 }, color);

		if (!board.add_cub(cub))
		{
			break;
		}

		do {  } while (board.fall_cub());
		while(board.destruction_rows()) {}

		previous_color = color;

	} while (1);
}