#include "Vertex.h"
#include <iostream>

Vertex::Vertex(int theX, int theY) {
  data_ = to_string(theX) + "," + to_string(theY);
  x = theX;
  y = theY;
};

Vertex::~Vertex() {};

bool Vertex::hasEdgeWith(shared_ptr<Vertex> vertex) {
  if (vertex) {
    string data = vertex->getData();
    shared_ptr<Vertex> vertexInMap = edges_[data];
    if (vertexInMap){
      return true;
    }
  }
  return false;
};

bool Vertex::addEdge(shared_ptr<Vertex> vertex) {
  if (vertex) {
    if (!hasEdgeWith(vertex)) {
      edges_[vertex->getData()] = vertex;
      return true;
    }
  }
  return false;
};

bool Vertex::removeEdge(shared_ptr<Vertex> vertex) {
  if (vertex) {
    if (hasEdgeWith(vertex)) {
      edges_[vertex->getData()] = NULL;
      return true;
    }
  }
  return false;
}

map<string, shared_ptr<Vertex>> Vertex::getEdges() {
  return edges_;
};

string Vertex::getData() {
  try {
    return data_;
  } catch (...) {
    cout << "something went wrong" << endl;
  }
}

void Vertex::clearEdges() {
  edges_.clear();
}

int Vertex::numEdges() {
  int numEdges = 0;
  for (map<string, shared_ptr<Vertex>>::iterator it = edges_.begin(); it != edges_.end(); ++it) {
    if (it->second) {
      numEdges++;
    }
  }
  return numEdges;
}

int Vertex::isEdgeVertex(int matrixSize) {
  return !isCornerVertex(matrixSize) && (y == 0 || y == matrixSize - 1 || x == 0 || x == matrixSize - 1);
}

int Vertex::isCornerVertex(int matrixSize) {
  return (x == 0 && y == 0) || (x == matrixSize - 1 && y == 0) || (x == 0 && y == matrixSize - 1) || (x == matrixSize - 1 && y == matrixSize - 1);
}

int Vertex::maxEdges(int matrixSize) {
  if (isEdgeVertex(matrixSize)){
    return 3;
  } else if (isCornerVertex(matrixSize)) {
    return 2;
  } else {
    return 4;
  }
}

bool Vertex::isFull(int matrixSize) {
  int edges = numEdges();
  int max = maxEdges(matrixSize);
  return numEdges() == maxEdges(matrixSize);
}