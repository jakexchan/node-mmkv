#include "MMKVModule.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

Napi::Object MMKVModule::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
      env,
      "MMKVModule",
      {InstanceMethod<&MMKVModule::SetString>("setString"),
       InstanceMethod<&MMKVModule::GetString>("getString"),
       InstanceMethod<&MMKVModule::SetBoolean>("setBoolean"),
       InstanceMethod<&MMKVModule::GetBoolean>("getBoolean"),
       InstanceMethod<&MMKVModule::SetNumber>("setNumber"),
       InstanceMethod<&MMKVModule::GetNumber>("getNumber"),
       InstanceMethod<&MMKVModule::ContainsKey>("containsKey"),
       InstanceMethod<&MMKVModule::GetKeys>("getKeys"),
       InstanceMethod<&MMKVModule::RemoveKey>("removeKey"),
       InstanceMethod<&MMKVModule::ClearMemoryCache>("clearMemoryCache"),
       InstanceMethod<&MMKVModule::ClearAll>("clearAll")});
  Napi::FunctionReference *constructor = new Napi::FunctionReference();

  *constructor = Napi::Persistent(func);
  exports.Set("MMKVModule", func);
  env.SetInstanceData<Napi::FunctionReference>(constructor);
  return exports;
}

MMKVModule::MMKVModule(const Napi::CallbackInfo &info) : Napi::ObjectWrap<MMKVModule>(info)
{
  Napi::Env env = info.Env();
  if (info[0].IsUndefined())
  {
    Napi::TypeError::New(env, "options is required").ThrowAsJavaScriptException();
  }

  Napi::Object options = info[0].As<Napi::Object>().ToObject();
  if (options.Get("rootDir").IsUndefined() || !options.Get("rootDir").IsString())
  {
    Napi::TypeError::New(env, "options.rootDir is required, string type").ThrowAsJavaScriptException();
  }

  string rootDir = options.Get("rootDir").As<Napi::String>().ToString();
  string mmapID = DEFAULT_MMAP_ID;
  MMKVMode mode = MMKV_SINGLE_PROCESS;
  string cryptKey;
  if (options.Get("id").IsString())
  {
    mmapID = options.Get("id").As<Napi::String>().ToString();
  }
  if (options.Get("multiProcess").IsBoolean() && options.Get("multiProcess").As<Napi::Boolean>().ToBoolean())
  {
    mode = MMKV_MULTI_PROCESS;
  }
  if (options.Get("cryptKey").IsString())
  {
    cryptKey = options.Get("cryptKey").As<Napi::String>().ToString();
  }

  MMKVPath_t mmkvRootDir = string2MMKVPath_t(rootDir);
  MMKV::initializeMMKV(mmkvRootDir);
  this->mmkv = MMKV::mmkvWithID(mmapID, mode, &cryptKey, &mmkvRootDir);
}

Napi::Value MMKVModule::SetString(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv || info[0].IsUndefined() || info[1].IsUndefined())
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  string value = info[1].As<Napi::String>().ToString();
  mmkv->set(value, key);
  return Napi::Boolean::New(env, true);
}

Napi::Value MMKVModule::GetString(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv || info[0].IsUndefined())
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  string result;
  bool called = mmkv->getString(key, result);
  if (called)
  {
    return Napi::String::New(env, result);
  }
  return env.Undefined();
}

Napi::Value MMKVModule::SetBoolean(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv || info[0].IsUndefined())
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  bool value = info[1].As<Napi::Boolean>().ToBoolean();
  mmkv->set(value, key);
  return Napi::Boolean::New(env, true);
}

Napi::Value MMKVModule::GetBoolean(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  if (!mmkv->containsKey(key))
  {
    return env.Undefined();
  }
  return Napi::Boolean::New(env, mmkv->getBool(key, false));
}

Napi::Value MMKVModule::SetNumber(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv || info[0].IsUndefined())
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  double value = info[1].As<Napi::Number>().ToNumber();
  mmkv->set(value, key);
  return Napi::Boolean::New(env, true);
}

Napi::Value MMKVModule::GetNumber(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  string key = info[0].As<Napi::String>().ToString();
  if (!mmkv->containsKey(key))
  {
    return env.Undefined();
  }

  return Napi::Number::New(env, mmkv->getDouble(key));
}

Napi::Value MMKVModule::ContainsKey(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }
  string key = info[0].As<Napi::String>().ToString();

  return Napi::Boolean::New(env, mmkv->containsKey(key));
}

Napi::Value MMKVModule::GetKeys(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  vector<string> keys = mmkv->allKeys();
  Napi::Array result = Napi::Array::New(env);
  for (uint32_t index = 0; index < keys.size(); index++)
  {
    result.Set(index, Napi::String::New(env, keys[index]));
  }
  return result;
}

Napi::Value MMKVModule::RemoveKey(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  string rmKey = info[0].As<Napi::String>().ToString();
  mmkv->removeValueForKey(rmKey);
  return env.Undefined();
}

Napi::Value MMKVModule::ClearMemoryCache(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  mmkv->clearMemoryCache();
  return env.Undefined();
}

Napi::Value MMKVModule::ClearAll(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (!mmkv)
  {
    return env.Undefined();
  }

  mmkv->clearAll();
  return env.Undefined();
}

Napi::Object InitNodeModule(Napi::Env env, Napi::Object exports)
{
  return MMKVModule::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitNodeModule);