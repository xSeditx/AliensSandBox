#pragma once
#include"Vertex.h"
#include"window.h"
#include<vector>

#define NUMBER_OF_CREATURES     20

class Cell;
class Spring;



class Organism
{
public:
    Organism(){}
        Organism( int cellcount, Vec2 pos);
        ~Organism(){}
      
       Vec2 Position;

       Vec2 Force,
            Acceleration,
            Velocity;

       float Angle, 
             Speed;

       float Radius;
       float Mass;

       int ID;

       int NumberOfCells;
       int NumberOfEdges;

       std::vector<Cell> Cells;
       std::vector<Spring> Springs;

       void Render();
       void Update();
       void Rotate(float Angle);

       void SetPosition(float x, float y);
       void ClampPosition();

       void CheckCollision();

static int NumberOfCreatures;
static  std::vector<Organism *> CreatureList;
};

class Cell
{
public:
        Cell(){}
        Cell(Organism *parent, Vec2 pos);

        ~Cell(){}
      
       Vec2 Offset,
            Starting,
            Real;

       Vec2 Force,
            Velocity;

       float Speed, 
             Angle;

       float Mass;  

       DWORD Color;

       Organism *Parent;

       void Render();
       void Update();
       void ApplyForce();
};

class Spring
{
public:
    Spring(){}
   ~Spring(){}
    Spring(Cell *parent, Cell *child);
           Cell *Parent,
                *Child;
     Vec2 Rest, Updated;
     float Length;
     float DamperCo, Tension;
   void Render();
   void ApplyForce();

   void Update();
};
