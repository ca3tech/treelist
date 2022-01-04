# treelist

## Introduction

This repository defines a C++ library containing a single template class
named TreeList and some supporting entities. TreeList provides you an API
for storing and retrieving items by noncontiguous index. As you might have
guessed from the name a tree, specifically a self balancing binary tree,
is used. As such the runtime for all operations is O(log n).

## API

```{c++}
TreeList<T>::TreeList()
```
+ This is the only constructor

```{c++}
void TreeList<T>::set(unsigned int i, T& data)
```
+ Store item **data** at index **i**

```{c++}
T* TreeList<T>::operator[] (unsigned int i)
```
+ Retrieve a pointer to the item stored at index **i**;
  if no item has been stored at index **i** then a **nullptr** will be returned

```{c++}
T* TreeList<T>::remove(unsigned int i)
```
+ Remove item stored at index **i** and return a pointer to the
  removed item; if no item has been stored at index **i** then
  a **nullptr** will be returned

```{c++}
int TreeList<T>::length()
```
+ Get the list length; the value returned will be **max** + 1

```{c++}
int TreeList<T>::max()
```
+ Get the maximum index for which an item has been stored

```{c++}
int TreeList<T>::min()
```
+ Get the minimal index for which an item has been stored

## Usage

```{c++}
#include <TreeList.h>

using namespace std;

// Create the tree object
TreeList<int> tr;

// Add some items
int data[5] = {1, 2, 3, 4, 5};
int j = 0;
for(int i = 2; i < 12; i+=2) {
  tr.set(i, data[j++]);
}

// You can iterate through the list using indices
for(int i = 0; i < tr.length(); i++) {
  int* item = tr[i];
  if(item) {
    cout << "[" << i << "]: " << item << endl;
  } else {
    cout << "No item at index " << i << endl;
  }
}

// You can iterate from smallest to largest index with an iterator
// Note that using an iterator we don't need to worry about index
// positions for which no item has been stored
for(int x : tr) {
  cout << x << endl;
}

// You can iterate from largest to smallest index with an iterator
for(auto it = t.rbegin(), end = t.rend(); it != end; ++it) {
  cout << *it << endl;
}
```