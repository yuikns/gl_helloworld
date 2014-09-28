#if defined(__APPLE__)
    #include <Glut/glut.h>
#elif defined(_WIN32) || defined(_WIN64)
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

#include <stdio.h>
#include <math.h>

#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES) ; \
	glVertex2f((x1),(y1)); glVertex2f((x2),(y2)); glEnd();

int main_title_id = -1;

float color[3] = {0,0,0};
float pos[3] = {0,0,0};
int i = 0;
int mode = 0;


int fullScreen = 0;
int saved_width = 800;
int saved_height = 600;
int saved_pos_x = 100;
int saved_pos_y = 100;

//glutReshapeFunc
void ReshapeABSSence(int w,int h)
{
	if(!fullScreen)
	{
		saved_width = w;
		saved_height = h;
	}
	
	if(h == 0) h = 1;
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

//
void ReshapeCenterSence(int w,int h)
{
	if(!fullScreen)
	{
		saved_width = w;
		saved_height = h;
	}
	//int saved_pos_x = 100;
	//int saved_pos_y = 100;
	float nRange = 300.0f;
	if(h == 0) h = 1;
	float nRatio = w / h;
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		glOrtho(-nRange,nRange,-nRange / nRatio,nRange / nRatio,-nRange,nRange);
	else
		glOrtho(-nRange * nRatio,nRange * nRatio,-nRange,nRange,-nRange,nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void setupRC(void)
{
	glClearColor(0.9,0.9,1.0,1.0f);
}

float colorPos(float x)
{
	return x > 1.0 ? x - 1.0 : x;
}


//glutDisplayFunc
void DisplaySence(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glBegin(GL_POLYGON);
	glColor3f(color[0],color[1],color[2]);
	//glBegin(GL_QUADS);
	int offset = -128;
	glVertex2f(pos[0] + offset,pos[1]+ offset);
	glVertex2f(pos[1] + offset,pos[2]+ offset);
	glVertex2f(pos[2] + offset,pos[0]+ offset);
	glEnd();
	
	glBegin(GL_POLYGON);
	glColor3f(color[0],color[1],color[2]);
	glBegin(GL_QUADS);
	glVertex2f(-pos[0] - offset,-pos[1] - offset);
	glVertex2f(-pos[1] - offset,-pos[2] - offset);
	glVertex2f(-pos[2] - offset,-pos[0] - offset);
	glEnd();
	
	//int i;
	//int R = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2])/3;
	//float Pi = 3.14;
	//int n = 720;
	//glColor3f(color[1],color[2],color[0]);
	//glBegin(GL_LINE_LOOP);
	//glBegin(GL_LINE_STRIP);
	//glBegin(GL_TRIANGLE_FAN); //solid
	//for(i=0; i<n; i++)
	//	glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
	//glEnd();
	
	//glLineStipple(1,0x3F07);
	//glEnable(GL_LINE_STIPPLE);
	
	//glColor3f(1,1,1);
	//drawOneLine(0,0,300,300);
	
	glutSwapBuffers();
}



void KeyboardSence(unsigned char key,int x,int y)
{
	printf("%c(%d),%d,%d\n",key,key,x,y);   
	switch(key)
	{
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'f':
	case 'F':
		fullScreen = fullScreen? 0: 1;
		break;
	default :
		break;
	}
	 
        if(fullScreen)
        {
        	
                glutFullScreen();
        }
        else
        {
                glutReshapeWindow(saved_width,saved_height);
                glutPositionWindow(saved_pos_x,saved_pos_y);
        }
}


void MouseSence(int button,int state,int x,int y)
{
	//state : 0 in 1 out
	switch(button)
	{
	case 0: // click
		printf("click %s (%d,%d)",state?"up":"down",x,y);
		break;
	case 1: // middle click
		printf("middle click %s (%d,%d)",state?"up":"down",x,y);
		break;
	case 2: // right click
		printf("right click %s (%d,%d)",state?"up":"down",x,y);
		break;
	case 3: //roll up
		printf("roll up %s (%d,%d)",state?"up":"down",x,y);
		break;
	case 4: //roll down
		printf("roll down %s (%d,%d)",state?"up":"down",x,y);
		break;
	default :
		printf("unknown button::%d (%d,%d)",button,x,y);
	}
	if(state) // state : 0) down 1) up
	{
		putchar('\n');
	}
	//printf("%d|%d|%d|%d\n",button,state,x,y);
	fflush(NULL);
}

void MotionSence(int x, int y)
{
	printf("<%d,%d>",x,y);
	fflush(NULL);
}

void EntrySence(int state)
{
	printf("::%s\n",state?"in":"out");
	fflush(NULL);
}

void TimerFunction(int value)
{
	if(i == 256){
		i = 0;
		mode --;
		//if(mode == 3) mode = 0;
		if(mode == -1) mode = 2;
	}
	color[mode % 3] = (float)i/255;
	color[(mode + 1) % 3] = (float)(255 - i)/255;
	color[(mode + 2) % 3] = 0;
	
	pos[mode % 3] = i - 128 + 128;
	pos[(mode + 1) % 3] = 128 - i + 128;
	pos[(mode + 2) % 3] = -128 + 128;
	
	i++;
	glutPostRedisplay();
	glutTimerFunc(30,TimerFunction,1);
}

int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE|GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	
	glEnable(GL_LIGHTING);
	  
	main_title_id = glutCreateWindow("Hello World!");
	//glutWarpPointer(0,0);
	//glutFullScreen();
	glutDisplayFunc(DisplaySence);
	glutReshapeFunc(ReshapeCenterSence);
	glutKeyboardFunc(KeyboardSence);
	glutMouseFunc(MouseSence);
	glutMotionFunc(MotionSence);
	glutEntryFunc(EntrySence);

	setupRC();
	glutTimerFunc(200,TimerFunction,1);
	glutMainLoop();
	return 0;
}


