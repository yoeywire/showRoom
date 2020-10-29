#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "wx/wx.h"
#include "../Engine/RgbEngine.h"

class main : public wxFrame
{
public:
	main(RgbEngine* engine);

	wxButton* m_btn1 = nullptr;
	wxButton* m_btn2 = nullptr;
	wxButton* m_btn3 = nullptr;

	wxSlider* sld1 = nullptr;
	wxSlider* sld2 = nullptr;
	wxSlider* sld3 = nullptr;
	wxSlider* sld4 = nullptr;

	//wxTextCtrl* m_txt1 = nullptr;
	//wxListBox* m_list1 = nullptr;

	void OnButtonClicked(wxCommandEvent& evt);
	void sliderChange(wxCommandEvent& evt);
	void printLn(std::string line);


	wxDECLARE_EVENT_TABLE();

private:
	RgbEngine* rgbEngine = nullptr;
};
