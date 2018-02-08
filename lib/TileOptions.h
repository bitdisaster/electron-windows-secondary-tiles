#pragma once

#include <nan.h>
#include <v8.h>


class TileOptions : public Nan::ObjectWrap {
public:
  std::string Square70x70Logo;
  std::string Square150x150Logo;
  std::string Wide310x150Logo;
  std::string Square310x310Logo;

  std::string BackgroundColor;
  int32_t ForegroundText = 1;

  bool ShowNameOnSquare150x150Logo;
  bool ShowNameOnWide310x150Logo;
  bool ShowNameOnSquare310x310Logo;

  bool RoamingEnabled = true;

  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(Add);

  static NAN_GETTER(HandleGetters);
  static NAN_SETTER(HandleSetters);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};