#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

const int EDGE_TILES = 12;

const int LEVEL_WIDTH = 1080;
const int LEVEL_HEIGHT = 720;

//can chinh so do cua Tile
const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const int TOTAL_TILES = 144;
const int TOTAL_TILE_SPRITES = 9;

//can chinh tileType
const int TILE_GRASS = 0;
const int TILE_FLOWER = 1;
const int TILE_DEATH = 2;
const int TILE_PLANK = 3;
const int TILE_BRICK = 4;
const int TILE_FLOOR = 5;
const int TILE_SAND = 6;
const int TILE_GOAL = 7;
const int TILE_VOID = 8;

enum status
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    NONE = 4,
};

enum GoalStatus
{
    GOAL,
    GOAL_NOT
};

enum Occupied
{
    yes,
    no
};

#endif // CONSTANT_H_INCLUDED
