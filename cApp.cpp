#include "cApp.h"
#include "wx/wx.h"

wxIMPLEMENT_APP(cApp);

cApp::cApp()
{
	// MAIN
}
cApp:: ~cApp() {
	// DESCTRUCTOR
}
bool cApp::OnInit() {
	// IMPORTANT CODE TO SHOW THE FRAME//
	//
	//m_frame1->Connect(wxID_ABOUT,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MyFrame::OnAbout));
	m_frame1 = new cMain();
	m_frame1->Connect(wxID_EXIT, wxEVT_GRID_CELL_LEFT_CLICK, wxGridEventHandler(cMain::LeftClick));
	m_frame1->Connect(wxID_EXIT, wxEVT_GRID_CELL_RIGHT_CLICK, wxGridEventHandler(cMain::RightClick));
	m_frame1->Show();
	return true;
}
