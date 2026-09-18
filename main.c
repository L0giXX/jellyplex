#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct {
    char *data;
    size_t size;
} Response;

// *data zeigt auf die neuen Daten von libcurl
// nmemb = Number of Members
size_t write_callback(char *data, size_t size, size_t nmemb, void *userdata) {
    // userdata ist der Pointer, den wir über CURLOPT_WRITEDATA übergeben haben
    Response *response = userdata;
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


int main(void) {
    CURL *curl = curl_easy_init();
    CURLcode result;

    if (curl == NULL) {
        fprintf(stderr, "Could not initialize curl\n");
        return 1;
    }

    Response response = {
        .data = NULL,
        .size = 0,
    };

    curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.104:8096/System/Info/Public");
    // Funktion festlegen, die empfangene Daten verarbeitet
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    // &response wird als userdata an write_callback weitergegeben
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        fprintf(stderr, "curl error: %s\n", curl_easy_strerror(result));

        free(response.data);
        curl_easy_cleanup(curl);
        return 1;
    }

    printf("%s\n", response.data);
    free(response.data);
    curl_easy_cleanup(curl);

    return 0;
}
