#ifndef INCLUDE_BOARD_H_
#define INCLUDE_BOARD_H_


#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>


#include "Cub.h"


class Board {

	private:

		const int size_x_;
		const int size_y_;
		std::vector<std::vector<int>> board_;
		std::vector<std::vector<int>> board_copy_;
		std::unique_ptr<Cub> cub_;

	public:

		Board(const int size_x, const int size_y);

		void draw_board();
		bool add_cub(Cub& cub);
		bool fall_cub();
		bool destruction_rows();
		void change_coordinates_cub_down();
		bool permit_rotate_cub_left();
		bool permit_rotate_cub_right();
};


#endif 