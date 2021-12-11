//.................................................... Bibliotecas necessarias
//#include <stdio.h>			// printf
#include <GL/glut.h>		    // openGL  a GLUT já inclui as librarias: GL.h e GLU.h


//..................................................}.. Variaveis
GLfloat r, g, b;						// cor RGB


//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void Inicializa(void){
	glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)
	gluOrtho2D(-10, 10, -10, 10);		//....	Definicao sistema coordenadas area de desenho
	glShadeModel(GL_SMOOTH);			//....  Interpolacao de cor com base na cor dos vertices

}


//---------------------------------------- Função callback de desenho (principal)
void Desenha(void){
	glClear(GL_COLOR_BUFFER_BIT);		

	glPushMatrix();
	
	glBegin(GL_TRIANGLES);				
		glVertex2f(1, 1);
		glVertex2f(1, 6);
		glVertex2f(6, 1);
	glEnd();

	glPopMatrix();

	//---------------------------------------
	glPushMatrix();

	glColor3f(1, 0, 0);
	glTranslatef(1, 1, 0);
	glRotatef(135, 0, 0, 1);
	glScalef(0.2, 1, 1);
	glRotatef(-135, 0, 0, 1);
	glTranslatef(-1, -1, 0);

	glBegin(GL_TRIANGLES);				
		glVertex2f(1, 1);
		glVertex2f(1, 6);
		glVertex2f(6, 1);
	glEnd();

	glPopMatrix();

	glutSwapBuffers();						//.. actualiza ecran
}



//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv){
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    //		:Recursos que ajanela vai usar: Double mode, RBG
	glutInitWindowSize(500, 500);					//		:dimensoes (pixeis)
	glutInitWindowPosition(200, 100);				//		:localizacao do vertoce superior esquerdo
	glutCreateWindow(" Exemplo inicial ");	        //      :}nome da janela

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Inicializa();									//===2:Inicializacao estado/parametros 

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
													//===3:Definicao callbaks	
	glutDisplayFunc(Desenha);						//		:desenho
	//glutKeyboardFunc(Teclado);						//		:eventos teclado

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutMainLoop();									//===4:Inicia processamento
	return 1;
}