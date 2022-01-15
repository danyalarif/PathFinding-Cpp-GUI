#pragma once
// HEADER FILE
#include "wx/wx.h"
#include "cMain.h"
class cApp : public wxApp // INTERITS 
{
public:
	cApp(); // CONST
	~cApp(); // DESC
private:
	cMain* m_frame1 = nullptr; // FRAME PTR

public:
	virtual bool OnInit(); // FN CALL TO SHOW WINDOWS, IT IS ALWAYS TRUE
};
