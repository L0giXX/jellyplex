#include <stdio.h>

#include "jellyfin.h"

int main(void) {
    const char *url = "http://192.168.0.104:8096";
    JellyfinServerInfo response = jellyfin_get_server_info(url);

    printf("%s\n", response.name);
    printf("%s\n", response.version);

    jellyfin_free_server_info(&response);

    return 0;
}
