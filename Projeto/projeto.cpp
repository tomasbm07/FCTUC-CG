/*
	Tomás Mendes - 2019232272

	Controls:

		Move Joystick:
		A W S D

		Buttons:
		K L

		Mudar observador de sítio:
		U I O P

		Reset buttons and joystick:
		0
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define PI 3.14159


static GLfloat vertices[] = {  // Coordenadas dos vértices de um cubo
	1,1,1,  	/*0*/
	1,1,-1, 	/*1*/   
	1,-1,-1,	/*2*/   
	1,-1,1,		/*3*/
	-1,1,1,		/*4*/ 
	-1,1,-1,	/*5*/  
	-1,-1,-1,	/*6*/  
	-1,-1,1		/*7*/  
};
          
static GLfloat faces[] = {  
	//Posição     	//texture
	3, 2, 1, 0,  	/* 0, 0, 1, 0, 1, 1, 0, 1, */  	    // direita
	5, 6, 7, 4,		/* 0, 0, 1, 0, 1, 1, 0, 1,	 */	    // esquerda
	4, 0, 1, 5,		/* 0, 0, 1, 0, 1, 1, 0, 1, */		// cima
	6, 2, 3, 7,		/* 0, 0, 1, 0, 1, 1, 0, 1, */		// baixo
	0, 4, 7, 3,		/* 1, 1, 0, 1, 0, 0, 1, 0, */		// frente
	5, 1, 2, 6,		/* 0, 0, 1, 0, 1, 1, 0, 1, */		// tras
};

int direita[] = {
	3, 2, 1, 0
};

int esquerda[] = {
	5, 6, 7, 4
};

int cima [] = {
	4, 0, 1, 5
};

int baixo [] = {
	6, 2, 3, 7
};

int frente [] = {
	0, 4, 7, 3
};

int tras [] = {
	5, 1, 2, 6
};

static int normais[] = {
	//direita
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	1, 0, 0,
	// esquerda
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	-1, 0, 0,
	// cima
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	0, 1, 0,
	// baixo
	0, -1, 0, 
	0, -1, 0, 
	0, -1, 0, 
	0, -1, 0, 
	// frente
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	0, 0, 1,
	// tras
	0, 0, -1,
	0, 0, -1,
	0, 0, -1,
	0, 0, -1
};


static GLfloat texturas_cubo[] = {
	// direita
  	0, 0,
	1, 0,
	1, 1,
	0, 1,
	// esquerda
    0, 0,
    1, 0,
    1, 1,
    0, 1,
	// cima
    0, 1,
	1, 1,
	1, 0,
	0, 0,
	// baixo
    0, 0, 
    1, 0, 
    1, 1, 
    0, 1,
	// frente
	1, 1, 
	0, 1, 
	0, 0, 
	1, 0,
	// tras
    0, 0,
    1, 0, 
    1, 1, 
    0, 1
};


int edgefaces[24] = {
        0,1,  1,5,  5,4,  4,0,    // faces de cima
        7,3,  3,2,  2,6,  6,7,    // faces de baixo
        1,2,  0,3,  4,7,  5,6     // ligação da face de baixo e a de cima
}; 

float vertexColors[72] = {
        1,0,0,  1,0,0,  1,0,0,  1,0,0,      // red
        0,1,0,  0,1,0,  0,1,0,  0,1,0,      // green
        0,0,1,  0,0,1,  0,0,1,  0,0,1,      // blue
        1,1,0,  1,1,0,  1,1,0,  1,1,0,      // yellow
        0,1,1,  0,1,1,  0,1,1,  0,1,1,      // cyan
        1,0,1,  1,0,1,  1,0,1,  1,0,1,   	// red
}; 											


// Objectos (sistema coordenadas)
GLint		wScreen = 800, hScreen = 600;			// janela (pixeis)
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;		// Mundo (unidades mundo)

// Visualizacao/Observador
GLfloat  rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat  obsPos[3];
GLfloat  obsLook[3];
GLfloat  angZoom = 45;
GLfloat  incZoom = 3;

// Random 
GLfloat joystic_x = 0, joystic_y = 0, joystic_z = 0;
GLboolean botao_1 = 0, botao_2 = 0;
GLfloat button1_y = 0, button2_y = 0;
GLfloat button_step = 0.02;

GLUquadricObj* obj;

GLuint textures_list[10];

//------------Materiais
GLfloat blackPlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat blackPlasticDif []={ 0.00 ,0.00 ,0.00 };
GLfloat blackPlasticSpec[]={ 0.0 ,0.00 ,0.0 };
GLint blackPlasticCoef = 0.25 *128;


//---------------------------------------------------- AMBIENTE - fixa
GLfloat intensidadeDia = 0.2;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1 };   // 

//Luz
GLint   ligaTeto = 1;		 //:::   'T'  
GLfloat intensidadeT = 0.3;  //:::   'I'  
GLfloat   luzR = 1;		 	 //:::   'R'  
GLfloat   luzG = 1;			 //:::   'G'  
GLfloat   luzB = 1;			 //:::   'B'  
GLfloat localPos[4] = { 1, 1.0, 0.0, 0 };
GLfloat localCorAmb[4] = { 0.2, 0.2, 0.2, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };

GLfloat Pos1[] = {6, 0, 1, 1};   // Foco 1
GLfloat	aberturaFoco = 25;


GLint dim = 64;

//-----------------------------------------------
void init_texturas() {
    int width, height, nrChannels;
    unsigned char *data; //"black_plastic.png"
    const char* texture_name[] = {"black_plastic.png", "red_plastic.png", "colorida.bmp"};

    for (int i = 0; i < 2; i++) {
        glGenTextures(1, &textures_list[i]);
        glBindTexture(GL_TEXTURE_2D, textures_list[i]);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // load and generate the texture
        data = stbi_load(texture_name[i], &width, &height, &nrChannels, 0);
        if (data!=NULL) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            printf("Failed to load image %s!\n", texture_name[i]);
        }
        stbi_image_free(data);
    }
}


void init_lights(void) {

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

   	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
   	glEnable(GL_COLOR_MATERIAL);

	float iop[] = {0.5, 0.5, 0.5 , 0};
	glMaterialfv(GL_FRONT, GL_AMBIENT, iop);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, iop);
	glMaterialfv(GL_FRONT, GL_SPECULAR, iop);

	//ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
	
	// Luz direcional
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);


	//===== FOCO 1
	GLfloat Foco_direccao[] = { 0, 0, -1, 0 };	//��� -Z
	GLfloat Foco1_cor[] = { 0, 0,  1, 1 };	//��� Cor da luz 1
	//GLfloat Foco2_cor[] = { 1, 0,  0, 1 };	//��� Cor da luz 2
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;		// Foco, SPOT_Exponent

	//�����������������������������������������������Foco Esquerda
	glLightfv(GL_LIGHT1, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

}



GLUquadricObj* quadric(){
	obj = gluNewQuadric();
	gluQuadricDrawStyle ( obj, GLU_FILL );
	gluQuadricNormals ( obj, GLU_SMOOTH );
	gluQuadricTexture ( obj, GL_TRUE );

	return obj;
}


void init_material(){
	glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
	glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
}



// Init
void inicializa(void){
	glClearColor(0.2, 0.2, 0.1, 1);		//Apagar

	glEnable(GL_NORMALIZE);

	init_texturas();

	init_lights();

	glEnable(GL_DEPTH_TEST);	//Profundidade
	glShadeModel(GL_SMOOTH);	//Interpolacao de cores	

	glVertexPointer(3, GL_FLOAT, 0, vertices); //VertexArray
	glEnableClientState(GL_VERTEX_ARRAY);

	glNormalPointer(3, GL_FLOAT, normais); //Normal Array
	glEnableClientState(GL_NORMAL_ARRAY);

	glColorPointer( 3, GL_FLOAT, 0, vertexColors );
    glEnableClientState( GL_COLOR_ARRAY );

	glTexCoordPointer(2, GL_FLOAT, 0, texturas_cubo); // Texture Array
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Posição inicial do observador
	obsPos[0] = rVisao*cos(aVisao);
	obsPos[1] = 5;
	obsPos[2] = rVisao*sin(aVisao);

	obsLook[0] = 1;
	obsLook[1] = 1;
	obsLook[2] = 0;


}


//Desenahar um criculo
void draw_circle(float radius, float n) {
	float x, y;
    glBegin(GL_POLYGON);
		for (int i = 0; i < n; i++) {
			x = radius * cos(i * PI * (360 / n) / 180);
			y = radius * sin(i * PI * (360 / n) / 180);
			glVertex2f(x, y);
		}
    glEnd();
}


void mainDraw() {

	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
		//Joystic
		
		glPushMatrix();

			glRotatef(joystic_x, 1, 0, 0);
			glRotatef(joystic_y, 0, 1, 0);
			glRotatef(joystic_z, 0, 0, 1);
			
			//cilindro
			glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textures_list[1]);
				//glDisable();

				obj = quadric();
				//glColor4f(0.9, 0.9, 0, 1);
				glRotatef(-90, 1, 0, 0);
				glScalef(0.2, 0.2, 2.5);
				gluCylinder(obj, 1, 1, 1, 100, 100);
				gluDeleteQuadric(obj);
				glDisable(GL_TEXTURE_2D);
			glPopMatrix();
			
			//esfera
			//glEnable(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, textures_list[0]);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
				obj = quadric();
				glColor4f(0, 0, 0.7, 0.4);
				glTranslatef(0, 2.5, 0);
				glScalef(0.6, 0.6, 0.6);
				gluSphere(obj, 1, 100, 100);
				gluDeleteQuadric(obj);
			glPopMatrix();
			glDisable(GL_BLEND);
			//glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		//	botao1
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures_list[1]);
		//glEnable(GL_COLOR_MATERIAL);

		glPushMatrix();
			obj = quadric();
			if (botao_1) {
				if (button1_y >= -0.5){
					button1_y -= button_step;
					if (button1_y < -0.5)
						botao_1 = !botao_1;
				}
			} else {
				if (button1_y <= 0){
					button1_y += button_step;
				}
			}
	
			glColor4f(0.9, 0, 0, 0.1);
			glTranslatef(2, button1_y, -0.7);
			glRotatef(-90, 1, 0, 0);
			glScalef(0.4, 0.4, 1);
			gluCylinder(obj, 1, 1, 1, 100, 100);
			//circulo em cima do cilindro do botao
			glPushMatrix();
				glTranslatef(0, 0, 1);
				draw_circle(1, 100);
			glPopMatrix();
			gluDeleteQuadric (obj);
		glPopMatrix();
		//glDisable(GL_COLOR_MATERIAL);

		//	botao2
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, textures_list[1]);
		glPushMatrix();
			obj = quadric();
			if (botao_2) {
				if (button2_y >= -0.5){
					button2_y -= button_step;
					if (button2_y < -0.5)
						botao_2 = !botao_2;
				}
			} else {
				if (button2_y <= 0){
					button2_y += button_step;
				}
			}

			//glColor4f(0.9, 0, 0, 0.1);
			glTranslatef(2.5, button2_y, 0.7);
			glRotatef(-90, 1, 0, 0);
			glScalef(0.4, 0.4, 1);
			gluCylinder(obj, 1, 1, 1, 100, 100);
			//circulo em cima do cilindro do botao
			glPushMatrix();
				glTranslatef(0, 0, 1);
				draw_circle(1, 100);
			glPopMatrix();
			gluDeleteQuadric (obj);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		// base
		//glBindTexture(GL_TEXTURE_2D, textures_list[0]);
		glPushMatrix();
			glColor4f(0.9, 1, 0.8, 0.1);
			glTranslatef(1, 0, 0);
			glScalef(3, 0.4, 2);

			//glDisable(GL_TEXTURE_2D);
			//glBindTexture(GL_TEXTURE_2D, textures_list[0]);
			//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, faces);

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();


			// glPushMatrix();
			// 	glTranslatef(0, 1, 0);
			// 	glRotatef(45, 1,0,0);
			// 
			// glPopMatrix();

			//glCullFace(GL_BACK);

			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, textures_list[0]);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
			glDisable(GL_TEXTURE_2D);	

			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente);
			glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras);
			
			glMatrixMode(GL_MODELVIEW);
			
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	
	float med_dim = (float)dim / 2;

	glTranslatef(5, 0, 0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures_list[1]);

	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	glutPostRedisplay();

}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//init_lights();

	//smal window
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 5, 200, 200);
	glLoadIdentity();
	gluLookAt(4.5,1,0,0,0,0,0,1,0);

	mainDraw();

	//main camera
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glViewport(0, 0, wScreen, hScreen);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(obsPos[0]+1, obsPos[1]+1, obsPos[2], obsLook[0], obsLook[1], obsLook[2], 0, 1, 0);
	glPopMatrix();

	mainDraw();
	
	// Refresh
	glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {

		//Joystick movement
		case '0':
			joystic_x = 0;
			joystic_z = 0;
			botao_1 = 0;
			botao_2 = 0;
			button1_y = 0;
			button2_y = 0;
			obsPos[0] = rVisao*cos(aVisao);
			obsPos[1] = 5;
			obsPos[2] = rVisao*sin(aVisao);
			obsLook[0] = 1;
			obsLook[1] = 1;
			obsLook[2] = 0;
			rVisao = 10;
			aVisao = 0.5 * PI; 
			incVisao = 0.05;
			break;
		case 's':
			joystic_x += 1.5;
			if (joystic_x > 30)
				joystic_x = 30;
			break;
		case 'w':
			joystic_x -= 1.5;
			if (joystic_x < -30)
				joystic_x = -30;
			break;
		case 'a':
			joystic_z += 1.5;
			if (joystic_z > 30)
				joystic_z = 30;
			break;
		case 'd':
			joystic_z -= 1.5;
			if (joystic_z < -30)
				joystic_z = -30;
			break;
			
		//Button movement
		case 'k':
			botao_1 = !botao_1;
			break;
		case 'l':
			botao_2 = !botao_2;
			break;
		
		//Observer Positions
		case 'u':
			obsPos[0] = 10;
			obsPos[1] = 0;
			obsPos[2] = 0;
			obsLook[0] = 1;
			obsLook[1] = 1;
			obsLook[2] = 0;
			break;
		case 'i':
			obsPos[0] = 0;
			obsPos[1] = 0;
			obsPos[2] = 10;
			obsLook[0] = 1;
			obsLook[1] = 1;
			obsLook[2] = 0;
			break;
		case 'o':
			obsPos[0] = -10;
			obsPos[1] = 0;
			obsPos[2] = 0;
			obsLook[0] = 1;
			obsLook[1] = 1;
			obsLook[2] = 0;
			break;
		case 'p':
			obsPos[0] = 0;
			obsPos[1] = 0;
			obsPos[2] = -10;
			obsLook[0] = 1;
			obsLook[1] = 1;
			obsLook[2] = 0;
			break;
		case 'g':
		case 'G':
			dim = 2 * dim;
			if (dim > 256) dim = 256;
			glutPostRedisplay();
			break;
		case 'f':
		case 'F':
			dim = 0.5 * dim;
			if (dim < 1) dim = 1;
			glutPostRedisplay();
			break;
		case 'h':
		case 'H':
			aberturaFoco = aberturaFoco + 3;
			if (aberturaFoco > 70)
				aberturaFoco = 70;
			break;
		case 'n':
		case 'N':
			aberturaFoco = aberturaFoco - 3;
			if (aberturaFoco < 3)
				aberturaFoco = 3;
			break;

        case 27:
            exit(0);
            break;
	
    }

	glutPostRedisplay();
}


// Setas para controlar o observador
void teclasNotAscii(int key, int x, int y) {
	// if (key == GLUT_KEY_UP)
	// 	obsPos[1] = (obsPos[1] + 0.1);
	// if (key == GLUT_KEY_DOWN)
	// 	obsPos[1] = (obsPos[1] - 0.1);

	// if (obsPos[1] > yC)
	// 	obsPos[1] = yC;
	// if (obsPos[1] < -yC)
	// 	obsPos[1] = -yC;

	// if (key == GLUT_KEY_LEFT)
	// 	aVisao = (aVisao + 0.1);
	// if (key == GLUT_KEY_RIGHT)
	// 	aVisao = (aVisao - 0.1);

	// obsPos[0] = rVisao * cos(aVisao);
	// obsPos[2] = rVisao * sin(aVisao);
	

	
	if (key == GLUT_KEY_UP){
		obsPos[1] += 0.1;
		obsLook[1] += 0.1;
	}
	if (key == GLUT_KEY_DOWN){
		obsPos[1] -= 0.1;
		obsLook[1] -= 0.1;
	}

	if (key == GLUT_KEY_LEFT){
		obsPos[0] -= 0.1;
		obsLook[0] -= 0.1;
	}

	if (key == GLUT_KEY_RIGHT){
		obsPos[0] += 0.1;
		obsLook[0] += 0.1;
	}

	glutPostRedisplay();
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("Projeto CG - Tomas Mendes - 2019232272");

	inicializa();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}
