#include "Matrix.h"


string get_indentation(int iteration) {
  string ind = "";
  int i = 0;
  while (i < iteration) {
      ind += " ";
      i++;
  }
  return ind;
}

void Matrix::Clear() {
  for (int x = 0; x < Size(); x++) {
    for (int y = 0; y < Size(); y++) {
      shared_ptr<Vertex> node = getNodeAt(x, y);
      node->clearEdges();
    }
  }
}

void Matrix::Print() {
  for (int line = 0; line < Size(); line++) {
    cout << "-------";
  }
  cout << endl << endl;

  for (int y = Size() - 1; y >= 0; y--) {
    for (int x = 0; x < Size(); x++) {
      // print x
      shared_ptr<Vertex> a = getNodeAt(x, y);
      string aData = a->getData();
      cout << aData;
      // if connected to next x, print line
      bool hasRightEdge = false;
      if (x + 1 < Size()) {
        shared_ptr<Vertex> b = getNodeAt(x + 1, y);
        if (a->hasEdgeWith(b)){
          hasRightEdge = true;
          cout << "----";
        }
      }
      if (!hasRightEdge) {
        cout << "    ";
      }
    }
    cout << endl;
    if (y >= 1) {
      for (int x = 0; x < Size(); x++) {
        // if curr x at curr y has edge with lower y
        shared_ptr<Vertex> currY = getNodeAt(x, y);
        shared_ptr<Vertex> lowerY = getNodeAt(x, y - 1);
        string edgeWithLine = " |     ";
        string space = "       ";
        if (currY && lowerY) {
          if (currY->hasEdgeWith(lowerY)) {
            cout << edgeWithLine;
          } else {
            cout << space;
          }
        } else {
          cout << space;
        }
      }
    }
    cout << endl;
  }
  for (int line = 0; line < Size(); line++) {
    cout << "-------";
  }
  cout << endl;
}


Matrix::Matrix(int size) {
  size_ = size;
  matrix_ = {};
  occupied_edges_ = 0;
  available_edges_ = 0;
  for (int x = 0; x < size; x++) {
    vector<shared_ptr<Vertex>> column = {};
    for (int y = 0; y < size; y++) {
      shared_ptr<Vertex> v(new Vertex(x, y));
      available_edges_ += v->maxEdges(size);
      column.push_back(v);
    }
    matrix_.push_back(column);
  }
};

Matrix::~Matrix() {};

int Matrix::Size() {
  return size_;
}

shared_ptr<Vertex> Matrix::getNodeAt(int x, int y) {
  if (x < Size() && y < Size() && x >= 0 && y >= 0) {
    return matrix_.at(x).at(y);
  }
  return NULL;
}

bool Matrix::addEdgeBetween(shared_ptr<Vertex> a, shared_ptr<Vertex> b) {
  bool successA = false;
  bool successB = false;
  if (a && b) {
    int aX = a->x;
    int aY = a->y;
    int bX = b->x;
    int bY = b->y;
    if (abs(aX - bX) > 1) {
      return false;
    }
    if (abs(aY - bY) > 1) {
      return false;
    }
    int greaterX = aX > bX ? aX : bX;
    if (greaterX >= Size()) {
      return false;
    }
    int greaterY = aY > bY ? aY : bY;
    if (greaterY >= Size()) {
      return false;
    }
    int lesserX = aX < bX ? aX : bX;
    if (lesserX < 0) {
      return false;
    }
    int lesserY = aY < bY ? aY : bY;
    if (lesserY < 0) {
      return false;
    }
    bool sameDot = aX == bX && aY == bY;
    if (sameDot) {
      return false;
    }
    bool isDiagonal = aX != bX && aY != bY;
    if (isDiagonal) {
      return false;
    }
    successA = a->addEdge(b);
    successB = b->addEdge(a);
    if (!successA && successB) {
      b->removeEdge(a);
    }
    if (!successB && successA) {
      a->removeEdge(b);
    }
    if (successA && successB) {
      occupied_edges_ += 2;
    }
  }
  return successA && successB;
}

int Matrix::numSquaresMade(shared_ptr<Vertex> a, shared_ptr<Vertex> b){
  // if a and b are horizontal, check edges between upper and lower nodes
  int numSquares = 0;
  bool isHorizontal = abs(a->x - b->x) == 1;
  if (isHorizontal) {
    if (a->y < Size() - 1) {
      shared_ptr<Vertex> aUpper = getNodeAt(a->x, a->y + 1);
      shared_ptr<Vertex> bUpper = getNodeAt(b->x, b->y + 1);
      bool hasMadeUpperSquare = aUpper->hasEdgeWith(a) && aUpper->hasEdgeWith(bUpper) && bUpper->hasEdgeWith(b);
      if (hasMadeUpperSquare) {
        numSquares += 1;
      }
    }
    if (a->y > 0) {
      shared_ptr<Vertex> aLower = getNodeAt(a->x, a->y - 1);
      shared_ptr<Vertex> bLower = getNodeAt(b->x, b->y - 1);
      bool hasMadeLowerSquare = aLower->hasEdgeWith(a) && aLower->hasEdgeWith(bLower) && bLower->hasEdgeWith(b);
      if (hasMadeLowerSquare) {
        numSquares += 1;
      }
    }
  } else {
  // if a and b are vertical, check edges between left and right nodes
    if (a->x < Size() - 1) {
      // check right side
      shared_ptr<Vertex> aRight = getNodeAt(a->x + 1, a->y);
      shared_ptr<Vertex> bRight = getNodeAt(b->x + 1, b->y);
      bool hasMadeRightSquare = aRight->hasEdgeWith(a) && aRight->hasEdgeWith(bRight) && bRight->hasEdgeWith(b);
      if (hasMadeRightSquare) {
        numSquares += 1;
      }
    }
    if (a->x > 0) {
      shared_ptr<Vertex> aLeft = getNodeAt(a->x - 1, a->y);
      shared_ptr<Vertex> bLeft = getNodeAt(b->x - 1, b->y);
      bool hasMadeLeftSquare = aLeft->hasEdgeWith(a) && aLeft->hasEdgeWith(bLeft) && bLeft->hasEdgeWith(b);
      if (hasMadeLeftSquare) {
        numSquares += 1;
      }
    }
  }
  return numSquares;
}

bool Matrix::allEdgesFull() {
  return available_edges_ == occupied_edges_;
}
