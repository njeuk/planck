#include <JavaScriptCore/JavaScript.h>

struct SystemResult {
    int status;
    char *stdout;
    char *stderr;
};

int system_call2(char **cmd, char *in_str, char **env, char *dir, int cb_idx, struct SystemResult *res);

JSValueRef function_shellexec(JSContextRef ctx, JSObjectRef function, JSObjectRef this_object,
                              size_t argc, const JSValueRef args[], JSValueRef *exception);
