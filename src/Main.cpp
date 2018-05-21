#include"Window.h"
#include"Organism.h"

Vec2 Position = Vec2(0,100);

Organism *Creatures[NUMBER_OF_CREATURES];

bool DANCE  = false,
     ROTATE = false;

float Speed = 10.0f;

Cell *Selected;

void MClick(int x, int y)
{
     for_loop(Index, NUMBER_OF_CREATURES)
     { 
        for_loop(Index2, Creatures[Index]->NumberOfCells)
        {
             if(SCREEN->Mouse.Position.X < (Creatures[Index]->Cells[Index2].Real.x + 10) && 
                SCREEN->Mouse.Position.X > (Creatures[Index]->Cells[Index2].Real.x - 10) &&
                SCREEN->Mouse.Position.Y < (Creatures[Index]->Cells[Index2].Real.y + 10) && 
                SCREEN->Mouse.Position.Y > (Creatures[Index]->Cells[Index2].Real.y - 10))
             {
                 Selected = & Creatures[Index]->Cells[Index2];
             }
         }
     }
}
void MouseUp(int x, int y)
{
    Selected = nullptr;
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle)
{
    if(Selected != nullptr)
    {
        Selected->Offset.x += relX;
        Selected->Offset.y += relY;
    }
}
void KeyPress(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier , Uint8 rep)
{

    if(Keycode == 82) // UP
    {
        Position.y -= Speed;
    }
    if(Keycode == 81) // DOWN
    {
        Position.y += Speed;
    }
    if(Keycode == 80) // LEFT
    {
        Position.x -= Speed;
    }
    if(Keycode == 79) // RIGHT
    {
        Position.x += Speed;
    }
}

//__________________________________===+~~ GUI STUFF ~~+===_______________________________________

void ButtonPress(int x, int y)
{
     DANCE =(!DANCE);
}
void ButtonTwo(int x, int y)
{
    ROTATE = (!ROTATE);
}
//________________________________________________________________________________________________

auto LAMBDA  = [](int value) {std::cout << "Value:" << value << std::endl;};


void __cdecl main(char *Params)
{
    
    for_loop(Index, NUMBER_OF_CREATURES)
    { 
        Creatures[Index] = new Organism(10, Position);
    }
    for_loop(Index, NUMBER_OF_CREATURES)
    { 
        Position.x += 140;
        if(Position.x > SCREENWIDTH - 40)
        {
            Position.x  = 140;
            Position.y += 140;
        }
        Creatures[Index]->SetPosition(Position.x,Position.y);
    }


    Window MainWin(0,0,SCREENWIDTH,SCREENHEIGHT, "A.L.I.E.Ns");
        MainWin.CallBacks.SetOnLButtonDown(MClick);
        MainWin.CallBacks.SetOnKeyDown(KeyPress);
        MainWin.CallBacks.SetOnMouseMove(MouseMove);
        MainWin.CallBacks.SetOnLButtonUp(MouseUp);
    GUI *Interface = new GUI(&MainWin);

    Interface->Begin();
        Interface->Button();
        Interface->Position(10,10);
        Interface->Size(80,40);
        Interface->Text("Dance");
        Interface->LeftMouseDown(ButtonPress);
        Interface->Push();
        Interface->Button();
        Interface->Position(90,10);
        Interface->Size(80,40);
        Interface->Text("Rotate");
        Interface->LeftMouseDown(ButtonTwo);
        Interface->Push();
    Interface->End();
    MainWin.SetGUI(Interface);


    while(MainWin.LOOP_GAME())
    {
    _CLS;
        for_loop(Index, NUMBER_OF_CREATURES)
        { 
            if(ROTATE == true)
            {
                Creatures[Index]->Rotate(10);
            }
            if(DANCE == true)
            {
                for_loop(Index, NUMBER_OF_CREATURES)
                { 
                   for_loop(Index2, Creatures[Index]->NumberOfCells)
                   {
                       Creatures[Index]->Cells[Index2].Force.x += RANDOM(1) - .5;
                       Creatures[Index]->Cells[Index2].Force.y += RANDOM(1) - .5;
                   }
                }
            }
            Creatures[Index]->Update();
        }
    _SYNC;
    }
 }