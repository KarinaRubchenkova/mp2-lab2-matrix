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
template <typename T>
class TDynamicVectorTriangle {
protected:
    size_t sz;
    size_t si;
    T* pMem;
public:
    static size_t check_matrix_size(size_t s)
    {
        if (s > MAX_MATRIX_SIZE)
            throw "too large";
        return s;
    }
    TDynamicVectorTriangle(size_t size = 1, size_t si_ = 0) : sz(size), si(si_)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        else if (sz > MAX_VECTOR_SIZE) { throw "too large"; }
        if (si > MAX_VECTOR_SIZE) { throw "too large"; }
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVectorTriangle(T* arr, size_t s, size_t _si) : sz(s), si(_si) {
        if (sz == 0)
            throw ("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) {
            throw ("Vector is too large");
        }
        if (si > MAX_VECTOR_SIZE) {
            throw ("Vector is too large");
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVectorTriangle(const TDynamicVectorTriangle& v) : sz(v.sz), si(v.si)
    {
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVectorTriangle(TDynamicVectorTriangle&& v) noexcept
    {
        sz = v.sz;
        si = v.si;
        pMem = v.pMem;
        v.pMem = nullptr;
        v.sz = 0;
        v.si = 0;
        
    }
    ~TDynamicVectorTriangle()
    {
        delete[] pMem;
    }
    TDynamicVectorTriangle& operator=(const TDynamicVectorTriangle& v)
    {
        if (this != &v) {
            if (sz != v.sz) {
                sz = v.sz;
                delete[] pMem;
                pMem = new T[sz];
            }
            si = v.si;
            for (size_t i = 0; i < sz; i++) { pMem[i] = v.pMem[i]; }
        }
        return *this;
    }
    TDynamicVectorTriangle& operator=(TDynamicVectorTriangle&& v) noexcept
    {
        if (this != &v) {
            sz = v.sz;
            si = v.si;
            delete[] pMem;
            pMem = v.pMem;
            v.pMem = nullptr;
            v.sz = 0;
            v.si = 0;
        }
        return *this;
    }

    size_t size() const noexcept { return sz; }
    size_t num_strok() const noexcept { return si; }   


    // индексация
    T& operator[](size_t ind)
    {
        if (ind < si || ind - si >= sz) {
            throw "Error";
        }
        return pMem[ind - si];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < si || ind - si >= sz) {
            throw "Error";
        }
        return pMem[ind-si];
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if (ind < si || ind - si >= sz) { throw "Error"; }
        else { return pMem[ind-si]; }
    }
    const T& at(size_t ind) const
    {
        if (ind < si || ind - si >= sz) { throw "Error"; }
        else { return pMem[ind-si]; }
    }

    // сравнение
    bool operator==(const TDynamicVectorTriangle& v) const noexcept
    {
        if (sz != v.sz || si != v.si) { return false; }
        else {
            for (size_t i = 0; i < sz; i++) {
                if (pMem[i] != v.pMem[i]) return false;
            }
        }
        return true;
    }
    bool operator!=(const TDynamicVectorTriangle& v) const noexcept
    {
        if (*this == v) { return false; }
        else { return true; }
    }

    // скалярные операции
    TDynamicVectorTriangle operator+(T val)
    {
        TDynamicVectorTriangle res(*this);
        for (size_t i = 0; i < sz; i++) { res.pMem[i] += val; }
        return res;
    }
    TDynamicVectorTriangle operator-(T val)
    {
        TDynamicVectorTriangle res(*this);
        for (size_t i = 0; i < sz; i++) { res.pMem[i] -= val; }
        return res;
    }
    TDynamicVectorTriangle operator*(T val)
    {

        TDynamicVectorTriangle res(*this);
        for (size_t i = 0; i < sz; i++) { res.pMem[i] *= val; }
        return res;
    }

    // векторные операции
    TDynamicVectorTriangle operator+(const TDynamicVectorTriangle& v)
    {
        if (sz != v.sz || si != v.si) { throw "Error"; }
        else {
            TDynamicVectorTriangle res(*this);
            for (size_t i = 0; i < sz; i++) {
                res.pMem[i] += v.pMem[i];
            }
            return res;
        }

    }
    TDynamicVectorTriangle operator-(const TDynamicVectorTriangle& v)
    {
        if (sz != v.sz || si != v.si) { throw "Error"; }
        else {
            TDynamicVectorTriangle res(*this);
            for (size_t i = 0; i < sz; i++) {
                res.pMem[i] -= v.pMem[i];
            }
            return res;
        }

    }
    T operator*(const TDynamicVectorTriangle& v)
    {
        if (sz != v.sz || si != v.si) { throw "Error"; }
        T res = 0;

        for (size_t i = 0; i < sz; i++) {
            res += pMem[i] * v.pMem[i];
        }

        return res;
    }

    friend void swap(TDynamicVectorTriangle& lhs, TDynamicVectorTriangle& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.si, rhs.si);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVectorTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVectorTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }

};
template<typename T>
class TDynamicMatrixTriangle : private TDynamicVectorTriangle<TDynamicVectorTriangle<T>>
{
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::pMem;
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::sz;

public:
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::size;
    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::at;
    TDynamicMatrixTriangle(size_t s = 1)
        : TDynamicVectorTriangle<TDynamicVectorTriangle<T>>(check_matrix_size(s))
    {
        for (size_t i = 0; i < sz; i++)
            pMem[i] = TDynamicVectorTriangle<T>(sz-i,i);
    }

    using TDynamicVectorTriangle<TDynamicVectorTriangle<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrixTriangle& m) const noexcept
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
    TDynamicMatrixTriangle operator*(const T& val)
    {
        TDynamicMatrixTriangle<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] * val;
        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVectorTriangle<T> operator*(const TDynamicVectorTriangle<T>& v) {
        if (sz != v.size()|| v.num_strok() != 0 ) { throw "Error"; }
        TDynamicVectorTriangle<T> res(sz);

        for (size_t i = 0; i < sz; i++) {
            for (size_t j = i; j < sz; j++) {
                res[i] += pMem[i][j] * v[j];
            }
        }
        return res;
    }

    // матрично-матричные операции
    TDynamicMatrixTriangle operator+(const TDynamicMatrixTriangle& m)
    {
        if (sz != m.sz || m.num_strok() != 0) { throw "Error"; }
        TDynamicMatrixTriangle<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] + m.pMem[i];
        }
        return res;
    }
    TDynamicMatrixTriangle operator-(const TDynamicMatrixTriangle& m)
    {
        if (sz != m.sz || m.num_strok() != 0) { throw "Error"; }
        TDynamicMatrixTriangle<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            res.pMem[i] = pMem[i] - m.pMem[i];
        }
        return res;
    }
    TDynamicMatrixTriangle operator*(const TDynamicMatrixTriangle& m)
    {

        if (sz != m.sz|| m.num_strok() != 0 ) { throw "Error"; }
        TDynamicMatrixTriangle<T> res(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = i; j < sz; j++) {
                T sum = 0;
                for (size_t k = i; k < j + 1; k++) {
                    sum += pMem[i][k] * m.pMem[k][j];
                }
                res[i][j] = sum;
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrixTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            istr >> v.pMem[i];
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TDynamicMatrixTriangle& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            // Пустые ячейки до главной диагонали
            for (size_t j = 0; j < i; j++) {
                ostr << "| " << std::setw(5) << ' ' << ' ';
            }
            // Сама строка и элементы выше диагонали
            for (size_t j = i; j < v.sz; j++) {
                ostr << "| " << std::setw(5) << v.pMem[i][j] << ' ';
            }
            ostr << "|" << std::endl;
        }
        return ostr;
    }
};

#endif
