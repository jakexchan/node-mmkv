#ifndef MMKVMODULE_H
#define MMKVMODULE_H

#include <napi.h>
#include <MMKV.h>

using namespace mmkv;

class MMKVModule : public Napi::ObjectWrap<MMKVModule>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  MMKVModule(const Napi::CallbackInfo &info);

  void InitializeMMKV(const Napi::CallbackInfo &info);
  void SetString(const Napi::CallbackInfo &info);
  Napi::Value GetString(const Napi::CallbackInfo &info);

private:
  MMKV *mmkv;
};

#endif // MMKVMODULE_H