#include "stdafx.h"
#include "Engine/Graphics/UI/Text/DWClass.h"

using namespace Microsoft::WRL;

#include <sstream>

DWClass::DWClass()
{
	yellowBrush = nullptr;
	textFormatFPS = nullptr;
	textLayoutFPS = nullptr;
}

DWClass::~DWClass()
{
}

bool DWClass::Initialize(ComPtr<ID2D1DeviceContext> _D2DDeviceContext)
{
	//Create the DirectWrite factory object
	HRESULT result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), &factory);
	if (FAILED(result))
		return false;


	//Create the standard brushes
	result = _D2DDeviceContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &yellowBrush);
	if (FAILED(result))
		return false;

	//Setup text formats
	result = factory->CreateTextFormat(L"Lucida Console", nullptr, DWRITE_FONT_WEIGHT_LIGHT, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 32.0f, L"en-GB", &textFormatFPS);
	if (FAILED(result))
		return false;

	result = textFormatFPS->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(result))
		return false;

	textFormatFPS->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
	if (FAILED(result))
		return false;

	//Create text layout
	std::wostringstream outFPS;
	outFPS.precision(4);
	outFPS << "Hii" << std::endl;

	result = factory->CreateTextLayout(outFPS.str().c_str(), (UINT32)outFPS.str().size(), textFormatFPS.Get(), 500.0f, 500.0f, &textLayoutFPS);
	if (FAILED(result))
		return false;


	

	return true;
}

IDWriteTextLayout* DWClass::GetTextLayout()
{
	return textLayoutFPS.Get();
}

ID2D1SolidColorBrush* DWClass::GetYellowBrush()
{
	return yellowBrush;
}
