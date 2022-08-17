#ifndef MMKVMODULE_H
#define MMKVMODULE_H

#include <napi.h>
#include <MMKV.h>

using namespace mmkv;

class MMKVModule : public Napi::ObjectWrap<MMKVModule>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  explicit MMKVModule(const Napi::CallbackInfo &info);

  Napi::Value SetString(const Napi::CallbackInfo &info);
  Napi::Value GetString(const Napi::CallbackInfo &info);
  Napi::Value SetBoolean(const Napi::CallbackInfo &info);
  Napi::Value GetBoolean(const Napi::CallbackInfo &info);
  Napi::Value SetNumber(const Napi::CallbackInfo &info);
  Napi::Value GetNumber(const Napi::CallbackInfo &info);

  Napi::Value ContainsKey(const Napi::CallbackInfo &info);
  Napi::Value GetKeys(const Napi::CallbackInfo &info);
  Napi::Value RemoveKey(const Napi::CallbackInfo &info);
  Napi::Value ClearMemoryCache(const Napi::CallbackInfo &info);
  Napi::Value ClearAll(const Napi::CallbackInfo &info);

private:
  MMKV *mmkv;
};

#endif // MMKVMODULE_H