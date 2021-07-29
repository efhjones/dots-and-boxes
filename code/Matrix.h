#ifndef MATRIX_H__
#define MATRIX_H__

#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include "Vertex.h"

using namespace std;

class Matrix {
public:
  Matrix(int size);
  ~Matrix();
  void Print();
  void Clear();
  int Size();
  shared_ptr<Vertex> getNodeAt(int x, int y);
  bool addEdgeBetween(shared_ptr<Vertex> a, shared_ptr<Vertex> b);
  int numSquaresMade(shared_ptr<Vertex> a, shared_ptr<Vertex> b);
  bool allEdgesFull();
  
private:
  vector<vector<shared_ptr<Vertex>>> matrix_;
  int available_edges_;
  int occupied_edges_;
  int size_;
};

#endif // MATRIX_H__