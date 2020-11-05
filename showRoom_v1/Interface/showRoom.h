#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "main.h"
#include "EffectWindow.h"
#include "../Engine/MainEngine.h"


class showRoom : public wxApp
{
public:
	virtual bool OnInit();

private:
	MainEngine* rgbEngine = new MainEngine;

	main* mainFrame = nullptr;
	EffectWindow* effectFrame = nullptr;
};

