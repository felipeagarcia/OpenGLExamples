#include <cstdlib>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14

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

typedef struct  User{
  int draw_type;
}User;


typedef struct Object{
	Point p1;
	Point p2;
	int draw_type;
}Object;

typedef struct ListOfObjects{
	Object object[100];
	int count;
}ListOfObjects;

User user;
bool menuOn = false;
ListOfObjects objects;


int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  
  GLint screen_width  = glutGet(GLUT_SCREEN_WIDTH),
        screen_height = glutGet(GLUT_SCREEN_HEIGHT);  
  
  glutInitWindowPosition((screen_width - WINDOW_WIDTH) / 2, (screen_height - WINDOW_WIDTH) / 2);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_WIDTH);
  glutCreateWindow("OpenGL manipulacao de entradas (teclado/mouse)");
  user.draw_type = 1;
  for(int i = 0; i < 100; i++){
  	objects.object[i].draw_type = -1;
  }
  init();
  glutDisplayFunc(draw_test);
  objects.count = 0;  
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
  glutRemoveMenuItem(0);
  glutRemoveMenuItem(6);
  glutRemoveMenuItem(7);
  glutRemoveMenuItem(8);
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


void draw_line(GLint x1, GLint y1, GLint x2, GLint y2){
  /*This function draws a line between two points
  * @params: x1 = initial x
  *          y1 = initial y
  *          x2 = final x
  *          y2 = final y
  */
  //glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0, 0, 0);
  glPointSize(2.0f);
  GLint dx = x2 - x1 , dy = y2 - y1, inc;
  GLfloat i = (GLfloat)x1, j = (GLfloat)y1,  m;
  if(dy == 0 || dx == 0){
    m = 0;
  }
  else{
    m = (GLfloat)dy/dx;
  }
  glBegin(GL_POINTS);
    if(abs(dx) > abs(dy)){ // variacao de x eh maior
      inc = dx < 0? -1 : 1;
      m = inc * m;
      printf("inc = %d e dx eh maior\n",inc );
      while(i != x2){
        glVertex2f(i, j);
        i = i + (GLfloat)inc;
        j = j + m;
      }
    } else{ // variacao de y eh maior
      inc = dy < 0? -1 : 1;
      m = (GLfloat)dx/dy;
      m = inc * m;
      printf("inc = %d e dy eh maior\n",inc );
      while(j != y2){
        glVertex2f(i, j);
        i = i + m;
        j = j + (GLfloat)inc;
      }
    }
  glEnd();
}


void draw_square(GLint x1, GLint y1, GLint x2, GLint y2){
  draw_line(x1, y1, x2, y1);
  draw_line(x1, y1, x1, y2);
  draw_line(x1, y2, x2, y2);
  draw_line(x2, y1, x2, y2);
}

void draw_triangle(GLint x1, GLint y1, GLint x2, GLint y2){
  draw_line(x1, y1, x2, y2);
  GLint dx = x2 - x1;
  draw_line(x1, y1, x1 - dx, y2);
  draw_line(x1 - dx, y2, x2, y2);

}

void draw_circle(GLint x1, GLint y1, GLint x2, GLint y2){
  int r = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)), i;
  int qtd_retas = 100;
  int xi, yi, xf, yf;
  for(i = 1; i <= qtd_retas; i++){
    xi = x1 + r*cos((2 * PI * (i-1))/qtd_retas);
    yi = y1 + r*sin((2 * PI * (i-1))/qtd_retas);
    xf = x1 + r*cos((2 * PI * (i))/qtd_retas);
    yf = y1 + r*sin((2 * PI * (i))/qtd_retas);
    draw_line(xi, yi, xf, yf);
  }
}

void draw_ellipse(GLint x1, GLint y1, GLint x2, GLint y2){
  //int h = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
  float rx = abs(x2 - x1);
  float ry = abs(y2 - y1);  
  int qtd_retas = 50, i;
  int xi, yi, xf, yf;
  for(i = 1; i <= qtd_retas; i++){
    xi = x1 + rx*cos((2 * PI * (i-1))/qtd_retas);
    yi = y1 + ry*sin((2 * PI * (i-1))/qtd_retas);
    xf = x1 + rx*cos((2 * PI * (i))/qtd_retas);
    yf = y1 + ry*sin((2 * PI * (i))/qtd_retas);
    draw_line(xi, yi, xf, yf);
  }
}

void addObject(Point p1, Point p2, int type){
	objects.object[objects.count].p1 = p1;
	objects.object[objects.count].p2 = p2;
	objects.object[objects.count].draw_type = type;
	objects.count++;
}

void draw_object(Object obj){
	Point p1 = obj.p1;
	Point p2 = obj.p2;
	int type = obj.draw_type;
	printf("Meu tipo eh %d\n", type);
	switch(type){
      case 1: // linha
        draw_line(p1.x, p1.y, p2.x, p2.y);
        break;
      case 2: // quadrado
        draw_square(p1.x, p1.y, p2.x, p2.y);
        break;
      case 3: // triangulo
        draw_triangle (p1.x, p1.y, p2.x, p2.y);
        break;
      case 4: //circulo
        draw_circle(p1.x, p1.y, p2.x, p2.y);
        break;
      case 5: //elipse
        draw_ellipse(p1.x, p1.y, p2.x, p2.y);
        break;
      default:
        break;
    }
}

void redrawAll(ListOfObjects list_objects){
	int i = 0;
	while(list_objects.object[i].draw_type != -1){
		draw_object(list_objects.object[i]);
		i++;
	}
	glFlush();
}

void removeObject(){
	if(objects.count >= 0){
		objects.object[objects.count - 1].draw_type = -1;
		objects.count --;
		glClear(GL_COLOR_BUFFER_BIT);
		redrawAll(objects);
	}
}



void draw_test()
{

  std::cout<<"Desenho\n";
  
}

void rotate(Object obj, float angle){

}

void translate(Object obj, Point pf){

}

void scale(Object obj, float mult){
	//obj.p1.x = obj.p1.x * mult;
  //obj.p1.y = obj.p1.y * mult;
  obj.p2.x = obj.p2.x * mult; 
  obj.p2.y = obj.p2.y * mult;
  removeObject();
  addObject(obj.p1, obj.p2, obj.draw_type);
  redrawAll(objects);  
}

void mouse_test(GLint button, GLint action, GLint x, GLint y)
{ 
  switch(button)
  {
    case GLUT_LEFT_BUTTON: 
    {
      std::cout<<"Esquerda";
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
  
  if(action == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
    std::cout<<" preciona";
    initialPoint.x = x;
    initialPoint.y = y;
  }
  else if(button == GLUT_LEFT_BUTTON && !menuOn){ //GLUT_UP
  	Point p1, p2;
  	p1.x = initialPoint.x;
  	p1.y = initialPoint.y;
  	p2.x = x;
  	p2.y = y;
    switch(user.draw_type){
      case 1: // linha
        draw_line(initialPoint.x, initialPoint.y,x,y);
        addObject(p1,p2,user.draw_type);
        break;
      case 2: // quadrado
        draw_square(initialPoint.x, initialPoint.y, x, y);
        addObject(p1,p2,user.draw_type);
        break;
      case 3: // triangulo
        draw_triangle (initialPoint.x, initialPoint.y,x,y);
        addObject(p1,p2,user.draw_type);
        break;
      case 4: //circulo
        draw_circle(initialPoint.x, initialPoint.y,x,y);
        addObject(p1,p2,user.draw_type);
        break;
      case 5: //elipse
        draw_ellipse(initialPoint.x, initialPoint.y,x,y);
        addObject(p1,p2,user.draw_type);
        break;
      default:
        break;
    }
    glFlush();
  }
// x cresce da esquerda pra direita. O y cresce de cima para baixo  
  std::cout<<" em (x:"<<x<<", y:"<<y<<")";
    menuOn = false;
  std::cout<<"\n"; 
}

void mouse_test2(GLint x, GLint y)
{
  std::cout<<"Movendo mouse sem clicar para posicao (x:"<<x<<", y:"<<y<<")\n"; 
}

void mouse_test3(GLint x, GLint y)
{
  //draw_line(x,y);
  std::cout<<"Arrastando o mouse para posicao (x:"<<x<<", y:"<<y<<")\n"; 
}

void keybord_test(GLubyte key, GLint x, GLint y)
{
  GLint m = glutGetModifiers();
  
  if(m == GLUT_ACTIVE_SHIFT)
    std::cout<<"Shift ou Caps ";
  else if(m == GLUT_ACTIVE_CTRL && (GLint)key == 26)
    removeObject();
  else if(m == GLUT_ACTIVE_ALT)
    std::cout<<"Alt "; 
  
  if((GLint)key == 43)
  	scale(objects.object[objects.count - 1], 1.1f);
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
  menuOn = true;
  std::cout<<"Item "<<item_number<<"\n";
  user.draw_type = item_number;
  glutPostRedisplay();
}

void test_create_menu()
{
  GLint submenu_id = glutCreateMenu(menu_test);
  glutAddMenuEntry("Subitem 1", 6);
  glutAddMenuEntry("Subitem 2", 7);
  glutAddMenuEntry("Subitem 3", 8);  
  
  GLint menu_id = glutCreateMenu(menu_test);  
  glutAddMenuEntry("Reta", 1);
  glutAddMenuEntry("Quadrado", 2);
  glutAddMenuEntry("Triangulo", 3);
  glutAddMenuEntry("Circulo", 4);
  glutAddMenuEntry("Elipse", 5);
  glutAddSubMenu("Item 3", submenu_id);  
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}



