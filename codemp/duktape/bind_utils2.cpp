#include "duktapestuff.h"
#include "duktape.h"	
#include "bind_utils.h"
#ifdef _WIN32
#include <Windows.h>
#endif

int duk_func_utils_screensize(duk_context *ctx) {
	//char *address = (char *)duk_to_int(ctx, 0);
	//char *text = (char *)duk_to_string(ctx, 1);
	//strncpy(address, text, 256);
	int w = 800, h = 600;
	duk_push_object(ctx);
	duk_push_int(ctx, w);
	duk_put_prop_string(ctx, -2, "width");
	//duk_put_prop_index(ctx, -2, 0);
	duk_push_int(ctx, h);
	//duk_put_prop_index(ctx, -2, 1);
	duk_put_prop_string(ctx, -2, "height");
	return 1;
}

int duk_func_exedir(duk_context *ctx) {
#ifdef _WIN32
	char exedir[MAX_PATH];
	// When NULL is passed to GetModuleHandle, the handle of the exe itself is returned
	HMODULE hModule = GetModuleHandle(NULL);
	GetModuleFileName(hModule, exedir, sizeof(exedir));
	duk_push_string(ctx, exedir);
#else
	// todo for linux server
	duk_push_string(ctx, ".");
#endif
	return 1;
}

void ICARUS_InterrogateScript( const char *filename );
int duk_func_icarus_run(duk_context *ctx) {
	const char *filename = duk_to_string(ctx, 0);
	ICARUS_InterrogateScript(filename);
	return 0;
}

void Com_Frame();
int duk_func_Com_Frame(duk_context *ctx) {
	Com_Frame();
	return 0;
}

void Com_BusyWait();
int duk_func_Com_BusyWait(duk_context *ctx) {
	Com_BusyWait();
	return 0;
}

void bind_utils() {
	struct funcis funcs[] = {
		{ "utils_screensize",	   duk_func_utils_screensize   },
		{ "exedir",	               duk_func_exedir             },
		{ "icarus_run",	           duk_func_icarus_run         },
		{ "Com_Frame",	           duk_func_Com_Frame          },
		{ "Com_BusyWait",	       duk_func_Com_BusyWait       },
		{NULL, NULL}
	};
	for (int i=0; funcs[i].name; i++) {
		js_register_function(ctx, funcs[i].name, funcs[i].func);
	}
}