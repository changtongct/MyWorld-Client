#include "GAME_Maze.h"

GAME_Maze::GAME_Maze(int h, int w, Coordinate c) {
	setHeight(h);
	setWidth(w);
	setCoor(c);
	buildMaze1(getHeight(), getWidth());
	displayMaze1(getHeight(), getWidth());
	myCamera.setCamera(-499,-499,0.5,0,0,0.5,0,0,1);
	myCamera.setSpeed(0.1);
}

void GAME_Maze::displayMaze1(int width, int height) {
	vector<Coordinate>::iterator c_iter;
	int i=50;
	/*for (c_iter=Walls.begin();c_iter!=Walls.end();++c_iter) {
		AllEntity.addEntity(i++, 1, ColorRGBA(1, 1, 1, 1),
			Coordinate(getOriginCoor().x+c_iter->x, getOriginCoor().y+c_iter->y, getOriginCoor().z+c_iter->z));
	}*/
	for (int m=0;m<height;++m)
		for (int n=0;n<width;++n) {
			if (maze1[m][n] == true)
				AllEntity.addEntity(i++, 1, Coordinate(1, 1, 1),
				Coordinate(getOriginCoor().x + n, getOriginCoor().y + m, getOriginCoor().z));
		}
}

void GAME_Maze::buildMaze1(int width, int height) {
	maze1 = new bool*[height];
	for (int i=0;i<height;++i) {
		maze1[i] = new bool[width];
		memset(maze1[i], false, sizeof(maze1[i]));
	}
	for (int m=0;m<width;++m) {
		maze1[0][m] = true;
		maze1[height-1][m] = true;
	}
	for (int n=1;n<height-1;++n) {
		maze1[n][0] = true;
		maze1[n][width-1] = true;
	}
	srand((unsigned)time(0));
	genMaze1(1, 1, 98, 98);
}

void GAME_Maze::openAdoor(int x1, int y1, int x2, int y2) {
	int pos;
	if (x1 == x2) {
		if (y2 == y1) {
			pos = y1;
		}
		else {
			pos = y1 + rand()%(y2 - y1 + 1);
			while (pos % 2 == 0)
				pos = y1 + rand()%(y2 - y1 + 1);
		}
		maze1[pos][x1] = false;
	}
	else if (y1 == y2) {
		if (x2 == x1) {
			pos = x1;
		}
		else {
			pos = x1 + rand()%(x2 - x1 + 1);
			while (pos % 2 == 0)
				pos = x1 + rand()%(x2 - x1 + 1);
		}
		maze1[y1][pos] = false;
	}
	else {
		printf("wrong");
	}
}

void GAME_Maze:: genMaze1(int x, int y, int height, int width) {
	int xPos, yPos;

	if (height <= 2 || width <= 2)
		return;

    //竖着画墙 
	xPos = x + rand()%(width-2) + 1;	//r = rand()%(n - m + 1) + m;
	while (xPos % 2 == 1)
		xPos = x + rand()%(width-2) + 1;
	for (int i = y; i < y + height; ++i) {
		maze1[i][xPos] = true;
	}

    //横着画墙 
    yPos = y + rand()%(height-2) + 1;
    while (yPos % 2 == 1)
    	yPos = y + rand()%(height-2) + 1;
    for (int i = x; i < x + width; ++i) {
        maze1[yPos][i] = true;
    }

    //随机开三扇门，上方墙壁为1，顺时针旋转
    int isClosed = rand()%4 + 1;
    switch (isClosed) 
    {
		case 1:
			openAdoor(xPos, y, xPos, yPos - 1);					//1
			openAdoor(xPos + 1, yPos, x + width - 1, yPos);		//2
			openAdoor(xPos, yPos + 1, xPos, y + height - 1);	//3
			break;
		case 2:
			openAdoor(xPos, y, xPos, yPos - 1);					//1
			openAdoor(xPos + 1, yPos, x + width - 1, yPos);		//2
			openAdoor(x, yPos, xPos - 1, yPos);					//4
			break;
		case 3:
			openAdoor(xPos, y, xPos, yPos - 1);					//1
			openAdoor(xPos, yPos + 1, xPos, y + height - 1);	//3
			openAdoor(x, yPos, xPos - 1, yPos);					//4
			break;
		case 4:
			openAdoor(xPos + 1, yPos, x + width - 1, yPos);		//2
			openAdoor(xPos, yPos + 1, xPos, y + height - 1);	//3
			openAdoor(x, yPos, xPos - 1, yPos);					//4
			break;
		default:
			break;
    }

    // 左上角
    genMaze1(x, y, yPos - y, xPos - x);
    // 右上角
	genMaze1(xPos + 1, y, yPos - y, x + width - xPos - 1);
    // 左下角
    genMaze1(x, yPos + 1, y + height - yPos - 1, xPos - x);
    // 右下角
    genMaze1(xPos + 1, yPos + 1, y + height - yPos - 1, x + width - xPos - 1);
}
