#include <stdlib.h>
#include <curl/curl.h>

#include "cJSON.h"
#include "http.h"

int main(void) {
    HttpResponse response = http_get("http://192.168.0.104:8096/System/Info/Public");

    if (!response.success) {
        fprintf(stderr, "HTTP request failed\n");
        http_response_free(&response);
        return 1;
    }

    if (response.status >= 400) {
        fprintf(stderr, "HTTP error: %ld\n", response.status);

        if (response.data != NULL) {
            fprintf(stderr, "Response: %s\n", response.data);
        }

        http_response_free(&response);
        return 1;
    }

    cJSON *json = cJSON_Parse(response.data);
    if (json == NULL) {
        fprintf(stderr, "Could not parse JSON\n");
        return 1;
    }
    char *result = cJSON_Print(json);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    }

    cJSON_Delete(json);
    http_response_free(&response);

    return 0;
}
