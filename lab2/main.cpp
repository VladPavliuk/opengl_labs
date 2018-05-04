#include <GL/glut.h>
#include <math.h>

//------------------КОНСТАНТИ ТА ГЛОБАЛЬНІ ЗМІННІ-------------------------

int Width = 800, Height = 800; //парметри вікна виводу
const double Pi = 3.1415926535897932384;
const double e = 2.718;

//Управління виводом на екран!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


void DrawSphere() {
	/*const double a = 0.5;
	const double b = 0.8;
	const double c = 8;

	double x = a*(sin(c*t)+b)*cos(t);
	double y = a * (sin(c*t) + b)*sin(t);
	double z = a * cos(c*t);
	while (t <= 2*Pi)
	{
		double xpred = x;
		double ypred = y;
		double zpred = z;
		x = a * (sin(c*t) + b)*cos(t);
		y = a * (sin(c*t) + b)*sin(t);
		z = a * cos(c*t);
		t += 0.05;

		glColor3d(1, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(xpred, ypred, zpred); glVertex3f(x, y, z);
		glEnd();
	};*/

	double r = 2, i = 0, j = 0;
	double m = 10;
	double n = 10;
	double x = r * sin(j) * cos(i);
	double y = r * sin(j) * cos(i); 
	double z = r * cos(j);

	while(i <= 2 * Pi) {
		while(j <= Pi) {
            glColor3d(1, 0, 1);
            glBegin(GL_LINES);
			glVertex3f(x, y, z);

			x = r * sin(j) * cos(i);
			y = r * sin(j) * cos(i); 
			z = r * cos(j);

            glVertex3f(x, y, z);
			glEnd();
			
			j += Pi / n;
		 }

		i += 2 * Pi / m;
	}
};

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//=========================================================	

	glRotated(10, 2, 1, 0);

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


//Ініціалізація  GLUT-додатку!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main(int argc, char **argv)
{
	glutInit(&argc, argv); //ф-я здійснює необхіжні початкові значення для побудови вікна додатку
	glutInitWindowPosition(0, 0); //положення вікна
	glutInitWindowSize(Width, Height); //розмір вікна
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);// режими відображення інформації (вікно з: буфером глибини, подвійним буфером, режим RGB роботи з кольором)
	glutCreateWindow("camera"); //назва 
	glClearColor(0, 0, 0, 0);//колір фону

	glutDisplayFunc(display); // вказується що малювати у вікні додатку при кожній  перемальовці вікні
							  //glutKeyboardFunc(keyboard); //вказується що ф-я Keyboard(яка опрацьовує виклики із клавіатури) буде викликатися при перемальовці вікні

	scene();

	glutMainLoop();// Основной цикл GLUT

	return 0;
}


