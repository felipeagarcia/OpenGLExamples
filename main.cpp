#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

GLint WINDOW_WIDTH  = 500,
      WINDOW_HEIGHT = 500;
      
void init();      
void draw_test();

void mouse_test(GLint button, GLint action, GLint x, GLint y);
void mouse_test2(GLint x, GLint y);
void mouse_test3(GLint x, GLint y);

void keybord_test(GLubyte key, GLint x, GLint y);
void keybord_test2(GLint key, GLint x, GLint y);

void test_create_menu();
void menu_test(GLint item_number);


typedef struct Point{
  GLint x;
  GLint y;
}Point;

Point initialPoint;


int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("OpenGL manipulacao de entradas (teclado/mouse)");
  
  init();
  glutDisplayFunc(draw_test);
  
  glutMouseFunc(mouse_test);
  glutPassiveMotionFunc(mouse_test2);
  glutMotionFunc(mouse_test3);
  
  glutKeyboardFunc(keybord_test);
  glutSpecialFunc(keybord_test2);

  test_create_menu();
  //valores variam entre [0−1]
  glClearColor(1, 1, 1, 1);
  //GL_MODELVIEW (padrao), GL_PROJECTION, GL_TEXTURE, ←-

  //void glMatrixMode(GLenum mode);

  glutMainLoop();
  
  
  return EXIT_SUCCESS;
}

void init()
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glClear(GL_COLOR_BUFFER_BIT);
  //glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
}


void draw_line(GLint x, GLint y){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0, 0, 0);
  glPointSize(2.0f);
  GLint dx = x - initialPoint.x , dy = y - initialPoint.y, inc;
  GLfloat i = (GLfloat)initialPoint.x, j = (GLfloat)initialPoint.y,  m = (GLfloat)dy/dx;
  glBegin(GL_POINTS);
    if(abs(dx) > abs(dy)){ // variacao de x eh maior
      inc = dx < 0? -1 : 1;
      m = inc * m;
      printf("inc = %d e dx eh maior\n",inc );
      while(i != x && j != y){
        glVertex2f(i, j);
        i = i + (GLfloat)inc;
        j = j + m;
      }
    } else{ // variacao de y eh maior
      inc = dy < 0? -1 : 1;
      m = (GLfloat)dx/dy;
      m = inc * m;
      printf("inc = %d e dy eh maior\n",inc );
      while(i != x && j != y){
        glVertex2f(i, j);
        i = i + m;
        j = j + (GLfloat)inc;
      }
    }
  glEnd();
  glutSwapBuffers();
}


void draw_test()
{

  
  std::cout<<"Desenho\n";
  
}

void mouse_test(GLint button, GLint action, GLint x, GLint y)
{ 

  switch(button)
  {
    case GLUT_LEFT_BUTTON: 
    {
      std::cout<<"Esquerda";
      draw_line(x,y);
      break;
    }
    case GLUT_MIDDLE_BUTTON:
    {
      std::cout<<"Meio";
      break;
    }      
    case GLUT_RIGHT_BUTTON:
    {
      std::cout<<"Direita";
      break;
    }      
    default: break;
  }
  
  if(action == GLUT_DOWN){
    std::cout<<" preciona";
    initialPoint.x = x;
    initialPoint.y = y;
  }

  else //GLUT_UP
    draw_line(x, y);
  
// x cresce da esquerda pra direita. O y cresce de cima para baixo  
  std::cout<<" em (x:"<<x<<", y:"<<y<<")";
    
  std::cout<<"\n"; 
}

void mouse_test2(GLint x, GLint y)
{
  std::cout<<"Movendo mouse sem clicar para posicao (x:"<<x<<", y:"<<y<<")\n"; 
}

void mouse_test3(GLint x, GLint y)
{
  draw_line(x,y);
  std::cout<<"Arrastando o mouse para posicao (x:"<<x<<", y:"<<y<<")\n"; 
}

void keybord_test(GLubyte key, GLint x, GLint y)
{
  GLint m = glutGetModifiers();
  
  if(m == GLUT_ACTIVE_SHIFT)
    std::cout<<"Shift ou Caps ";
  else if(m == GLUT_ACTIVE_CTRL)
    std::cout<<"Control ";
  else if(m == GLUT_ACTIVE_ALT)
    std::cout<<"Alt "; 
  
//VERIFICAR TABELA ASCII QUANDO O CTRL ESTIVER PRECIONADO COM ALGUMA LETRA  
  if(m == GLUT_ACTIVE_CTRL && (GLint) key == 4)
    exit(EXIT_SUCCESS);

  std::cout<<"Tecla: "<<(GLint) key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
  //ESC = 27
  if (key == 27)
    glutReshapeWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void keybord_test2(GLint key, GLint x, GLint y)
{
//GLUT_KEY_F1 .. GLUT_KEY_F12
//GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_LEFT, GLUT_KEY_RIGHT
//GLUT_KEY_PAGE_DOWN, GLUT_KEY_HOME etc.  
  
  std::cout<<"Tecla especial: "<<key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
  if(key == GLUT_KEY_F11)
    glutFullScreen();
}

void menu_test(GLint item_number)
{
  std::cout<<"Item "<<item_number<<"\n";
  glutPostRedisplay();
}

void test_create_menu()
{
  GLint submenu_id = glutCreateMenu(menu_test);
  glutAddMenuEntry("Subitem 1", 4);
  glutAddMenuEntry("Subitem 2", 5);
  glutAddMenuEntry("Subitem 3", 6);  
  
  GLint menu_id = glutCreateMenu(menu_test);  
  glutAddMenuEntry("Item 1", 1);
  glutAddMenuEntry("Item 2", 2);
  glutAddSubMenu("Item 3", submenu_id);  
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}


