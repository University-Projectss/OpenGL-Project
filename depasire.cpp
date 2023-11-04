//
// ================================================
// | Grafica pe calculator                        |
// ================================================
// | PROIECTUL 2D |
// ============================================
//
//	Masinuta in depasire 
//
//	Biblioteci

#include <iostream>			//	Biblioteca necesara pentru afisarea in consola;
#include <windows.h>        //	Utilizarea functiilor de sistem Windows (crearea de ferestre, manipularea fisierelor si directoarelor);
#include <stdlib.h>         //  Biblioteci necesare pentru citirea shaderelor;
#include <stdio.h>
#include <GL/glew.h>        //  Definește prototipurile functiilor OpenGL si constantele necesare pentru programarea OpenGL moderna; 
#include <GL/freeglut.h>    //	Include functii pentru: 
							//	- gestionarea ferestrelor si evenimentelor de tastatura si mouse, 
							//  - desenarea de primitive grafice precum dreptunghiuri, cercuri sau linii, 
							//  - crearea de meniuri si submeniuri;
#include "loadShaders.h"	//	Fisierul care face legatura intre program si shadere;
#include "glm/glm.hpp"		//	Bibloteci utilizate pentru transformari grafice;
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

//  Identificatorii obiectelor de tip OpenGL;
GLuint
	VaoId,
	VboId,
	ColorBufferId,
	ProgramId,
	myMatrixLocation,
	matrScaleLocation,
	matrTranslLocation,
	matrRotlLocation,
	codColLocation;

//	Dimensiunile ferestrei de afisare;
GLfloat
	winWidth = 500, winHeight = 1000;

//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrRot;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;			

//	Variabile pentru proiectia ortogonala;
float xMin = -250.f, xMax = 250.f, yMin = -500.f, yMax = 500.f;

//	Variabile pentru deplasarea pe axa Ox si pentru rotatie;
float i = -375.0, j = -750.0, alpha = 0.0, alpha2 = 0.0, step=0.5, step2=1.0, beta = 0.002, angle = 0, aux = 0.f;

//	Functie pentru afisarea matricei de transformare;
void DisplayMatrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			cout << myMatrix[i][j] << "  ";
		cout << endl;
	};
	cout << "\n";
};

//	Schimba sensul animatiei in sus;
void MoveUp(void)
{
	i = i + alpha;
	j = j + alpha2;
	if (i > 600.0) {
		alpha = 0;
		alpha2 = 0;
	}
	else if (i < 0.0) {
		alpha = step;
		alpha2 = step2;
	}
	angle = angle - beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	
			alpha = step;
			alpha2 = step2;
		glutIdleFunc(MoveUp);
	
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("depasire.vert", "depasire.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {

	//	Varfuri pentru axa principala;
		0.0f, -500.0f, 0.0f, 1.0f,
		0.0f, 500.0f, 0.0f, 1.0f,

	//	Varfuri pentru masina;
		-25.0f,  -50.0f, 0.0f, 1.0f,
		 25.0f,  -50.0f, 0.0f, 1.0f,
		 25.0f,   50.0f, 0.0f, 1.0f,
		-25.0f,   50.0f, 0.0f, 1.0f,

	// Varfuri pentru trotuar;
		200.0f,  500.0f, 0.0f, 1.0f,
		250.0f,  500.0f, 0.0f, 1.0f, 
		250.0f, -500.0f, 0.0f, 1.0f, 
		200.0f,  -500.0f, 0.0f, 1.0f, 

		-200.0f,  500.0f, 0.0f, 1.0f,
		-200.0f,  -500.0f, 0.0f, 1.0f,
		-250.0f,  -500.0f, 0.0f, 1.0f,
		-250.0f,  500.0f, 0.0f, 1.0f,

	// Varfuri pentru tufis;
		175.0f,  500.0f, 0.0f, 1.0f,
		200.0f,  500.0f, 0.0f, 1.0f,
		200.0f,  -500.0f, 0.0f, 1.0f,
		175.0f,  -500.0f, 0.0f, 1.0f,

		-175.0f,  500.0f, 0.0f, 1.0f,
		-175.0f,  -500.0f, 0.0f, 1.0f,
		-200.0f,  -500.0f, 0.0f, 1.0f,
		-200.0f,  500.0f, 0.0f, 1.0f,

	// Varf pentru felinar;
		0.0f,  0.0f, 0.0f, 1.0f,

	// Varfuri pentru faruri;
		-20.0f,  45.0f, 0.0f, 1.0f,
	     20.0f,  45.0f, 0.0f, 1.0f, 

	// Varfuri pentru bara din spate a masinii;
		-25.0f,  -50.0f, 0.0f, 1.0f,
		 25.0f,  -50.0f, 0.0f, 1.0f,
		 25.0f,  -45.0f, 0.0f, 1.0f,
		-25.0f,  -45.0f, 0.0f, 1.0f,

	// Varfuri pentru lumina farurilor;
		-20.0f,  45.0f, 0.0f, 1.0f,
		-40.0f,  100.0f, 0.0f, 1.0f,
     	  0.0f,  100.0f, 0.0f, 1.0f,

		 20.0f,  45.0f, 0.0f, 1.0f,
		  0.0f, 100.0f, 0.0f, 1.0f,
		 40.0f, 100.0f, 0.0f, 1.0f,

	// Varfuri pentru stopuri;
		-10.0f, -55.0f, 0.0f, 1.0f,
		 10.0f, -55.0f, 0.0f, 1.0f,

	// Varfuri pentru semnalizare;
		 -25.0f, -50.0f, 0.0f, 1.0f,
		 -10.0f, -55.0f, 0.0f, 1.0f,

		  10.0f, -55.0f, 0.0f, 1.0f, 
		  25.0f, -50.0f, 0.0f, 1.0f
	};

	//  Culorile axelor;
	GLfloat Colors[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f
	};

	//  Transmiterea datelor prin buffere;

	//  Se creeaza / se leaga un VAO (Vertex Array Object) - util cand se utilizeaza mai multe VBO;
	glGenVertexArrays(1, &VaoId);                                                   //  Generarea VAO si indexarea acestuia catre variabila VaoId;
	glBindVertexArray(VaoId);

	//  Se creeaza un buffer pentru VARFURI;
	glGenBuffers(1, &VboId);                                                        //  Generarea bufferului si indexarea acestuia catre variabila VboId;
	glBindBuffer(GL_ARRAY_BUFFER, VboId);                                           //  Setarea tipului de buffer - atributele varfurilor;
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);      //  Punctele sunt "copiate" in bufferul curent;
	//  Se asociaza atributul (0 = coordonate) pentru shader;
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//  Se creeaza un buffer pentru CULOARE;
	glGenBuffers(1, &ColorBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, ColorBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
	//  Se asociaza atributul (1 =  culoare) pentru shader;
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

//  Elimina obiectele de tip shader dupa rulare;
void DestroyShaders(void)
{
	glDeleteProgram(ProgramId);
}

//  Eliminarea obiectelor de tip VBO dupa rulare;
void DestroyVBO(void)
{
	//  Eliberarea atributelor din shadere (pozitie, culoare, texturare etc.);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	//  Stergerea bufferelor pentru varfuri, culori;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &ColorBufferId);
	glDeleteBuffers(1, &VboId);

	//  Eliberaea obiectelor de tip VAO;
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}

//  Functia de eliberare a resurselor alocate de program;
void Cleanup(void)
{
	DestroyShaders();
	DestroyVBO();
}

//  Setarea parametrilor necesari pentru fereastra de vizualizare;
void Initialize(void)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);		//  Culoarea de fond a ecranului;
	CreateVBO();								//  Trecerea datelor de randare spre bufferul folosit de shadere;
	CreateShaders();							//  Initilizarea shaderelor;
	//	Instantierea variabilelor uniforme pentru a "comunica" cu shaderele;
	codColLocation = glGetUniformLocation(ProgramId, "codCol");
	myMatrixLocation = glGetUniformLocation(ProgramId, "myMatrix");
}

void DrawCar(glm::mat4 mymatrix, int carCodCol) {
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	// ------> DESENAREA MASINII
	codCol = carCodCol;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 2, 4);

	// ------> DESENAREA FARURILOR MASINII
	codCol = 6;
	glUniform1i(codColLocation, codCol);
	glPointSize(10.0);
	glDisable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POINTS, 23, 2);

	// ------> COSMETIZAREA MASINII - BARA + LUMINA FARURI + STOPURI
	codCol = 5;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 25, 4);

	codCol = 6;
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_TRIANGLES, 29, 6);

	codCol = 2;
	glLineWidth(30.0);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_LINES, 35, 2);

	codCol = 7;
	glLineWidth(50.0);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_LINES, 37, 2);
	glDrawArrays(GL_LINES, 39, 2);

}

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);
	
	//	Matricea de redimensionare (pentru elementele "fixe" - axele);
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);

	//	------> DESENAREA AXEI PRINCIPALE (DESPARTIRE BENZI)

	codCol = 0;
	glUniform1i(codColLocation, codCol);
	glLineWidth(10.0);
	glDrawArrays(GL_LINES, 0, 2);

	//  ------> DESENAREA MASINII 1
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(100.0, i, 0.0));
	myMatrix = resizeMatrix * matrTransl;
	DrawCar(myMatrix, 1);

	//  ------> DESENAREA MASINII 2
	// mers drept banda dreapta
	if (j < -325) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(100.0, j, 0.0));
		myMatrix = resizeMatrix * matrTransl;
	}
	// viraj spre stanga de pe banda dreapta
	else if(j < -300){
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(100.0, j, 0.0));
		angle = 3.1415 / 100 * (j + 325);
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// mers drept pe diagonala spre banda din stanga
	else if (j < -100) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-200.0 - j, j, 0.0));
		angle = 3.1415 / 4;
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// viraj spre dreapta pentru a indrepta masina pe banda stanga
	else if (j < -75) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0, j, 0.0));
		angle = -3.1415 / 100 * (j + 100) + 3.1415/4;
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// mers drept pe banda din stanga
	else if (j < 100) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0, j, 0.0));
		myMatrix = resizeMatrix * matrTransl;
	}
	// viraj spre stanga spre banda din dreapta
	else if (j < 125) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0, j, 0.0));
		angle = - 3.1415 / 100 * (j - 100);
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// mers drept pe diagonala spre banda din dreapta
	else if (j < 325) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(-225.0 + j, j, 0.0));
		angle = -3.1415 / 4;
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// viraj spre stanga pentru a indrepta masina pe banda din dreapta
	else if (j < 350) {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(100.0, j, 0.0));
		angle = 3.1415 / 100 * (j - 325) - 3.1415/4;
		matrRot = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0, 0.0, 1.0));
		myMatrix = resizeMatrix * matrTransl * matrRot;
	}
	// mers drept pe banda din dreapta
	else {
		matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(100.0, j, 0.0));
		myMatrix = resizeMatrix * matrTransl;
	}
	DrawCar(myMatrix, 2);

	// ------> DESENAREA TROTUARULUI
	myMatrix = resizeMatrix;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	codCol = 3;
	glUniform1i(codColLocation, codCol);
	glPointSize(15.0);
	glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POLYGON, 6, 4);

	codCol = 3;
	glUniform1i(codColLocation, codCol);
	glPointSize(15.0);
	glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POLYGON, 10, 4);

	// ------> DESENAREA TUFISURILOR

	codCol = 4;
	glUniform1i(codColLocation, codCol);
	glPointSize(15.0);
	glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POLYGON, 14, 4);

	codCol = 4;
	glUniform1i(codColLocation, codCol);
	glPointSize(15.0);
	glEnable(GL_POINT_SMOOTH);
	glDrawArrays(GL_POLYGON, 18, 4);

	// ------> DESENAREA FELINARELOR

	codCol = 6;
	glUniform1i(codColLocation, codCol);
	glPointSize(20.0);
	glEnable(GL_POINT_SMOOTH);
	for (int y = -500; y <= 500; y += 100) {
		for (int x = -200; x <= 200; x += 400) {
			myMatrix = resizeMatrix * glm::translate(glm::mat4(1.0f), glm::vec3((float)x, (float)y, 0.0));
			glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
			glDrawArrays(GL_POINTS, 22, 1);
		}
	}

	glutSwapBuffers();	//	Inlocuieste imaginea deseneata in fereastra cu cea randata; 
	glFlush();	//  Asigura rularea tuturor comenzilor OpenGL apelate anterior;
}

//	Punctul de intrare in program, se ruleaza rutina OpenGL;
int main(int argc, char* argv[])
{
	//  Se initializeaza GLUT si contextul OpenGL si se configureaza fereastra si modul de afisare;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);					//	Se folosesc 2 buffere (unul pentru afisare si unul pentru randare => animatii cursive) si culori RGB;
	glutInitWindowPosition(100, 20);								//  Pozitia initiala a ferestrei;
	glutInitWindowSize(winWidth, winHeight);									//  Dimensiunea ferestrei;
	glutCreateWindow("Masinuta in depasire");		//	Creeaza fereastra de vizualizare, indicand numele acesteia;

	//	Se initializeaza GLEW si se verifica suportul de extensii OpenGL modern disponibile pe sistemul gazda;
	//  Trebuie initializat inainte de desenare;

	glewInit();
	
	Initialize();						//  Setarea parametrilor necesari pentru fereastra de vizualizare; 
	glutDisplayFunc(RenderFunction);	//  Desenarea scenei in fereastra;
	glutMouseFunc(UseMouse);			//	Activarea utilizarii mouseului;
	glutCloseFunc(Cleanup);				//  Eliberarea resurselor alocate de program;

	//  Bucla principala de procesare a evenimentelor GLUT (functiile care incep cu glut: glutInit etc.) este pornita;
	//  Prelucreaza evenimentele si deseneaza fereastra OpenGL pana cand utilizatorul o inchide;

	glutMainLoop();

	return 0;
}

