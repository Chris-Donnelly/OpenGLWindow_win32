#include "OpenGLWindow.h"

#pragma comment (lib, "OpenGL32.lib")

COpenGLWindow::COpenGLWindow(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, std::wstring title, LOGICFUNC callback) 
	: CWindow(xPos, yPos, width, height, title, callback), m_hRC(0), m_hDC(::GetDC(m_Hwnd)), m_displayRefresh(GetRefreshRate())
{
	if (!InitRenderer())
	{
		::MessageBox(m_Hwnd, L"Failed to Initialize renderer", L"Error", MB_ICONERROR);
	}
	SetRenderDefaults();
}

COpenGLWindow::~COpenGLWindow()
{
	ShutdownRenderer();
}

bool COpenGLWindow::InitRenderer()
{
	return (SetPF() && (m_hRC = ::wglCreateContext(m_hDC)) != nullptr && ::wglMakeCurrent(m_hDC, m_hRC));
}

bool COpenGLWindow::ShutdownRenderer()
{
	::ReleaseDC(m_Hwnd, m_hDC);
	::wglMakeCurrent(nullptr, nullptr);
	::wglDeleteContext(m_hRC);
	::DeleteDC(m_hDC);
	return true;
}

void COpenGLWindow::PostRender()
{
	// nothing to implement here
}

bool COpenGLWindow::SetPF()
{
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	return ::SetPixelFormat(m_hDC, ::ChoosePixelFormat(m_hDC, &pfd), &pfd);
}

void COpenGLWindow::SetRenderDefaults()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glDepthMask(false);
}

float COpenGLWindow::GetRefreshRate(float defaultRefresh)
{
	float refresh = defaultRefresh;

	MONITORINFOEX monInfo;
	std::memset(&monInfo, 0, sizeof(MONITORINFOEX));
	monInfo.cbSize = sizeof(MONITORINFOEX);

	if (::GetMonitorInfo(::MonitorFromWindow(m_Hwnd, MONITOR_DEFAULTTOPRIMARY), &monInfo))
	{
		DEVMODE devMode;
		std::memset(&devMode, 0, sizeof(DEVMODE));
		devMode.dmSize = sizeof(DEVMODE);

		::EnumDisplaySettings(monInfo.szDevice, ENUM_CURRENT_SETTINGS, &devMode);
		refresh = static_cast<float>(devMode.dmDisplayFrequency);
	}

	return refresh;
}
