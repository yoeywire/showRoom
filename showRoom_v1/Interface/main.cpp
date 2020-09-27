#include "main.h"

wxBEGIN_EVENT_TABLE(main, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
EVT_BUTTON(10002, OnButtonClicked)
EVT_BUTTON(10003, OnButtonClicked)
EVT_BUTTON(10004, OnButtonClicked)
EVT_BUTTON(10005, OnButtonClicked)
EVT_SLIDER(10101, sliderChange)
EVT_SLIDER(10102, sliderChange)
wxEND_EVENT_TABLE()

main::main() : wxFrame(nullptr, wxID_ANY, "ledstrip controller interface", wxPoint(480, 150), wxSize(510, 350))
{
	m_btn1 = new wxButton(this, 10001, "RED", wxPoint(10, 10), wxSize(150, 90));
	m_btn2 = new wxButton(this, 10002, "GREEN", wxPoint(170, 10), wxSize(150, 90));
	m_btn3 = new wxButton(this, 10003, "BLUE", wxPoint(330, 10), wxSize(150, 90));
	m_btn4 = new wxButton(this, 10004, "RAINBOW", wxPoint(10, 110), wxSize(230, 90));
	m_btn5 = new wxButton(this, 10005, "STEP", wxPoint(250, 110), wxSize(230, 90));

	sld1 = new wxSlider(this, 10101, 1, 1, 296*2, wxPoint(10, 220), wxSize(475, 15), wxSL_VALUE_LABEL);
	sld2 = new wxSlider(this, 10102, 10, 1, 40, wxPoint(10, 280), wxSize(475, 15), wxSL_VALUE_LABEL);

	//m_txt1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 70), wxSize(300, 30));
	//m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
	
	wxLog* logger = new wxLogStream();
	wxLog::SetActiveTarget(logger);
}



void main::OnButtonClicked(wxCommandEvent& evt)
{
	int buttonId = evt.GetId();
	wxLogDebug("<main frame> Button %d pressed", evt.GetId());

	switch (buttonId) {
	case 10001 :
		rgbEngine.inputBtnChange(0);
		break;
	case 10002:
		rgbEngine.inputBtnChange(1);
		break;
	case 10003:
		rgbEngine.inputBtnChange(2);
		break;	
	case 10004:
		rgbEngine.inputBtnChange(11);
		break;	
	case 10005:
		rgbEngine.inputBtnChange(12);
		break;
	}
	evt.Skip();
}


void main::sliderChange(wxCommandEvent& evt) {
	wxLogDebug("<main frame> Slider changed, value: %d", evt.GetInt());
	rgbEngine.inputSldChange(evt.GetId(), evt.GetInt());
}


void main::printLn(std::string line) {
	//m_list1->AppendString(line);
}