#include <iostream>
#include "../code/Matrix.h"
#include <vector>
#include <regex>

using namespace std;

vector<int> getCoordsFromString(string coords) {
  regex comma ("\,*");
  string noCommas = regex_replace(coords, comma, "");
  string one = noCommas.substr(0, 1);
  int coord1 = stoi(one); 
  string two = noCommas.substr(1, 1);
  int coord2 = stoi(two); 
  return { coord1, coord2 };
}

bool isValidInput(string coords) { 
  regex pattern("\\d,\\d");
  bool matches = regex_match(coords, pattern);
  return matches;
}

void printPlayerPoints(int playerOnePoints, int playerTwoPoints) {
  cout << "Player 1 points: " << to_string(playerOnePoints) << endl;
  cout << "Player 2 points: " << to_string(playerTwoPoints) << endl;
}

void playerTurn(shared_ptr<Matrix> matrix, string playerName, int& playerPoints, bool& isGraphFull) {
  if (isGraphFull) {
    return;
  }
  string coords1, coords2;
  bool canGoAgain = false;
  bool addedValidLine = true;
  do {
    cout << "Player " << playerName << ", what's the starting point from which you'll draw your line?" << endl;
    cout << "For example, 2,2. Please don't use spaces!" << endl;
    cin.clear();
    cin >> coords1;
    while (!isValidInput(coords1)) {
      cout << "Sorry, that's not a valid point." << endl;
      cout << "Please enter the coordinates in the format x,y" << endl;
      cin.clear();
      cin >> coords1;
    }
    cout << "You chose " << coords1 << endl;
    cout << "Great. And the second point?" << endl;
    cin.clear();
    cin >> coords2;
    while (!isValidInput(coords2)) {
      cout << "Sorry, that's not a valid point." << endl;
      cout << "Please enter the coordinates in the format x,y" << endl;
      cin.clear();
      cin >> coords2;
    }

    vector<int> firstPoint = getCoordsFromString(coords1);
    vector<int> secondPoint = getCoordsFromString(coords2);

    shared_ptr<Vertex> player1FirstDot, player1SecondDot;

    player1FirstDot = matrix->getNodeAt(firstPoint[0], firstPoint[1]);
    player1SecondDot = matrix->getNodeAt(secondPoint[0], secondPoint[1]);

    addedValidLine = matrix->addEdgeBetween(player1FirstDot, player1SecondDot);

    if (addedValidLine == false){
      cout << "Sorry, that doesn't appear to be a valid line. Please try again." << endl;
      cout << "You can only draw a line between adjacent dots." << endl;
      matrix->Print();
    } else {
      matrix->Print();
      isGraphFull = matrix->allEdgesFull();
      int numSquares = matrix->numSquaresMade(player1FirstDot, player1SecondDot);
      if (numSquares > 0) {
        cout << "That's a point for player " << playerName << "!" << endl;
        playerPoints += numSquares;
        canGoAgain = true;
      } else {
        canGoAgain = false;
      }
    }
  } while (!isGraphFull && (!addedValidLine || canGoAgain));
}

int main(){

  cout << "Welcome to Dots and Boxes!" << endl << endl;

  cout << "The rules are simple: " << endl;
  cout << "  1. This is a two player game. Each player draws a line on the graph." << endl;
  cout << "  2. When a player draws a line that forms a square, they score a point." << endl;
  cout << "  3. If you draw a line that forms a square, you get to have another turn!" << endl;
  cout << "  4. If you draw a line that forms multiple squares, you get multiple points!" << endl;
  cout << "  5. When no more lines can be drawn, the game is over and the winner is the player who scored the most points." << endl << endl;
  cout << "Ready to play? Type y or n" << endl;

  string yesOrNo;
  cin >> yesOrNo;

  if (yesOrNo == "y") {
    cout << "Great! What size of graph would you like? Min: 2, Max: 8" << endl;
    int size;
    int player1Points = 0;
    int player2Points = 0;

    cin >> size;
    while (size < 2 || size > 8) {
      std::cout <<  "Whoa there! Please choose a graph size within the limits." << endl;
      cin >> size;
    }
    cout << "Awesome, you chose a graph size of " + to_string(size) + ". Isn't it pretty?" << endl;
    shared_ptr<Matrix> matrix (new Matrix(size));
    matrix->Print();

    int playerOnePoints = 0;
    int playerTwoPoints = 0;
    printPlayerPoints(playerOnePoints, playerTwoPoints);
    bool isGraphFull = matrix->allEdgesFull();

    while (!isGraphFull) {
      playerTurn(matrix, "one", playerOnePoints, isGraphFull);
      printPlayerPoints(playerOnePoints, playerTwoPoints);
      playerTurn(matrix, "two", playerTwoPoints, isGraphFull);
      printPlayerPoints(playerOnePoints, playerTwoPoints);
    }

    bool isTie = playerOnePoints == playerTwoPoints;
    if (isTie) { 
      cout << "Wow! A tie! I'm not even mad. I'm impressed." << endl;
      printPlayerPoints(playerOnePoints, playerTwoPoints);
      cout << "Good game!" << endl;
    } else {
      string winningPlayer = playerOnePoints > playerTwoPoints ? "Player 1" : "Player 2";
      cout << "*-*-*-* " << winningPlayer << " wins! " << " *-*-*-*" << endl;
      cout << "Points: " << endl;
      printPlayerPoints(playerOnePoints, playerTwoPoints);
      cout << "Good game!" << endl;
    }
  } else {
    cout << "Ok then. Bye bye!" << endl;
  }
  return 0;
}