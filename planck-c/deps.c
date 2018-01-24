#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "deps.h"

char* get_deps_classpath() {

    struct SystemResult result = {0, NULL, NULL};
    struct SystemResult *res = &result;

    char** cmd = malloc(3*sizeof(char*));
    cmd[0] = strdup("clojure");
    cmd[1] = strdup("-Spath");
    cmd[2] = NULL;

    int err = system_call(cmd, NULL, NULL, NULL, -1, res);

    if (err) {
        return NULL;
    }

    if (result.status != 0) {
        return NULL;
    }

    fputs(res->stderr, stderr);

    char* classpath = strdup(res->stdout);

    // Get rid of trailing newline
    classpath[strlen(classpath)-1] = 0;

    return classpath;
}