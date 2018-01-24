#include <stdio.h>
#include <stdlib.h>

#include "deps.h"

void get_classpath() {
    FILE *pp;
    pp = popen("clojure -Spath", "r");
    if (pp != NULL) {
        while (1) {
            char *line;
            char buf[1000];
            line = fgets(buf, sizeof buf, pp);
            if (line == NULL) break;
        }
        pclose(pp);
    }
}