#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include <wx/grid.h>
#include "../Engine/MainEngine.h"

class EffectWindow : public wxFrame
{
public:
	EffectWindow(MainEngine* engine);

	wxChoice* attrBox = nullptr;
	wxChoice* formBox = nullptr;
	wxChoice* dirBox = nullptr;
	wxStaticText* attrTxt = nullptr;
	wxStaticText* formTxt = nullptr;
	wxStaticText* dirTxt = nullptr;

	wxTextCtrl* speedVal = nullptr;
	wxTextCtrl* rateVal = nullptr;
	wxTextCtrl* groupsVal = nullptr;
	wxStaticText* speedTxt = nullptr;
	wxStaticText* rateTxt = nullptr;
	wxStaticText* groupsTxt = nullptr;

	wxStaticText* highTxt = nullptr;
	wxStaticText* lowTxt = nullptr;
	wxStaticText* dutyTxt = nullptr;
	wxTextCtrl* highVal = nullptr;
	wxTextCtrl* lowVal = nullptr;
	wxTextCtrl* dutyVal = nullptr;

	void TextValueChanged(wxCommandEvent& evt);
	void ChoiceValueChanged(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
	

private:
	MainEngine* engine = nullptr;
};

