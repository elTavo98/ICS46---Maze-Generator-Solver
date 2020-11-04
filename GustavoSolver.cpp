#include "MazeSolution.hpp"
#include "Maze.hpp"
#include "Direction.hpp"
#include "MazeSolutionFactory.hpp"
#include "GustavoSolver.hpp"
#include <vector>
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, GustavoSolver, "Gustavo Velazquez's Solver (Required)");

GustavoSolver::GustavoSolver()
{

}

void GustavoSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{

	generate_maze_vector(mazeSolution.getWidth(), mazeSolution.getHeight());

	Recursive_PathFinder(maze, mazeSolution);



}

void GustavoSolver::generate_maze_vector(unsigned int x, unsigned int y)
{
	std::vector<std::vector<int>> a(x, std::vector<int>(y, 0));
	maze_vector = a;
}

void GustavoSolver::Log_coordinates( unsigned int x, unsigned int y)
{
	maze_vector[x][y] = 1;

}

bool GustavoSolver::check_up(const Maze& maze, MazeSolution& mazeSolution)
{
	int x = mazeSolution.getCurrentCell().first;
	int y = mazeSolution.getCurrentCell().second;

	if((y-1) >= 0 && maze_vector[x][y-1] != 1)
	{
		if(!maze.wallExists(x,y,Direction::up))
		{
			Log_coordinates(x,y);
			return true;
		}
			
	}
	return false;
}

bool GustavoSolver::check_down(const Maze& maze, MazeSolution& mazeSolution)
{
	int x = mazeSolution.getCurrentCell().first;
	int y = mazeSolution.getCurrentCell().second;

	if( (y + 1) <= maze.getHeight() -1 && maze_vector[x][y+1] != 1)
	{
		if(!maze.wallExists(x,y,Direction::down))
		{
			Log_coordinates(x,y);
			return true;
		}
	}
	
	return false;
}

bool GustavoSolver::check_left(const Maze& maze, MazeSolution& mazeSolution)
{
	int x = mazeSolution.getCurrentCell().first;
	int y = mazeSolution.getCurrentCell().second;

	if( (x - 1) >= 0 && maze_vector[x-1][y] != 1)
	{
		if(!maze.wallExists(x,y,Direction::left))
		{
			Log_coordinates(x,y);
			return true;
		}
	}
	
	return false;

}

bool GustavoSolver::check_right(const Maze& maze, MazeSolution& mazeSolution)
{
	int x = mazeSolution.getCurrentCell().first;
	int y = mazeSolution.getCurrentCell().second;

	if( (x + 1) <= maze.getWidth() -1 && maze_vector[x+1][y] != 1)
	{
		if(!maze.wallExists(x,y,Direction::right))
		{
			Log_coordinates(x,y);
			return true;
		}
	}
		
	return false;

}


bool GustavoSolver::noMoves(const Maze& maze, MazeSolution& mazeSolution)
{
	int x = mazeSolution.getCurrentCell().first;
	int y = mazeSolution.getCurrentCell().second;

	if(!check_up(maze, mazeSolution) &&
		!check_down(maze, mazeSolution) &&
		!check_left(maze, mazeSolution) &&
		!check_right(maze, mazeSolution))
	{
		Log_coordinates(x,y);
		return true;
	}

	return false;
}




void GustavoSolver::Recursive_PathFinder(const Maze& maze, MazeSolution& mazeSolution)
{


	if(mazeSolution.isComplete())
	{
		return;
	}

	if(noMoves(maze, mazeSolution))
	{
		mazeSolution.backUp();
		Recursive_PathFinder(maze, mazeSolution);

		if(mazeSolution.isComplete())
		{
			return;
		}
	}

	if(check_right(maze, mazeSolution))
	{
		mazeSolution.extend(Direction::right);
		Recursive_PathFinder(maze, mazeSolution);
		
		if(mazeSolution.isComplete())
		{
			return;
		}
	}

	if(check_down(maze, mazeSolution))
	{
		mazeSolution.extend(Direction::down);
		Recursive_PathFinder(maze, mazeSolution);
		if(mazeSolution.isComplete())
		{
			return;
		}
	}

	if(check_left(maze, mazeSolution))
	{
		mazeSolution.extend(Direction::left);
		Recursive_PathFinder(maze, mazeSolution);

		if(mazeSolution.isComplete())
		{
			return;
		}
	}

	if(check_up(maze, mazeSolution))
	{
		mazeSolution.extend(Direction::up);
		Recursive_PathFinder(maze, mazeSolution);
		if(mazeSolution.isComplete())
		{
			return;
		}
	}


	return;

}


