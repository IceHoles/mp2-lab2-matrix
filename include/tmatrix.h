// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <assert.h>
#include <iostream>

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
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz <= 0)
        throw std::out_of_range("Vector size should be greater than zero");
    if(sz > MAX_VECTOR_SIZE)
        throw std::out_of_range("Vector size is too big");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      if (s <= 0 || s > MAX_VECTOR_SIZE)
          throw std::out_of_range("Vector size is out of range");
      assert(arr != nullptr && "TDynamicVector requires non-nullptr arg");
      pMem = new T[sz];
      std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) :sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = 0;
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &v) {
          return *this;          
      }
      TDynamicVector temp(v);
      swap(*this, temp);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if(ind < 0 || ind >= sz)
          throw std::out_of_range("Index out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
          throw std::out_of_range("Index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
          return 0;
      for (size_t i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i])
              return 0;
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) 
          temp.pMem[i] = pMem[i] + val;
      return temp;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++) 
          temp.pMem[i] = pMem[i] - val;
      return temp;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] * val;
      return temp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("Vectors are different in size");
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] + v.pMem[i];
      return temp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("Vectors are different in size");
      TDynamicVector temp(sz);
      for (size_t i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] - v.pMem[i];
      return temp;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw std::logic_error("Product of two vectors with different size is undefined");
      T result = pMem[0] * v.pMem[0];
      for (int i = 1; i < sz; i++) {
          result = result + pMem[i] * v.pMem[i];
      }
      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector& v)
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
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s <= 0)
          throw std::out_of_range("Matrix size should be greater than zero");
      if (s > MAX_MATRIX_SIZE)
          throw std::out_of_range("Matrix size is too big");
      for (size_t i = 0; i < s; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  T size() const { return sz;}

  using TDynamicVector<TDynamicVector<T>>::operator[];
  T& at(size_t a, size_t b)
  {
      if (a < 0 || a >= sz || b < 0 || b >= sz)
          throw std::out_of_range("Index out of range");
      return pMem[a].at(b);
  }
  const T& at(size_t a, size_t b) const
  {
      if (a < 0 || a >= sz || b < 0 || b >= sz)
          throw std::out_of_range("Index out of range");
      return pMem[a].at(b);
  }

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
      TDynamicMatrix temp(sz);
      for (size_t i = 0; i < sz; i++) 
          temp.pMem[i] = pMem[i]*val;
      return temp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw std::out_of_range("Vectors are different in size");
      TDynamicVector<T> temp(sz);
      for (size_t i = 0; i < sz; i++) 
          temp[i] = pMem[i] * v;
      return temp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::out_of_range("Matrices are different in size");
      TDynamicMatrix temp(sz);
      for (size_t i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] + m.pMem[i];
      return temp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::out_of_range("Matrices are different in size");
      TDynamicMatrix temp(sz);
      for (size_t i = 0; i < sz; i++)
          temp.pMem[i] = pMem[i] - m.pMem[i];
      return temp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)
          throw std::out_of_range("Matrices are different in size");
      TDynamicMatrix temp(sz);
      for (size_t i = 0; i < sz; i++) {
          for (size_t j = 0; j < sz; j++) {
              for (size_t k = 0; k < sz; k++) {
                  temp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return temp;
  }

  // ввод/вывод
  friend std::istream& operator>>(std::istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v.pMem[i];
      return istr;
  }
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v.pMem[i] << ' ';
      return ostr;  
  }
};

#endif
