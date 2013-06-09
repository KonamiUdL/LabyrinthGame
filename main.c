#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "/home/zem/local/include/CUnit/CUnit.h";
//#include "/home/zem/local/include/CUnit/Basic.h";

int PlotSquare(int x, int y, double size);
int GenerateParameters(int maze_columns);
void GeneratePath();
void GenerateMaze();
void DrawMaze();
void animate();
void Move();
void FillWithWall();

typedef int boolean;
#define true 1
#define false 0

struct point {
    int h;
    int v;
};

const int EMPTY = 0;
const int WALL = 1;
const int PATH = 2;
const int EDGE = 3;
const int ANIMATION = 4;

const int TIMERMSECS = 100;

const int wind_size = 600;
const int maze_columns = 50;

int move_v =1;
int move_h = 1;

int wind_size_x = 0;
int wind_size_y = 0;

int hor_point_number = 0;
int ver_point_number = 0;

int size = 0;

int *ver_points;
int *hor_points;

int paint_points[1000][1000];
 
/*******************************************************/
void display()
{

  glClearColor(1.0,1.0,1.0,0.0);
  glClear(GL_COLOR_BUFFER_BIT);

  animate(); //Funcion que se llamara varias veces para producir la animacion
  
  glutSwapBuffers();
}


/*******************************************************/
int main(int argc, char **argv)
{
  
    wind_size_x = wind_size; 
    wind_size_y = wind_size;

    srand (time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //doble buffer
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(wind_size_x, wind_size_y);
    glutCreateWindow("Maze generator");

    GenerateParameters(maze_columns); //generamos parametros del laberinto segun resolucion de pantalla y num columnas
    
    FillWithWall();
    GenerateMaze(); //creamos el laberinto aleatoriamente

    GeneratePath(); //creamos el camino aleatoriamente
    
    glutDisplayFunc(display);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,wind_size_x,0.0,wind_size_y);

    glutMainLoop();
    return 0;
}

void animate(){
        
    glutTimerFunc(TIMERMSECS, animate, 0);

    Move(); //creamos siguiente movimiento
    DrawMaze(); //dibujamos

    glutSwapBuffers();
}

/*******************************************************/
int GenerateParameters(int maze_columns)
{

    size = round(wind_size_x/maze_columns);

    hor_point_number = round(wind_size_x/size)-1;
    ver_point_number = round(wind_size_y/size)-1;

    ver_points = malloc(sizeof(*ver_points) * hor_point_number);
    hor_points = malloc(sizeof(*hor_points) * ver_point_number);

    //guardamos los puntos horizontales
    int i = 0;
    int partialSize = 0;
    for(partialSize=0, i=0; i<hor_point_number; i++)
    {
      
      hor_points[i] = partialSize+(size/2); //guardamos punto central

      partialSize= partialSize+size;
    }

    //guardamos los puntos verticales
    for( partialSize=0, i=0; i<ver_point_number; i++)
    {

      ver_points[i] = partialSize+round(size/2);

      partialSize= partialSize+size;
    }

    return size;
}

void FillWithWall(){
    
    int v;
    int h;

    //llenamos todo con pared
    for(v = 0; v<ver_point_number; v++)
    {
      for(h = 0; h<hor_point_number; h++)
      {
          
        boolean found_edge =  (h == 0 || h==hor_point_number-1 || v==0 || v==ver_point_number-1);
        
        if (found_edge)
        {
          paint_points[h][v] = EDGE;
        }
        else{
          paint_points[h][v] = WALL;
        }
        
        
      }
    }
}

/*******************************************************/
void GenerateMaze()
{

    int v;
    int h;
    //pintamos esqueleto aleatoriamente
    int random_num1;
    int random_num2;
    int i=0;
    while (i < 100000){
      boolean found_hor_edge =  paint_points[h+1][v] != 0 && paint_points[h-1][v] != 0;
      if (found_hor_edge)
      {
        if(paint_points[h][v] != 3){paint_points[h][v] = 0;}
        if(paint_points[h][v+1] != 3){paint_points[h][v+1] = 0;}
        if(paint_points[h][v-1] != 3){paint_points[h][v-1] = 0;}
        
      }
      boolean found_ver_edge =  paint_points[h][v+1] != 0 && paint_points[h][v-1] != 0;
      if (found_ver_edge)
      {
        
        if(paint_points[h][v] != 3){paint_points[h][v] = 0;}
        if(paint_points[h+1][v] != 3){paint_points[h+1][v] = 0;}
        if(paint_points[h-1][v] != 3){paint_points[h-1][v] = 0;}
        
      }

      random_num1 = rand()%2;
      random_num2 = rand()%2;

      if (h<hor_point_number){
        h = h + random_num1;
      }
      if (v<ver_point_number){
        v = v + random_num2;
      }


      random_num1 = rand()%2;
      random_num2 = rand()%2;

      if (h>1 && v>1){
        h = h - random_num1;
        v = v - random_num2;
      }
      
      i++;
    }


    
}

/*******************************************************/
void GeneratePath()
{
    //generamos camino aleatoriamente
    int h = 1;
    int v = 1;
    int random_num1;
    int random_num2;

    paint_points[h][v] = PATH;
    boolean not_maze_end = (v<ver_point_number-1 && h<hor_point_number-1);
    while (not_maze_end){
      
      random_num1 = rand()%2;
      if (random_num1 == 0){
        h++;
      }
      else{
        v++;
      }
      
      paint_points[h][v] = PATH;
      not_maze_end = (v<ver_point_number-1 && h<hor_point_number-1);
    }
}
    
/*******************************************************/
void DrawMaze()
{
    int v = 0;
    int h = 0;

    //pintamos segun el numero de cada posicion de la matriz
    
    for(h = 0; h<hor_point_number; h++)
    {
      for(v = 0; v<ver_point_number; v++)
      {

        if(paint_points[h][v] == WALL){ //pared
          glColor3f(0,0,1.0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == PATH){ //camino
          glColor3f(0,1.0,0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == ANIMATION){ //animacion
          glColor3f(0,0,0);
          paint_points[h][v] = 2;
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == EDGE){ //bordes
          glColor3f(1.0,0,0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == EMPTY){ //vacio
          glColor3f(1.0,1.0,1.0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }

      }
    }
    
 
};

/*******************************************************/
void Move()
{ 
    //cada vez que se llama a esta funcion nos movemos un paso mas en el camino resultado
    int h;
    int v;

    for(v = move_v; v<ver_point_number; v)
    {
      for(h = move_h; h<hor_point_number; h)
      {
        boolean maze_end = (h==hor_point_number-1 && v==ver_point_number-1);
        if (maze_end)
        {
          return;
        }
        else{
          if (paint_points[h][v] == 2){
            paint_points[h][v] = ANIMATION;
            h++;
            move_h = h;
            move_v = v;
            return;
          }else{
            h++;
          }

        }
        
      }
      move_h = 1;
      move_v = v + 1;
      return;
    }
}

/*******************************************************/
int PlotSquare(int x, int y, double sq_size)
{
    //pintamos un cuadrado en las posicion x, y con tamaño sq_size
    sq_size = ceil(sq_size/2);

    struct point bottom_left;
    struct point top_left;
    struct point top_right;
    struct point bottom_right;
    
    bottom_left.h = -sq_size;
    bottom_left.v = -sq_size;
    
    top_left.h = -sq_size;
    top_left.v = sq_size;
    
    top_right.h = sq_size;
    top_right.v = sq_size;
    
    bottom_right.h = sq_size;
    bottom_right.v = -sq_size;
    
    glPushMatrix();

    glTranslatef(x, y, 0);

    glBegin(GL_QUADS); // Start drawing a quad primitive  

    glVertex2f(bottom_left.h, bottom_left.v); // The bottom left corner  
    glVertex2f(top_left.h, top_left.v); // The top left corner  
    glVertex2f(top_right.h, top_right.v); // The top right corner  
    glVertex2f(bottom_right.h, bottom_right.v); // The bottom right corner  
    glEnd(); 

    glPopMatrix();

    return sq_size;
};