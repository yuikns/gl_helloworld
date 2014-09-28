//*******************************
//by: Seaboy100, www.CSDN.net
//*******************************
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <gl\gl.h>

HGLRC		hRC;
HDC			hDC;
HWND		hWnd;
WNDCLASS	wc;
int			pf;
PIXELFORMATDESCRIPTOR pfd;
HINSTANCE	hInstance;

//��Ⱦһ֡
void DrawGLScene(GLfloat rotx, GLfloat roty, GLfloat rotz)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// ����ɻ��漰�����
	glLoadIdentity();										// ����ģ�͹۲����
	glTranslatef(0.0f,0.0f,rotz);							// ˳��Z��ƫ��rotz
	glRotatef(-roty,1.0f,0.0f,0.0f);						// ��X����תroty
	glRotatef(-rotx,0.0f,1.0f,0.0f);						// ��Y����תrotx

	//��������
	glBegin(GL_QUADS);
	{
		glColor3ub(255,0,0);glVertex3f(-0.51f,+0.51f,-0.51f);glVertex3f(+0.51f,+0.51f,-0.51f);glVertex3f(+0.51f,-0.51f,-0.51f);glVertex3f(-0.51f,-0.51f,-0.51f);
		glColor3ub(0,255,0);glVertex3f(-0.51f,+0.51f,+0.51f);glVertex3f(-0.51f,-0.51f,+0.51f);glVertex3f(+0.51f,-0.51f,+0.51f);glVertex3f(+0.51f,+0.51f,+0.51f);
		glColor3ub(0,0,255);glVertex3f(+0.51f,+0.51f,+0.51f);glVertex3f(+0.51f,-0.51f,+0.51f);glVertex3f(+0.51f,-0.51f,-0.51f);glVertex3f(+0.51f,+0.51f,-0.51f);
		glColor3ub(255,255,0);glVertex3f(-0.51f,+0.51f,+0.51f);glVertex3f(-0.51f,+0.51f,-0.51f);glVertex3f(-0.51f,-0.51f,-0.51f);glVertex3f(-0.51f,-0.51f,+0.51f);
		glColor3ub(255,0,255);glVertex3f(-0.51f,+0.51f,+0.51f);glVertex3f(+0.51f,+0.51f,+0.51f);glVertex3f(+0.51f,+0.51f,-0.51f);glVertex3f(-0.51f,+0.51f,-0.51f);
		glColor3ub(0,255,255);glVertex3f(-0.51f,-0.51f,+0.51f);glVertex3f(-0.51f,-0.51f,-0.51f);glVertex3f(+0.51f,-0.51f,-0.51f);glVertex3f(+0.51f,-0.51f,+0.51f);
	}
	glEnd();

	//��������
	glLineWidth (1.0);
	glBegin(GL_LINES);
	{
		//X
		glColor3ub(255, 0, 0);glVertex3f(-1,0,0);glVertex3f(1,0,0);
		glVertex3f(1,0,0);glVertex3f(1-0.05f,0.05f,0);
		glVertex3f(1,0,0);glVertex3f(1-0.05f,-0.05f,0);
		glVertex3f(1,0,0);glVertex3f(1-0.05f,0,0.05f);
		glVertex3f(1,0,0);glVertex3f(1-0.05f,0,-0.05f);
		//Y
		glColor3ub(0, 255, 0);glVertex3f(0,-1,0);glVertex3f(0,1,0);
		glVertex3f(0,1,0);glVertex3f(0.05f,1-0.05f,0);
		glVertex3f(0,1,0);glVertex3f(-0.05f,1-0.05f,0);
		glVertex3f(0,1,0);glVertex3f(0,1-0.05f,0.05f);
		glVertex3f(0,1,0);glVertex3f(0,1-0.05f,-0.05f);
		//Z
		glColor3ub(0, 0, 255);glVertex3f(0,0,-1);glVertex3f(0,0,1);
		glVertex3f(0,0,1);glVertex3f(0.05f,0,1-0.05f);
		glVertex3f(0,0,1);glVertex3f(-0.05f,0,1-0.05f);
		glVertex3f(0,0,1);glVertex3f(0,0.05f,1-0.05f);
		glVertex3f(0,0,1);glVertex3f(0,-0.05f,1-0.05f);
	}
	glEnd();

	glFlush();
	SwapBuffers(hDC);
}

//��Ϣ������
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static struct tagPOINT MousePosNow,MousePosStart;	//��¼��굥��ʱ��λ��
	static GLfloat rotx,roty,rotz;						//��¼ͼ���ƶ�����ת����
	static int isLButtonDown=0;							//��¼�������Ƿ���
	switch (uMsg)
	{
		case WM_TIMER:
			DrawGLScene(rotx,roty,rotz);
			return 0;

		case WM_MOUSEMOVE:
			if(isLButtonDown)
			{
				GetCursorPos(&MousePosNow);
				rotx+=MousePosStart.x-MousePosNow.x;
				roty+=MousePosStart.y-MousePosNow.y;
				MousePosStart.x=MousePosNow.x;
				MousePosStart.y=MousePosNow.y;
			}
			return 0;

		case WM_LBUTTONDOWN:
			if (!isLButtonDown)SetCapture(hWnd);
			GetCursorPos(&MousePosStart);
			isLButtonDown=1;
			return 0;

		case WM_LBUTTONUP:
			if (isLButtonDown)SetCapture (NULL);
			isLButtonDown=0;
			return 0;

		case WM_MOUSEWHEEL:
			rotz+=(float)((short)HIWORD(wParam))/0xff;
			return 0;

		//�öδ��������ڴ��ڴ�С�ı�ʱ�������þ������
		//�˶δ���ͬʱ���д��ڴ���ʱ��ʼ����ز��������ã����Ա����������һ�Σ������ʲôҲ������
		case WM_SIZE:							
		{
			float temp;

			//���������ӿڣ�ʹ����������
			glViewport(0,0,LOWORD(lParam),HIWORD(lParam));

			//��������ͶӰ����
			//�ö������Ǽ������ʹ�ӿ���������ԭ�㣬�Ա�֤���������Ǵ�����Ұ����
			if(LOWORD(lParam)<HIWORD(lParam))	
				temp=LOWORD(lParam);
			else
				temp=HIWORD(lParam);
			temp=0.04f/temp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//����ͶӰ����Ҳ������glu.h�е�gluPerspective()
			glFrustum (-LOWORD(lParam)*temp, LOWORD(lParam)*temp, 
						-HIWORD(lParam)*temp, HIWORD(lParam)*temp,
						0.1f, 100.0f);
			glTranslatef(0.0f,0.0f,-3.0f);

			//�ص�ģ�͹۲����
			glMatrixMode (GL_MODELVIEW);

			return 0;
		}

		case WM_CREATE:
			SetTimer(hWnd, 1, 20, NULL);
			return 0;

		case WM_CLOSE:
			KillTimer(hWnd,1);
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,
					HINSTANCE	hPrevInstance,
					LPSTR		lpCmdLine,
					int			nCmdShow)
{
	MSG			msg;

	hInstance = GetModuleHandle(NULL);

	//ע�ᴰ����
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= "OpenGL";
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "RegisterClass() ʧ��!", "����", MB_OK);
		return 0;
	}

	//��������
	hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	//��չ������ʽ
						"OpenGL",				//��������
						"OpenGL Win32 Sample",	//���ڱ���
						WS_OVERLAPPEDWINDOW |WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//������ʽ��������Ϊ������
						0, 0, 400, 300,			// ����λ�ü���С
						NULL,					// �����ھ��������Ҫ
						NULL,					// �˵����������Ҫ
						hInstance,				// ����ʵ�����
						NULL);					// �������ݣ�����Ҫ
	if (hWnd == NULL)
	{
		MessageBox(hWnd,"CreateWindowEx() ʧ��!","����",MB_OK);
		return 0;
	}
	hDC = GetDC(hWnd);

	//�������ظ�ʽ
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize		= sizeof(pfd);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 32;
	pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0)
	{
		MessageBox(NULL, "ChoosePixelFormat() ʧ��! ", "����", MB_OK); 
		return 0;
	} 
	if (SetPixelFormat(hDC, pf, &pfd) == FALSE)
	{
		MessageBox(NULL, "SetPixelFormat() ʧ��! ", "����", MB_OK);
		return 0;
	}
	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//����OpenGL��Ⱦ����hRC
	hRC = wglCreateContext(hDC);

	//���õ�ǰ�̵߳�Ĭ����Ⱦ����ΪhRC��
	//һ����Ⱦ����ͬһʱ��ֻ�ܱ�һ���߳���ռ�ã�
	//��������Ƕ��߳���Ⱦ����������Ⱦ��ʼʱ�ڸ�����Ⱦ���Ǹ��߳��е��øú�����
	//��NULL����������ȡ��ռ�á�
	wglMakeCurrent(hDC, hRC);

	//����OpenGL��Ⱦģʽ
	glShadeModel(GL_SMOOTH);							// ������ɫģʽΪƽ����ɫ
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// ���ñ���Ϊ��ɫ
	glClearDepth(1.0f);									// ����glClear()�������ȣ�1.0Ϊȫ�����
	glEnable(GL_DEPTH_TEST);							// ���þ������
	glDepthFunc(GL_LEQUAL);								// ���þ������ģʽΪ����С�ڻ����ʱ��Ⱦ
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����͸���㷨����Ϊ���

	ShowWindow(hWnd, nCmdShow);

	//��Ϣѭ��
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//����
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);

	return (msg.wParam);
}
