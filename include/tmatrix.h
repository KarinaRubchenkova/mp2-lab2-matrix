// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iomanip>

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
  static size_t check_matrix_size(size_t s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw "too large";
      return s;
  }
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    else if (sz > MAX_VECTOR_SIZE) { throw "too large"; }
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v): sz(v.sz)
  {
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++) {
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              sz = v.sz;
              delete[] pMem;
              pMem = new T[sz];
          }
          for (size_t i = 0; i < sz; i++) { pMem[i] = v.pMem[i]; }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          sz = v.sz;
          delete[] pMem;
          pMem = v.pMem;
          v.pMem = nullptr;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
      {
          if (ind >= sz) { throw "Error"; }
          return pMem[ind];
      }
      const T& operator[](size_t ind) const
      {
          if (ind >= sz) { throw "Error"; }
          return pMem[ind];
      }
      // индексация с контролем
      T& at(size_t ind)
      {
          if (ind >= sz) { throw "Error"; }
          else { return pMem[ind]; }
      }
      const T& at(size_t ind) const
      {
          if (ind >= sz) { throw "Error"; }
          else { return pMem[ind]; }
      }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) { return false; }
      else {
          for (size_t i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) return false;
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (*this == v) { return false; }
      else { return true; }
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) { res.pMem[i] += val; }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) { res.pMem[i] -= val; }
      return res;
  }
  TDynamicVector operator*(T val)
  {

      TDynamicVector res(*this);
      for (size_t i = 0; i < sz; i++) { res.pMem[i] *= val; }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) { throw "Error"; }
      else {
          TDynamicVector res(*this);
          for (size_t i = 0; i < sz; i++) {
              res.pMem[i] += v.pMem[i];
          }
          return res;
      }
      
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {throw "Error";}
      else {
          TDynamicVector res(*this);
          for (size_t i = 0; i < sz; i++) {
              res.pMem[i] -= v.pMem[i];
          }
          return res;
      }
      
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) { throw "Error"; }
      T res = 0;

      for (size_t i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }

      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
  
public:
    using TDynamicVector<TDynamicVector<T>>::size;
    using TDynamicVector<TDynamicVector<T>>::at;
    TDynamicMatrix(size_t s = 1)
        : TDynamicVector<TDynamicVector<T>>(check_matrix_size(s))
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVector<T>(sz);
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) { return false; }
        else {
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i] != m.pMem[i]) { return false; }
            }
        }
        return true;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        if (sz != v.size()) { throw "Error"; }
        TDynamicVector<T> res(sz);

        for (size_t i = 0; i < sz; i++) {
            res[i] = pMem[i] * v;
        }

        return res;
    }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) { throw "Error"; }
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) { throw "Error"; }
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      
      if (sz != m.sz) { throw "Error"; }
      TDynamicMatrix<T> res(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              T sum = 0;
              for (size_t k = 0; k < sz; k++) {
                  sum += pMem[i][k] * m.pMem[k][j];
              }
              res[i][j] = sum;
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          for (size_t j = 0; j < v.sz; j++) {
              ostr << "| " << std::setw(5) << v.pMem[i][j] << ' ';
          }

          ostr << "| " << std::endl;
      }

      return ostr;
  }
};

#endif
