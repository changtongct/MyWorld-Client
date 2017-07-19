#ifndef __GAME_MAZE_H__
#define __GAME_MAZE_H__

#include "GAME_BaseGameEntity.h"
#include "CoorManagement.h"
#include "Camera.h"
#include <vector>
#include <time.h> 
#include <stack>

extern CoorManagement AllEntity;
extern Camera myCamera;

class GAME_Maze : public GAME_BaseGameEntity {
public:
	GAME_Maze(int height, int width, Coordinate c);
	~GAME_Maze(){};
	

	void displayMaze1(int width, int height);
	void buildMaze1(int width = 100, int height = 100);
	void openAdoor(int x1, int y1, int x2, int y2);
	void genMaze1(int x, int y, int height, int width);

private:
	vector<Coordinate> Walls;
	bool **maze1;
};

#endif