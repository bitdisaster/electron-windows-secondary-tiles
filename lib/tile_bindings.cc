#include <nan.h>
#include <v8.h>
#include "SecondaryTilesLib.h"
#include "TileOptions.h"

using v8::Local;
using v8::String;
using v8::Boolean;
using v8::Integer;

SecondaryTiles::TileOptions ToTileOptions(TileOptions* tileOptionsObject) {
	SecondaryTiles::TileOptions tileOptions;

	tileOptions.Square70x70Logo = tileOptionsObject->Square70x70Logo;
	tileOptions.Square150x150Logo = tileOptionsObject->Square150x150Logo;
	tileOptions.Wide310x150Logo = tileOptionsObject->Wide310x150Logo;
	tileOptions.Square310x310Logo = tileOptionsObject->Square310x310Logo;
	tileOptions.BackgroundColor = tileOptionsObject->BackgroundColor != "undefined" ? tileOptionsObject->BackgroundColor : "";
	tileOptions.ForegroundText = (SecondaryTiles::ForegroundText)tileOptionsObject->ForegroundText;
	tileOptions.ShowNameOnSquare150x150Logo = tileOptionsObject->ShowNameOnSquare150x150Logo;
	tileOptions.ShowNameOnWide310x150Logo = tileOptionsObject->ShowNameOnWide310x150Logo;
	tileOptions.ShowNameOnSquare310x310Logo = tileOptionsObject->ShowNameOnSquare310x310Logo;
	tileOptions.RoamingEnabled = tileOptionsObject->RoamingEnabled;

	return tileOptions;
}

void RequestCreateOrUpdateInternal(Nan::NAN_METHOD_ARGS_TYPE info, bool update) {
	bool callWithOptions;

	if (info.Length() > 6
		&& info[1]->IsString()
		&& info[2]->IsString()
		&& info[3]->IsString()
		&& info[4]->IsString()
		&& info[5]->IsBoolean()
		&& info[6]->IsBoolean())
	{
		callWithOptions = false;
	}
	else if (info.Length() > 5
		&& info[1]->IsString()
		&& info[2]->IsString()
		&& info[3]->IsString()
		&& info[4]->IsInt32()
		&& info[5]->IsObject())
	{
		callWithOptions = true;
	}
	else
	{
		Nan::ThrowTypeError("Invalid arguments, expected arguments are: hwnd [HWND], tileId [string], displayName [string], arguments [string], squareLogo150x150Uri [string], showNameOnSquare150x150Logo [bool], roamingEnabled [bool]\r\n or hwnd [HWND], tileId [string], displayName [string], arguments [string], tileSize [int], tileOptions [TileOptions]");
		return;
	}

	auto bufferObj = Nan::To<v8::Object>(info[0]).ToLocalChecked();
	unsigned char *bufferData = (unsigned char *)node::Buffer::Data(bufferObj);
	unsigned long handle = *reinterpret_cast<unsigned long *>(bufferData);
	HWND hWnd = (HWND)handle;

	String::Utf8Value p1(info[1]->ToString());
	std::string tileId = std::string(*p1);

	Local<String> p2 = Nan::To<String>(info[2]).ToLocalChecked();
	String::Value displayName(p2);

	String::Utf8Value p3(info[3]->ToString());
	std::string arguments = std::string(*p3);


	if (!callWithOptions)
	{
		String::Utf8Value p4(info[4]->ToString());
		std::string squareLogo150x150Uri = std::string(*p4);

		bool showNameOnSquare150x150Logo = info[5]->BooleanValue();
		bool roamingEnabled = info[6]->BooleanValue();

		if (!update)
		{
			SecondaryTiles::RequestCreate(hWnd, tileId, (PCWSTR)* displayName, arguments, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
		}
		else
		{
			SecondaryTiles::RequestUpdate(hWnd, tileId, (PCWSTR)* displayName, arguments, squareLogo150x150Uri, showNameOnSquare150x150Logo, roamingEnabled);
		}

		info.GetReturnValue().SetNull();
	}
	else
	{
		int32_t sizeValue = info[4]->Int32Value();

		SecondaryTiles::TileSize desiredSize = (SecondaryTiles::TileSize)sizeValue;
		Nan::MaybeLocal<v8::Object> maybe = Nan::To<v8::Object>(info[5]);
		auto tileOptionsObject = Nan::ObjectWrap::Unwrap<TileOptions>(maybe.ToLocalChecked());

		SecondaryTiles::TileOptions tileOptions = ToTileOptions(tileOptionsObject);

		if (!update)
		{
			SecondaryTiles::RequestCreate(hWnd, tileId, (PCWSTR)* displayName, arguments, desiredSize, tileOptions);
		}
		else
		{
			SecondaryTiles::RequestUpdate(hWnd, tileId, (PCWSTR)* displayName, arguments, desiredSize, tileOptions);
		}

		info.GetReturnValue().SetNull();
	}
}

NAN_METHOD(RequestCreate) {
	RequestCreateOrUpdateInternal(info, false);
}

NAN_METHOD(RequestUpdate) {
	RequestCreateOrUpdateInternal(info, true);
}

NAN_METHOD(Exists) {

	if (info.Length() < 1 || !info[0]->IsString())
	{
		Nan::ThrowTypeError("Invalid arguments, expected arguments are: tileId [string]");
		return;
	}

	auto local = Nan::To<String>(info[0]).ToLocalChecked();
	auto tileId = std::string(*Nan::Utf8String(local));

	auto result = SecondaryTiles::Exists(tileId);
	auto message = Nan::New<Boolean>(result);

	info.GetReturnValue().Set(message);
}

NAN_METHOD(RequestDelete) {

	if (info.Length() < 1 || !info[0]->IsString())
	{
		Nan::ThrowTypeError("Invalid arguments, expected arguments are: tileId [string]");
		return;
	}

	auto local = Nan::To<String>(info[0]).ToLocalChecked();
	auto tileId = std::string(*Nan::Utf8String(local));

	SecondaryTiles::RequestDelete(tileId);
	info.GetReturnValue().SetNull();
}

NAN_METHOD(Notify) {

	if (info.Length() < 1 || !info[0]->IsString() || !info[1]->IsString())
	{
		Nan::ThrowTypeError("Invalid arguments, expected arguments are: tileId [string], contentXml [string]");
		return;
	}

	auto p0 = Nan::To<v8::String>(info[0]).ToLocalChecked();
	auto tileId = std::string(*Nan::Utf8String(p0));

	auto p1 = Nan::To<v8::String>(info[1]).ToLocalChecked();
	auto contentXml = std::string(*Nan::Utf8String(p1));

	SecondaryTiles::Notify(tileId, contentXml);
	info.GetReturnValue().SetNull();
}

NAN_MODULE_INIT(Initialize) {
	NAN_EXPORT(target, RequestCreate);
	NAN_EXPORT(target, RequestUpdate);
	NAN_EXPORT(target, RequestDelete);
	NAN_EXPORT(target, Exists);
	NAN_EXPORT(target, Notify);
	TileOptions::Init(target);
}

NODE_MODULE(tile_bindings, Initialize)