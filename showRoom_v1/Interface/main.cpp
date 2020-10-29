#include "main.h"

wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
EVT_BUTTON(10002, OnButtonClicked)
EVT_BUTTON(10003, OnButtonClicked)
EVT_SLIDER(10101, sliderChange)
EVT_SLIDER(10102, sliderChange)
EVT_SLIDER(10103, sliderChange)
EVT_SLIDER(10104, sliderChange)
wxEND_EVENT_TABLE()



main::main(RgbEngine* engine) : wxFrame(nullptr, wxID_ANY, "ShowRoom Main Window", wxPoint(20, 150), wxSize(510, 400))
{
	rgbEngine = engine;

	m_btn1 = new wxButton(this, 10001, "Static Color", wxPoint(10, 10), wxSize(150, 90));
	m_btn2 = new wxButton(this, 10002, "Rainbow", wxPoint(170, 10), wxSize(150, 90));
	m_btn3 = new wxButton(this, 10003, "Effect", wxPoint(330, 10), wxSize(150, 90));

	sld1 = new wxSlider(this, 10101, 255, 0, 255, wxPoint(10, 120), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld2 = new wxSlider(this, 10102, 255, 0, 255, wxPoint(10, 180), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld3 = new wxSlider(this, 10103, 255, 0, 255, wxPoint(10, 240), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld4 = new wxSlider(this, 10104, 255, 0, 255, wxPoint(10, 300), wxSize(475, 15), wxSL_VALUE_LABEL);

	//m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	//m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));

	wxLog* logger = new wxLogStream();
	wxLog::SetActiveTarget(logger);
}



void main::OnButtonClicked(wxCommandEvent& evt)
{
	int buttonId = evt.GetId();
	//wxLogDebug("<main frame> Button %d pressed", buttonId);

	rgbEngine->inputBtnChange(buttonId);
	evt.Skip();
}



void main::sliderChange(wxCommandEvent& evt) {
	//wxLogDebug("<main frame> Slider changed, value: %d", evt.GetInt());
	rgbEngine->inputSldChange(evt.GetId(), evt.GetInt());
}



void main::printLn(std::string line) {
	//m_list1->AppendString(line);
}