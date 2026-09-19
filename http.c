//
// Created by Marc Müller on 18.09.26.
//

#include "http.h"

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// *data zeigt auf die neuen Daten von libcurl
// nmemb = Number of Members
static size_t write_callback(char *data, size_t size, size_t nmemb, void *userdata) {
    // userdata ist der Pointer, den wir über CURLOPT_WRITEDATA übergeben haben
    HttpResponse *response = userdata;

    // Tatsächliche Anzahl der neu empfangenen Bytes
    size_t len = size * nmemb;

    // Buffer vergrößern: bisherige Daten + neue Daten + '\0'
    char *ptr = realloc(response->data, response->size + len + 1);
    if (!ptr) return 0;

    response->data = ptr; // neue Addresse des Speichers mit mehr Platz
    memcpy(response->data + response->size, data, len);

    response->size += len;
    // Null-Terminator setzen, damit response->data ein gültiger C-String ist
    response->data[response->size] = '\0';
    
    return len;
}

void http_response_free(HttpResponse *response) {
    free(response->data);
    response->data = NULL;
    response->size = 0;
}

HttpResponse http_get(const char *url) {
    HttpResponse response = {
        .data = NULL,
        .size = 0,
        .status = 0,
        .success = 0
    };

    CURL *curl = curl_easy_init();
    if (curl == NULL) {
        fprintf(stderr, "Could not initialize curl\n");
        return response;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    // Funktion festlegen, die empfangene Daten verarbeitet
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    // &response wird als userdata an write_callback weitergegeben
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));
        http_response_free(&response);
        curl_easy_cleanup(curl);
        return response;
    }

    response.success = 1;

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response.status);
    curl_easy_cleanup(curl);

    return response;
}
