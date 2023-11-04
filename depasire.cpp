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
	winWidth = 600, winHeight = 750;

//	Variabile catre matricile de transformare;
glm::mat4
	myMatrix, resizeMatrix, matrTransl, matrScale1, matrScale2, matrRot, matrDepl;

//	Variabila ce determina schimbarea culorii pixelilor in shader;
int codCol;			

//	Variabile pentru proiectia ortogonala;
float xMin = -450.f, xMax = 450.f, yMin = 0.f, yMax = 300.f;

//	Variabile pentru deplasarea pe axa Ox si pentru rotatie;
float i = 0.0, alpha = 0.0, step=0.1, beta = 0.002, angle = 0;

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
	if (i > 300.0)			
		alpha =  0;		
	else if (i < 0.0)
		alpha = step;
	angle = angle - beta;	//	Se actualizeaza unghiul de rotatie constant (mentine orbitarea);
	glutPostRedisplay();	//	Forteza redesenarea scenei;
}

//	Functie ce modifica deplasarea dreptunghiurilor in functie de apasarea butoanelor de pe mouse;
void UseMouse(int button, int state, int x, int y)
{
	
			alpha = step;
		glutIdleFunc(MoveUp);
	
}

//  Crearea si compilarea obiectelor de tip shader;
//	Trebuie sa fie in acelasi director cu proiectul actual;
//  Shaderul de varfuri / Vertex shader - afecteaza geometria scenei;
//  Shaderul de fragment / Fragment shader - afecteaza culoarea pixelilor;
void CreateShaders(void)
{
	ProgramId = LoadShaders("03_02_Shader.vert", "03_02_Shader.frag");
	glUseProgram(ProgramId);
}

//  Se initializeaza un Vertex Buffer Object (VBO) pentru tranferul datelor spre memoria placii grafice (spre shadere);
//  In acesta se stocheaza date despre varfuri (coordonate, culori, indici, texturare etc.);
void CreateVBO(void)
{
	//  Coordonatele varfurilor;
	GLfloat Vertices[] = {

	//	Varfuri pentru axa principala (0-1);
		0.0f, -300.0f, 0.0f, 1.0f,
		0.0f, 300.0f, 0.0f, 1.0f,

	//	Varfuri pentru masina (2-5);
		-100.0f,  -50.0f, 0.0f, 1.0f,
		100.0f, -50.0f, 0.0f, 1.0f,
		100.0f,  100.0f, 0.0f, 1.0f,
		-100.0f,  100.0f, 0.0f, 1.0f,

	// Varfuri pentru colorare trotuar (6-9, 10-13);
		340.0f,  300.0f, 0.0f, 1.0f,
		450.0f,  300.0f, 0.0f, 1.0f, 
		450.0f,  0.0f, 0.0f, 1.0f, 
		340.0f,  0.0f, 0.0f, 1.0f, 

		-340.0f,  300.0f, 0.0f, 1.0f,
		-340.0f,  0.0f, 0.0f, 1.0f,
		-450.0f,  0.0f, 0.0f, 1.0f,
		-450.0f,  300.0f, 0.0f, 1.0f,

	// Varfuri pentru axele imaginare de pe cele doua benzi (14-15, 16-17);
		175.0f, -300.0f, 0.0f, 1.0f,
		175.0f, 300.0f, 0.0f, 1.0f, 

		-175.0f, -300.0f, 0.0f, 1.0f,
		-175.0f, 300.0f, 0.0f, 1.0f, 

	// Varfuri pentru tufis (18-21, 22-25);
		340.0f,  300.0f, 0.0f, 1.0f,
		370.0f,  300.0f, 0.0f, 1.0f,
		370.0f,  0.0f, 0.0f, 1.0f,
		340.0f,  0.0f, 0.0f, 1.0f,

		-340.0f,  300.0f, 0.0f, 1.0f,
		-340.0f,  0.0f, 0.0f, 1.0f,
		-370.0f,  0.0f, 0.0f, 1.0f,
		-370.0f,  300.0f, 0.0f, 1.0f,

	// Varfuri pentru felinare (26 - 29);
		370.0f,  0.0f, 0.0f, 1.0f,
		370.0f,  50.0f, 0.0f, 1.0f,
		370.0f,  100.0f, 0.0f, 1.0f,
		370.0f,  150.0f, 0.0f, 1.0f,
		370.0f,  200.0f, 0.0f, 1.0f,
		370.0f,  250.0f, 0.0f, 1.0f,
		370.0f,  300.0f, 0.0f, 1.0f, 

		-370.0f,  0.0f, 0.0f, 1.0f,
		-370.0f,  50.0f, 0.0f, 1.0f,
		-370.0f,  100.0f, 0.0f, 1.0f,
		-370.0f,  150.0f, 0.0f, 1.0f,
		-370.0f,  200.0f, 0.0f, 1.0f,
		-370.0f,  250.0f, 0.0f, 1.0f,
		-370.0f,  300.0f, 0.0f, 1.0f, 

	// Varfuri pentru faruri (40-41);
		50.0f,  100.0f, 0.0f, 1.0f,
		-50.0f,  100.0f, 0.0f, 1.0f, 

	// Varfuri pentru bara din spate a masinii (42-45);
		-100.0f,  -50.0f, 0.0f, 1.0f,
		100.0f, -50.0f, 0.0f, 1.0f,
		100.0f, -25.0f, 0.0f, 1.0f,
		-100.0f,  -25.0f, 0.0f, 1.0f,

	// Varfuri pentru lumina farurilor (46-48, 49-51);
		-50.0f,  100.0f, 0.0f, 1.0f,
		-100.0f, 150.0f, 0.0f, 1.0f,
		-10.0f, 150.0f, 0.0f, 1.0f,

		50.0f,  100.0f, 0.0f, 1.0f,
		100.0f, 150.0f, 0.0f, 1.0f,
		-10.0f, 150.0f, 0.0f, 1.0f,

	// Varfuri pentru stopuri (52-53);
		-50.0f, -45.0f, 0.0f, 1.0f,
		50.0f, -45.0f, 0.0f, 1.0f,

	// Varfuri pentru semnalizare (54-55, 56-57);
		- 50.0f, -45.0f, 0.0f, 1.0f,
		-100.0f,  -50.0f, 0.0f, 1.0f,

		50.0f, -45.0f, 0.0f, 1.0f, 
		100.0f, -50.0f, 0.0f, 1.0f
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

//  Functia de desenarea a graficii pe ecran;
void RenderFunction(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//  Se curata ecranul OpenGL pentru a fi desenat noul continut;
	
	resizeMatrix = glm::ortho(xMin, xMax, yMin, yMax);							//	"Aducem" scena la "patratul standard" [-1,1]x[-1,1];
	matrTransl = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, i, 0.0));		//	Se translateaza de-a lungul axei Oy;
	matrScale1 = glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.3, 0.0));			//	Se scaleaza coordonatele initiale si se obtine masina;
	
	//	Matricea de redimensionare (pentru elementele "fixe" - axele);
	myMatrix = resizeMatrix;

	//	------> DESENAREA AXEI PRINCIPALE (DESPARTIRE BENZI)

	codCol = 0;
	//	Transmiterea variabilelor uniforme pentru MATRICE DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINES, 0, 2);

	// ------> DESENAREA AXELOR IMAGINARE DE PE BENZI 
	// - le-am adaugat ca sa putem muta masina de pe o axa pe alta, ele sunt gri ca soseaua

	codCol = 8;									//  Culoarea;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glLineWidth(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINES, 14, 2);
	
	codCol = 8;									//  Culoarea;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glLineWidth(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_LINES, 16, 2);

	// ------> DESENAREA TROTUARULUI
	
	codCol = 3;									//  Culoarea;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glPointSize(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_POLYGON, 6, 4);

	codCol = 3;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glPointSize(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_POLYGON, 10, 4);

	// ------> DESENAREA TUFISURILOR

	codCol = 4;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glPointSize(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_POLYGON, 18, 4);

	codCol = 4;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glPointSize(15.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_POLYGON, 22, 4);

	// ------> DESENAREA FELINARELOR

	codCol = 6;
	glUniform1i(codColLocation, codCol);		//	Transmiterea variabilei uniforme pentru COLORARE spre shadere;
	glPointSize(30.0);							//  Se seteaza dimensiunea punctelor si netezirea marginilor;
	glEnable(GL_POINT_SMOOTH);
	//  Functia de desenare primeste 3 argumente:
	//  - arg1 = tipul primitivei desenate,
	//  - arg2 = indicele primului punct de desenat din buffer,
	//  - arg3 = numarul de puncte consecutive de desenat;
	glDrawArrays(GL_POINTS, 26, 14);

	// ------> DESENAREA MASINII
	
	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 1;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 2, 4);

	// ------> DESENAREA FARURILOR MASINII

	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 6;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POINTS, 40, 2);

	// ------> COSMETIZAREA MASINII - BARA + LUMINA FARURI + STOPURI

	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 5;
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_POLYGON, 42, 4);
	
	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	srand(time(NULL));
	codCol = 6 + rand() % 2;  // Generează un număr aleatoriu între 6 și 7 și actualizează alternatorul
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_TRIANGLES, 46, 6);

	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 2;
	glLineWidth(30.0);
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_LINES, 52, 2);

	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 7;
	glLineWidth(50.0);
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_LINES, 54, 2);

	//	Matricea de transformare pentru masina; 
	myMatrix = resizeMatrix * matrTransl * matrScale1;
	codCol = 7;
	glLineWidth(50.0);
	//	Transmiterea variabilelor uniforme pentru MATRICEA DE TRANSFORMARE si COLORARE spre shadere;
	glUniformMatrix4fv(myMatrixLocation, 1, GL_FALSE, &myMatrix[0][0]);
	glUniform1i(codColLocation, codCol);
	glDrawArrays(GL_LINES, 56, 2);

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

