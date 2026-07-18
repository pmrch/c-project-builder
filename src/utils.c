#include <ctype.h>
#include <string.h>

#include "utils.h"
#include "log.h"

void normalize_whitespaces(char *s) {
    if (s == NULL) {
        LOG_WARN("Not normalizing whitespaces, passed NULL");
        return;
    }

    char *read_ptr = s;
    char *write_ptr = s;
    unsigned int found_whitespace = 0;

    while (*read_ptr != '\0') {
        if (isspace(*read_ptr)) {
            if (++found_whitespace == 1) {
                *write_ptr++ = ' ';
            }
        } else {
            *write_ptr++ = *read_ptr;
            found_whitespace = 0;
        }

        read_ptr++;
    }

    *write_ptr = '\0';
    return;
}