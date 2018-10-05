#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <stdio.h>

class Matrix{
  static const int n = 4;
  int matrix[n][n];
  int score;
public:
  void init();
  void move(int, bool&);
  void printTest();
  bool isOver();
  int  getElement(int, int);
  void printFormat();
  int  getScore();
};

int Matrix::getScore(){
	return score;
}

int Matrix::getElement(int line, int col){
	return matrix[line][col];
}

bool Matrix::isOver(){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      if(!matrix[i][j])
        return false;
      if(j < n-1 && matrix[i][j] == matrix[i][j+1])
        return false;
      if(j > 0 && matrix[i][j] == matrix[i][j-1])
        return false;
      if(i < n-1 && matrix[i][j] == matrix[i+1][j])
        return false;
      if(i > 0 && matrix[i][j] == matrix[i-1][j])
        return false;
    }
  }
  return true;
}

void Matrix::printTest(){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j)
      std::cout << matrix[i][j];
    std::cout << "\n";
  }
}

void Matrix::printFormat(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			std::cout << "| " << matrix[i][j] << " |";
		}
		std::cout << "\n";
	}
}

void Matrix::init(){
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < n; ++j)
      matrix[i][j] = 0;
  srand(time(0));
  int i1 = rand() % n;
  int i2 = rand() % n;
  int j1 = rand() % n;
  int j2 = rand() % n;
  //  int i1 = 0, i2 = 0, j1 = 1, j2 = 3;
  matrix[i1][j1] = matrix[i2][j2] = 2;
}

/*  -2
  -1  1
     2
 */

void Matrix::move(int direction, bool& gameover){
  auto newEl = [&](){
                 srand(time(0));
                 int ri = rand() % n, rj = rand() % n;
                 while(matrix[ri][rj])ri = rand() % n, rj = rand() % n;
                 matrix[ri][rj] = 2;
               };
  if(isOver()){
    std::cout << "Game over!";
    gameover = true;
  } else {
    gameover = false;
  switch (direction){
    //move left
  case -1:
    for(int i = 0; i < n; ++i){
      for(int j = n-1; j > 0; --j){
        if(matrix[i][j] && (!matrix[i][j-1] || matrix[i][j-1] == matrix[i][j])){
          int aux = j-1;
          while(aux > 0 && !matrix[i][aux]) --aux;
          if(matrix[i][aux] == matrix[i][j]) matrix[i][aux] *= 2,
			score += matrix[i][aux];
          else if(!matrix[i][aux]) matrix[i][aux] = matrix[i][j];
          else matrix[i][aux+1] = matrix[i][j];
          matrix[i][j] = 0;
        }
      }
    }
    newEl();
    break;
    //move right
  case 1:
    for(int i = 0; i < n; ++i){
      for(int j = 0; j < n-1; ++j){
        if(matrix[i][j] && (!matrix[i][j+1] || matrix[i][j+1] == matrix[i][j])){
          int aux = j+1;
          while(aux < n-1 && !matrix[i][aux]) ++aux;
          if(matrix[i][aux] == matrix[i][j]) matrix[i][aux] *= 2,
		score += matrix[i][aux];
          else if(!matrix[i][aux]) matrix[i][aux] = matrix[i][j];
          else matrix[i][aux-1] = matrix[i][j];
          matrix[i][j] = 0;
        }
      }
    }
    newEl();
    break;
    //move up:
  case -2:
    for(int i = n-1; i > 0; --i){
      for(int j = 0; j < n; ++j){
        if(matrix[i][j] && (!matrix[i-1][j] || matrix[i-1][j] == matrix[i][j])){
          int aux = i-1;
          while(aux > 0 && !matrix[aux][j]) --aux;
          if(matrix[aux][j] == matrix[i][j]) matrix[aux][j] *= 2,
		score += matrix[aux][j];
          else if(!matrix[aux][j]) matrix[aux][j] = matrix[i][j];
          else matrix[i][aux+1] = matrix[i][j];
          matrix[i][j] = 0;
        }
      }
    }
    newEl();
    break;
    //move down
  case 2:
    for(int i = 0; i < n-1; ++i){
      for(int j = 0; j < n; ++j){
        if(matrix[i][j] && (!matrix[i+1][j] || matrix[i+1][j] == matrix[i][j])){
          int aux = i+1;
          while(aux < n-1 && !matrix[aux][j]) ++aux;
          if(matrix[aux][j] == matrix[i][j]) matrix[aux][j] *= 2,
		score += matrix[aux][j];
          else if(!matrix[aux][j]) matrix[aux][j] = matrix[i][j];
          else matrix[i][aux-1] = matrix[i][j];
          matrix[i][j] = 0;
        }
      }
    }
    newEl();
    break;
  default:
    break;
  }
  }
}
