#ifndef __CHARACTERJSB_H__
#define __CHARACTERJSB_H__
#include "jsapi.h"
#include "jsfriendapi.h"
#include "scripting/js-bindings/manual/ScriptingCore.h"
#include "Game/Character.h"
void register_all_character(JSContext* cx, JS::HandleObject obj);
#endif