#pragma once

#include "stdafx.h"
#include <string>
#include <future>

using namespace std;

#ifdef SECONDARYTILESLIB_EXPORTS
#define SECONDARYTILESLIB_API __declspec(dllexport)   
#else  
#define SECONDARYTILESLIB_API __declspec(dllimport)   
#endif  

namespace SecondaryTiles
{
	enum TileSize
	{
		Default = 0,
		Square30x30 = 1,
		Square70x70 = 2,
		Square150x150 = 3,
		Wide310x150 = 4,
		Square310x310 = 5,
		Square71x71 = 6,
		Square44x44 = 7
	};

	enum ForegroundText
	{
		Dark = 0,
		Light = 1
	};

	struct SECONDARYTILESLIB_API TileOptions
	{
		wstring LockScreenBadgeLogo;
		wstring Square30x30Logo;
		wstring Wide310x150Logo;
		wstring Square310x310Logo;
		wstring Square44x44Logo;
		wstring Square70x70Logo;

		string BackgroundColor;
		ForegroundText ForegroundText = ForegroundText::Light;

		bool LockScreenDisplayBadgeAndTileText;
		bool ShowNameOnSquare150x150Logo;
		bool ShowNameOnWide310x150Logo;
		bool ShowNameOnSquare310x310Logo;

		bool RoamingEnabled = true;
	};

	SECONDARYTILESLIB_API void Test(HWND hWnd);

	SECONDARYTILESLIB_API std::future<void> RequestCreateAsync(HWND hWnd, wstring tileId, wstring displayName, wstring arguments, wstring squareLogo150x150Uri, TileSize desiredSize);

	SECONDARYTILESLIB_API std::future<void> RequestCreateAsync(HWND hWnd, wstring tileId, wstring displayName, wstring arguments, wstring squareLogo150x150Uri, TileSize desiredSize, TileOptions options);

	SECONDARYTILESLIB_API bool SecondaryTileExists(wstring tileId);

	SECONDARYTILESLIB_API std::future<void> RequestDeleteAsync(wstring tileId);

	SECONDARYTILESLIB_API void Update(wstring tileId);
}