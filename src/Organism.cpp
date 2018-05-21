#include "Organism.h"
#include "Window.h"

int Organism::NumberOfCreatures = 0;
std::vector<Organism*> Organism::CreatureList;

//  Organism  UPDATE
//         Cell   UPDATE
//                APPLYFORCE
//        Edges   UPDATE
//                APPLYFORCE
//           RENDER     
//                RENDER
//                RENDER




// Algorithm 1. Mass-spring integration on the CPU
//================================================
// For each spring
//     Compute internal forces
// End for
//                                    
// For each mass point
//     Add external forces
//     Compute velocity
//     Do collision detection and response (modify velocity)
//     Compute
// End for
   
// Algorithm 2. Mass-spring integration on the GPU
//================================================
// Rendering 1:
// For each mass point
//     Compute internal forces
//     Add external forces
//     Compute velocity
//     Do collision detection and response (modify velocity)
// End for
// Rendering 2:
// For each mass point
//     Compute new position
// End for
//===============================================================================================================================================
//                                                    EDGE                                                                                     
//===============================================================================================================================================
Spring::Spring(Cell *parent, Cell *child)
    : Parent(parent), 
      Child(child),
      DamperCo(1.f),
      Tension(.1)
{
    Rest = Vec2::Get_Displacement(Parent->Offset, Child->Offset);
    Length = sqrt(Squared(Child->Offset.y - Parent->Offset.y) + Squared(Child->Offset.x - Parent->Offset.x));
}
void Spring::Render()
{
    SCREEN->LINE(Parent->Real.x, Parent->Real.y,  
                  Child->Real.x,  Child->Real.y);
}
void Spring::Update()
{
    ApplyForce();
}
void Spring::ApplyForce()
{

    Vec2 Displacement;
    Displacement.x = (Child->Offset.x - Parent->Offset.x) - Rest.x;
    Displacement.y = (Child->Offset.y - Parent->Offset.y) - Rest.y;
   // float CurrentLength = sqrt(Squared(Child->Offset.y - Parent->Offset.y) + Squared(Child->Offset.x - Parent->Offset.x));
   // float  Displacement = CurrentLength - Length;

    Child->Force.x  +=  (Displacement.x * -Tension);
    Child->Force.y  +=  (Displacement.y * -Tension);

    Parent->Force.x -=  (Displacement.x * -Tension);
    Parent->Force.y -=  (Displacement.y * -Tension);

}

//===============================================================================================================================================
//                                                  CELL                                                                                       
//===============================================================================================================================================

Cell::Cell(Organism *parent, Vec2 pos)
    : Parent(parent),
      Offset(pos), 
      Starting(pos),
      Mass(10),
      Speed(0), 
      Angle(0),Color(RGB(rand()%255, rand()%255, rand()%255))
{
    Parent->Mass += Mass;
    Real =  Offset + Parent->Position;
}
void Cell::Render()
{ 
    SCREEN->SET_DRAW_COLOR(Color);
    SCREEN->CIRCLE(Real.x, Real.y, 5);
}
void Cell::Update()
{
    Real.x = Offset.x + Parent->Position.x;
    Real.y = Offset.y + Parent->Position.y;
    ApplyForce();
}
void Cell::ApplyForce()
{

    Velocity *= .5;
    Vec2 Acceleration = Force / Mass;
         Velocity  += Acceleration;
         Offset    += Velocity;
         Force = 0;
}

//===============================================================================================================================================
//                                                  ORGANISM                                                                                       
//===============================================================================================================================================

Organism::Organism(int cellcount, Vec2 pos)
    : Position(pos),
      NumberOfCells(cellcount),
      Speed(0), Mass(0), 
      Velocity(Vec2(0,0)), 
      Acceleration(Vec2(0,0)),     
      NumberOfEdges(0),
      Angle(0),
      ID(NumberOfCreatures++),
      Radius(50)
{
    Vec2  Offset;

    float Theta = 360.0f / NumberOfCells;

    for_loop(Index, NumberOfCells)
    {
         Offset.x = Radius * _COS(Angle);
         Offset.y = Radius * _SIN(Angle);
         Cells.push_back(Cell(this, Vec2(Offset.x, 
                                         Offset.y)));
         Angle += Theta;
    }

    for_loop(Parent, NumberOfCells)
    {
        for_loop(Child, NumberOfCells)
        {
            if(Parent != Child)
            {
                Springs.push_back(Spring(&Cells[Parent], &Cells[Child]));
                NumberOfEdges++;
            }
        }
    }
    CreatureList.push_back(this);
}
void Organism::Render()
{
    for_loop(Index,NumberOfCells)
    {
        Cells[Index].Render();
    }
    for_loop(Index, NumberOfEdges)
    {
        Springs[Index].Render();
    }
    SCREEN->CIRCLE(Position.x, Position.y, 30);
    SCREEN->LINE(Position.x, Position.y, Position.x + 100 * _COS(Angle),Position.y + 100 *  _SIN(Angle));
}
void Organism::Update()
{
    CheckCollision();
        Vec2 Avg;

    for_loop(Index, NumberOfEdges)
    {
       Springs[Index].Update();
    } 

    for_loop(Index,NumberOfCells)
    {
        Cells[Index].Update();
    }
     for_loop(Index,NumberOfCells)
     {
       Avg.x +=  Cells[Index].Real.x;
       Avg.y +=  Cells[Index].Real.y;
     }
     Avg /= NumberOfCells;
     Position = Avg;

    SCREEN->CIRCLE(Position.x, Position.y, 10);

    ClampPosition();
    Render();
}
void Organism::Rotate(float angle)
{
    float s = sin(RADIANS(angle)),
          c = cos(RADIANS(angle));

    Angle += angle;
    Vec2 New;
 
    for_loop(Index, NumberOfEdges)
    {
        New.x = Springs[Index].Rest.x * c - Springs[Index].Rest.y * s;
        New.y = Springs[Index].Rest.x * s + Springs[Index].Rest.y * c;

        Springs[Index].Rest.x = New.x;
        Springs[Index].Rest.y = New.y;

    }
    for_loop(Index, NumberOfCells)
    {
        New.x = Cells[Index].Force.x * c - Cells[Index].Force.y * s;
        New.y = Cells[Index].Force.x * s + Cells[Index].Force.y * c;

        Cells[Index].Force.x = New.x;
        Cells[Index].Force.y = New.y;

        New.x = Cells[Index].Velocity.x * c - Cells[Index].Velocity.y * s;
        New.y = Cells[Index].Velocity.x * s + Cells[Index].Velocity.y * c;

        Cells[Index].Velocity.x = New.x;
        Cells[Index].Velocity.y = New.y;

      //  New.x = Cells[Index].Offset.x * c - Cells[Index].Offset.y * s;
      //  New.y = Cells[Index].Offset.x * s + Cells[Index].Offset.y * c;
      //
      //  Cells[Index].Offset.x = New.x;
      //  Cells[Index].Offset.y = New.y;
    }

    SCREEN->CIRCLE(Position.x, Position.y, 20);
}
void Organism::SetPosition(float x, float y)
{
    Position = Vec2(x,y);
}
void Organism::ClampPosition()
{
    if(Position.x > SCREENWIDTH) Position.x -= SCREENWIDTH;
    if(Position.x < 0) Position.x += SCREENWIDTH;
    if(Position.y > SCREENHEIGHT) Position.y -= SCREENHEIGHT;
    if(Position.y < 0) Position.y += SCREENHEIGHT;
}
void Organism::CheckCollision()
{

float X = Position.x,
      Y = Position.y;

float K = 2;

   // for(Organism *Creature : Organism::CreatureList){
    for_loop(Index, NumberOfCreatures)
    {
        if(CreatureList[Index] != this)
        {
            float SX = CreatureList[Index]->Position.x, 
                  SY = CreatureList[Index]->Position.y;
           
            if((Squared(SY - Y) +  Squared(SX - X)) < Squared(CreatureList[Index]->Radius + this->Radius))
            {

	            for(Cell &Parent: this->Cells)
                {
                    float TestX = Parent.Real.x;
                    float TestY = Parent.Real.y;

                    for(Cell &Other: CreatureList[Index]->Cells)
                    {
                        float TX2 = Other.Real.x;
                        float TY2 = Other.Real.y;

                        if((Squared((TestY - TY2)) +  Squared((TestX - TX2))) <= Squared((20)))
                        {
                            Vec2 AxisDisplacement; 
                            AxisDisplacement.x = (TestX - TX2) * 5;
                            AxisDisplacement.y = (TestY - TY2) * 5; 

                            Parent.Force.x -=  -K * AxisDisplacement.x;
                            Parent.Force.y -=  -K * AxisDisplacement.y;

                            Other.Force.x +=  -K * AxisDisplacement.x;
                            Other.Force.y +=  -K * AxisDisplacement.y;
                            SCREEN->FILLED_CIRCLE(TX2,TY2,10);
                            SCREEN->FILLED_CIRCLE(TestX,TestY,10);
                        }
                    }
                }
            }
        }
    }
}    