#include <stdio.h>
#include "cache.h"

int main() {

    Cache * cache = newCache(5);
    inicializarHashTable();

    printCache(cache);

    solicitarPagina(2, cache);
    solicitarPagina(4, cache);
    solicitarPagina(1, cache);
    solicitarPagina(7, cache);
    solicitarPagina(9, cache);

    printCache(cache);

    return 0;
}
