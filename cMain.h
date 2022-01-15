#pragma once
#include "wx/wx.h"
#include "Graph.h"
#include<wx/grid.h>
#include<wx/choice.h>
class cMain : public wxFrame
{
public:
	cMain();
public:
	wxGrid* grid;
	int V;
	wxChoice* box;
	Graph g;
	int sourceX;
	int sourceY;
	int destinationY;
	int destinationX;
	wxCheckBox* checkBox;
	wxStaticText* txt;
	void Start(wxCommandEvent& evt);
	void Reset(wxCommandEvent& evt);
	void Maze(wxCommandEvent& evt);
	void RightClick(wxGridEvent& evt);
	void LeftClick(wxGridEvent& evt);
	void Speed(wxCommandEvent& evt);
	void Help(wxCommandEvent& evt);
};
