#ifndef VERTEX_H__
#define VERTEX_H__

#include <memory>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Vertex {
public:
  Vertex(int x, int y);
  ~Vertex();
  int x;
  int y;
  bool hasEdgeWith(shared_ptr<Vertex> vertex);
  bool addEdge(shared_ptr<Vertex> vertex);
  bool removeEdge(shared_ptr<Vertex> vertex);
  void clearEdges();
  int numEdges();
  int isEdgeVertex(int matrixSize);
  int isCornerVertex(int matrixSize);
  int maxEdges(int matrixSize);
  bool isFull(int matrixSize);

  string getData();
  map<string, shared_ptr<Vertex>> getEdges();
  
private:
  map<string, shared_ptr<Vertex>> edges_;
  string data_;
};

#endif // VERTEX_H__