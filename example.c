#include <stdio.h>
#include <stdlib.h>
#include "linenoise.h"

#define COMMAND_COUNT	3

char *completeLine(char *line) {
    /* here goes code that implements line completion. here is just simple example, it may be more complex */
    char *completion = NULL;
    char *commands[COMMAND_COUNT] = { "hello", "world", "linenoise" };

    size_t len = strlen(line);

    int i;
    for (i = 0; i < COMMAND_COUNT; i++) {
	if (strncmp(commands[i],line,len) == 0) {
	    size_t complen = strlen(commands[i] + len);
	    completion = calloc(complen, sizeof(char));
	    strncpy(completion, commands[i]+len, complen);
	}
    }
    /* in case of more than one command we can out here possible options */

    return completion;
}

int main(void) {
    linenoiseCompletionSetFunc(&completeLine); /* registering tab handler */
    linenoiseHistoryOpen("./history"); /* loading existing history file */

    char *line;

    while((line = linenoise("hello> ")) != NULL) {
        if (line[0] != '\0') {
            printf("echo: '%s'\n", line);
            linenoiseHistoryAdd(line);
        }
        free(line);
    }

    linenoiseHistoryClose();
    return 0;
}
