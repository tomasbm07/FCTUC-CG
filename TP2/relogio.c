/* ===================================================================================
    Computacao Grafica - 2021/22
    ..............................................................
    Trabalho 2 - relogio - Transformacoes geometricas

======================================================================================= */


//.................................................... Bibliotecas necessarias
#include <stdio.h>			
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#define PI  3.14159

struct tm *timeinfo; 
GLint hour, minute, second;
char texto[30];		            //.. texto, i.e, numeros do relogio = [1..12]


//.................................................... Variaveis
GLint   msecDelay = 100;			//.. definicao do timer (actualizacao da janela visualizacao)


//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void Inicializa(void){
    glClearColor(0.79, 0.78, 0.78, 1.0);	//....	Cor para apagar (Acinzentado)
    gluOrtho2D(-10, 10, -10, 10);		//....	Definicao sistema coordenadas mundo - area de desenho
    glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor interior poligono com base na cor dos vertices
}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------
void Teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 27: //ESC
        exit(0);
        break;
    }
}


//-----------------------------------------------------------------------------------
//------------------------------------------------------------------------- DESENHO 
//-----------------------------------------------------------------------------------
void DesenhaTriangulo(float tam){
    //float tam = 0.5;
    glBegin(GL_TRIANGLES);
        glVertex3f( -tam,  tam,  0.0);
        glVertex3f(  tam,  tam,  0.0);
        glVertex3f(  0.0, -tam,  0.0);
    glEnd();
}


void desenhaCirculo(GLfloat x, GLfloat y, GLfloat raio){
    int i;
    int num_triangulos = 40; //# de triangulos a desenhar
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // centro do circulo
        for(i = 0; i <= num_triangulos; i++) { 
            glVertex2f(
                x + (raio * cos(i *  2 * PI / num_triangulos)), 
                y + (raio * sin(i * 2 * PI / num_triangulos))
            );
        }
    glEnd();
}


void desenhaTexto(char* string, GLfloat x, GLfloat y){
    glRasterPos2f(x, y);
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}


//---------------------------------------- Fun��o callback de desenho (principal)
void Desenha(void){
    //-------------------------------- determinar horas, minutos segundos
    time_t now = time(0); //time now
    time(&now);
    timeinfo = localtime(&now);
    hour = timeinfo->tm_hour;
    minute = timeinfo->tm_min;
    second = timeinfo->tm_sec;
    /*
    hour = 18;
    minute = 45;
    second = 0;
    */

    //----------------------------------------------- DESENHO JANELA 
    glClear(GL_COLOR_BUFFER_BIT);		//.. Limpa de acordo com cor predefinida
    
    glColor3d(0, 0, 0);
    sprintf(texto, "%02d:%02d:%02d", hour, minute, second);
    desenhaTexto(texto, -1.2, 9.3);

    //base do relogio
    glColor3d(0,0,0);
    desenhaCirculo(0, 0, 9);

    //texto das horas
    glColor3f(1, 1, 1);
    int horas[] = {3,2,1,12,11,10,9,8,7,6,5,4};
    for (int i = 0; i < 12; i++){
        double anglet = i *  2 * PI / 12;
        double xt = (7.5 * cos(anglet));
        double yt = (7.5 * sin(anglet));
        sprintf(texto, "%2d", horas[i]);
        glPushMatrix();
            glScalef(0.8, 0.8, 1);
            glTranslatef(-0.3, -0.2, 1);
            desenhaTexto(texto, xt, yt);
        glPopMatrix();

    }

    //ticks
    glColor3f(1, 1, 1);
    double sum = -90;
    for (int i = 0; i < 12; i++){
        double anglet = i *  2 * PI / 12;
        double xt = (8 * cos(anglet));
        double yt = (8 * sin(anglet));

        glPushMatrix();
            glTranslatef(xt, yt, 0);
            glRotatef(sum, 0, 0, 1);
            glScalef(0.5, 1, 0);
            sum += 360 / 12;
            if (i % 3 == 0){
                glScalef(0.5, 1, 0);
            }
            else{
                glTranslatef(0.5, 0.5, 0);
                glScalef(0.4, 0.5, 0);
            }
            DesenhaTriangulo(1);
        glPopMatrix();
    }
    
    //minutos
    glColor3d(1, 0, 0); 
    double m_angle = 90 - (360/60 * minute);
    double offset = 2.5;
    double x = offset * cos(PI * m_angle / 180);
    double y = offset * sin(PI * m_angle / 180);
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(m_angle + 90, 0, 0, 1);
        glScalef(0.4, 2.5, 0);
        DesenhaTriangulo(1);
    glPopMatrix();

    //horas
    glColor3d(0, 0, 1); 
    double h_angle = 90 - ((360/12 * hour) + minute/2) ;
    offset = 2;
    x = offset * cos(PI * h_angle / 180);
    y = offset * sin(PI * h_angle / 180);
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(h_angle + 90, 0, 0, 1);
        glScalef(0.3, 2, 0);
        DesenhaTriangulo(1);
    glPopMatrix();

    //segundos
    glColor3d(0, 1, 0); 
    double s_angle = 90 - (360/60 * second);
    offset = 3.5;
    x = offset * cos(PI * s_angle / 180);
    y = offset * sin(PI * s_angle / 180);
    glPushMatrix();
        glTranslatef(x, y, 0);
        glRotatef(s_angle + 90, 0, 0, 1);
        glScalef(0.2, 3.5, 0);
        DesenhaTriangulo(1);
    glPopMatrix();

    //centro do relogio 
    glColor3f(1, 1, 1); 
    desenhaCirculo(0, 0, 0.5);

    glutSwapBuffers();					//.. actualiza ecran
}

//-------------------------- Actualizar janlea de msecDelay em msecDelay (milisegundos)
void Timer(int value){
    glutPostRedisplay();
    glutTimerFunc(msecDelay, Timer, 1);
}


//-----------------------------------------------------------------------------------
//MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    glutInit(&argc, argv);							//===1:Inicia janela
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //	  :Single mode, RBG
    glutInitWindowSize(600, 600);					//	  :dimensoes (pixeis)
    glutInitWindowPosition(200, 100);				//	  :localizacao
    glutCreateWindow("Relogio");

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    Inicializa();									//===2:Inicializacao estado/parametros 

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                                                   //===3:Definicao callbaks	
    glutDisplayFunc(Desenha);						//	  :desenho
    glutKeyboardFunc(Teclado);						//	  :eventos teclado
    glutTimerFunc(msecDelay, Timer, 1);			//    :controlar o tempo de actualizao do Desenha

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    glutMainLoop();								//===4:Inicia processamento
    return 1;
}
