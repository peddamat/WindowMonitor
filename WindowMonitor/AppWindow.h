#pragma once
#include "CWindow.h"
#include "AppWindowAcceleratorHandler.h"
#include "AppWindowCursorHandler.h"
#include "AppWindowMenuHandler.h"
#include "WindowMonitorObserver.h"
#include "DwmThumbnail.h"
#include "PresetWindow.h"
#include "EventHookHandler.h"

class WindowMonitor;

class AppWindow : public CWindow, public WindowMonitorObserver, public EventHookHandler
{
public:
	AppWindow(WindowMonitor * const windowMonitor, PresetWindow * const presetWindow);
	void ToggleBorder();
	void ToggleFullscreen();
	void ToggleClickThrough();
	void ShowPresetWindow();
	inline bool IsBorderVisible() { return borderVisible; }
	inline bool IsFullscreen() { return fullScreen; }
	void OnWindowMonitorEvent(WindowMonitorEvent const & event);
	static const COLORREF BackgroundColour;
	virtual void OnEventHookTriggered(DWORD const & event, HWND const & hwnd, LONG const & obj, LONG const & child) override;

protected:
	virtual LRESULT WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	// Events
	AppWindowCursorHandler cursorHandler;
	AppWindowAcceleratorHandler acceleratorhandler;
	AppWindowMenuHandler menuHandler;
	bool OnMouseMove(WPARAM const & wParam, LPARAM const & lParam);
	bool OnSizing(WPARAM const & wParam, LPARAM const & lParam);
	void OnCreate();
	void OnDestroy();

	// Methods
	void UpdateWindow();
	void CenterWindow();

	// Vars
	DwmThumbnail adjustableThumbnail;
	POINTS lastPos;
	int chromeWidth, chromeHeight;
	bool wasSizing, borderVisible, fullScreen;
	WindowMonitor * windowMonitor;
	PresetWindow * presetWindow;
	HWND hookedSource;
};