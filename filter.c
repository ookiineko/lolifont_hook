#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUFFIX_COUNT				3
#define SUFFIX_LENGTH				3
#define PREFIX_LENGTH				17

static const char *LOLIFONT			= "/home/yurri/Documents/fonts/Heiti.ttc";
static const char *PREFIX			= "/usr/share/fonts/";
static const char *SUFFIXES[SUFFIX_COUNT]	= {"ttf", "ttc", "otf"};

const char *handle_font(const char *filepathname) {
    size_t length, i;
    char *buff = NULL;

    if (!filepathname) {
        fprintf(stderr, "lolifont_hook: filter: filepathname is NULL\n");
        goto exit;
    }

    length = strlen(filepathname);

    if (length < PREFIX_LENGTH) {
#ifdef DEBUG
        printf("lolifont_hook: filter: '%s' is too short\n", filepathname);
#endif
        goto exit;
    }

    if (strncmp(filepathname, PREFIX, PREFIX_LENGTH)) {
#ifdef DEBUG
        printf("lolifont_hook: filter: '%s' is not starting with the prefix\n", filepathname);
#endif
        goto exit;
    }

    buff = (typeof(buff)) malloc(sizeof(char) * (length + 1));

    for (i = 0; i < length; i++)
        buff[i] = (char) toupper(filepathname[i]);

    buff[length] = '\0';

    if (strstr(buff, "MONO")) {  // mono font
#ifdef DEBUG
        printf("lolifont_hook: filter: '%s' is mono font\n", filepathname);
#endif
        goto exit;
    }

    free(buff);

    for (i = 0; i < SUFFIX_COUNT; i++) {
        if (!strncmp(filepathname + length - SUFFIX_LENGTH, SUFFIXES[i], SUFFIX_LENGTH)) {  // endswith one of the suffixes
#ifdef DEBUG
            printf("lolifont_hook: filter: matched '%s'\n", filepathname);
#endif
            return LOLIFONT;  // replace with lolifont
        }
    }

exit:
    if (buff)
        free(buff);

#ifdef DEBUG
    printf("lolifont_hook: filter: '%s' is unmatched\n", filepathname);
#endif
    return filepathname;  // use the original font
}
