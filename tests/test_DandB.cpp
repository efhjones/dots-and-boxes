// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#define private public
#include "../code/Vertex.h"
#include "../code/Matrix.h"

using namespace std;

class test_DandB : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

TEST_F(test_DandB, TestMatrixInit) {
	Matrix matrix = Matrix(6);
	bool builtMatrix = true;
	for (int row = 0; row < matrix.Size(); row++) {
		for (int col = 0; col < matrix.Size(); col++) {
			string expected_data = to_string(row) + "," + to_string(col);
			if (matrix.getNodeAt(row, col)->getData() != expected_data) {
				builtMatrix = false;
			}
		}
	}
	ASSERT_TRUE(builtMatrix);
}

TEST_F(test_DandB, TestAddEdge) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> a, b;
	bool result;
	a = matrix.matrix_.at(4).at(1);
	b = matrix.matrix_.at(4).at(2);
	result = a->addEdge(b);
	ASSERT_TRUE(result);

	a = matrix.matrix_.at(4).at(1);
	b = matrix.matrix_.at(4).at(4);
	result = a->addEdge(b);
	ASSERT_TRUE(result);
}

TEST_F(test_DandB, TestAddEdgeBetween) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> a = matrix.matrix_.at(4).at(1);
	shared_ptr<Vertex> b = matrix.matrix_.at(4).at(2);
	bool result = matrix.addEdgeBetween(a, b);
	ASSERT_TRUE(result);	
}

TEST_F(test_DandB, TestHasEdgeWith) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> a = matrix.matrix_.at(4).at(1);
	shared_ptr<Vertex> b = matrix.matrix_.at(4).at(2);
	matrix.addEdgeBetween(a, b);

	map<string, shared_ptr<Vertex>> aEdges = a->getEdges();
	map<string, shared_ptr<Vertex>> bEdges = b->getEdges();
	// bool aContainsB = aEdges[b->getData()] != NULL;
	// bool bContainsA = bEdges[a->getData()] != NULL;
	ASSERT_TRUE(aEdges[b->getData()]);
	ASSERT_TRUE(bEdges[a->getData()]);
	ASSERT_TRUE(a->hasEdgeWith(b));
	ASSERT_TRUE(b->hasEdgeWith(a));

	shared_ptr<Vertex> c = matrix.matrix_.at(4).at(3);
	ASSERT_FALSE(aEdges[c->getData()]);
	ASSERT_FALSE(a->hasEdgeWith(c));
}

TEST_F(test_DandB, TestImpossibleEdgesDenied) {
	Matrix matrix = Matrix(6);
	matrix.Print();
	// too far apart on x axis
	shared_ptr<Vertex> a = matrix.getNodeAt(2, 2);
	shared_ptr<Vertex> b = matrix.getNodeAt(4, 2);
	bool tooFarX = matrix.addEdgeBetween(a, b);
	ASSERT_FALSE(tooFarX);

	// too far apart on y axis
	shared_ptr<Vertex> c = matrix.getNodeAt(1, 2);
	shared_ptr<Vertex> d = matrix.getNodeAt(1, 4);
	bool tooFarY = matrix.addEdgeBetween(c, d);
	ASSERT_FALSE(tooFarY);

	// nodes out of range x axis
	shared_ptr<Vertex> e = matrix.getNodeAt(6, 0);
	shared_ptr<Vertex> f = matrix.getNodeAt(7, 0);
	bool OutOfRangeX = matrix.addEdgeBetween(e, f);
	ASSERT_FALSE(OutOfRangeX);

	// nodes out of range y axis
	shared_ptr<Vertex> g = matrix.getNodeAt(0, 6);
	shared_ptr<Vertex> h = matrix.getNodeAt(0, 7);
	bool OutOfRangeY = matrix.addEdgeBetween(g, h);
	ASSERT_FALSE(OutOfRangeY);

	shared_ptr<Vertex> i = matrix.getNodeAt(1, 3);
	shared_ptr<Vertex> j = matrix.getNodeAt(2, 2);
	bool diagonalLine = matrix.addEdgeBetween(i, j);
	ASSERT_FALSE(diagonalLine);
}

TEST_F(test_DandB, TestSquaresMade) {
	Matrix matrix = Matrix(6);
	int numSquares = 0;
	shared_ptr<Vertex> a, b, c, d, e, f;

	a = matrix.getNodeAt(2,2);
	b = matrix.getNodeAt(3,2);
	c = matrix.getNodeAt(2,3);
	d = matrix.getNodeAt(3,3);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, c);
	numSquares = matrix.numSquaresMade(a, c);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, d);
	numSquares = matrix.numSquaresMade(b, d);
	ASSERT_EQ(1, numSquares);

	matrix.Print();
	matrix.Clear();

	a = matrix.getNodeAt(1,1);
	b = matrix.getNodeAt(1,2);
	c = matrix.getNodeAt(1,3);
	d = matrix.getNodeAt(2,3);
	e = matrix.getNodeAt(2,2);
	f = matrix.getNodeAt(2,1);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, c);
	numSquares = matrix.numSquaresMade(b, c);
	ASSERT_EQ(0, numSquares);
	
	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(d, e);
	numSquares = matrix.numSquaresMade(d, e);
	ASSERT_EQ(0, numSquares);
	
	matrix.addEdgeBetween(e, f);
	numSquares = matrix.numSquaresMade(e, f);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, f);
	numSquares = matrix.numSquaresMade(a, f);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, e);
	numSquares = matrix.numSquaresMade(b, e);
	ASSERT_EQ(2, numSquares);

	matrix.Print();
	matrix.Clear();

	a = matrix.getNodeAt(0, 1);
	b = matrix.getNodeAt(0, 2);
	c = matrix.getNodeAt(1, 2);
	d = matrix.getNodeAt(1, 1);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, c);
	numSquares = matrix.numSquaresMade(b, c);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, d);
	numSquares = matrix.numSquaresMade(a, d);
	ASSERT_EQ(1, numSquares);

	matrix.Print();
	matrix.Clear();

	a = matrix.getNodeAt(5, 2);
	b = matrix.getNodeAt(5, 1);
	c = matrix.getNodeAt(4, 1);
	d = matrix.getNodeAt(4, 2);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, c);
	numSquares = matrix.numSquaresMade(b, c);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, d);
	numSquares = matrix.numSquaresMade(a, d);
	ASSERT_EQ(1, numSquares);

	matrix.Print();
	matrix.Clear();

	a = matrix.getNodeAt(0, 0);
	b = matrix.getNodeAt(0, 1);
	c = matrix.getNodeAt(1, 1);
	d = matrix.getNodeAt(1, 0);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, c);
	numSquares = matrix.numSquaresMade(b, c);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, d);
	numSquares = matrix.numSquaresMade(a, d);
	ASSERT_EQ(1, numSquares);

	e = matrix.getNodeAt(2, 0);
	f = matrix.getNodeAt(2, 1);

	matrix.addEdgeBetween(e, f);
	numSquares = matrix.numSquaresMade(e, f);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(d, e);
	numSquares = matrix.numSquaresMade(d, e);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, f);
	numSquares = matrix.numSquaresMade(c, f);
	ASSERT_EQ(1, numSquares);

	matrix.Print();
	matrix.Clear();

	a = matrix.getNodeAt(0, 5);
	b = matrix.getNodeAt(1, 5);
	c = matrix.getNodeAt(1, 4);
	d = matrix.getNodeAt(0, 4);

	matrix.addEdgeBetween(a, b);
	numSquares = matrix.numSquaresMade(a, b);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(b, c);
	numSquares = matrix.numSquaresMade(b, c);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(c, d);
	numSquares = matrix.numSquaresMade(c, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(a, d);
	numSquares = matrix.numSquaresMade(a, d);
	ASSERT_EQ(1, numSquares);

	e = matrix.getNodeAt(0, 3);
	f = matrix.getNodeAt(1, 3);

	matrix.addEdgeBetween(e, f);
	numSquares = matrix.numSquaresMade(e, f);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(e, d);
	numSquares = matrix.numSquaresMade(e, d);
	ASSERT_EQ(0, numSquares);

	matrix.addEdgeBetween(f, c);
	numSquares = matrix.numSquaresMade(f, c);
	ASSERT_EQ(1, numSquares);

	matrix.Print();
	matrix.Clear();
}

TEST_F(test_DandB, TestIsEdgeVertex) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> edge = matrix.getNodeAt(1, 0);
	bool isEdge = edge->isEdgeVertex(matrix.Size());
	ASSERT_TRUE(isEdge);

	shared_ptr<Vertex> center = matrix.getNodeAt(2, 2);
	isEdge = center->isEdgeVertex(matrix.Size());
	ASSERT_FALSE(isEdge);

	shared_ptr<Vertex> corner = matrix.getNodeAt(0, 0);
	isEdge = corner->isEdgeVertex(matrix.Size());
	ASSERT_FALSE(isEdge);
}

TEST_F(test_DandB, TestIsCornerVertex) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> edge = matrix.getNodeAt(1, 0);
	bool isCorner = edge->isCornerVertex(matrix.Size());
	ASSERT_FALSE(isCorner);

	shared_ptr<Vertex> center = matrix.getNodeAt(2, 2);
	isCorner = center->isCornerVertex(matrix.Size());
	ASSERT_FALSE(isCorner);

	shared_ptr<Vertex> cornerOne = matrix.getNodeAt(0, 0);
	isCorner = cornerOne->isCornerVertex(matrix.Size());
	ASSERT_TRUE(isCorner);

	shared_ptr<Vertex> cornerTwo = matrix.getNodeAt(0, 5);
	isCorner = cornerTwo->isCornerVertex(matrix.Size());
	ASSERT_TRUE(isCorner);

	shared_ptr<Vertex> cornerThree = matrix.getNodeAt(5, 0);
	isCorner = cornerThree->isCornerVertex(matrix.Size());
	ASSERT_TRUE(isCorner);

	shared_ptr<Vertex> cornerFour = matrix.getNodeAt(5, 5);
	isCorner = cornerFour->isCornerVertex(matrix.Size());
	ASSERT_TRUE(isCorner);
}

TEST_F(test_DandB, TestMaxEdges) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> edge = matrix.getNodeAt(1, 0);
	int maxEdges = edge->maxEdges(matrix.Size());
	ASSERT_EQ(maxEdges, 3);

	shared_ptr<Vertex> mid = matrix.getNodeAt(2, 2);
	maxEdges = mid->maxEdges(matrix.Size());
	ASSERT_EQ(maxEdges, 4);

	shared_ptr<Vertex> corner = matrix.getNodeAt(0, 0);
	maxEdges = corner->maxEdges(matrix.Size());
	ASSERT_EQ(maxEdges, 2);
}

TEST_F(test_DandB, TestNumEdges) {
	Matrix matrix = Matrix(6);
	shared_ptr<Vertex> a, b, c, d;

	a = matrix.getNodeAt(1, 2);
	b = matrix.getNodeAt(2, 2);
	c = matrix.getNodeAt(2, 1);
	d = matrix.getNodeAt(1, 1);

	matrix.addEdgeBetween(a, b);
	int aEdges = a->numEdges();
	ASSERT_EQ(1, aEdges);

	matrix.addEdgeBetween(b, c);
	int bEdges = b->numEdges();
	ASSERT_EQ(2, bEdges);

	matrix.addEdgeBetween(c, d);
	int cEdges = c->numEdges();
	ASSERT_EQ(2, cEdges);

	matrix.addEdgeBetween(d, a);
	int dEdges = d->numEdges();
	ASSERT_EQ(2, dEdges);

	aEdges = a->numEdges();
	ASSERT_EQ(2, aEdges);
}

TEST_F(test_DandB, TestVertexFull) {
	Matrix matrix = Matrix(6);

	shared_ptr<Vertex> a, b, c, d, e;

	a = matrix.getNodeAt(2, 2);
	b = matrix.getNodeAt(2, 1);
	c = matrix.getNodeAt(2, 3);
	d = matrix.getNodeAt(1, 2);
	e = matrix.getNodeAt(3, 2);

	matrix.addEdgeBetween(a, b);
	matrix.addEdgeBetween(a, c);
	matrix.addEdgeBetween(a, d);
	matrix.addEdgeBetween(a, e);

	bool aIsFull = a->isFull(matrix.Size());
	ASSERT_TRUE(aIsFull);

	bool bIsFull = b->isFull(matrix.Size());
	ASSERT_FALSE(bIsFull);
}

TEST_F(test_DandB, TestMatrixFull) {
	Matrix matrix = Matrix(6);

	ASSERT_FALSE(matrix.allEdgesFull());

	for (int x = 0; x < matrix.Size(); x++){
		ASSERT_FALSE(matrix.allEdgesFull());
		for (int y = 0; y < matrix.Size(); y++) {
			shared_ptr<Vertex> node = matrix.getNodeAt(x, y);
			shared_ptr<Vertex> nodeLeft = matrix.getNodeAt(x - 1, y);
			shared_ptr<Vertex> nodeRight = matrix.getNodeAt(x + 1, y);
			shared_ptr<Vertex> nodeUp = matrix.getNodeAt(x, y + 1);
			shared_ptr<Vertex> nodeDown = matrix.getNodeAt(x, y - 1);
			matrix.addEdgeBetween(node, nodeLeft);
			matrix.addEdgeBetween(node, nodeRight);
			matrix.addEdgeBetween(node, nodeUp);
			matrix.addEdgeBetween(node, nodeDown);
		}
	}

	ASSERT_TRUE(matrix.allEdgesFull());

	Matrix matrix4 = Matrix(4);
	matrix4.Print();
	shared_ptr<Vertex> top, right, left, bottom, curr;
	for (int x = 0; x < matrix4.Size(); x++) {
		for (int y = 0; y < matrix4.Size(); y++) {
			curr = matrix4.getNodeAt(x, y);
			top = matrix4.getNodeAt(x + 1, y);
		}
	}
}