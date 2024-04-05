#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>

#include <iostream>

// using namespace std; //

class S21Matrix {
 private:
  int rows_ = 0, cols_ = 0;
  double** matrix_ = nullptr;
  void SetNull();
  void DeleteMatrix();

 public:
  S21Matrix();  // база
  S21Matrix(int rows, int cols);  //  Параметризированный конструктор с
                                  //  количеством строк и столбцов
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор переноса
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  int GetRows();
  int GetColms();
  void SetRows(int row);
  void SetColms(int colm);
  void FillMatrix();
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator=(S21Matrix&& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(double num);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*=(double num);
  double& operator()(int i, int j);
  void PrintMatrix();
  void S21_Miner(const S21Matrix& other, int i, int c);

 protected:
};

#endif