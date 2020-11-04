#include "GustavoMazeGenerator.hpp"

#include "Maze.hpp"
#include "MazeFactory.hpp"
#include "Direction.hpp"
#include <random>
#include <vector>
#include <ics46/factory/DynamicFactory.hpp>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, GustavoMazeGenerator, "Gustavo Velazquez's Generator (Required)");



GustavoMazeGenerator::GustavoMazeGenerator()
{
	maze_vector = {};

}


void GustavoMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();
	generate_maze_vector(maze.getWidth(), maze.getHeight());

	Recursive_Wall_Killer(maze, 0, 0);

}

void GustavoMazeGenerator::generate_maze_vector(unsigned int x, unsigned int y)
{
	std::vector<std::vector<int>> a(x, std::vector<int>(y, 0));
	maze_vector = a;
}

void GustavoMazeGenerator::Log_coordinates( unsigned int x, unsigned int y)
{
	maze_vector[x][y] = 1;

}



int GustavoMazeGenerator::Choose_Direction()
{

	std::random_device device;
	std::default_random_engine engine{device()};
	std::uniform_int_distribution<int> distribution{1,4};

	return distribution(engine);
}

bool GustavoMazeGenerator::check_move_validity_up(Maze& maze, int x, int y)
{
	if((y - 1) >= 0 && maze_vector[x][y-1] != 1)
	{
		if(maze.wallExists(x,y,Direction::up))
		{
			Log_coordinates(x,y);
			return true;
		}
	}

	return false;
}

bool GustavoMazeGenerator::check_move_validity_down(Maze& maze, int x, int y)
{
	if((y + 1) <= maze.getHeight() - 1 && maze_vector[x][y+1] != 1)
	{
		if(maze.wallExists(x,y,Direction::down))
		{
			Log_coordinates(x,y);
			return true;
		}
	}
	return false;
}

bool GustavoMazeGenerator::check_move_validity_left(Maze& maze, int x, int y)
{
	if( (x - 1) >= 0 && maze_vector[x-1][y] != 1)
	{
		if(maze.wallExists(x,y,Direction::left))
		{
			Log_coordinates(x,y);
			return true;
		}
	}
	return false;

}

bool GustavoMazeGenerator::check_move_validity_right(Maze& maze, int x, int y)
{

	if((x + 1) <= maze.getWidth() -1 && maze_vector[x+1][y] != 1)
	{
		if(maze.wallExists(x,y,Direction::right))
		{
			Log_coordinates(x,y);
			return true;
		}
			
	}
	return false;

}

bool GustavoMazeGenerator::all_Cells_Logged(unsigned int x_boundary, unsigned int y_boundary)
{
	for (int i = 0; i < x_boundary; i++)
	{
		for(int j = 0; j < y_boundary; j++)
		{
			if(maze_vector[i][j] == 0)
			{
				return false;
			}
		}
	}

	return true;
}

bool GustavoMazeGenerator::noMoves(Maze& maze, int x, int y)
{
	if(!check_move_validity_up(maze, x,y) &&
		!check_move_validity_down(maze, x,y) &&
		!check_move_validity_left(maze, x,y) &&
		!check_move_validity_right(maze, x,y))
	{
		Log_coordinates(x,y);
		return true;
	}

	return false;
}


void GustavoMazeGenerator::Recursive_Wall_Killer(Maze& maze, int x, int y)
{
	
	
	if (all_Cells_Logged(maze.getWidth(), maze.getHeight()))
	{
		return;
	}

	if(noMoves(maze, x, y))
	{
		return;
	}

	bool run = true;

	while (run)
	{
		int direction = Choose_Direction();
		if (direction == 1 && check_move_validity_up(maze, x, y))
		{
			maze.removeWall(x ,y ,Direction::up);
			Recursive_Wall_Killer(maze, x, y-1);
			run = false;
		}
		else if (direction == 2 && check_move_validity_down(maze, x, y))
		{
			maze.removeWall(x ,y ,Direction::down);
			Recursive_Wall_Killer(maze, x, y+1);
			run = false;
		}
		else if (direction == 3 && check_move_validity_left(maze, x, y))
		{
			maze.removeWall(x ,y ,Direction::left);
			Recursive_Wall_Killer(maze, x-1, y);
			run = false;
		}
		else if (direction == 4 && check_move_validity_right(maze, x, y))
		{
			maze.removeWall(x ,y ,Direction::right);
			Recursive_Wall_Killer(maze, x+1, y);
			run = false;
		}

	}

	if (check_move_validity_up(maze, x, y))
	{
		maze.removeWall(x ,y ,Direction::up);
		Recursive_Wall_Killer(maze, x, y-1);
		
	}
	if (check_move_validity_down(maze, x, y))
	{
		maze.removeWall(x ,y ,Direction::down);
		Recursive_Wall_Killer(maze, x, y+1);
		
	}
	if (check_move_validity_left(maze, x, y))
	{
		maze.removeWall(x ,y ,Direction::left);
		Recursive_Wall_Killer(maze, x-1, y);
		
	}
	if (check_move_validity_right(maze, x, y))
	{
		maze.removeWall(x ,y ,Direction::right);
		Recursive_Wall_Killer(maze, x+1, y);
		
	}

	
	return;

}


