#include "hash_table.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int collisions = 0;
int total_equals = 0;

int get_equal() { return total_equals; }
int get_total_collisions() { return collisions; }

hash_table_t *init_hash_table(int size) {
  hash_table_t *hash_table_instance;
  
  hash_table_instance = (hash_table_t *)malloc(sizeof(hash_table_t);

  if (hash_table_instance == NULL) {
    return NULL;
  }
  hash_table_instance->table = malloc(sizeof(url_dict_t *) * size);
  if (hash_table_instance->table == NULL) {
    return NULL;
  }

  for (int i = 0; i < size; i++) {
    hash_table_instance->table[i] = NULL;
  }

  hash_table_instance->length = size;
  hash_table_instance->count = 0;

  return hash_table_instance;
}

int ht_hash(hash_table_t *hash_table_members, char *shortened_url_key) {
  int i = 0;
  int hash_value = 0;

  while (shortened_url[i] != '\0' && hash_value < INT_MAX) {
    if (i % 2 == 0)
      hash_value >> 8;
    else {
      int char_value = (int) shortened_url[i];
      hash_value += char_value;
      hash_value *= char_value;
    }

  }

  return hash_value % hash_table_members->length;
}

url_dict_t *init_hash_tableNovourl_dict_t(char *shortened_url_key, char *big_url) {
  url_dict_t *url_assoc;
  url_assoc = malloc(sizeof(url_dict_t)));
  if (url_assoc == NULL) {
    return NULL;
  }

  strcpy(url_assoc->shortened_url, shortened_url_key);
  strcpy(url_assoc->big_url, big_url);

  return url_assoc;
}

void insert_into_hash_table(hash_table_t *hash_table_members, char *shortened_url_key, char *big_url_value) {
  int hash_position = 0;

  url_dict_t *base_position = NULL;

  hash_position = ht_hash(hash_table_members, shortened_url_key);

  base_position = hash_table_members->table[hash_position]; 

  // chave não existe
  if (base_position == NULL) {
    url_dict_t *new_assoc = init_hash_tableNovourl_dict_t(shortened_url_key, big_url_value);
    
    hash_table_members->table[hash_position] = new_assoc;
    hash_table_members->count++;

    return;
  }

  // chave existe
  if (strcmp(shortened_url_key, base_position->shortened_url) == 0) {
    total_equals++;
    strcpy(base_position->big_url, big_url_value); // sobrescrever

    return;
  } 

  // chave não existe, colidiu
  int i = hash_position + 1;

  if (i >= hash_table_members->length)
    i = 0; // circulando

  while (hash_table_members->table[i] != NULL) {

    // encontrou chave
    if (strcmp(shortened_url_key, hash_table_members->table[i]->shortened_url) == 0) {
      total_equals++;
      strcpy(hash_table_members->table[i]->big_url, big_url_value); // sobrescrever

      return;
    }

    i++;
    if (i >= hash_table_members->length) {
      i = 0; // circulando
    }
  }
  // chave não encontrada, inserir
  collisions++;

  if (i < hash_table_members->length) {
    url_dict_t *new_assoc = init_hash_tableNovourl_dict_t(shortened_url_key, big_url_value);
    hash_table_members->table[i] = new_assoc;
    hash_table_members->count++;
  }
}

char *search_by_key(hash_table_t *hash_table_members, char *short_url) {
  int hash_position = 0, i;
  url_dict_t *url_assoc;

  hash_position = ht_hash(hash_table_members, short_url);

  url_assoc = hash_table_members->table[hash_position];

  if (url_assoc == NULL) {
    return NULL;
  } else {
    i = hash_position;
    while (url_assoc != NULL) {
      if (strcmp(hash_table_members->table[i]->shortened_url, short_url) == 0)
        return hash_table_members->table[i]->big_url; // encontrou

      // se não continuar
      i++;
      if (i >= hash_table_members->length)
        i = 0; // circulando
      url_assoc = hash_table_members->table[i];
    }
  }

  return NULL; // nada
}

void free_hash_table(hash_table_t *hash_table_members) {
  url_dict_t *key;
  int size = hash_table_members->length;
  for (int i = 0; i < size; i++) {
    key = hash_table_members->table[i];
    if (key != NULL) {
      free(key);
    }
  }

  free(hash_table_members);
}
