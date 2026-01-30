#include <iostream>
#include <raylib.h>
#include<deque>
#include<raymath.h> 
using namespace std;
Color green = {173,204,96,255};
Color Darkgreen = {43,51,24,255};

int cellsize = 30 ; 
int cellCount= 25 ;
int offset = 75 ; 
double LastUpdateTime = 0 ; 

bool EventTriggered(double interval)
{
    double CurrentTime = GetTime();
    if(CurrentTime - LastUpdateTime >= interval)
    {
      LastUpdateTime = CurrentTime;
      return true;
    }
    return false ; 
}
bool ElementInDeque(Vector2 Element , deque<Vector2> deque)
{
  for(unsigned int i = 0 ; i<deque.size() ; i++)
  {
    if(Vector2Equals(deque[i] , Element))
    {
      return true;
    }
  }
  return false;
}
//Creating snake 
class Snake
{
  public:
  deque<Vector2> body= { Vector2{7,9} , Vector2{6,9},Vector2{5,9}};
  Vector2 Direction = {1,0};
  bool addSegment = false;



  void Draw()
  {
    for(unsigned int i = 0 ; i<body.size() ; i++)
    {
      float x = body[i].x;
      float y = body[i].y;
      Rectangle segement = Rectangle{offset+ x*cellsize , offset+ y*cellsize , (float)cellsize , (float)cellsize };

      DrawRectangleRounded(segement , 0.5 , 6 , Darkgreen);
    }

  } 

  void update()
  {
     body.push_front(Vector2Add(body[0],Direction));
    if(addSegment == true)
    {
      addSegment =false;
    }
    else
    {
      body.pop_back();
   
    }
   
  } 

  void Reset()
  {
    body = {Vector2{6,9} , Vector2{5,9} , Vector2{4,9}};
    Direction = {1,0};
  }
} ;
//Creating food for snake 
class SnakeFood
{
  public:
  Vector2 position ;
  Texture2D texture;
 
  SnakeFood(deque<Vector2> snakeBdoy)
  {
    Image FoodImage  = LoadImage("Provide Absolute path for image ");
    texture = LoadTextureFromImage(FoodImage);
    UnloadImage(FoodImage);
    position = GenerateRandomPos(snakeBdoy);
  }

  ~SnakeFood()
  {
    UnloadTexture(texture);
  }
  void draw()
  {
    DrawTexture(texture , offset+ position.x * cellsize , offset+ position.y * cellsize , WHITE );
  }

  Vector2 GenerateRandomCell()
  {
    float x = GetRandomValue(0,cellCount -1);
    float y = GetRandomValue(0,cellCount -1);
    return Vector2{x,y};
  }
  Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
  {
    Vector2 position = GenerateRandomCell();
    while(ElementInDeque(position , snakeBody))
    {
      position = GenerateRandomCell();
    }
    return position;
  }
};

//Game for easy understanding of the code 

class Game 
{
public:
  Snake snake = Snake();
  SnakeFood food = SnakeFood(snake.body);
  bool running = true ; 
  int score = 0 ; 

  Sound EatSound;
  Sound WallSound;


  Game()
  {
    InitAudioDevice();
    EatSound = LoadSound("Provide Absolute path for image");
    WallSound = LoadSound("Provide Absolute path for image");
     
  }

  ~Game()
  {
    UnloadSound(EatSound);
    UnloadSound(WallSound);
    CloseAudioDevice();
  }
  void Draw()
  {
    food.draw();
    snake.Draw();

  }
  void update()
  {
    if(running)
    {
      snake.update();
      CheckCollisonWithFood();
      CheckCollisonsWithEdges();
      CheckCollisonWithTail();
 
    }
    }
  void CheckCollisonWithFood()
  {
    if(Vector2Equals(snake.body[0] , food.position))
    {
      food.position = food.GenerateRandomPos(snake.body);
      snake.addSegment = true;
      score++;
      
      PlaySound(EatSound);
    }
  }


  void CheckCollisonsWithEdges()
  {
    if(snake.body[0].x == cellCount || snake.body[0].x == -1)
    {
      GameOver();
    }
    if(snake.body[0].y == cellCount || snake.body[0].y == -1)
    {
      GameOver();
    }


  }

  void GameOver()
  {
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0 ;
    PlaySound(WallSound);

  }

  void CheckCollisonWithTail()
  {
    deque<Vector2> headlessBody = snake.body;
    headlessBody.pop_front();
    if(ElementInDeque(snake.body[0] , headlessBody))
    {
      GameOver();
    }
  }
};



int main () 
{

  cout<< " Stating the game ....!! "<<endl;
  InitWindow(2*offset + cellsize*cellCount , 2*offset + cellsize*cellCount, "SNAKE GAME ");
  SetTargetFPS(60);

  Game game = Game();


  while(WindowShouldClose()== false)
  {
    BeginDrawing();
    if(EventTriggered(0.2))
    {
      game.update(); 
    }
    //Update Directions
    if(IsKeyPressed(KEY_UP) && game.snake.Direction.y !=1)
    {
        game.snake.Direction = {0,-1};
        game.running = true;
    }
    if(IsKeyPressed(KEY_DOWN) &&  game.snake.Direction.y !=-1)
    {
      game.snake.Direction = {0 , 1};
      game.running = true;
    }
    if(IsKeyPressed(KEY_LEFT) &&  game.snake.Direction.x !=1)
    {
        game.snake.Direction = {-1 , 0};
        game.running = true;
    }
    if(IsKeyPressed(KEY_RIGHT) &&  game.snake.Direction.x !=-1)
    {
        game.snake.Direction={1 , 0};
        game.running = true;
    }



    //Draw - background with green color
    ClearBackground(green);
    DrawRectangleLinesEx(Rectangle{(float)offset -5 , (float)offset -5 , (float)cellsize*cellCount + 10 ,  (float)cellsize*cellCount + 10 } , 5, Darkgreen );
    
    DrawText("SNAKE GAME" , offset -5 , 20, 40 , Darkgreen);
    DrawText(TextFormat("%i" ,game.score), offset -5 , offset + cellsize*cellCount + 10  , 40 , Darkgreen);

    game.Draw();

    EndDrawing();

  }
  CloseWindow();
}