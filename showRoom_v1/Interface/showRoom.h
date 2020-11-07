#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "mainWindow.h"
#include "EffectWindow.h"
#include "../Engine/MainEngine.h"


class ShowRoom : public wxApp
{
public:
	virtual bool OnInit();
	~ShowRoom();

private:
	MainEngine* mainEngine = new MainEngine;

	mainWindow* mainFrame = nullptr;
	EffectWindow* effectFrame = nullptr;
};

