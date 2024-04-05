#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

void fillMatrix(double* seq, S21Matrix& other) {
  int n = 0;
  for (int i = 0; i < other.GetRows(); i++) {
    for (int j = 0; j < other.GetColms(); j++) {
      other(i, j) = seq[n++];
    }
  }
}

TEST(Matrix, Constructors) { EXPECT_ANY_THROW(S21Matrix test); }

TEST(Matrix, Constructors2) {
  S21Matrix test(2, 2);
  S21Matrix test1(2, 2);
  double seq1[] = {1, 1, 1, 1};
  double seq2[] = {2, 2, 2, 2};
  EXPECT_EQ(1, test.EqMatrix(test1));
}

TEST(Matrix, Move) {
  S21Matrix basic(2, 2);
  double seq[] = {11.11, 12.12, 21.21, 31.31};
  fillMatrix(seq, basic);
  S21Matrix copy(basic);
  S21Matrix move(std::move(basic));
  EXPECT_EQ(move, copy);
  EXPECT_FALSE(move == basic);
}

TEST(Matrix, TestSetterGetter) {
  S21Matrix matrix(1, 1);
  matrix.SetRows(2);
  matrix.SetColms(2);
  int row = matrix.GetRows();
  int colm = matrix.GetColms();
  EXPECT_EQ(2, row);
  EXPECT_EQ(2, colm);
}

TEST(Matrix, Operations) {
  S21Matrix basic(3, 3);
  double seq[] = {1, 2, 4, 3, 3, 5, 2, 4, 4};
  fillMatrix(seq, basic);
  S21Matrix one(3, 3);
  double seq_one[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  fillMatrix(seq_one, one);
  S21Matrix calc(3, 3);
  calc = basic.InverseMatrix();
  EXPECT_TRUE(calc == basic.InverseMatrix());
}

TEST(Matrix, Determinant) {
  S21Matrix first(2, 2);
  double tmp[] = {1, 2, 3, 4};
  fillMatrix(tmp, first);
  double result = -2;
  EXPECT_EQ(first.Determinant(), result);
  S21Matrix second(3, 3);
  double tmp1[] = {1, 2, 3, 4, 5, 6, 7, 8, 10};
  fillMatrix(tmp1, second);
  double result1 = -3;
  EXPECT_EQ(second.Determinant(), result1);
}

TEST(Matrix, Operators) {
  S21Matrix basic(3, 3);
  double seq[] = {11.01, 22.02, 33.03, 44.04, 55.05,
                  66.06, 77.07, 88.08, 99.09};
  fillMatrix(seq, basic);
  S21Matrix sum(3, 3);
  sum = basic + basic;
  basic = basic * 2.0;
  EXPECT_EQ(sum, basic);
  for (int i = 0; i < 3; i++) {
    sum += basic;
    sum *= 2.0;
    EXPECT_FALSE(sum == basic);
    sum *= 0.5;
    sum -= basic;
  }
  EXPECT_EQ(sum, basic);
  sum = sum * sum;
  basic = basic * basic;
  EXPECT_EQ(basic, sum);
  basic = basic - sum;
  sum = sum - basic;
  EXPECT_FALSE(basic == sum);
}

TEST(Matrix, Errors) {
  EXPECT_ANY_THROW(S21Matrix errors(-123, 0));
  EXPECT_ANY_THROW(S21Matrix errors(1, 0));
  S21Matrix errorLeft(1, 55);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}