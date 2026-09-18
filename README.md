# jellyplex

- Personal project for learning c
- For an actual synchronization tool go to: (https://github.com/luigi311/JellyPlex-Watched)
- Synchronize watches movies, series and episodes between Plex and Jellyfin

## TODO

### HTTP

* [x] libcurl einrichten
* [x] GET-Request an Jellyfin senden
* [x] Response in dynamischem Buffer speichern
* [x] Speicher mit `realloc()` vergrößern
* [x] Response-Buffer mit `free()` freigeben
* [x] HTTP-Code aus `main.c` in `http.c` / `http.h` auslagern
* [x] Fehlerbehandlung für HTTP-Statuscodes hinzufügen

### Jellyfin

* [x] JSON-Parser hinzufügen (z. B. cJSON)
* [ ] JSON-Parser in `http.c` / `http.h` auslagern (Response Funktion)
* [ ] `/System/Info/Public` parsen
* [ ] Servername und Version ausgeben
* [ ] Jellyfin API-Token über HTTP-Header mitsenden
* [ ] Eigene `jellyfin.c` / `jellyfin.h` erstellen
* [ ] Filmliste des Benutzers abrufen
* [ ] Filme in eigene `Movie`-Structs umwandeln
* [ ] Watched-Status eines Films auslesen

### Plex

* [ ] Verbindung zur Plex API herstellen
* [ ] Plex-Authentifizierung hinzufügen
* [ ] Eigene `plex.c` / `plex.h` erstellen
* [ ] Filmliste abrufen
* [ ] Filme in dieselbe interne Struktur umwandeln
* [ ] Watched-Status auslesen

### Synchronisierung

* [ ] Jellyfin- und Plex-Filme über IMDb/TMDB-ID matchen
* [ ] Unterschiede im Watched-Status anzeigen
* [ ] Dry-Run-Modus implementieren
* [ ] Filme auf Plex als watched markieren
* [ ] Filme auf Jellyfin als watched markieren
* [ ] Bidirektionalen Sync implementieren

### Später

* [ ] Serien und Episoden unterstützen
* [ ] Konfigurationsdatei für URLs und Tokens
* [ ] Secrets nicht in Git committen (`.gitignore`)
* [ ] SQLite für Sync-Historie
* [ ] Unwatched-Änderungen sicher synchronisieren
* [ ] CLI-Argumente wie `--dry-run` und `--verbose`

