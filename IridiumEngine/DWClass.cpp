#include "stdafx.h"
#include "Engine/Graphics/UI/Text/DWClass.h"

using namespace Microsoft::WRL;


DWClass::DWClass()
{
}

DWClass::~DWClass()
{
}

bool DWClass::Initialize()
{
	//Create the DirectWrite factory object
	HRESULT result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), &factory);
	if (FAILED(result))
		return false;



	return true;
}
