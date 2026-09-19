//
// Created by Marc Müller on 19.09.26.
//

#ifndef JELLYPLEX_JELLYFIN_H
#define JELLYPLEX_JELLYFIN_H

typedef struct {
    char *name;
    char *version;
} JellyfinServerInfo;

JellyfinServerInfo jellyfin_get_server_info(const char *url);

void jellyfin_free_server_info(JellyfinServerInfo *info);

#endif //JELLYPLEX_JELLYFIN_H
