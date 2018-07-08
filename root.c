#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "root.h"

char* exec(char* command) {
	printf("DEBUG: EXEC: %s\n", command);

	FILE *fp;
        char path[1035];
        char* output = (char*) malloc(2048 * sizeof(char));
	strcpy(output, "");

        /* Open the command for reading. */
        fp = popen(command, "r");
        if (fp == NULL) {
                printf("Failed to run command\n" );
                exit(1);
        }

        /* Read the output a line at a time - output it. */
        while (fgets(path, sizeof(path)-1, fp) != NULL) {
                strcat(output, path);
        }

        /* close */
        pclose(fp);
        return output;
}

