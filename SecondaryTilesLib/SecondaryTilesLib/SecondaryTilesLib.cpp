// SecondaryTilesLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "ShObjIdl.h"
#include "ROApi.h"
#include "SecondaryTilesLib.h"

#include <string>
#include <experimental\resumable>
#include <pplawait.h>
#include <future>
#include <sstream>

using namespace std;
using namespace Windows::Foundation;
using namespace Windows::System;
using namespace Windows::UI::StartScreen;
using namespace Windows::UI::Notifications;
using namespace Windows::Data::Xml::Dom;


const wstring msAppx = L"ms-appx:///";
const wstring msData = L"ms-appdata:///";

void SecondaryTiles::Test(HWND hWnd)
{
	IInitializeWithWindow* pIInitializeWithWindow;

	auto square150x150Logo = ref new Uri("ms-appx:///images/Square150x150Logo.png");

	Platform::String ^id = "Bridge-2";
	Platform::String ^title = "Bridge Sec";
	Platform::String ^args = "launchme";

	auto secondaryTile = ref new SecondaryTile(id,
		title,
		args,
		square150x150Logo,
		Windows::UI::StartScreen::TileSize::Square150x150);

	secondaryTile->VisualElements->ShowNameOnSquare150x150Logo = true;

	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(secondaryTile);
	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);

		secondaryTile->RequestCreateAsync();
	}

	MessageBox(NULL, NULL, NULL, NULL);

	return;
}


Platform::String^ ToPlatformString(wstring str)
{
	return ref new Platform::String(str.c_str());
}

Uri^ GetUriSafe(wstring uriString)
{
	if (uriString.empty() || (uriString.find(msAppx, 0) != 0 && uriString.find(msData, 0) != 0))
	{
		return ref new Uri(ToPlatformString(L"ms-appx:///"));
	}
	else
	{
		return ref new Uri(ToPlatformString(uriString));
	}
}

Windows::UI::Color HexToUIColor(string hexCode)
{
	if (hexCode.at(0) == '#') {
		hexCode = hexCode.erase(0, 1);
	}

	int r, g, b;

	std::istringstream(hexCode.substr(0, 2)) >> std::hex >> r;
	std::istringstream(hexCode.substr(2, 2)) >> std::hex >> g;
	std::istringstream(hexCode.substr(4, 2)) >> std::hex >> b;

	return Windows::UI::ColorHelper::FromArgb(255, r, g, b);
}

std::future<void> RequestCreateInternalAsync(HWND hWnd, SecondaryTile ^secondaryTile)
{
	IInitializeWithWindow* pIInitializeWithWindow;
	IInspectable* iInspectable = reinterpret_cast<IInspectable*>(secondaryTile);

	if (SUCCEEDED(iInspectable->QueryInterface(IID_PPV_ARGS(&pIInitializeWithWindow))))
	{
		pIInitializeWithWindow->Initialize((HWND)(void *)hWnd);

		co_await secondaryTile->RequestCreateAsync();

		pIInitializeWithWindow->Release();
	}
}

std::future<void> SecondaryTiles::RequestCreateAsync(HWND hWnd, wstring tileId, wstring displayName, wstring arguments, wstring squareLogo150x150Uri, TileSize desiredSize)
{
	auto secondaryTile = ref new SecondaryTile(
		ToPlatformString(tileId),
		ToPlatformString(displayName),
		ToPlatformString(arguments),
		GetUriSafe(squareLogo150x150Uri),
		(Windows::UI::StartScreen::TileSize)desiredSize);

	co_await RequestCreateInternalAsync(hWnd, secondaryTile);
}

std::future<void> SecondaryTiles::RequestCreateAsync(HWND hWnd, wstring tileId, wstring displayName, wstring arguments, wstring squareLogo150x150Uri, TileSize desiredSize, TileOptions options)
{
	auto secondaryTile = ref new SecondaryTile(
		ToPlatformString(tileId),
		ToPlatformString(displayName),
		ToPlatformString(arguments),
		GetUriSafe(squareLogo150x150Uri),
		(Windows::UI::StartScreen::TileSize)desiredSize);

	secondaryTile->RoamingEnabled = options.RoamingEnabled;

	if (options.LockScreenBadgeLogo.find(msAppx, 0) == 0 || options.LockScreenBadgeLogo.find(msData, 0) == 0)
	{
		secondaryTile->LockScreenBadgeLogo = GetUriSafe(options.LockScreenBadgeLogo);
	}
	
	secondaryTile->LockScreenDisplayBadgeAndTileText = options.LockScreenDisplayBadgeAndTileText;

	if (options.Square30x30Logo.find(msAppx, 0) == 0 || options.Square30x30Logo.find(msData, 0) == 0)
	{
		secondaryTile->VisualElements->Square30x30Logo = GetUriSafe(options.Square30x30Logo);
	}

	if (options.Square310x310Logo.find(msAppx, 0) == 0 || options.Square310x310Logo.find(msData, 0) == 0)
	{
		secondaryTile->VisualElements->Square310x310Logo = GetUriSafe(options.Square310x310Logo);
	}

	if (options.Square44x44Logo.find(msAppx, 0) == 0 || options.Square44x44Logo.find(msData, 0) == 0)
	{
		secondaryTile->VisualElements->Square44x44Logo = GetUriSafe(options.Square44x44Logo);
	}

	if (options.Square70x70Logo.find(msAppx, 0) == 0 || options.Square70x70Logo.find(msData, 0) == 0)
	{
		secondaryTile->VisualElements->Square70x70Logo = GetUriSafe(options.Square70x70Logo);
	}

	if (options.Wide310x150Logo.find(msAppx, 0) == 0 || options.Wide310x150Logo.find(msData, 0) == 0)
	{
		secondaryTile->VisualElements->Wide310x150Logo = GetUriSafe(options.Wide310x150Logo);
	}

	secondaryTile->VisualElements->ShowNameOnSquare150x150Logo = options.ShowNameOnSquare150x150Logo;
	secondaryTile->VisualElements->ShowNameOnWide310x150Logo = options.ShowNameOnWide310x150Logo;
	secondaryTile->VisualElements->ShowNameOnSquare310x310Logo = options.ShowNameOnSquare310x310Logo;

	if (options.BackgroundColor.length() >= 6)
	{
		secondaryTile->VisualElements->BackgroundColor = HexToUIColor(options.BackgroundColor);
	}
	secondaryTile->VisualElements->ForegroundText = (Windows::UI::StartScreen::ForegroundText)options.ForegroundText;
	co_await RequestCreateInternalAsync(hWnd, secondaryTile);
}

bool SecondaryTiles::SecondaryTileExists(wstring tileId)
{
	return SecondaryTile::Exists(ToPlatformString(tileId));
}

std::future<void> SecondaryTiles::RequestDeleteAsync(wstring tileId)
{
	auto secondaryTile = ref new SecondaryTile(ToPlatformString(tileId));
	co_await secondaryTile->RequestDeleteAsync();
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void SecondaryTiles::Update(wstring tileId)
{

	Platform::String^ myxml = 
L"<tile><visual><binding template = \"TileSmall\"> \
<text hint-style = \"caption\">Jennifer Parker</text>\
</binding>\
<binding template = \"TileMedium\">\
<text hint-style = \"caption\">Jennifer Parker</text>\
</binding>\
<binding template = \"TileWide\">\
<text hint-style = \"caption\">Jennifer Parker</text>\
</binding>\
<binding template = \"TileLarge\">\
<text hint-style = \"caption\">Jennifer Parker</text>\
</binding>\
</visual>\
</tile>";

	auto tileXml = ref new XmlDocument(); 
	tileXml->LoadXml(myxml);

	TileNotification^ tileNotification = ref new TileNotification(tileXml);
	auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(ToPlatformString(tileId));

	// this call fails :(
	updater->Update(tileNotification);	
}

