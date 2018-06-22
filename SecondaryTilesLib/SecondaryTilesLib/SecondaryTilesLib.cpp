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

const wstring msAppxW = L"ms-appx:///";
const wstring msDataW = L"ms-appdata:///";

const string msAppx = "ms-appx:///";
const string msData = "ms-appdata:///";

wstring ToWString(string str)
{
	std::wstring ws;
	ws.assign(str.begin(), str.end());
	return	ws.c_str();
}

Platform::String^ ToPlatformString(string str)
{
	std::wstring ws(str.begin(), str.end());
	return ref new Platform::String(ws.c_str());
}

Platform::String^ ToPlatformString(wstring str)
{
	return ref new Platform::String(str.c_str());
}

Platform::String^ ToPlatformString(PCWSTR str)
{
	return ref new Platform::String(str);
}

bool IsValidImageUri(string uriString)
{
	return !uriString.empty() && (uriString.find(msAppx, 0) == 0 || uriString.find(msData, 0) == 0);
}

bool IsValidImageUri(wstring uriString)
{
	return !uriString.empty() && (uriString.find(msAppxW, 0) == 0 || uriString.find(msDataW, 0) == 0);
}

Uri^ GetUriSafe(wstring uriString)
{
	if (!IsValidImageUri(uriString))
	{
		return ref new Uri(ToPlatformString(L"ms-appx:///"));
	}
	else
	{
		return ref new Uri(ToPlatformString(uriString));
	}
}

Uri^ GetUriSafe(string uriString)
{
	if (!IsValidImageUri(uriString))
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

bool IsNotificationSupported()
{
	auto versionStr = Windows::System::Profile::AnalyticsInfo::VersionInfo->DeviceFamilyVersion;

	// convert to char*
	std::wstring w(versionStr->Begin());
	std::string a(w.begin(), w.end());
	const char* charVersionStr = a.c_str();

	unsigned long long v = atoll(charVersionStr);

	unsigned short v1 = (v & 0xFFFF000000000000L) >> 48;
	unsigned short v2 = (v & 0x0000FFFF00000000L) >> 32;
	unsigned short v3 = (v & 0x00000000FFFF0000L) >> 16;
	unsigned short v4 = (v & 0x000000000000FFFFL);

	// Notification were introduced in the FCU. However the API had a bug
	// that was only fixed in 10.0.17134.81
	return v1 > 10 || v2 > 0 || v3 > 17134 || v4 >= 81;
}

Windows::UI::StartScreen::TileSize ToUITileSize(SecondaryTiles::TileSize tilSize)
{
	switch (tilSize)
	{
	case SecondaryTiles::TileSize::Default:
		return Windows::UI::StartScreen::TileSize::Default;
	case SecondaryTiles::TileSize::Square150x150:
		return Windows::UI::StartScreen::TileSize::Square150x150;
	case SecondaryTiles::TileSize::Wide310x150:
		return Windows::UI::StartScreen::TileSize::Wide310x150;
	default:
		throw new invalid_argument("Unknown tile size");
	}
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

	auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(secondaryTile->TileId);
	updater->EnableNotificationQueue(true);
}

SecondaryTile^ CreateTile(string tileId, PCWSTR displayName, string arguments, string squareLogo150x150Uri, bool showNameOnSquare150x150Logo, bool roamingEnabled)
{
	auto secondaryTile = ref new SecondaryTile(
		ToPlatformString(tileId),
		ToPlatformString(displayName),
		ToPlatformString(arguments),
		GetUriSafe(squareLogo150x150Uri),
		ToUITileSize(SecondaryTiles::TileSize::Default));

	secondaryTile->VisualElements->ShowNameOnSquare150x150Logo = showNameOnSquare150x150Logo;
	secondaryTile->RoamingEnabled = roamingEnabled;

	return secondaryTile;
}

SecondaryTile^ CreateTile(string tileId, PCWSTR displayName, string arguments, SecondaryTiles::TileSize desiredSize, SecondaryTiles::TileOptions options)
{
	auto secondaryTile = ref new SecondaryTile(
		ToPlatformString(tileId),
		ToPlatformString(displayName),
		ToPlatformString(arguments),
		GetUriSafe(options.Square150x150Logo),
		ToUITileSize(desiredSize));

	if (IsValidImageUri(options.Square70x70Logo))
	{
		secondaryTile->VisualElements->Square70x70Logo = GetUriSafe(options.Square70x70Logo);
	}

	if (IsValidImageUri(options.Wide310x150Logo))
	{
		secondaryTile->VisualElements->Wide310x150Logo = GetUriSafe(options.Wide310x150Logo);
	}

	if (IsValidImageUri(options.Square310x310Logo))
	{
		secondaryTile->VisualElements->Square310x310Logo = GetUriSafe(options.Square310x310Logo);
	}

	secondaryTile->VisualElements->ShowNameOnSquare150x150Logo = options.ShowNameOnSquare150x150Logo;
	secondaryTile->VisualElements->ShowNameOnWide310x150Logo = options.ShowNameOnWide310x150Logo;
	secondaryTile->VisualElements->ShowNameOnSquare310x310Logo = options.ShowNameOnSquare310x310Logo;

	secondaryTile->RoamingEnabled = options.RoamingEnabled;

	if (options.BackgroundColor.length() >= 6)
	{
		secondaryTile->VisualElements->BackgroundColor = HexToUIColor(options.BackgroundColor);
	}

	secondaryTile->VisualElements->ForegroundText = (Windows::UI::StartScreen::ForegroundText)options.ForegroundText;

	return secondaryTile;
}


void SecondaryTiles::RequestCreate(HWND hWnd, string tileId, PCWSTR displayName, string arguments, string squareLogo150x150Uri, bool showNameOnSquare150x150Logo, bool roamingEnabled)
{
	auto secondaryTile = CreateTile(tileId, displayName, arguments, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
	RequestCreateInternalAsync(hWnd, secondaryTile);
}

void SecondaryTiles::RequestCreate(HWND hWnd, string tileId, PCWSTR displayName, string arguments, SecondaryTiles::TileSize desiredSize, SecondaryTiles::TileOptions options)
{
	auto secondaryTile = CreateTile(tileId, displayName, arguments, desiredSize, options);
	RequestCreateInternalAsync(hWnd, secondaryTile);
}

void SecondaryTiles::RequestUpdate(string tileId, PCWSTR displayName, string arguments, string squareLogo150x150Uri, bool showNameOnSquare150x150Logo, bool roamingEnabled)
{
	auto secondaryTile = CreateTile(tileId, displayName, arguments, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
	secondaryTile->UpdateAsync();
	auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(secondaryTile->TileId);
	updater->EnableNotificationQueue(true);
}

void SecondaryTiles::RequestUpdate(string tileId, PCWSTR displayName, string arguments, SecondaryTiles::TileSize desiredSize, SecondaryTiles::TileOptions options)
{
	auto secondaryTile = CreateTile(tileId, displayName, arguments, desiredSize, options);
	secondaryTile->UpdateAsync();
	auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(secondaryTile->TileId);
	updater->EnableNotificationQueue(true);
}

bool SecondaryTiles::Exists(string tileId)
{
	return SecondaryTile::Exists(ToPlatformString(tileId));
}

void SecondaryTiles::RequestDelete(string tileId)
{
	auto secondaryTile = ref new SecondaryTile(ToPlatformString(tileId));
	secondaryTile->RequestDeleteAsync();
}

void SecondaryTiles::Notify(string tileId, string contentXml)
{
	if (IsNotificationSupported())
	{
		 auto tileXml = ref new XmlDocument();
		 tileXml->LoadXml(ToPlatformString(contentXml));

		 TileNotification^ tileNotification = ref new TileNotification(tileXml);
		 auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(ToPlatformString(tileId));

		 updater->Update(tileNotification);
	}
}

void SecondaryTiles::BadgeNotify(string tileId, string badgeXml)
{
	if (IsNotificationSupported())
	{
		auto tileXml = ref new XmlDocument();
		tileXml->LoadXml(ToPlatformString(badgeXml));

		BadgeNotification^ badgeNotification = ref new BadgeNotification(tileXml);
		auto updater = BadgeUpdateManager::CreateBadgeUpdaterForSecondaryTile(ToPlatformString(tileId));

		updater->Update(badgeNotification);
	}
}

void SecondaryTiles::ClearNotification(string tileId)
{
	if (IsNotificationSupported())
	{
		auto updater = TileUpdateManager::CreateTileUpdaterForSecondaryTile(ToPlatformString(tileId));
		updater->Clear();
	}
}

void SecondaryTiles::ClearBadge(string tileId)
{
	if (IsNotificationSupported())
	{
		auto updater = BadgeUpdateManager::CreateBadgeUpdaterForSecondaryTile(ToPlatformString(tileId));
		updater->Clear();
	}
}