#include "collections.h"

#include <stdlib.h>


extern collection_iterator_traits_t collections_iterator_traits[];


collection_cyclic_iterator_t
collection_cyclic_iterator(collection_t collection, collection_container_t collection_container) {
  collection_cyclic_iterator_t iterator = NULL;

  if (!(iterator = (collection_cyclic_iterator_t)calloc(1, sizeof(struct collection_cyclic_iterator))))
    return NULL;
  iterator->container = collection_container;
  iterator->collection = collection;
  iterator->self = collections_iterator_traits[iterator->container].begin(collection);

  return iterator;
}

collection_cyclic_iterator_t
collection_cyclic_iterator_next(collection_cyclic_iterator_t iterator) {
  collection_iterator_traits_t iterator_traits = collections_iterator_traits[iterator->container];

  if ((iterator->self == iterator_traits.end(iterator->collection) || !iterator_traits.next(iterator->self)))
    iterator->self = iterator_traits.begin(iterator->collection);
  else
    iterator->self = iterator_traits.next(iterator->self);

  return iterator;
}

collection_cyclic_iterator_t
collection_cyclic_iterator_prev(collection_cyclic_iterator_t iterator) {
  collection_iterator_traits_t iterator_traits = collections_iterator_traits[iterator->container];

  if (iterator->self == iterator_traits.begin(iterator->collection))
    iterator->self = iterator_traits.end(iterator->collection);
  else
    iterator->self = iterator_traits.prev(iterator->self);

  return iterator;
}

collection_cyclic_iterator_t
collection_cyclic_iterator_begin(collection_cyclic_iterator_t iterator) {
  collection_iterator_traits_t iterator_traits = collections_iterator_traits[iterator->container];

  iterator->self = iterator_traits.begin(iterator->collection);

  return iterator;
}

collection_cyclic_iterator_t
collection_cyclic_iterator_end(collection_cyclic_iterator_t iterator) {
  collection_iterator_traits_t iterator_traits = collections_iterator_traits[iterator->container];

  iterator->self = iterator_traits.end(iterator->collection);

  return iterator;
}

void
collection_cyclic_iterator_free(collection_cyclic_iterator_t iterator) {
  if (iterator) {
    free(iterator);
  }
}
