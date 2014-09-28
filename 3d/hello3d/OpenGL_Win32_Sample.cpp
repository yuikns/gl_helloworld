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

//渲染一帧
void DrawGLScene(GLfloat rotx, GLfloat roty, GLfloat rotz)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// 清除旧画面及景深缓存
	glLoadIdentity();										// 重置模型观察矩阵
	glTranslatef(0.0f,0.0f,rotz);							// 顺着Z轴偏移rotz
	glRotatef(-roty,1.0f,0.0f,0.0f);						// 绕X轴旋转roty
	glRotatef(-rotx,0.0f,1.0f,0.0f);						// 绕Y轴旋转rotx

	//画正方体
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

	//画坐标轴
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

//消息处理函数
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static struct tagPOINT MousePosNow,MousePosStart;	//记录鼠标单击时的位置
	static GLfloat rotx,roty,rotz;						//记录图像移动、旋转参数
	static int isLButtonDown=0;							//记录鼠标左键是否按下
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

		//该段代码用来在窗口大小改变时重新设置矩阵参数
		//此段代码同时具有窗口创建时初始化相关参数的作用，所以必须调用至少一次，否则会什么也看不到
		case WM_SIZE:							
		{
			float temp;

			//重新设置视口，使其填满窗口
			glViewport(0,0,LOWORD(lParam),HIWORD(lParam));

			//重新设置投影矩阵
			//该段作用是计算参数使视口正对坐标原点，以保证正方体总是处于视野中央
			if(LOWORD(lParam)<HIWORD(lParam))	
				temp=LOWORD(lParam);
			else
				temp=HIWORD(lParam);
			temp=0.04f/temp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			//设置投影矩阵，也可以用glu.h中的gluPerspective()
			glFrustum (-LOWORD(lParam)*temp, LOWORD(lParam)*temp, 
						-HIWORD(lParam)*temp, HIWORD(lParam)*temp,
						0.1f, 100.0f);
			glTranslatef(0.0f,0.0f,-3.0f);

			//回到模型观察矩阵
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

	//注册窗口类
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
		MessageBox(NULL, "RegisterClass() 失败!", "错误", MB_OK);
		return 0;
	}

	//创建窗口
	hWnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	//扩展窗口样式
						"OpenGL",				//窗口类名
						"OpenGL Win32 Sample",	//窗口标题
						WS_OVERLAPPEDWINDOW |WS_CLIPSIBLINGS | WS_CLIPCHILDREN,//窗口样式，后两项为必须项
						0, 0, 400, 300,			// 窗口位置及大小
						NULL,					// 父窗口句柄，不需要
						NULL,					// 菜单句柄，不需要
						hInstance,				// 进程实例句柄
						NULL);					// 额外数据，不需要
	if (hWnd == NULL)
	{
		MessageBox(hWnd,"CreateWindowEx() 失败!","错误",MB_OK);
		return 0;
	}
	hDC = GetDC(hWnd);

	//设置像素格式
	memset(&pfd, 0, sizeof(pfd));
	pfd.nSize		= sizeof(pfd);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 32;
	pf = ChoosePixelFormat(hDC, &pfd);
	if (pf == 0)
	{
		MessageBox(NULL, "ChoosePixelFormat() 失败! ", "错误", MB_OK); 
		return 0;
	} 
	if (SetPixelFormat(hDC, pf, &pfd) == FALSE)
	{
		MessageBox(NULL, "SetPixelFormat() 失败! ", "错误", MB_OK);
		return 0;
	}
	DescribePixelFormat(hDC, pf, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	//创建OpenGL渲染环境hRC
	hRC = wglCreateContext(hDC);

	//设置当前线程的默认渲染环境为hRC，
	//一个渲染环境同一时间只能被一个线程所占用，
	//所以如果是多线程渲染，必须在渲染开始时在负责渲染的那个线程中调用该函数，
	//以NULL参数调用则取消占用。
	wglMakeCurrent(hDC, hRC);

	//设置OpenGL渲染模式
	glShadeModel(GL_SMOOTH);							// 设置着色模式为平滑着色
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// 设置背景为黑色
	glClearDepth(1.0f);									// 设置glClear()的清除深度，1.0为全部清除
	glEnable(GL_DEPTH_TEST);							// 启用景深测试
	glDepthFunc(GL_LEQUAL);								// 设置景深测试模式为景深小于或相等时渲染
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 设置透视算法精度为最高

	ShowWindow(hWnd, nCmdShow);

	//消息循环
	while(GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//清理
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
	DestroyWindow(hWnd);

	return (msg.wParam);
}
