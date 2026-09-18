//
// Created by Marc Müller on 18.09.26.
//

#ifndef JELLYPLEX_HTTP_H
#define JELLYPLEX_HTTP_H
#include <stddef.h>

typedef struct {
    char *data;
    size_t size;
    long status;
    int success;
} HttpResponse;

// Führt einen GET-Request aus
HttpResponse http_get(const char *url);

// Gibt Speicher einer Response wieder frei
void http_response_free(HttpResponse *response);

#endif //JELLYPLEX_HTTP_H
