#include <stdio.h>
#include <GL/glut.h>		


GLfloat r, g, b;


void Inicializa(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)
	gluOrtho2D(-50, 50, -50, 50);		//....	Definicao sistema coordenadas area de desenho
	glShadeModel(GL_SMOOTH);			//....  Interpolacao de cor com base na cor dos vertices
	//glShadeModel(GL_FLAT);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	r = 1; g = 1; b = 0;						//....  Vermelho
}


void Teclado(unsigned char key, int x, int y) {

	switch (key) {
	case 'r':
		r = 1.0; g = 0.0; b = 0.0;
		glutPostRedisplay();
		break;
	case 'g':
		r = 0.0; g = 1.0; b = 0.0;
		glutPostRedisplay();
		break;
	case 'b':
		r = 0.0; g = 0.0; b = 1.0;
		glutPostRedisplay();
		break;
	case 27:	//ESC
		exit(0);
	}
}


void Desenha(void){
	glClear(GL_COLOR_BUFFER_BIT);		//.. Limpa de acordo com cor predefinida -glClearColor

	glColor3f(1.0, 1.0, 0.0);					//.. Inicializa cor 
	glBegin(GL_POLYGON);
		glVertex2f(-25.0f, -50.0f);
		glVertex2f(-25.0f, 10.0f);
		glVertex2f(25.0f, 10.0f);
		glVertex2f(25.0f, -50.0f);
	glEnd();

	//porta
	glColor3f(0.6, 0.298, 0);
	glBegin(GL_POLYGON);
		glVertex2f(10.0f, -50.0f);
		glVertex2f(10.0f, -25.0f);
		glVertex2f(20.0f, -25.0f);
		glVertex2f(20.0f, -50.0f);
	glEnd();

	//janela
	glColor3f(0.101, 0.345, 0.619);
	glBegin(GL_POLYGON);
	int l = 8;
	int base = -10;
		glVertex2f(base-l, base-l);
		glVertex2f(base-l, base+l);
		glVertex2f(base+l, base+l);
		glVertex2f(base+l, base-l);
	glEnd();

	//telhado
	glColor3f(1.0, 0.0, 0);
	glBegin(GL_TRIANGLES);
		glVertex2f(-25.0f, 10.0f);
		glVertex2f(25.0f, 10.0f);
		glVertex2f(0.0f, 40.0f);
	glEnd();


	glutSwapBuffers();						//.. actualiza ecran
}


int main(int argc, char** argv){
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    //		:Recursos que ajanela vai usar: Double mode, RBG
	glutInitWindowSize(600, 500);					//		:dimensoes (pixeis)
	glutInitWindowPosition(200, 100);				//		:localizacao do vertice superior esquerdo
	glutCreateWindow(" Exemplo inicial 1 ");	    //      :nome da janela 

	Inicializa();									//===2:Inicializacao estado/parametros 
													//===3:Definicao callbaks	
	glutDisplayFunc(Desenha);						//		:desenho
	glutKeyboardFunc(Teclado);						//		:eventos teclado

	glutMainLoop();									//===4:Inicia processamento
	return 0;
}
