#include "MMKVModule.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

Napi::Object MMKVModule::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "MMKVModule", {InstanceMethod<&MMKVModule::InitializeMMKV>("initializeMMKV"), InstanceMethod<&MMKVModule::SetString>("setString"), InstanceMethod<&MMKVModule::GetString>("getString")});
  Napi::FunctionReference *constructor = new Napi::FunctionReference();

  *constructor = Napi::Persistent(func);
  exports.Set("MMKVModule", func);
  env.SetInstanceData<Napi::FunctionReference>(constructor);
  return exports;
}

MMKVModule::MMKVModule(const Napi::CallbackInfo &info) : Napi::ObjectWrap<MMKVModule>(info)
{
}

void MMKVModule::InitializeMMKV(const Napi::CallbackInfo &info)
{
  string rootDir = "/tmp/mmkv";
  MMKV::initializeMMKV(rootDir);
  // string aesKey = "cryptKey";
  // mmkv = MMKV::mmkvWithID("test/Encrypt", MMKV_SINGLE_PROCESS, &aesKey);
  mmkv = MMKV::defaultMMKV();
}

void MMKVModule::SetString(const Napi::CallbackInfo &info)
{
  if (mmkv)
  {
    string key = info[0].As<Napi::String>().ToString();
    string value = info[1].As<Napi::String>().ToString();
    mmkv->set(value, key);
  }
}

Napi::Value MMKVModule::GetString(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  if (mmkv)
  {
    string key = info[0].As<Napi::String>().ToString();
    string result;
    bool called = mmkv->getString(key, result);
    if (called)
    {
      return Napi::String::New(env, result);
    }
  }
  return env.Undefined();
}

Napi::Object InitNodeModule(Napi::Env env, Napi::Object exports)
{
  return MMKVModule::Init(env, exports);
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, InitNodeModule);