#include "s21_matrix_oop.h"

void S21Matrix::PrintMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int S21Matrix::GetRows() { return this->rows_; }

int S21Matrix::GetColms() { return this->cols_; }

void S21Matrix::SetRows(int row) {
  S21Matrix tmp(row, this->cols_);
  if (row < this->rows_) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    for (int i = this->rows_; i < row; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = 0;
      }
    }
  }
  *this = std::move(tmp);
}

void S21Matrix::SetColms(int colm) {
  S21Matrix tmp(this->rows_, colm);
  if (colm < this->cols_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < colm; j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix_[i][j] = this->matrix_[i][j];
      }
    }
    for (int i = 0; i < this->rows_; i++) {
      for (int j = this->cols_; j < colm; j++) {
        tmp.matrix_[i][j] = 0;
      }
    }
  }
  *this = std::move(tmp);
}

S21Matrix S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    this->DeleteMatrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->matrix_ = other.matrix_;
    other.SetNull();
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix tmp(*(this));
  tmp.SumMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix tmp(*(this));
  tmp.SubMatrix(other);
  return tmp;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix tmp(*(this));
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix tmp(*(this));
  tmp.MulMatrix(other);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int i, int j) {
  if (i > rows_ || j > cols_) {
    throw std::out_of_range("Invalid size of Matrix, they must be same size");
  }
  return matrix_[i][j];
}

void S21Matrix::SetNull() {
  this->matrix_ = nullptr;
  this->rows_ = 0;
  this->cols_ = 0;
}

void S21Matrix::DeleteMatrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
}

void S21Matrix::FillMatrix() {
  double count = 0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = count;
      count += 1;
    }
  }
}

S21Matrix::S21Matrix() {
  if (this->rows_ <= 0 || this->cols_ <= 0) {
    throw std::out_of_range("Invalid size of matrix, matrix must be > 0");
  }
  this->matrix_ = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    this->matrix_[i] = new double[this->cols_];
  }
}

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  if (rows <= 0 || cols <= 0) {
    throw std::out_of_range("Invalid size of Matrix, they must be same size");
  }
  this->matrix_ = new double*[rows];
  for (int i = 0; i < rows; i++) {
    this->matrix_[i] = new double[cols];
  }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->matrix_ = new double*[other.rows_];
  for (int i = 0; i < other.rows_; i++) {
    this->matrix_[i] = new double[other.cols_];
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    return false;
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      double eps = fabs(this->matrix_[i][j] - other.matrix_[i][j]);
      if (eps > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::out_of_range("Invalid size of Matrix, they must be same size");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::out_of_range("Invalid size of Matrix, they must be same size");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (this->cols_ != other.cols_ || this->rows_ != other.rows_) {
    throw std::out_of_range("Invalid size of Matrix, they must be same size");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      tmp.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_) {
    throw std::length_error("Matrix are not squar");
  }
  if (this->rows_ == 1 || this->cols_ == 1) {
    throw std::length_error("Matrix rows or colms = 1");
  }
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21_Miner(minor, i, j);
      result.matrix_[i][j] = pow(-1, (j + i) + 2) * minor.Determinant();
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double result = 0.0;
  if (rows_ != cols_) {
    throw std::length_error("Matrix is not square");
  }
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    S21Matrix minor(rows_ - 1, cols_ - 1);
    for (int j = 0; j < cols_; j++) {
      S21_Miner(minor, 0, j);
      result += pow(-1.0, j) * minor.Determinant() * matrix_[0][j];
    }
  }
  return result;
}

void S21Matrix::S21_Miner(const S21Matrix& other, int i, int c) {
  int minor_i = 0;
  int minor_j = 0;
  for (int current_i = 0; current_i < rows_; current_i++) {
    for (int current_j = 0; current_j < cols_; current_j++) {
      if (current_j != c && current_i != i) {
        other.matrix_[minor_i][minor_j] = matrix_[current_i][current_j];
        minor_j++;
        if (minor_j == cols_ - 1) {
          minor_i++;
          minor_j = 0;
        }
      }
    }
  }
}

S21Matrix S21Matrix::InverseMatrix() {
  double determ = Determinant();
  S21Matrix tmp(this->rows_, this->cols_);
  if (determ == 0.) {
    throw std::logic_error("Determinant = 0");
  }
  if (rows_ == 1) {
    tmp.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    tmp = CalcComplements().Transpose();
    tmp.MulNumber(1. / determ);
  }

  return tmp;
}
