#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define STARTING_CAPACITY 8

typedef struct DA {
  void **ptr;
  size_t length;
  size_t capacity;
} DA;

DA *DA_new(void) {
  DA *da = malloc(sizeof(DA));
  da->ptr = malloc(STARTING_CAPACITY * sizeof(void *));
  da->capacity = STARTING_CAPACITY;
  da->length = 0;
  return da;
}

int DA_size(DA *da) { return da->length; }

void DA_push(DA *da, void *x) {
  if (da->length == da->capacity) {
    void **new_ptr = malloc((da->capacity * 2) * sizeof(void *));
    for (int i = 0; i < da->length; i++) {
      new_ptr[i] = da->ptr[i];
    }
    void **old_ptr = da->ptr;
    da->ptr = new_ptr;
    free(old_ptr);
    da->capacity *= 2;
  }
  da->ptr[da->length] = x;
  da->length++;
}

void *DA_pop(DA *da) {
  // TODO pop from the end
  if (da->length == 0) {
    return NULL;
  }
  void *tmp = da->ptr[da->length - 1];
  if (da->length * 2 < da->capacity) {
    void **new_ptr = malloc((da->capacity / 2) * sizeof(void *));
    for (int i = 0; i < da->length - 1; i++) {
      new_ptr[i] = da->ptr[i];
    }
    void **old_ptr = da->ptr;
    da->ptr = new_ptr;
    free(old_ptr);
    da->capacity /= 2;
  }
  da->length--;
  return tmp;
}

void DA_set(DA *da, void *x, int i) {
  if (i < da->length) {
    da->ptr[i] = x;
  }
}

void *DA_get(DA *da, int i) {
  if (i < da->length) {
    return da->ptr[i];
  }
  return NULL;
}

void DA_free(DA *da) {
  free(da->ptr);
  free(da);
}

int main() {
  DA *da = DA_new();

  assert(DA_size(da) == 0);

  // basic push and pop test
  int x = 5;
  float y = 12.4;
  DA_push(da, &x);
  DA_push(da, &y);
  assert(DA_size(da) == 2);

  assert(DA_pop(da) == &y);
  assert(DA_size(da) == 1);

  assert(DA_pop(da) == &x);
  assert(DA_size(da) == 0);
  assert(DA_pop(da) == NULL);

  // basic set/get test
  DA_push(da, &x);
  DA_set(da, &y, 0);
  assert(DA_get(da, 0) == &y);
  DA_pop(da);
  assert(DA_size(da) == 0);

  // expansion test
  DA *da2 = DA_new(); // use another DA to show it doesn't get overriden
  DA_push(da2, &x);
  int i, n = 100 * STARTING_CAPACITY, arr[n];
  for (i = 0; i < n; i++) {
    arr[i] = i;
    DA_push(da, &arr[i]);
  }
  assert(DA_size(da) == n);
  for (i = 0; i < n; i++) {
    assert(DA_get(da, i) == &arr[i]);
  }
  for (; n; n--)
    DA_pop(da);
  assert(DA_size(da) == 0);
  assert(DA_pop(da2) == &x); // this will fail if da doesn't expand

  DA_free(da);
  DA_free(da2);
  printf("OK\n");
}
