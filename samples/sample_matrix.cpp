// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  int i, j;
  TDynamicMatrixTriangle<int> d(5), e(5), f(5);
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с треугольными матрицами"
      << endl;
  for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++)
      {
          d[i][j] = i * 10 + j;
          e[i][j] = (i * 10 + j) * 100;
      }
  f = d + e;
  cout << "Matrix d = " << endl << d << endl;
  cout << "Matrix e = " << endl << e << endl;
  cout << "Matrix f = d + e" << endl << f << endl;
}
//---------------------------------------------------------------------------
