#pragma once
#include "Window.h"

#include <GL/gl.h>

class COpenGLWindow : public CWindow
{

public:

	COpenGLWindow(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, std::wstring title, LOGICFUNC callback);
	~COpenGLWindow();

protected:

	virtual bool InitRenderer() override;
	virtual bool ShutdownRenderer() override;
	virtual void PostRender() override;

	virtual void Present() override
	{
		glFlush();
		::SwapBuffers(m_hDC);
	}

	virtual void PreRender() override
	{
		ClearBuffers();
	}

private:

	bool SetPF();
	void SetRenderDefaults();

	inline void ClearBuffers()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	HGLRC           m_hRC;
	HDC             m_hDC;
};
