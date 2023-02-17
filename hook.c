#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include <freetype/freetype.h>

#include "filter.h"

static int (*orig_FT_New_Face)( FT_Library   library,
                                const char*  filepathname,
                                FT_Long      face_index,
                                FT_Face     *aface ) = NULL;

static __attribute__((constructor(14514))) void init(void) {
    printf("lolifont_hook: init\n");
    orig_FT_New_Face = dlsym(RTLD_NEXT, "FT_New_Face");
    if (!orig_FT_New_Face) {
            perror("lolifont_hook: dlsym FT_New_Face failed");
            abort();
    }
}

int FT_New_Face( FT_Library   library,
                 const char*  filepathname,
                 FT_Long      face_index,
                 FT_Face     *aface ) {
    if (!orig_FT_New_Face) {
        fprintf(stderr, "lolifont_hook: FT_New_Face is NULL\n");
        abort();
    }

    return orig_FT_New_Face(library, handle_font(filepathname), face_index, aface);
}
