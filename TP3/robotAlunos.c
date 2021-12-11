
//#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>


//---------------------------------------------------------------------------
//-------------------------------------------------------  Variaveis globais
//---------------------------------------------------------------------------

GLfloat wC = 10.0, hC = 10.0;		    //.. coordenadas reais - defini��o do mundo

GLfloat wSup = 4.0, hSup = 1.0;			//.. dimensoes da base
GLfloat xSup = 0.0, incSup = 0.45;		//.. posicao horizontal da base / incremento para deslocamento
GLfloat ySup = 0;						//.. posicao vertical da base
GLfloat agLig = 90, incLig = 6.0;		//.. angulo  da Ligacao / incremento para rotacao em graus
GLfloat agExt = 90, incExt = 8.0;		//.. angulo  da extremidade / incremento para rotacao

GLint   msec = 20;						//.. definicao do timer (actualizacao)
char    texto[30];					    //.. texto a ser escrito no ecran
GLint   tentativas = 0;					//.. numero de alvos gerados

GLfloat Matriz[4][4];					// para acede � matriz ModelView  posi��o Px, Py
GLfloat Px, Py;							// posi��o final da extremidade


//---------------------------------------------------------------------------
//----------------------------------------------------  Inicializa par�metros 
//---------------------------------------------------------------------------

void inicializa(void) {
	glClearColor(0, 0, 0, 1);
	glShadeModel(GL_SMOOTH);
	gluOrtho2D(-wC, wC, -hC, hC);  // coordenadas mundo
	srand(1);                     // para gerar posicao aleat�ria
}

float aleatorio(GLint minimo, GLint maximo) {
	GLfloat y;
	y = rand() % 1000;
	return (minimo + 0.001 * y * (maximo - minimo));
}

//---------------------------------------------------------------------------
//-----------------------------------------------------------------  Desenhar
//---------------------------------------------------------------------------
void desenhaAlvo(GLfloat tam, GLfloat r, GLfloat g, GLfloat b){
	//------------------------------------ deswnhado na origem 
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
		glVertex2f(0 - tam, 0 - tam);
		glVertex2f(0 - tam, 0 + tam);
		glVertex2f(0 + tam, 0 + tam);
		glVertex2f(0 + tam, 0 - tam);
	glEnd();
}

void desenhaTexto(char* string, GLfloat x, GLfloat y){
	glRasterPos2f(x, y);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}


void desenhaRobot(GLfloat xSup, GLfloat agLig, GLfloat agExt) {
	
	glPushMatrix();
		
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Base vermelha
	glColor3f(1, 0, 0);
	glTranslatef(xSup, 0.0, 0.0);
	glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);		// Acede � posicao atual da "Base"
	glPushMatrix();
		glScalef(wSup, hSup, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ligacao verde
	glColor3d(0, 1, 0);
	glRotatef(agLig-45, 0, 0, 1);	
	//glScalef(1.5, 1, 1);
	glPushMatrix();
		glTranslatef(2, 0, 0);
		glScalef(wSup, hSup, 1);
		glutSolidCube(1.0);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Extremidade Azul
	glColor3d(0, 0, 1);

	//glScalef(1.5, 0.5, 1);
	glPushMatrix();
		glTranslatef(3.5, 0, 0);
		glRotatef(agExt, 0, 0, 1);
		glScalef(wSup, hSup, 0.5);
		glutSolidCube(1.0);
	glPopMatrix();


	glPopMatrix();

}



//---------------------------------------------------------------------------
//.............................................................. Desenha Cena
//---------------------------------------------------------------------------
void desenhaJanela(void) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~limpa
	glClear(GL_COLOR_BUFFER_BIT);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Bra�oArticulado
	desenhaRobot(xSup, agLig, agExt);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Alvo a cair
	//  a fazer


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Apanhou ou nao??
	//+++++++++++++++++++++++++++++++++++++ posicao final da extremidade
	// o glGetFloatv est� no local pretendido  !!!!!!!
	// onde se quer conher a posicao final 
	// deve-se sar  glGetFloatv(GL_MODELVIEW_MATRIX, &Matriz[0][0]);  // valor final do ponto 'extremidade  '
	Px = wC * Matriz[3][0];
	Py = hC * Matriz[3][1];
	printf(" Px=%4.3f    Py=%4.3f\n ", Px, Py);

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX JOGO ????
	// A fazer pelos alunos
	sprintf(texto, "Tentativas = %d", tentativas);
	desenhaTexto(texto, -wC + 1, hC - 3);
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX A fazer pelos alunos


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Informacao
	//glColor3f(0, 0, 0.97);
	//char t[] = "{jh,avperrotta}@dei.uc.pt";
	//desenhaTexto(t, -wC + 0.2, -hC + 0.1);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Refresh
	glutSwapBuffers();
}


//---------------------------------------------------------------------------
//......................................................................Timer
//---------------------------------------------------------------------------
void Timer(int value){
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


//---------------------------------------------------------------------------
//....................................................................Eventos
//---------------------------------------------------------------------------

void teclasNotAscii(int key, int x, int y){
	if (key == GLUT_KEY_LEFT) {
		xSup -= incSup;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_RIGHT) {
		xSup += incSup;
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_UP) {
		agLig += incLig;		
		glutPostRedisplay();
	}
	if (key == GLUT_KEY_DOWN) {
		agLig -= incLig;
		glutPostRedisplay();
	}
}

void teclado(unsigned char key, int x, int y) {
	switch (key) {
	case 'A':
	case 'a':
		agExt += incExt;		
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		agExt -= incExt;				
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}


//-----------------------------------------------------
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Teclas: left, right, up, down, q, a ");

	inicializa();

	glutDisplayFunc(desenhaJanela);
	glutKeyboardFunc(teclado);
	glutSpecialFunc(teclasNotAscii);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();
	return 0;
}



