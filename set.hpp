#pragma once

#include "searchable_bag.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

class set {
 protected:
  searchable_bag *bag;

 public:
  set(searchable_bag &);
  set(const set &);
  set &operator=(const set &);
  ~set();

  void insert(int);
  void insert(int *, int);
  bool has(int) const;
  void print() const;
  void clear();

  searchable_bag &get_bag();
};
