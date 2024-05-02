#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_KEY_SIZE 50
#define STARTING_BUCKETS 8
#define PRIME_NUMBER 53
struct Node {
  char *key;
  void *value;
  struct Node *next;
};
typedef struct Hashmap {
  size_t size;
  struct Node **buckets;
} Hashmap;
size_t hash(char *s, size_t bucket_size) {
  const int p = PRIME_NUMBER;
  size_t n = strlen(s);
  // hash(s) = ( s[0] + s[1]*p + s[2]*p^2 + ... + s[n-1]*p^(n-1)) % bucket_size
  const int m = 1e9 + 9;
  size_t hash_value = 0;
  size_t p_pow = 1;
  for (size_t i = 0; i < n; i++) {
    // can be faster if we store it
    hash_value = (hash_value + s[i] * p_pow) % bucket_size;
    p_pow = (p_pow * p) % bucket_size;
  }
  return hash_value;
}
Hashmap *Hashmap_new(void) {
  Hashmap *hashmap = malloc(sizeof(Hashmap));
  hashmap->size = STARTING_BUCKETS;
  hashmap->buckets = malloc(sizeof(struct Node *) * STARTING_BUCKETS);
  for (size_t i = 0; i < STARTING_BUCKETS; i++) {
    hashmap->buckets[i] = NULL;
  }
  return hashmap;
}
void Hashmap_set(Hashmap *h, char *key, void *value) {
  size_t index = hash(key, h->size);
  if (h->buckets[index] == NULL) {
    h->buckets[index] = malloc(sizeof(struct Node));
    h->buckets[index]->key = malloc(sizeof(char) * strlen(key));
    strcpy(h->buckets[index]->key, key);
    h->buckets[index]->value = value;
    h->buckets[index]->next = NULL;
    return;
  }

  struct Node *tmp = h->buckets[index];
  while (strcmp(tmp->key, key) != 0 && tmp->next != NULL) {
    tmp = tmp->next;
  }

  if (strcmp(tmp->key, key) == 0) {
    tmp->value = value;
  } else {
    tmp->next = malloc(sizeof(struct Node));
    tmp->next->key = malloc(sizeof(char) * strlen(key));
    strcpy(tmp->next->key, key);
    tmp->next->value = value;
    tmp->next->next = NULL;
    return;
  }
}
void *Hashmap_get(Hashmap *h, char *key) {
  size_t index = hash(key, h->size);
  struct Node *tmp = h->buckets[index];
  if (tmp == NULL) {
    return NULL;
  }
  while (strcmp(tmp->key, key) != 0 && tmp->next != NULL) {
    tmp = tmp->next;
  }
  if (strcmp(tmp->key, key) == 0) {
    return tmp->value;
  } else {
    return NULL;
  }
}
void Hashmap_delete(Hashmap *h, char *key) {
  size_t index = hash(key, h->size);
  struct Node *tmp = h->buckets[index];
  if (tmp == NULL) {
    return;
  }
  if (strcmp(tmp->key, key) == 0) {
    struct Node *cur = tmp->next;
    h->buckets[index] = cur;
    free(tmp);
    return;
  }
  while (tmp->next != NULL && strcmp(tmp->next->key, key) != 0) {
    tmp = tmp->next;
  }
  if (tmp->next == NULL) {
    return;
  } else {
    struct Node *cur = tmp->next;
    tmp->next = tmp->next->next;
    free(cur);
  }
}
void Hashmap_free(Hashmap *h) {
  for (size_t i = 0; i < h->size; i++) {
    if (h->buckets[i] == NULL) {
      return;
    }
    struct Node *tmp = h->buckets[i];
    while (tmp->next != NULL) {
      struct Node *nxt = tmp->next;
      free(tmp);
      tmp = nxt;
    }
    free(tmp);
    h->buckets[i] = NULL;
  }
  free(h);
  h = NULL;
}

int main() {
  Hashmap *h = Hashmap_new();

  // basic get/set functionality
  int a = 5;
  float b = 7.2;
  Hashmap_set(h, "item a", &a);
  Hashmap_set(h, "item b", &b);
  assert(Hashmap_get(h, "item a") == &a);
  assert(Hashmap_get(h, "item b") == &b);

  // using the same key should override the previous value
  int c = 20;
  Hashmap_set(h, "item a", &c);
  assert(Hashmap_get(h, "item a") == &c);

  // basic delete functionality
  Hashmap_delete(h, "item a");
  assert(Hashmap_get(h, "item a") == NULL);

  // handle collisions correctly
  // note: this doesn't necessarily test expansion
  int i, n = STARTING_BUCKETS * 10, ns[n];

  char key[MAX_KEY_SIZE];
  for (i = 0; i < n; i++) {
    ns[i] = i;
    sprintf(key, "item %d", i);
    Hashmap_set(h, key, &ns[i]);
  }
  for (i = 0; i < n; i++) {
    sprintf(key, "item %d", i);
    assert(Hashmap_get(h, key) == &ns[i]);
  }

  Hashmap_free(h);
  /*
     stretch goals:
     - expand the underlying array if we start to get a lot of collisions
     - support non-string keys
     - try different hash functions
     - switch from chaining to open addressing
     - use a sophisticated rehashing scheme to avoid clustered collisions
     - implement some features from Python dicts, such as reducing space use,
     maintaing key ordering etc. see https://www.youtube.com/watch?v=npw4s1QTmPg
     for ideas
     */
  printf("ok\n");
}
