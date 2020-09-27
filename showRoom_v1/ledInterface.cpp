#include "ledInterface.h"

wxIMPLEMENT_APP(ledInterface);

bool ledInterface::OnInit() {

	m_frame1 = new main();
	m_frame1->Show();

	return true;
}