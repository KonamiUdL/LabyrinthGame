#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
//CAMBIO!!!
void PlotSquare(int x, int y, int size);
void GenerateParameters(int maze_columns);
void GeneratePath();
void GenerateMaze();
void DrawMaze();
void animate();
void Move();

const int TIMERMSECS = 100;

int move_v =1;
int move_h = 1;

int wind_size_x;
int wind_size_y;

int hor_point_number;
int ver_point_number;

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
    //Resolucion ventana
    int wind_size = 600;
    
    //numero columnas del laberinto
    int maze_columns = 50;


    wind_size_x = wind_size; 
    wind_size_y = wind_size;

    srand (time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //doble buffer
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(wind_size_x, wind_size_y);
    glutCreateWindow("Maze generator");

    GenerateParameters(maze_columns); //generamos parametros del laberinto segun resolucion de pantalla y num columnas
    
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
void GenerateParameters(int maze_columns)
{

    size = round(wind_size_x/maze_columns);

    hor_point_number = round(wind_size_x/size)-1;
    ver_point_number = round(wind_size_y/size)-1;

    ver_points = malloc(sizeof(*ver_points) * hor_point_number);
    hor_points = malloc(sizeof(*hor_points) * ver_point_number);

    //guardamos los puntos horizontales
    int i = 0;
    int s = 0;
    for(s=0, i=0; i<hor_point_number; i++)
    {
      
      hor_points[i] = s+(size/2); //guardamos punto central

      s=s+size;
    }

    //guardamos los puntos verticales
    for(s=0, i=0; i<ver_point_number; i++)
    {

      ver_points[i] = s+(size/2);

      s=s+size;
    }


}

/*******************************************************/
void GenerateMaze(int maze_columns)
{

    int v;
    int h;

    //llenamos todo con pared
    for(v = 0; v<ver_point_number; v++)
    {
      for(h = 0; h<hor_point_number; h++)
      {

        if (h == 0 || h==hor_point_number-1 || v==0 || v==ver_point_number-1)
        {
          paint_points[h][v] = 3;
        }
        else{
          paint_points[h][v] = 1;
        }
        
        
      }
    }

    //pintamos esqueleto aleatoriamente
    int num1;
    int num2;
    int i;
    while (i < 100000){
      
      if (paint_points[h+1][v] != 0 && paint_points[h-1][v] != 0)
      {
        
        if(paint_points[h][v] != 3){paint_points[h][v] = 0;}
        if(paint_points[h][v+1] != 3){paint_points[h][v+1] = 0;}
        if(paint_points[h][v-1] != 3){paint_points[h][v-1] = 0;}
        
      }

      if (paint_points[h][v+1] != 0 && paint_points[h][v-1] != 0)
      {
        
        if(paint_points[h][v] != 3){paint_points[h][v] = 0;}
        if(paint_points[h+1][v] != 3){paint_points[h+1][v] = 0;}
        if(paint_points[h-1][v] != 3){paint_points[h-1][v] = 0;}
        
      }

      
      num1 = rand()%2;
      num2 = rand()%2;

      if (h<hor_point_number){
        h = h + num1;
      }
      if (v<ver_point_number){
        v = v + num2;
      }


      num1 = rand()%2;
      num2 = rand()%2;

      if (h>1 && v>1){
        h = h - num1;
        v = v - num2;
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
    int num1;
    int num2;

    paint_points[h][v] = 2;

    while ( v<ver_point_number-1 && h<hor_point_number-1){
      
      num1 = rand()%2;
      if (num1 == 0){
        h++;
      }
      else{
        v++;
      }
      
      paint_points[h][v] = 2;
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
        
        if(paint_points[h][v] == 1){ //pared
          glColor3f(0,0,1.0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == 2){ //camino
          glColor3f(0,1.0,0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == 4){ //animacion
          glColor3f(0,0,0);
          paint_points[h][v] = 2;
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == 3){ //bordes
          glColor3f(1.0,0,0);
          PlotSquare(hor_points[h], ver_points[v], size);
        }
        if(paint_points[h][v] == 0){ //vacio
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
        
        if (h==hor_point_number-1 && v==ver_point_number-1)
        {
          return;
        }
        else{
          if (paint_points[h][v] == 2){
            paint_points[h][v] = 4;
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
void PlotSquare(int x, int y, int sq_size)
{
    //pintamos un cuadrado en las posicion x, y con tamaño sq_size
    sq_size = round(sq_size/2);

    glPushMatrix();

    glTranslatef(x, y, 0);

    glBegin(GL_QUADS); // Start drawing a quad primitive  

    glVertex2f(-sq_size, -sq_size); // The bottom left corner  
    glVertex2f(-sq_size, sq_size); // The top left corner  
    glVertex2f(sq_size, sq_size); // The top right corner  
    glVertex2f(sq_size, -sq_size); // The bottom right corner  
    glEnd(); 

    glPopMatrix();

};