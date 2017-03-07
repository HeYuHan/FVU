#include "CharacterJSB.h"
#include "cocos2d.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
using namespace cocos2d;
using namespace JS;
NS_FVU_BEGIN
JSClass* jsb_character_class;
JSObject* jsb_character_prototype;
bool js_character_constructor(JSContext* cx, uint32_t argc, jsval* vp)
{
	log("js_character_constructor");
	CallArgs args = CallArgsFromVp(argc, vp);
	bool ok = true;
	Character* cobj = new (std::nothrow) Character();
	js_type_class_t *typeClass = js_get_type_from_native<Character>(cobj);
	// link the native object with the javascript object
	RootedObject jsobj(cx, jsb_ref_create_jsobject(cx, cobj, typeClass, "Character"));
	args.rval().set(OBJECT_TO_JSVAL(jsobj));
	if (JS_HasProperty(cx, jsobj, "_ctor", &ok) && ok)
	{
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(jsobj), "_ctor", args);
	}
	return true;
}
static bool js_character_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	Character *nobj = new (std::nothrow) Character();
	auto newproxy = jsb_new_proxy(nobj, obj);
	jsb_ref_init(cx, &newproxy->obj, nobj, "Character");
	bool isFound = false;
	if (JS_HasProperty(cx, obj, "_ctor", &isFound) && isFound)
		ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
	args.rval().setUndefined();
	return true;
}

bool js_character_create(JSContext* cx, uint32_t argc, jsval* vp)
{
	log("js_character_create");
	CallArgs args = CallArgsFromVp(argc, vp);
	if (argc == 0)
	{
		auto ret = Character::create();
		js_type_class_t *typeClass = js_get_type_from_native<Character>(ret);
		RootedObject jsret(cx, jsb_ref_autoreleased_create_jsobject(cx, ret, typeClass, "Character"));
		args.rval().set(OBJECT_TO_JSVAL(jsret));
		return true;
	}
	
	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return false;
}
void js_character_finalize(JSFreeOp* fop, JSObject* obj){
	log("JSBindings: finallizing JS object %p Character", obj);
	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	JS::RootedObject jsobj(cx, obj);
	auto proxy = jsb_get_js_proxy(jsobj);
	if (proxy)
	{
		Character *nobj = static_cast<Character *>(proxy->ptr);
		if (nobj)
			delete nobj;
		jsb_remove_proxy(proxy);
	}
}
bool js_character_function_setUID(JSContext* cx, uint32_t argc, jsval* vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Character* cobj = (Character *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_character_function_setID : Invalid Native Object");
	if (argc == 1) {
		int arg0 = 0;
		ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, false, "js_character_function_setUID : Error processing arguments");
		cobj->setUID(arg0);
		args.rval().setUndefined();
		return true;
	}

	JS_ReportError(cx, "js_character_function_setID : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
bool js_character_function_getUID(JSContext* cx, uint32_t argc, jsval* vp)
{
	JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
	bool ok = true;
	JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Character* cobj = (Character *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2(cobj, cx, false, "js_character_function_setUID : Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getUID();
		RootedValue jsret(cx);
		jsret = int32_to_jsval(cx, ret);
		args.rval().set(jsret);
		return true;
	}

	JS_ReportError(cx, "js_character_function_setID : wrong number of arguments: %d, was expecting %d", argc, 1);
	return false;
}
void register_all_character(JSContext* cx, HandleObject global)
{
	jsb_character_class = (JSClass*)calloc(1, sizeof(JSClass));
	jsb_character_class->name = "Character";
	jsb_character_class->addProperty = JS_PropertyStub;
	jsb_character_class->delProperty = JS_DeletePropertyStub;
	jsb_character_class->getProperty = JS_PropertyStub;
	jsb_character_class->setProperty = JS_StrictPropertyStub;
	jsb_character_class->enumerate = JS_EnumerateStub;
	jsb_character_class->resolve = JS_ResolveStub;
	jsb_character_class->convert = JS_ConvertStub;
	jsb_character_class->finalize = js_character_finalize;
	jsb_character_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
	static JSPropertySpec properties[] = {
		JS_PS_END
	};
	static JSFunctionSpec funcs[] = {
		JS_FN("setUID", js_character_function_setUID, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUID", js_character_function_getUID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ctor", js_character_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
	static JSFunctionSpec static_funcs[] = {
		JS_FN("create", js_character_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};
	jsb_character_prototype = JS_InitClass(
		cx, global,
		JS::NullPtr(),
		jsb_character_class,
		js_character_constructor, 0,
		properties,
		funcs,
		NULL,// no static properties
		static_funcs);
	RootedObject proto(cx, jsb_character_prototype);
	RootedValue className(cx, std_string_to_jsval(cx, "Character"));

	JS_SetProperty(cx, proto, "_className", className);
	JS_SetProperty(cx, proto, "_nativeObj", TrueHandleValue);
	JS_SetProperty(cx, proto, "_is_ref", TrueHandleValue);
	jsb_register_class<Character>(cx, jsb_character_class, proto, NullPtr());

	JS_DefineFunction(cx, proto, "retain", js_cocos2dx_retain, 0, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, proto, "release", js_cocos2dx_release, 0, JSPROP_READONLY | JSPROP_PERMANENT);
}
NS_FVU_END