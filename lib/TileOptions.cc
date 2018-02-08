#include "TileOptions.h"
#include <v8.h>

using v8::Local;
using v8::String;

Nan::Persistent<v8::FunctionTemplate> TileOptions::constructor;

NAN_MODULE_INIT(TileOptions::Init) {
	v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(TileOptions::New);
	constructor.Reset(ctor);
	ctor->InstanceTemplate()->SetInternalFieldCount(1);
	ctor->SetClassName(Nan::New("TileOptions").ToLocalChecked());

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("Square70x70Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("Square150x150Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("Wide310x150Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("Square310x310Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("BackgroundColor").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("ForegroundText").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);

	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("ShowNameOnSquare150x150Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("ShowNameOnWide310x150Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("ShowNameOnSquare310x310Logo").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);
	Nan::SetAccessor(ctor->InstanceTemplate(), Nan::New("RoamingEnabled").ToLocalChecked(), TileOptions::HandleGetters, TileOptions::HandleSetters);

	target->Set(Nan::New("TileOptions").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(TileOptions::New) {

	if (!info.IsConstructCall()) {
		return Nan::ThrowError(Nan::New("TileOptions::New - called without new keyword").ToLocalChecked());
	}

	TileOptions* tileOptions = new TileOptions();
	tileOptions->Wrap(info.Holder());

	info.GetReturnValue().Set(info.Holder());
}


NAN_GETTER(TileOptions::HandleGetters) {
	TileOptions* self = Nan::ObjectWrap::Unwrap<TileOptions>(info.This());

	std::string propertyName = std::string(*Nan::Utf8String(property));

	if (propertyName == "Square70x70Logo") {
		auto local = Nan::New(self->Square70x70Logo).ToLocalChecked();
		info.GetReturnValue().Set(local);
	}
	else if (propertyName == "Square150x150Logo") {
		auto local = Nan::New(self->Square150x150Logo).ToLocalChecked();
		info.GetReturnValue().Set(local);
	}
	else if (propertyName == "Wide310x150Logo") {
		auto local = Nan::New(self->Wide310x150Logo).ToLocalChecked();
		info.GetReturnValue().Set(local);
	}
	else if (propertyName == "Square310x310Logo") {
		auto local = Nan::New(self->Square310x310Logo).ToLocalChecked();
		info.GetReturnValue().Set(local);
	}
	else if (propertyName == "BackgroundColor") {
		auto local = Nan::New(self->BackgroundColor).ToLocalChecked();
		info.GetReturnValue().Set(local);
	}
	else if (propertyName == "ForegroundText") {
		info.GetReturnValue().Set(self->ForegroundText);
	}
	else if (propertyName == "ShowNameOnSquare150x150Logo") {
		info.GetReturnValue().Set(self->ShowNameOnSquare150x150Logo);
	}
	else if (propertyName == "ShowNameOnWide310x150Logo") {
		info.GetReturnValue().Set(self->ShowNameOnWide310x150Logo);
	}
	else if (propertyName == "ShowNameOnSquare310x310Logo") {
		info.GetReturnValue().Set(self->ShowNameOnSquare310x310Logo);
	}
	else if (propertyName == "RoamingEnabled") {
		info.GetReturnValue().Set(self->RoamingEnabled);
	}
	else {
		info.GetReturnValue().Set(Nan::Undefined());
	}
}

NAN_SETTER(TileOptions::HandleSetters) {
	TileOptions* self = Nan::ObjectWrap::Unwrap<TileOptions>(info.This());

	std::string propertyName = std::string(*Nan::Utf8String(property));

	if (propertyName == "Square70x70Logo") {
		auto local = Nan::To<v8::String>(value).ToLocalChecked();
		self->Square70x70Logo = std::string(*Nan::Utf8String(local));
	}
	else if (propertyName == "Square150x150Logo") {
		auto local = Nan::To<v8::String>(value).ToLocalChecked();
		self->Square150x150Logo = std::string(*Nan::Utf8String(local));
	}
	else if (propertyName == "Wide310x150Logo") {
		auto local = Nan::To<v8::String>(value).ToLocalChecked();
		self->Wide310x150Logo = std::string(*Nan::Utf8String(local));
	}
	else if (propertyName == "Square310x310Logo") {
		auto local = Nan::To<v8::String>(value).ToLocalChecked();
		self->Square310x310Logo = std::string(*Nan::Utf8String(local));
	}
	else if (propertyName == "BackgroundColor") {
		auto local = Nan::To<v8::String>(value).ToLocalChecked();
		self->BackgroundColor = std::string(*Nan::Utf8String(local));
	}
	else if (propertyName == "ForegroundText") {
		self->ForegroundText = value->Int32Value();
	}
	else if (propertyName == "ShowNameOnSquare150x150Logo") {
		self->ShowNameOnSquare150x150Logo = value->BooleanValue();
	}
	else if (propertyName == "ShowNameOnWide310x150Logo") {
		self->ShowNameOnWide310x150Logo = value->BooleanValue();
	}
	else if (propertyName == "ShowNameOnSquare310x310Logo") {
		self->ShowNameOnSquare310x310Logo = value->BooleanValue();
	}
	else if (propertyName == "RoamingEnabled") {
		self->RoamingEnabled = value->BooleanValue();
	}
}
