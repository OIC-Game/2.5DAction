#pragma once

#include	"Mof.h"

class CWindowProc : public CDefWindowProc {
public:
	CWindowProc();
	virtual ~CWindowProc();
	virtual MofProcResult WindowProc(MofWindowHandle hWnd, MofUInt msg, MofProcParamW wpar, MofProcParamL lpar);
};