#include "cMain.h"
#include<wx/grid.h>
#include<wx/button.h>
#include<wx/gbsizer.h>
#include<wx/choice.h>

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "PATH FINDING", wxPoint(0, 0), wxSize(1280, 800))
{
	this->SetBackgroundColour(wxColour("MEDIUM AQUAMARINE"));
	V = 40;
	g.setVertices(V);
	g.fillGrid();
	sourceX = sourceY = destinationX = destinationY = -1;
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	grid = new wxGrid(this, wxID_ANY, wxPoint(100, 100), wxSize(600, 0));
	grid->CreateGrid(V, V);
	grid->HideColLabels();
	grid->HideRowLabels();
	grid->SetDefaultColSize(1, true);
	grid->SetDefaultCellBackgroundColour(wxColour("PINK"));
	sizer->Add(grid, 1, wxALIGN_CENTER);
	//grid->FitInside();
	this->SetSizer(sizer);
	//grid->DisableCellEditControl();
	//grid->DisableColResize()
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			grid->SetReadOnly(i, j);
		}
	}
	grid->SetGridLineColour(wxColour("Black"));
	grid->DisableDragColSize();
	grid->DisableDragRowSize();
	grid->ShowScrollbars(wxSHOW_SB_NEVER, wxSHOW_SB_NEVER);
	wxString algos[2] = { wxT("A*"),wxT("Dijkstra") };
	box = new wxChoice(this, wxID_ANY, wxPoint(30, 100), wxSize(100, 50), 2, algos, 2, wxDefaultValidator, "Algo");
	box->SetSelection(0);
	wxButton* btn1 = new wxButton(this, wxID_ANY, "Start", wxPoint(30, 200), wxSize(100, 50), 0, wxDefaultValidator, "1");
	wxButton* btn2 = new wxButton(this, wxID_ANY, "Reset", wxPoint(30, 300), wxSize(100, 50), 0, wxDefaultValidator, "2");
	wxButton* btn3 = new wxButton(this, wxID_ANY, "Generate Maze", wxPoint(1100, 200), wxSize(100, 50), 0, wxDefaultValidator, "3");
	wxButton* btn4 = new wxButton(this, wxID_ANY, "Help", wxPoint(1100, 300), wxSize(100, 50), 0, wxDefaultValidator, "4");
	btn1->SetBackgroundColour(wxColour("YELLOW"));
	btn2->SetBackgroundColour(wxColour("MAGENTA"));
	btn3->SetBackgroundColour(wxColour("YELLOW"));
	btn4->SetBackgroundColour(wxColour("MAGENTA"));
	checkBox = new wxCheckBox(this, wxID_ANY, "MAX SPEED", wxPoint(1100, 100), wxSize(100, 50), 0, wxDefaultValidator);
	btn1->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::Start, this);
	btn2->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::Reset, this);
	btn3->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::Maze, this);
	btn4->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::Help, this);
	this->SetMinSize(wxSize(1280, 800));
	this->SetMaxSize(wxSize(1280, 800));
	this->SetSizer(sizer);
	grid->Bind(wxEVT_GRID_CELL_LEFT_CLICK, &cMain::LeftClick, this);
	grid->Bind(wxEVT_GRID_CELL_RIGHT_CLICK, &cMain::RightClick, this);
	checkBox->Bind(wxEVT_CHECKBOX, &cMain::Speed, this);
	txt = new wxStaticText(this, wxID_ANY, "", wxPoint(940, 400), wxSize(100, 100), 0);
	wxFont t_Font = txt->GetFont();
	t_Font.SetFamily(wxFONTFAMILY_MODERN);
	t_Font.SetPointSize(14);
	txt->SetFont(t_Font);
	txt->SetForegroundColour(wxColour("RED"));
}

void cMain::RightClick(wxGridEvent& evt) {
	// Destination Node
	txt->SetLabelText("");
	if (destinationX != -1 && destinationY != -1)
		grid->SetCellBackgroundColour(destinationX, destinationY, wxColour("PINK"));
	destinationX = evt.GetRow();
	destinationY = evt.GetCol();
	if (g.getEdge(destinationX, destinationY) == 0)
	{
		txt->SetLabelText("OBSTACLE CAN'T BE\nSOURCE/DESTINATION");
		evt.Skip();
		return;
	}
	grid->SetCellBackgroundColour(destinationX, destinationY, wxColour("BLACK"));
	this->Refresh();
	evt.Skip();
}

void cMain::LeftClick(wxGridEvent& evt) {
	// Source Node
	txt->SetLabelText("");
	int tempX = evt.GetRow();
	int tempY = evt.GetCol();
	if (evt.ControlDown())
	{
		grid->SetCellBackgroundColour(tempX, tempY, wxColour("RED"));
		grid->ForceRefresh();
		grid->Update();
		g.insertEdge(tempX, tempY, 0);
		//evt.Skip();
		return;
	}
	sourceX = tempX;
	sourceY = tempY;
	if (sourceX != -1 && sourceY != -1)		//removing previous selection
		grid->SetCellBackgroundColour(sourceX, sourceY, wxColour("PINK"));
	grid->SetCellBackgroundColour(sourceX, sourceY, wxColour("PURPLE"));
	this->Refresh();
	evt.Skip();
	//
}

void cMain::Start(wxCommandEvent& evt)
{
	if (sourceX == -1 || destinationX == -1)
	{
		txt->SetLabelText("NO SOURCE/DESTINATION FOUND!");
		evt.Skip();
		return;
	}
	int i = box->GetSelection();
	evt.Skip();
	bool res;
	if (i == 0)
		res = g.A_star(grid, sourceX, sourceY, destinationX, destinationY);
	else
		res = g.dijkstra(grid, sourceX, sourceY, destinationX, destinationY);
	if (!(res))
		txt->SetLabelText("NO PATH!");
}
void cMain::Reset(wxCommandEvent& evt)
{
	g.fillGrid();
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			grid->SetCellBackgroundColour(i, j, wxColour("PINK"));
		}
	}
	sourceX = sourceY = destinationX = destinationY = -1;
	this->Refresh();
}
void cMain::Maze(wxCommandEvent& evt)
{
	sourceX = sourceY = destinationX = destinationY = -1;
	g.fillGrid();		//resetting initial grid
	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			grid->SetCellBackgroundColour(i, j, wxColour("PINK"));
		}
	}
	evt.Skip();
	g.kruskal(grid);
	this->Refresh();
}
void cMain::Speed(wxCommandEvent& evt)
{
	g.instant = checkBox->GetValue();
	if (g.instant)
		checkBox->SetValue(true);
	else
		checkBox->SetValue(false);
	evt.Skip();
}
void cMain::Help(wxCommandEvent& evt)
{
	txt->SetLabelText("SET SOURCE: LEFT CLICK\nSET DESTINATION: RIGHT CLICK\nSET OBSTACLE: CTRL+LEFT CLICK\nBEGIN: PRESS START");
	evt.Skip();
}