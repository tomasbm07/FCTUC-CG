/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 3 - Visualizacao
======================================================================================= */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

#define tam 0.5

GLint flag = 0, rotate = 0;
float eixo_x = 0, eixo_y = 0, angle = 0;
float step = 0.1;

//================================================================================
//===========================================================Variaveis e constantes


static GLfloat vertices[] = {
	//�������������������������������������� x=tam (Esquerda)
	-tam,  -tam,  tam,	// 0 
	-tam,   tam,  tam,	// 1 
	-tam,   tam, -tam,	// 2 
	-tam,  -tam, -tam,	// 3 
	//�������������������� Direita
	tam,  -tam,  tam,	// 4 
	tam,   tam,  tam,	// 5 
	tam,   tam, -tam,	// 6 
	tam,  -tam, -tam,	// 7 
	//��������������������� (Cima
	-tam,  tam,  tam,	// 8 
	-tam,  tam, -tam,	// 9 
	tam,  tam, -tam,	// 10 
	tam,  tam,  tam,	// 11 
};

static GLfloat normais[] = {
	//�������������������������������������� x=tam (Esquerda)
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	//�������������������������������������� x=tam (Direita)
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
		//�������������������������������������� y=tam (Cima)
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
};

static GLfloat cor[] = {
	//�������������������������������������� //R
	1,  0.0,  0.0,
	1,  0.0,  0.0,
	1,  0.0,  0.0,
	1,  0.0,  0.0,
	//�������������������������������������� //G
	0,  1,  0.0,
	0,  1,  0.0,
	0,  1,  0.0,
 	0,  1,  0.0,
	//�������������������������������������� //B
	0.0,  0,  1,
	0.0,  0,  1,
	0.0,  0,  1,
	0.0,  0,  1,
};

	
//=========================================================== FACES DA MESA
GLboolean   frenteVisivel = 1;
static GLuint     cima[] = { 8, 11, 10,  9 };   // regra da mao direita
static GLuint     esquerda[] = {0, 1, 2, 3};   
static GLuint     direita[] = {4, 7, 6, 5};  


//------------------------------------------------------------ Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			//.. janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Visualizacao/Observador
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsP[] = {rVisao*cos(aVisao), 5, rVisao*sin(aVisao) };
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;

//================================================================================
//=========================================================================== INIT
void inicializa(void){
	glClearColor(BLACK);		//������������������������������Apagar
	glEnable(GL_DEPTH_TEST);	//������������������������������Profundidade
	glShadeModel(GL_SMOOTH);	//������������������������������Interpolacao de cores	

	glVertexPointer(3, GL_FLOAT, 0, vertices); //���������������VertexArrays: vertices + normais + cores
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, cor);
	glEnableClientState(GL_COLOR_ARRAY);
}


void drawEixos(){
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(10, 0, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 10, 0);
	glEnd();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 10);
	glEnd();

}


void drawScene() {
	//=================================================== Qual o lado visivel ???
	if (frenteVisivel);
	 //++++++++++++++++++++   falta fazer

	//==================================== MESA
	if (rotate == 1){	
		angle += 1;
		eixo_y += step;
		if (eixo_y > 3) step = -step;
		if (eixo_y < -1) step = -step;
	}

	glTranslatef(eixo_x, eixo_y, 0.0);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glPushMatrix();
		glScalef(2, 2, 2);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);   // desenhar as faces da mesa
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);  
	glPopMatrix();

	//==================================== Chaleira Amarela
	glColor4f(YELLOW);
	glPushMatrix();
		//+++++++++++++++++++++ escala, rotacao, translacao ??
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(0,3,0);
		glutWireTeapot(1);
	glPopMatrix();

}

void display(void) {
	//================================================================= APaga ecran e lida com profundidade (3D)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= N�o modificar !!!!!!!!!!!!
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	//================================================================= N�o modificar !!!!!!!!!!!!
	//����������������������������������������������������������Objectos
	drawEixos();
	drawScene();
	
	//. . . . . . . . . . . . . . . . . . . . .  Actualizacao
	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'F':
		case 'f':
			if (flag == 1){
				flag = 0;
				glDisable(GL_CULL_FACE);
			} else {
				flag = 1;
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
			}
			break;
		case 'A':
		case 'a':
			eixo_x += 0.25;
			break;
		case 'S':
		case 's':
			eixo_x -= 0.25;
			break;
		case 'E':
		case 'e':
			angle += 1.65;
			break;
		case 'D':
		case 'd':
			angle -= 1.65;
			break;
		case 'R':
		case 'r':
			rotate = !rotate;
			break;	

	case 27:
		exit(0);
		break;
	}
	glutPostRedisplay();

}


void teclasNotAscii(int key, int x, int y) {
	//.. observador pode andar � volda da cena  (setas esquerda / direita)
	//.. observador pode andar para cima e para baixo (setas cima / baixo )

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.1);

	if (obsP[1] > yC)
		obsP[1] = yC;
	if (obsP[1] < -yC)
		obsP[1] = -yC;

	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);


	glutPostRedisplay();
}


//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("{Mover/rodar Cima:'r'| |FaceVisivel:'f'| |Observador:'SETAS'| |Andar-'a/s'| |Rodar -'e/d'| ");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}


