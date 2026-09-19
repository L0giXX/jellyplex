//
// Created by Marc Müller on 19.09.26.
//

#include "jellyfin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cJSON.h"
#include "http.h"

JellyfinServerInfo jellyfin_get_server_info(const char *url) {
    JellyfinServerInfo info = {
        .name = NULL,
        .version = NULL
    };

    const char *endpoint = "/System/Info/Public";

    char *request_url = malloc(strlen(url) + strlen(endpoint) + 1);

    if (request_url == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        return info;
    }

    strcpy(request_url, url);
    strcat(request_url, endpoint);


    HttpResponse res = http_get(request_url);

    if (!res.success) {
        fprintf(stderr, "HTTP request failed\n");
        http_response_free(&res);

        free(request_url);

        return info;
    }

    if (res.status != 200) {
        fprintf(stderr, "HTTP request failed\n");
        fprintf(stderr, "HTTP status code: %ld\n", res.status);

        http_response_free(&res);
        free(request_url);

        return info;
    }

    cJSON *json = cJSON_Parse(res.data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }

        http_response_free(&res);
        free(request_url);

        return info;
    }

    http_response_free(&res);
    free(request_url);

    cJSON *server_name = cJSON_GetObjectItem(json, "ServerName");
    cJSON *server_version = cJSON_GetObjectItem(json, "Version");

    char *temp = server_name->valuestring;
    info.name = malloc(strlen(temp) + 1);
    if (info.name == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        cJSON_Delete(json);
        return info;
    }
    strcpy(info.name, temp);

    temp = server_version->valuestring;
    info.version = malloc(strlen(temp) + 1);
    if (info.version == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        cJSON_Delete(json);
        return info;
    }
    strcpy(info.version, temp);

    cJSON_Delete(json);

    return info;
}

void jellyfin_free_server_info(JellyfinServerInfo *info) {
    free(info->name);
    free(info->version);

    info->name = NULL;
    info->version = NULL;
}
