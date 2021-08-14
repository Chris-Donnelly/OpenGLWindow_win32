#pragma once

#include <windows.h>
#include <string>
#include "Timer.h"

#define FAIL_CONDITION(condition) if(condition) return false;

using namespace std;

typedef void(*LOGICFUNC) (float);

class CWindow {

	public:

		CWindow(uint32_t xPos, uint32_t yPos, uint32_t width, uint32_t height, std::wstring title, LOGICFUNC callback)
			: m_Width(0), m_Height(0), m_isWindowInitialized(false), m_ExitFlag(false), m_fTimeScale(1.0f), m_Hwnd(0), m_mainTimer{ }, m_logicCallback(callback)
		{
			m_isWindowInitialized = Create(xPos, yPos, width, height, title);
		}

		int Run();

		CWindow(const CWindow&) = delete;
		CWindow& operator=(const CWindow&) = delete;

		inline float GetTimeScale() 
		{ 
			return m_fTimeScale; 
		}

		inline void SetTimeScale(float const ftScale)
		{
			m_fTimeScale = ftScale; 
		}

		inline void Show(bool flag) 
		{ 
			ShowWindow(m_Hwnd, flag); 
		}

		inline const bool IsInitialized () const
		{
			return m_isWindowInitialized;
		}

	protected:

		LRESULT CALLBACK         MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK  MessageRouter(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		bool                     Create(const uint32_t xPos, const uint32_t yPos, const uint32_t winWidth, const uint32_t winHeight, const std::wstring title);

		virtual bool             InitRenderer() = 0;
		virtual bool             ShutdownRenderer() = 0;
		virtual void             PreRender() = 0;
		virtual void             PostRender() = 0;
		virtual void             Present() = 0;

		int        m_Width;
		int        m_Height;
		bool       m_isWindowInitialized;
		bool       m_ExitFlag;
		float      m_fTimeScale;
		HWND       m_Hwnd;
		wstring    m_AppTitle;
		Timer      m_mainTimer;
		LOGICFUNC  m_logicCallback;

		static constexpr DWORD m_WinStyles_Enabled   = { WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW | WS_VISIBLE | CS_HREDRAW | CS_VREDRAW | CS_OWNDC };
		static constexpr DWORD m_WinStyles_Disabled  = { WS_MAXIMIZEBOX | WS_THICKFRAME };
		static constexpr DWORD m_WinStyle            = {  m_WinStyles_Enabled & ~m_WinStyles_Disabled };
};
