//
// Created by Administrador on 21/12/2023.
//

#ifndef CACHELRU_CACHE_H
#define CACHELRU_CACHE_H
#define CANT_PAGINAS 128

typedef struct pagina{
    int numeroPagina;
    struct pagina * sig;
    struct pagina * ant;
}Pagina;

typedef struct cache{
    int capacidad;
    int tamanio;
    Pagina * cache;
    Pagina * end;
}Cache;

Pagina * newPagina(int numPagina);
Cache * newCache(int capacidad);

void insertInCache(Pagina * pagina, Cache * cache);
void eliminarCache(Cache * cache);
void moveInCache(int numSolicitado, Cache * cache);
void solicitarPagina(int numSolicitado, Cache * cache);

int hashFn(int numPagina);
void inicializarHashTable();


#endif //CACHELRU_CACHE_H
