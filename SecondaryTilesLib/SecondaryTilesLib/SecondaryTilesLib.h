#pragma once

#include "stdafx.h"
#include <string>
#include <future>
#include <VersionHelpers.h>

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
		Square150x150 = 1,
		Wide310x150 = 2,
	};

	enum ForegroundText
	{
		Dark = 0,
		Light = 1
	};

	class SECONDARYTILESLIB_API TileOptions
	{
	public: 
		string Square70x70Logo;
		string Square150x150Logo;
		string Wide310x150Logo;
		string Square310x310Logo;
	
		string BackgroundColor;
		ForegroundText ForegroundText = ForegroundText::Light;

		bool ShowNameOnSquare150x150Logo;
		bool ShowNameOnWide310x150Logo;
		bool ShowNameOnSquare310x310Logo;

		bool RoamingEnabled = true;
	};

	SECONDARYTILESLIB_API void RequestCreate(HWND hWnd, string tileId, PCWSTR displayName, string arguments, string squareLogo150x150Uri, bool showNameOnSquare150x150Logo, bool roamingEnabled);

	SECONDARYTILESLIB_API void RequestCreate(HWND hWnd, string tileId, PCWSTR displayName, string arguments, TileSize desiredSize, TileOptions options);

	SECONDARYTILESLIB_API void RequestUpdate(string tileId, PCWSTR displayName, string arguments, string squareLogo150x150Uri, bool showNameOnSquare150x150Logo, bool roamingEnabled);

	SECONDARYTILESLIB_API void RequestUpdate(string tileId, PCWSTR displayName, string arguments, TileSize desiredSize, TileOptions options);

	SECONDARYTILESLIB_API void RequestDelete(string tileId);

	SECONDARYTILESLIB_API bool Exists(string tileId);

	SECONDARYTILESLIB_API void Notify(string tileId, string contentXml);

	SECONDARYTILESLIB_API void BadgeNotify(string tileId, string badgeXml);

	SECONDARYTILESLIB_API void ClearNotification(string tileId);

	SECONDARYTILESLIB_API void ClearBadge(string tileId);
}