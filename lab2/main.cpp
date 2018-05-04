#include <GL/glut.h>
#include <math.h>
#include <iostream>

//------------------КОНСТАНТИ ТА ГЛОБАЛЬНІ ЗМІННІ-------------------------

GLfloat xRotated, yRotated, zRotated;
int Width = 800, Height = 800; //парметри вікна виводу
const double Pi = 3.1415926535897932384;
const double e = 2.718;

//Управління виводом на екран!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

class Sphere 
{
	struct Point
	{
		double x;
		double y;
		double z;		
	};

	private: 
		int radius, u, v;
		const static int m = 50;
		const static int n = 50;

		Point polygonNet [n][m];
		
	public:
		Sphere(int radius)
		{
			this->radius = 2;
			this->v = Pi * 2;
			this->u = Pi;
		}

		void draw() 
		{
			for(int i = 0; i < Sphere::n; i++) {
				for(int j = 0; j < Sphere::n; j++) {
					glColor3d(1, 0, 1);
					glBegin(GL_LINES);
					glVertex3f(
						this->polygonNet[i][j].x, 
						this->polygonNet[i][j].y, 
						this->polygonNet[i][j].z
					);

					glVertex3f(
						this->polygonNet[i][j + 1].x, 
						this->polygonNet[i][j + 1].y, 
						this->polygonNet[i][j + 1].z
					);
					glEnd();
				 }
			}	
		}

		void drawToConsole()
		{
			for(int i = 0; i < Sphere::n; i++) {
				for(int j = 0; j < Sphere::n; j++) {
					std::cout << "X: " << this->polygonNet[i][j].x << std::endl;
					std::cout << "Y: " << this->polygonNet[i][j].y << std::endl;
					std::cout << "Z: " << this->polygonNet[i][j].z << std::endl << std::endl;
				 }
			}	
		}

		void definePolygonNet()
		{
			for(int i = 0; (double) this->v / (double) Sphere::m * i < this->v; i++) {
				for(int j = 0; (double) this->u / (double) Sphere::n * j < this->u; j++) {
					this->polygonNet[i][j].x = this->radius * sin(j) * cos(i);
					this->polygonNet[i][j].y = this->radius * sin(j) * cos(i); 
					this->polygonNet[i][j].z = this->radius * cos(j);
				 }
			}
		}
				
};


void DrawSphere() {
	Sphere* sphere = new Sphere(2);
	sphere->definePolygonNet();
	sphere->draw();
	sphere->drawToConsole();
};

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//=========================================================	

	//glRotated(10, 2, 1, 0);


	glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about Y axis
    glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);

	//координатні осі
	glLineWidth(2);
	glColor3d(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0); glVertex3d(5, 0, 0); //Ox
	glVertex3d(4.8, 0.1, 0); glVertex3d(5, 0, 0);
	glVertex3d(4.8, -0.1, 0); glVertex3d(5, 0, 0);

	glVertex3d(0, 0, 0); glVertex3d(0, 5, 0); //oy
	glVertex3d(0.1, 4.8, 0); glVertex3d(0, 5, 0);
	glVertex3d(-0.1, 4.8, 0); glVertex3d(0, 5, 0);

	glVertex3d(0, 0, 0); glVertex3d(0, 0, 5);//oz
	glVertex3d(-0.1, 0.1, 4.8); glVertex3d(0, 0, 5);
	glVertex3d(0.1, -0.1, 4.8); glVertex3d(0, 0, 5);
	glEnd();

	DrawSphere();


							   //=========================================================
	glFlush(); 
	glutSwapBuffers();
}




//Параметри візуалізації тривимірної сцени!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void scene(void)
{

	//Параметри матеріалів та джерел світла
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  //колір дифузного освітлення
	GLfloat light_position[] = { 3.0, 3.0, -3.0, 1.0 }; // розміщення джерела світла 
	GLfloat light_dir[] = { 1.0,1.0,1.0,1.0 }; //напрям світла

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_dir);
	glEnable(GL_LIGHTING);//дозволити режим використання освітлення
	glEnable(GL_LIGHT0);//увімкнути джерело світла

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);//режим при якому видаляються невидимі лінії та поверхні



	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glOrtho(-5, 5, -5, 5, 2, 15);//ортографічна проекція
	gluLookAt(0.0, 0.0, 5.0, // положення спостерігача: точка спостереження (0,0,5) */
		0.0, 0.0, 0.0,      /* центр сцени що проектується в центр області виводу (0,0,0) */
		0.0, 1.0, 0.);      /*додатній напрям осі  ОY */


}

void idleFunc(void)
{
    /*xRotated += 0.3;
    yRotated += 0.3;
    zRotated += 0.3;*/
    display();
}


//Ініціалізація  GLUT-додатку!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(int argc, char **argv)
{
	xRotated = yRotated = zRotated = 0.1;
	glutInit(&argc, argv); //ф-я здійснює необхіжні початкові значення для побудови вікна додатку
	glutInitWindowPosition(0, 0); //положення вікна
	glutInitWindowSize(Width, Height); //розмір вікна
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// режими відображення інформації (вікно з: буфером глибини, подвійним буфером, режим RGB роботи з кольором)
	glutCreateWindow("camera"); //назва 
	glutIdleFunc(idleFunc);
	glClearColor(0, 0, 0, 0);//колір фону

	glutDisplayFunc(display); // вказується що малювати у вікні додатку при кожній  перемальовці вікні
							  //glutKeyboardFunc(keyboard); //вказується що ф-я Keyboard(яка опрацьовує виклики із клавіатури) буде викликатися при перемальовці вікні

	scene();

	glutMainLoop();// Основной цикл GLUT

	return 0;
}


