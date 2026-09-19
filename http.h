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

/**
 * Makes a GET request to the specified url.
 *
 * @param url: The url where the request which should be sent to
 * @return: Returns a HttpResponse struct
 */
HttpResponse http_get(const char *url);

/**
 * Frees the memory allocated for an HttpResponse.
 *
 * @param response: The HttpResponse which should be freed
 */
void http_response_free(HttpResponse *response);

#endif //JELLYPLEX_HTTP_H
