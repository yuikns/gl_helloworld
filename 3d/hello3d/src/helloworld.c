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

int rotx = 100,roty = 100,rotz = 100; // 3d 

int para = 300;

int i = 0;
int mode = 0;

//glutReshapeFunc
void ReshapeABSSence(int w,int h)
{
	//float nRange = 300.0f;
	if(h == 0) h = 1;
	//float nRatio = w / h;
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//if(w <= h)
	//	glOrtho(-nRange,nRange,-nRange / nRatio,nRange / nRatio,-nRange,nRange);
	//else
	//	glOrtho(-nRange * nRatio,nRange * nRatio,-nRange,nRange,-nRange,nRange);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	gluOrtho2D(0.0,(GLdouble)w,0.0,(GLdouble)h);
}

//
void ReshapeCenterSence(int w,int h)
{
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
	glClearColor(0.0,0.0,0.0,1.0f);
}

float colorPos(float x)
{
	return x > 1.0 ? x - 1.0 : x;
}


//glutDisplayFunc
void DisplaySence(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,rotz);							
	glRotatef(-roty,1.0f,0.0f,0.0f);						
	glRotatef(-rotx,0.0f,1.0f,0.0f);						
	
	glBegin(GL_QUADS);
	{
		//glColor3f(color[0],color[1],color[2]);
		glColor3ub(255,0,0);glVertex3f(-0.51f * para,+0.51f * para,-0.51f * para);glVertex3f(+0.51f * para,+0.51f * para,-0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,-0.51f * para);glVertex3f(-0.51f * para,-0.51f * para,-0.51f * para);
		glColor3ub(0,255,0);glVertex3f(-0.51f * para,+0.51f * para,+0.51f * para);glVertex3f(-0.51f * para,-0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,+0.51f * para,+0.51f * para);
		glColor3ub(0,0,255);glVertex3f(+0.51f * para,+0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,-0.51f * para);glVertex3f(+0.51f * para,+0.51f * para,-0.51f * para);
		glColor3ub(255,255,0);glVertex3f(-0.51f * para,+0.51f * para,+0.51f * para);glVertex3f(-0.51f * para,+0.51f * para,-0.51f * para);glVertex3f(-0.51f * para,-0.51f * para,-0.51f * para);glVertex3f(-0.51f * para,-0.51f * para,+0.51f * para);
		glColor3ub(255,0,255);glVertex3f(-0.51f * para,+0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,+0.51f * para,+0.51f * para);glVertex3f(+0.51f * para,+0.51f * para,-0.51f * para);glVertex3f(-0.51f * para,+0.51f * para,-0.51f * para);
		glColor3ub(0,255,255);glVertex3f(-0.51f * para,-0.51f * para,+0.51f * para);glVertex3f(-0.51f * para,-0.51f * para,-0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,-0.51f * para);glVertex3f(+0.51f * para,-0.51f * para,+0.51f * para);
	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}


int fullScreen = 0;
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
                glutReshapeWindow(800,600);
                glutPositionWindow(100,100);
        }
}

void MouseSence(int button,int state,int x,int y)
{
	//state : 0 in 1 out
	switch(button)
	{
	case 0: // click
		printf("click %s (%d,%d)\n",state?"up":"down",x,y);
		if(!state)
		{
			//rotx += x - y;
			//roty += y - y;
		}
		break;
	case 1: // middle click
		printf("middle click %s (%d,%d)\n",state?"up":"down",x,y);
		break;
	case 2: // right click
		printf("right click %s (%d,%d)\n",state?"up":"down",x,y);
		break;
	case 3: //roll up
		printf("roll up %s (%d,%d)\n",state?"up":"down",x,y);
		if(!state) rotz += 0xff;
		printf("$$$ rotz : %d\n",rotz);
		break;
	case 4: //roll down
		printf("roll down %s (%d,%d)\n",state?"up":"down",x,y);
		if(!state) rotz -= 0xff;
		printf("$$$ rotz : %d\n",rotz);
		break;
	}
	//printf("%d|%d|%d|%d\n",button,state,x,y);
	fflush(NULL);
}


void TimerFunction(int value)
{
	//rotx ++;
	roty ++ ;
	if(roty > 100 ) roty = -100;
	//rotz ++;
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
	
	//glEnable(GL_LIGHTING);
	glEnable( GL_CULL_FACE ); // 将不渲染看不见的隐消面
	glCullFace( GL_BACK );

	glEnable( GL_DEPTH_TEST ); //无论绘制的先后，让距离远的物体总在距离近的物体后面。
	glDepthFunc( GL_LEQUAL );
	  
	main_title_id = glutCreateWindow("Hello World!");
	//glutWarpPointer(0,0);
	//glutFullScreen();
	glutDisplayFunc(DisplaySence);
	glutReshapeFunc(ReshapeCenterSence);
	glutKeyboardFunc(KeyboardSence);
	glutMouseFunc(MouseSence);

	setupRC();
	glutTimerFunc(200,TimerFunction,1);
	glutMainLoop();
	return 0;
}


