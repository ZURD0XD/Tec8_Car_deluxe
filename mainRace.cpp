/*
* INTEGRANTES:
* IVAN FRANCO DELGADO
* JESUS EDUARDO SOSA DIAZ
* JOSUE TORRES AVALOS
*/
#include <GL/glut.h> // IMPORTA LA LIBRERIA DE GLUT
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iterator>
#include "Car.h"

// VALORES UTILIZADOS PARA EL TAMANO DE LA
// PANTALLA DEFINIENDO ALTO Y ANCHO
#define HEIGHT 720
#define WIDTH 1280

using namespace std;

// PROTOTIPOS DE FUNCIONES
void initializer(void);
int sum = 0;
void writeBitmapString(void *font, const char *string);
void userInterface(void);
list <Car> Enemigos_guardar(Car Enemigos[]);
void keyInput(unsigned char, int, int);
void specialKeyInput(int, int, int);
void mouseControl(int, int, int, int);
void ValueTime(int value);
void Colission(void);
void MapCar();
void Generar_Enemigos(list <Car> Enemigos);

static long font = (long)GLUT_BITMAP_TIMES_ROMAN_24;
Car carro(100,110,100,150,1.0,0.0,1.0);
Car Enemigos[3] = {Car (100,610,100,150,0.0,1.0,1.0),Car(210,610,100,150,0.0,1.0,1.0),Car(320,610,100,150,0.0,1.0,1.0) };

list<Car> Enemigos_ls = Enemigos_guardar(Enemigos);


Vertex Origin_carro(100,110);
Vertex Origin_enemigo(100, 610);

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT); // ESTABLECE EL TAMANO DE LA VENTANA
	glutCreateWindow("Tec8 Car Deluxe");

	initializer(); // INICIALIZA LA VENTANA

	glutDisplayFunc(userInterface); // ACTUALIZA LA PANTALLA DE TRAZADO
	glutKeyboardFunc(keyInput); // CAPTURA LAS TECLAS PERTENECIENTES AL ASCII
	glutSpecialFunc(specialKeyInput); // CAPTURA LAS TECLAS ESPECIALES COMO LAS FLECHAS
	glutTimerFunc(1000, ValueTime, 0);
	glutMouseFunc(mouseControl); // CAPTURA LOS CLICS
	glutMainLoop(); // GENERA EL LOOP

	return 0;
}

void Colission(void) {
	for (Car &enemy : Enemigos_ls) {
		float x1 = enemy.getOrigin().getX() - (enemy.getBase() / 2), x2 = x1 + enemy.getBase();
		float y1 = HEIGHT - (enemy.getOrigin().getY() - (enemy.getHeight() / 2)), y2 = y1 - enemy.getHeight();
		float x1_c = carro.getOrigin().getX() - (carro.getBase() / 2), x2_c = x1_c + carro.getBase();
		float y1_c = HEIGHT - (carro.getOrigin().getY() - (carro.getHeight() / 2)), y2_c = y1_c - carro.getHeight();
		// COMPARA LAS COORDENADAS EN EJE X E Y
		bool collisionX = (x1 <= x1_c && x2 >= x2_c);
		bool collisionY = (y1 >= y1_c && y2 <= y2_c);
		if (collisionX  && collisionY) {
			cout << "colisiona" << endl;
		}
	}
}

list <Car> Enemigos_guardar(Car Enemigos[]) {
	list <Car> temp;
	/*for (int i = 0; i < 3; i++)
	{*/
		temp.push_front(Enemigos[1]);
	//}
	return temp;
}

void Generar_Enemigos(list <Car> enemigos) {
	for (Car &enemy : enemigos) {
		enemy.drawShape();
	}
}

void Mover_enemigos() {
	if (Enemigos_ls.empty()) {
		cout << "vacía" << endl;
	}
	Vertex temp_origin;
	list<Car>::iterator itr = Enemigos_ls.begin();
	if (Enemigos_ls.empty() == false) {
		for (Car &enemy : Enemigos_ls) {
			if (Enemigos_ls.empty == false) {
				temp_origin = enemy.getOrigin();
			}

			if (temp_origin.getY() >= 50) {
				enemy.moveShape(0, -20);
			}
			else {
				Enemigos_ls.erase(itr);
			}
		}
	}
}

void MapCar() {
	glColor3f((rand() % 5), (rand() % 5), (rand() % 5));
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glVertex2f(40, 20);
	glVertex2f(380, 20);
	glVertex2f(380, 700);
	glVertex2f(40, 700);
	glEnd();
	glFlush();
}

void ValueTime(int value) {
	Mover_enemigos();
	glutPostRedisplay();
	glutTimerFunc(1000, ValueTime, 0);
	list<Car>Carros;
}

void writeBitmapString(void *font, const char *string){
	const char *c;
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void keyInput(unsigned char key, int x, int y){
	switch (key){
		
		case 97:
			if (Origin_carro.getX() != 100) {
				carro.moveShape(-110,0);
				Origin_carro.setX(Origin_carro.getX() - 110);
			}
			
			break;
		case 100:
			if (Origin_carro.getX() != 320.0) {
				carro.moveShape(110,0);
				Origin_carro.setX(Origin_carro.getX() + 110);
			}
			break;
		case 115:
			if (Origin_carro.getY() != 110) {
				carro.moveShape(0, -70);
				Origin_carro.setY(Origin_carro.getY() - 70);
			}
			break;
		case 119:
			if (Origin_carro.getY() <= 300) {
				carro.moveShape(0, 70);
				Origin_carro.setY(Origin_carro.getY() + 70);
			}
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void specialKeyInput(int key, int x, int y)
{
}

void mouseControl(int button, int state, int x, int y)
{
}

void initializer(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // COLOR CANVAS
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, WIDTH, 0.0, HEIGHT); // TAMANO DE MANTA
}

void menuOptions(void) {
	glColor3f(1.0, 0.0, 0.0);
	glRasterPos2f(1050, 690);
	writeBitmapString((void*)font, "TEC8 CAR DELUXE");
}

void userInterface(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Colission();
	MapCar();
	Generar_Enemigos(Enemigos_ls);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	menuOptions();
	carro.drawShape();
	glFlush();
}