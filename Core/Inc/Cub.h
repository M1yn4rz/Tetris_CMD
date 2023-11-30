#ifndef INCLUDE_CUB_H_
#define INCLUDE_CUB_H_


#include <iostream>
#include <vector>


class Cub {

	private:

		std::vector<std::vector<int>> coordinates_;
		std::vector<std::vector<int>> coordinates_down_;
		std::vector<int> coordinates_center_;
		std::vector<int> coordinates_bottom_;
		std::vector<int> coordinates_left_;
		std::vector<int> coordinates_right_;
		
		int color_ = 0;
		int size_ = 0;

	public:

		Cub(std::vector<std::vector<bool>> cubs, std::vector<int> coordinates_center, int color);
		Cub() {}
		Cub(const Cub& another_cub);
		Cub& operator = (const Cub& another_cub) {}

		int get_size() const { return size_; }
		int get_color() const { return color_; }
		std::vector<std::vector<int>> get_coordinates() const { return coordinates_; }
		std::vector<std::vector<int>> get_coordinates_down() const { return coordinates_down_; }
		std::vector<int> get_coordinates_center() const { return coordinates_center_; }
		std::vector<int> get_coordinates_left() const { return coordinates_left_; }
		std::vector<int> get_coordinates_right() const { return coordinates_right_; }
		std::vector<int> get_coordinates_bottom() const { return coordinates_bottom_; }
		
		void change_coordinates_down(int k);
		void find_coordinates_bottom();
		void find_coordinates_left();
		void find_coordinates_right();
		void fall_cub();
		void move_cub_down();
		void move_cub_left();
		void move_cub_right();
		void rotate_cub_left();
		void rotate_cub_right();
};


#endif 