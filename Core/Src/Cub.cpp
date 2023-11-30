#include "../Inc/Cub.h"


#include <iostream>
#include <vector>
#include <algorithm>


Cub::Cub(std::vector<std::vector<bool>> cubs, std::vector<int> coordinates_center, int color) : coordinates_center_(coordinates_center), color_(color)
{
	for (const auto& elem : cubs)
	{
		for (const auto& e : elem)
		{
			if (e == 1)
			{
			++size_;
			}
		}
	}

	int k = 0;

	for (std::size_t i = 0; i < size_; ++i)
	{
		coordinates_.push_back(std::vector<int>());
	}

	for (std::size_t j = 0; j < 3; ++j)
	{
		for (std::size_t i = 0; i < 3; ++i)
		{
			if (cubs[j][i])
			{
				coordinates_[k].push_back(i - 1 + coordinates_center_[0]);
				coordinates_[k].push_back(j - 1 + coordinates_center_[1]);
				++k;
			}
		}
	}

	for (std::size_t j = 0; j < 3; ++j)
	{
		for (std::size_t i = 0; i < 3; ++i)
		{
			if (cubs[j][i])
			{
				for (std::size_t m = 0; m < size_; ++m)
				{
					if (coordinates_[m][0] == i - 1 + coordinates_center_[0] && coordinates_[m][1] == j - 1 + coordinates_center_[1])
					{
						coordinates_left_.push_back(m);
						goto zam1;
					}
				}
			}
		}

	zam1:

		std::cout << "";
	}

	for (std::size_t j = 0; j < 3; ++j)
	{
		for (std::size_t i = 3; i > 0; --i)
		{
			if (cubs[j][i - 1])
			{
				for (std::size_t m = 0; m < size_; ++m)
				{
					if (coordinates_[m][0] == i - 2 + coordinates_center_[0] && coordinates_[m][1] == j - 1 + coordinates_center_[1])
					{
						coordinates_right_.push_back(m);
						goto zam2;
					}
				}
			}
		}

	zam2:

		std::cout << "";
	}

	for (std::size_t i = 0; i < 3; ++i)
	{
		for (std::size_t j = 3; j > 0; --j)
		{
			if (cubs[j - 1][i])
			{
				for (std::size_t m = 0; m < size_; ++m)
				{
					if (coordinates_[m][0] == i - 1 + coordinates_center_[0] && coordinates_[m][1] == j - 2 + coordinates_center_[1])
					{
						coordinates_bottom_.push_back(m);
						goto zam3;
					}
				}
			}
		}

	zam3:

		std::cout << "";
	}
}


Cub::Cub(const Cub& another_cub) : coordinates_(another_cub.coordinates_), 
coordinates_center_(another_cub.coordinates_center_), color_(another_cub.color_), 
size_(another_cub.size_),coordinates_bottom_(another_cub.coordinates_bottom_), 
coordinates_left_(another_cub.coordinates_left_), coordinates_right_(another_cub.coordinates_right_) {}


void Cub::change_coordinates_down(int k)
{
	coordinates_down_ = coordinates_;

	for (std::size_t i = 0; i < std::size(coordinates_); ++i)
	{
		for (std::size_t j = 0; j <= 1; ++j)
		{
			coordinates_down_[i][j] = j == 1 ? coordinates_[i][j] + k : coordinates_[i][j];
		}
	}
}


void Cub::find_coordinates_bottom()
{
	coordinates_bottom_.clear();
	
	std::vector<int> left;
	std::vector<int> center;
	std::vector<int> right;
	int max = -1;
	int max_add = -1;
	bool permit = false;

	for (std::size_t i = 0; i < std::size(coordinates_); ++i)
	{
		switch (coordinates_[i][0] - coordinates_center_[0])
		{
			case -1:
			{
				left.push_back(i);
				break;
			}
			case 0:
			{
				center.push_back(i);
				break;
			}
			case 1:
			{
				right.push_back(i);
				break;
			}
		}
	}

	for (const auto& elem : left)
	{
		permit = true;

		if (coordinates_[elem][1] > max)
		{
			max = coordinates_[elem][1];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_bottom_.push_back(max_add);
		max = -1;
		max_add = -1;
		permit = false;
	}
	

	for (const auto& elem : center)
	{
		permit = true;

		if (coordinates_[elem][1] > max)
		{
			max = coordinates_[elem][1];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_bottom_.push_back(max_add);
		max = -1;
		max_add = -1;
		permit = false;
	}

	for (const auto& elem : right)
	{
		permit = true;

		if (coordinates_[elem][1] > max)
		{
			max = coordinates_[elem][1];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_bottom_.push_back(max_add);
	}
}


void Cub::find_coordinates_left()
{
	coordinates_left_.clear();

	std::vector<int> up;
	std::vector<int> center;
	std::vector<int> down;
	int min = 100;
	int min_add = -1;
	bool permit = false;

	for (std::size_t i = 0; i < std::size(coordinates_); ++i)
	{
		switch (coordinates_[i][1] - coordinates_center_[1])
		{
		case -1:
		{
			down.push_back(i);
			break;
		}
		case 0:
		{
			center.push_back(i);
			break;
		}
		case 1:
		{
			up.push_back(i);
			break;
		}
		}
	}

	for (const auto& elem : down)
	{
		permit = true;

		if (coordinates_[elem][0] < min)
		{
			min = coordinates_[elem][0];
			min_add = elem;
		}
	}

	if (permit)
	{
		coordinates_left_.push_back(min_add);
		min = 100;
		min_add = -1;
		permit = false;
	}
	
	for (const auto& elem : center)
	{
		permit = true;

		if (coordinates_[elem][0] < min)
		{
			min = coordinates_[elem][0];
			min_add = elem;
		}
	}

	if (permit)
	{
		coordinates_left_.push_back(min_add);
		min = 100;
		min_add = -1;
		permit = false;
	}

	for (const auto& elem : up)
	{
		permit = true;

		if (coordinates_[elem][0] < min)
		{
			min = coordinates_[elem][0];
			min_add = elem;
		}
	}

	if (permit)
	{
		coordinates_left_.push_back(min_add);
	}
}


void Cub::find_coordinates_right()
{
	coordinates_right_.clear();

	std::vector<int> up;
	std::vector<int> center;
	std::vector<int> down;
	int max = -1;
	int max_add = -1;
	bool permit = false;

	for (std::size_t i = 0; i < std::size(coordinates_); ++i)
	{
		switch (coordinates_[i][1] - coordinates_center_[1])
		{
		case -1:
		{
			down.push_back(i);
			break;
		}
		case 0:
		{
			center.push_back(i);
			break;
		}
		case 1:
		{
			up.push_back(i);
			break;
		}
		}
	}

	for (const auto& elem : down)
	{
		permit = true;

		if (coordinates_[elem][0] > max)
		{
			max = coordinates_[elem][0];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_right_.push_back(max_add);
		max = -1;
		max_add = -1;
		permit = false;
	}
	
	for (const auto& elem : center)
	{
		permit = true;

		if (coordinates_[elem][0] > max)
		{
			max = coordinates_[elem][0];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_right_.push_back(max_add);
		max = -1;
		max_add = -1;
		permit = false;
	}

	for (const auto& elem : up)
	{
		permit = true;

		if (coordinates_[elem][0] > max)
		{
			max = coordinates_[elem][0];
			max_add = elem;
		}
	}

	if (permit)
	{
		coordinates_right_.push_back(max_add);
	}
}


void Cub::fall_cub()
{
	for (std::size_t i = 0; i < size_; ++i)
	{
		++coordinates_[i][1];
	}

	++coordinates_center_[1];
}


void Cub::move_cub_down()
{
	coordinates_ = coordinates_down_;
}


void Cub::move_cub_left()
{
	for (std::size_t i = 0; i < size_; ++i)
	{
		--coordinates_[i][0];
	}

	--coordinates_center_[0];
}


void Cub::move_cub_right()
{
	for (std::size_t i = 0; i < size_; ++i)
	{
		++coordinates_[i][0];
	}

	++coordinates_center_[0];
}


void Cub::rotate_cub_left()
{
	int cor_x;
	int cor_y;

	for (auto& elem : coordinates_)
	{
		cor_x = elem[0] - coordinates_center_[0];
		cor_y = elem[1] - coordinates_center_[1];

		if (cor_x == 0 && cor_y == 0) { continue; }
		else if (cor_x == -1 && cor_y == -1) { elem[1] += 2; }
		else if (cor_x == 0 && cor_y == -1) { elem[0] -= 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == -1) { elem[0] -= 2; }
		else if (cor_x == 1 && cor_y == 0) { elem[0] -= 1; elem[1] -= 1; }
		else if (cor_x == 1 && cor_y == 1) { elem[1] -= 2; }
		else if (cor_x == 0 && cor_y == 1) { elem[0] += 1; elem[1] -= 1; }
		else if (cor_x == -1 && cor_y == 1) { elem[0] += 2; }
		else if (cor_x == -1 && cor_y == 0) { elem[0] += 1; elem[1] += 1; }
	}
}


void Cub::rotate_cub_right()
{
	int cor_x;
	int cor_y;

	for (auto& elem : coordinates_)
	{
		cor_x = elem[0] - coordinates_center_[0];
		cor_y = elem[1] - coordinates_center_[1];

		if (cor_x == 0 && cor_y == 0) { continue; }
		else if (cor_x == -1 && cor_y == -1) { elem[0] += 2; }
		else if (cor_x == 0 && cor_y == -1) { elem[0] += 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == -1) { elem[1] += 2; }
		else if (cor_x == 1 && cor_y == 0) { elem[0] -= 1; elem[1] += 1; }
		else if (cor_x == 1 && cor_y == 1) { elem[0] -= 2; }
		else if (cor_x == 0 && cor_y == 1) { elem[0] -= 1; elem[1] -= 1; }
		else if (cor_x == -1 && cor_y == 1) { elem[1] -= 2; }
		else if (cor_x == -1 && cor_y == 0) { elem[0] += 1; elem[1] -= 1; }
	}
}