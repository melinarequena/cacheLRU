//
// Created by Administrador on 21/12/2023.
//

#include "cache.h"
#include <stdlib.h>
#include <stdio.h>

Pagina * hashTable[CANT_PAGINAS];

Pagina *newPagina(int numPagina) {
    Pagina * new = NULL;
    new = malloc(sizeof(Pagina));
    if(!new){
        printf("Error\n");
        exit (-1);
    }
    new->ant = new->sig = NULL;
    new->numeroPagina = numPagina;

    return new;
}

Cache *newCache(int capacidad) {
    Cache * new = NULL;
    new = malloc(sizeof(Cache));
    if(!new){
        printf("Error\n");
        exit (-1);
    }
    new->tamanio = 0;
    new->capacidad = capacidad;
    new->cache = new->end = NULL;

    return new;
}

void insertInCache(Pagina *pagina, Cache *cache) {
    if(!cache->cache){
        cache->cache = pagina;
        cache->end = pagina;
        cache->tamanio++;
        return;
    }
    pagina->sig = cache->cache;
    cache->cache->ant = pagina;
    cache->cache = pagina;
    cache->tamanio++;
}

void moveInCache(int numSolicitado, Cache *cache) {
    Pagina * aux = cache->cache;
    while (aux && aux->numeroPagina != numSolicitado){
        aux = aux->sig;
    }
    if(aux && aux->numeroPagina == numSolicitado){
        aux->ant->sig = aux->sig;
        aux->sig->ant = aux->ant;
        aux->sig = cache->cache;
        cache->cache->ant = aux;
        cache->cache = aux;
    }
}

int eliminarCache(Cache *cache) {
    if(cache->tamanio == 0){
        printf("Cache vacio");
        return -100;
    }
    Pagina * aux = cache->end;
    cache->end = aux->ant;
    cache->end->sig = NULL;
    //free(aux);
    cache->tamanio--;
    return aux->numeroPagina;
}

int hashFn(int numPagina) {
    return numPagina%CANT_PAGINAS;
}

void inicializarHashTable() {
    for(int i=0; i<CANT_PAGINAS; i++){
        hashTable[i] = NULL;
    }
}

void solicitarPagina(int numSolicitado, Cache *cache) {
    if(cache->tamanio == cache->capacidad){
        printf("\nEliminada pagina %d\n", eliminarCache(cache));
    }
    Pagina * pagina = hashTable[numSolicitado];
    if(pagina == NULL){
        pagina = newPagina(numSolicitado);
        insertInCache(pagina, cache);
        insertarHashTable(pagina);
        return;
    }
    moveInCache(numSolicitado, cache);
}

void insertarHashTable(Pagina *pagina) {
    int pos = hashFn(pagina->numeroPagina);
    if(hashTable[pos] == NULL){
        hashTable[pos] = pagina;
        return;
    }
    pagina->sig = hashTable[pos];
    hashTable[pos]->ant = pagina;
    hashTable[pos] = pagina;

}

void printCache(Cache *cache) {
    if(cache->tamanio == 0){
        printf("Cache vacio\n");
        return;
    }
    Pagina * aux = cache->cache;
    while (aux){
        printf("%d\t", aux->numeroPagina);
        aux = aux->sig;
    }

}
