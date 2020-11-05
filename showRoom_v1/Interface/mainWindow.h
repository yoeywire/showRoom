#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "../Engine/MainEngine.h"

class mainWindow : public wxFrame
{
public:
	mainWindow(MainEngine* engine);

	wxButton* m_btn1 = nullptr;
	wxButton* m_btn2 = nullptr;
	wxButton* m_btn3 = nullptr;

	wxSlider* sld1 = nullptr;
	wxSlider* sld2 = nullptr;
	wxSlider* sld3 = nullptr;
	wxSlider* sld4 = nullptr;

	wxMenuBar* menubar = nullptr;
	wxMenu* fileMenu = nullptr;

	//wxTextCtrl* m_txt1 = nullptr;
	//wxListBox* m_list1 = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);
	void sliderChange(wxCommandEvent& evt);
	void OnQuit(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();

private:
	MainEngine* rgbEngine = nullptr;
};
