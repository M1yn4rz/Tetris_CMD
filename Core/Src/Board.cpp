#include "../Inc/Board.h"



#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>



Board::Board(const int size_x, const int size_y) : size_x_(size_x), size_y_(size_y)
{
	for (std::size_t i = 0; i < size_y_; ++i)
	{
		board_.push_back(std::vector<int>());
	}

	for (std::size_t i = 0; i < size_y_; ++i)
	{
		for (std::size_t j = 0; j < size_x_; ++j)
		{
			if (i == 0 || i == size_y_ - 1 || j == 0 || j == size_x_ - 1)
			{
				board_[i].push_back(0);
			}
			else
			{
				board_[i].push_back(1);
			}
		}
	}

	board_copy_ = board_;
}


void Board::draw_board()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int color;

	board_copy_ = board_;

	if (cub_ != nullptr)
	{
		for (std::size_t k = 0; k < cub_->get_size(); ++k)
		{
			board_copy_[cub_->get_coordinates_down()[k][1]][cub_->get_coordinates_down()[k][0]] = 8;
			board_copy_[cub_->get_coordinates()[k][1]][cub_->get_coordinates()[k][0]] = cub_->get_color();
		}
	}

	for (std::size_t i = 0; i < size_y_; ++i)
	{
		for (std::size_t j = 0; j < size_x_; ++j)
		{
			color = board_copy_[i][j];
			
			switch (color)
			{
				case 0:
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
					std::cout << "  ";
					break;
				case 1:
					SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					std::cout << "  ";
					break;
				case 2:
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
					std::cout << "  ";
					break;
				case 3:
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN);
					std::cout << "  ";
					break;
				case 4:
					SetConsoleTextAttribute(hOut, BACKGROUND_RED);
					std::cout << "  ";
					break;
				case 5:
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_GREEN);
					std::cout << "  ";
					break;
				case 6:
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE | BACKGROUND_RED);
					std::cout << "  ";
					break;
				case 7:
					SetConsoleTextAttribute(hOut, BACKGROUND_GREEN | BACKGROUND_RED);
					std::cout << "  ";
					break;
				case 8:
					SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
					std::cout << "[]";
					break;
			}	
		}
		SetConsoleTextAttribute(hOut, 7);
		std::cout << "\n";
	}

	
}


bool Board::add_cub(Cub& cub)
{
	for (std::size_t i = 0; i < cub.get_size(); ++i)
	{
		if (board_[cub.get_coordinates()[i][1]][cub.get_coordinates()[i][0]] != 1)
		{
			return false;
		}
	}

	cub_ = std::make_unique<Cub>(cub);

	int k = 0;

	while (1)
	{
		for (const auto elem : cub_->get_coordinates_bottom())
		{
			if (board_[cub_->get_coordinates()[elem][1] + k][cub_->get_coordinates()[elem][0]] != 1)
			{
				goto exit;
			}
		}

		++k;
	}

	exit:
	
	cub_->change_coordinates_down(k-1);
	
	return true;
}


bool Board::fall_cub()
{
	for (std::size_t i = 0; i < std::size(cub_->get_coordinates_bottom()); ++i)
	{
		if (board_[cub_->get_coordinates()[cub_->get_coordinates_bottom()[i]][1] + 1][cub_->get_coordinates()[cub_->get_coordinates_bottom()[i]][0]] != 1)
		{
			for (std::size_t j = 0; j < cub_->get_size(); ++j)
			{
				board_[cub_->get_coordinates()[j][1]][cub_->get_coordinates()[j][0]] = cub_->get_color();
			}

			board_copy_ = board_;

			return false;
		}
	}

	int time = clock();
	bool permit = true;
	int symbol;

	cub_->fall_cub();
	system("cls");
	draw_board();

	while (clock() - time < 250)
	{
		if (_kbhit())
		{
			symbol = _getch();

			switch (symbol) {
				case 75:
				{
					for (std::size_t i = 0; i < std::size(cub_->get_coordinates_left()); ++i)
					{
						if (board_[cub_->get_coordinates()[cub_->get_coordinates_left()[i]][1]][cub_->get_coordinates()[cub_->get_coordinates_left()[i]][0] - 1] != 1)
						{
							permit = false;
							break;
						}
					}

					if (permit)
					{
						cub_->move_cub_left();
						change_coordinates_cub_down();
						system("cls");
						draw_board();
					}

					break;
				}
				case 77:
				{
					for (std::size_t i = 0; i < std::size(cub_->get_coordinates_right()); ++i)
					{
						if (board_[cub_->get_coordinates()[cub_->get_coordinates_right()[i]][1]][cub_->get_coordinates()[cub_->get_coordinates_right()[i]][0] + 1] != 1)
						{
							permit = false;
							break;
						}
					}

					if (permit)
					{
						cub_->move_cub_right();
						change_coordinates_cub_down();
						system("cls");
						draw_board();
					}

					break;
				}
				case 80:
				{
					for (std::size_t i = 0; i < std::size(cub_->get_coordinates_bottom()); ++i)
					{
						if (board_[cub_->get_coordinates()[cub_->get_coordinates_bottom()[i]][1] + 1][cub_->get_coordinates()[cub_->get_coordinates_bottom()[i]][0]] != 1)
						{
							permit = false;
							break;
						}
					}

					if (permit)
					{
						cub_->fall_cub();
						system("cls");
						draw_board();
					}

					break;
				}
				case 32:
				{
					cub_->move_cub_down();

					system("cls");
					draw_board();

					break;
				}
				case 97:
				{
					if (permit_rotate_cub_left())
					{
						cub_->rotate_cub_left();
						cub_->find_coordinates_bottom();
						cub_->find_coordinates_left();
						cub_->find_coordinates_right();
						change_coordinates_cub_down();
						system("cls");
						draw_board();
					}

					break;
				}
				case 100:
				{
					if (permit_rotate_cub_right())
					{
						cub_->rotate_cub_right();
						cub_->find_coordinates_bottom();
						cub_->find_coordinates_left();
						cub_->find_coordinates_right();
						change_coordinates_cub_down();
						system("cls");
						draw_board();
					}

					break;
				}
				default:
					break;
			}
			

			permit = true;
		}
	}

	return true;
}


bool Board::destruction_rows()
{
	std::vector<int> to_destruction;

	for (std::size_t i = 27; i > 0; --i)
	{
		for (std::size_t j = 1; j < 16; ++j)
		{
			if (board_[i][j] < 2)
			{
				goto exit;
			}
		}

		to_destruction.push_back(i);

	exit:
		std::cout << "";
	}

	if (std::size(to_destruction) == 0)
	{
		return false;
	}

	for (const auto& elem : to_destruction)
	{
		for (std::size_t i = 1; i < 16; ++i)
		{
			for (std::size_t j = elem; j > 1; --j)
			{
				board_[j][i] = board_[j - 1][i];
			}
		}
	}

	return true;
}


void Board::change_coordinates_cub_down()
{
	int k = 0;

	while (1)
	{
		for (const auto elem : cub_->get_coordinates_bottom())
		{
			if (board_[cub_->get_coordinates()[elem][1] + k][cub_->get_coordinates()[elem][0]] != 1)
			{
				goto exit;
			}
		}

		++k;
	}

	exit:

	cub_->change_coordinates_down(k - 1);
}


bool Board::permit_rotate_cub_left()
{
	int cor_x;
	int cor_y;

	for (auto elem : cub_->get_coordinates())
	{
		cor_x = elem[0] - cub_->get_coordinates_center()[0];
		cor_y = elem[1] - cub_->get_coordinates_center()[1];

		if (cor_x == 0 && cor_y == 0) { continue; }
		else if (cor_x == -1 && cor_y == -1) { elem[1] += 2; }
		else if (cor_x == 0 && cor_y == -1) { elem[0] -= 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == -1) { elem[0] -= 2; }
		else if (cor_x == 1 && cor_y == 0) { elem[0] -= 1; elem[1] -= 1; }
		else if (cor_x == 1 && cor_y == 1) { elem[1] -= 2; }
		else if (cor_x == 0 && cor_y == 1) { elem[0] += 1; elem[1] -= 1; }
		else if (cor_x == -1 && cor_y == 1) { elem[0] += 2; }
		else if (cor_x == -1 && cor_y == 0) { elem[0] += 1; elem[1] += 1; }

		if (!(board_[elem[1]][elem[0]] == 1 || board_[elem[1]][elem[0]] == cub_->get_color()))
		{
			return false;
		}
	}

	return true;
}


bool Board::permit_rotate_cub_right()
{
	int cor_x;
	int cor_y;

	for (auto elem : cub_->get_coordinates())
	{
		cor_x = elem[0] - cub_->get_coordinates_center()[0];
		cor_y = elem[1] - cub_->get_coordinates_center()[1];

		if (cor_x == 0 && cor_y == 0) { continue; }
		else if (cor_x == -1 && cor_y == -1) { elem[0] += 2; }
		else if (cor_x == 0 && cor_y == -1) { elem[0] += 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == -1) { elem[1] += 2; }
		else if (cor_x == 1 && cor_y == 0) { elem[0] -= 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == 1) { elem[0] -= 2; }
		else if (cor_x == 0 && cor_y == 1) { elem[0] -= 1; elem[1] -= 1; }
		else if (cor_x == -1 && cor_y == 1) { elem[1] -= 2; }
		else if (cor_x == -1 && cor_y == 0) { elem[0] += 1; elem[1] -= 1; }

		if (!(board_[elem[1]][elem[0]] == 1 || board_[elem[1]][elem[0]] == cub_->get_color()))
		{
			return false;
		}
	}

	return true;
}