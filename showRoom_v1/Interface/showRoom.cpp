#include "showRoom.h"

wxIMPLEMENT_APP(showRoom);

bool showRoom::OnInit() {

	mainFrame = new main(rgbEngine);
	mainFrame->Show();

	effectFrame = new EffectWindow(rgbEngine);
	effectFrame->Show();

	return true;
}