#include "set.hpp"
#include <cstdlib>

set::set(searchable_bag &src) : bag(0) {
  // try to detect dynamic type and copy
  searchable_array_bag *a = dynamic_cast<searchable_array_bag *>(&src);
  if (a != 0) {
    bag = new searchable_array_bag(*a);
    return;
  }
  searchable_tree_bag *t = dynamic_cast<searchable_tree_bag *>(&src);
  if (t != 0) {
    bag = new searchable_tree_bag(*t);
    return;
  }
  // fallback: no concrete type recognized; leave bag null
}

set::set(const set &src) : bag(0) {
  if (src.bag != 0) {
    // try copying known concrete types
    searchable_array_bag *a = dynamic_cast<searchable_array_bag *>(src.bag);
    if (a != 0) {
      bag = new searchable_array_bag(*a);
      return;
    }
    searchable_tree_bag *t = dynamic_cast<searchable_tree_bag *>(src.bag);
    if (t != 0) {
      bag = new searchable_tree_bag(*t);
      return;
    }
  }
}

set &set::operator=(const set &src) {
  if (this != &src) {
    if (bag != 0) {
      delete bag;
      bag = 0;
    }
    if (src.bag != 0) {
      searchable_array_bag *a = dynamic_cast<searchable_array_bag *>(src.bag);
      if (a != 0) {
        bag = new searchable_array_bag(*a);
      } else {
        searchable_tree_bag *t = dynamic_cast<searchable_tree_bag *>(src.bag);
        if (t != 0) {
          bag = new searchable_tree_bag(*t);
        }
      }
    }
  }
  return *this;
}

set::~set() {
  if (bag != 0)
    delete bag;
}

void set::insert(int item) {
  if (bag == NULL)
    return;
  if (!bag->has(item))
    bag->insert(item);
}

void set::insert(int *items, int count) {
  if (bag == NULL)
    return;
  for (int i = 0; i < count; ++i) {
    if (!bag->has(items[i]))
      bag->insert(items[i]);
  }
}

bool set::has(int item) const {
  if (bag == NULL)
    return false;
  return bag->has(item);
}

void set::print() const {
  if (bag != NULL)
    bag->print();
}

void set::clear() {
  if (bag != NULL)
    bag->clear();
}

searchable_bag &set::get_bag() { return *bag; }
