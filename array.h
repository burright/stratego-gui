#ifndef __ARRAY_H__
#define __ARRAY_H__

#include<iostream>
#include<stdlib.h>
#include<assert.h>

using namespace std;


template<class T>
class array
{
 public:
  array();
  array(int size);
  array(T * a, int size);
  array(array<T> * a);
  array(array<T> & a);

  virtual ~array();
  
  void set_element(T d, int index);
  T get_element(int index);
  T& operator[](int i);
  
  void grow(int howmuch);
  void shrink(int howmuch);

  void read(istream & in);
  void print(ostream & out);
  
  void copy_in(T * a, int size);
  void copy_in(array<T> * a);
  void operator=(array<T> & a);
  
  array * clone();

  void sort(int ascending=1);

  int get_size(){return _size;}
  T* get_data(){return _data;}
  
  template<class H>
    friend void operator>>(istream & in, array<H> & a);
  template<class H>
    friend void operator<<(ostream & out, array<H> & a);

 protected:
  
  void allocate_data();

  T * _data;
  int _size;
  
  
};

template<class T>
array<T>::array()
{
  _size = 1;
  allocate_data();
}

template<class T>
array<T>::array(int size)
{
  _size = size;
  allocate_data();
}

template<class T>
array<T>::array(T * a, int size)
{
  _data = 0;
  copy_in(a,size);
}

template<class T>
array<T>::array(array<T> * a)
{
  _data = 0;
  copy_in(a);
}

template<class T>
array<T>::array(array<T> & a)
{
  _data = 0;
  copy_in(a._data, a._size);
}

template<class T>
array<T>::~array()
{
  delete [] _data;
}

template<class T>
void array<T>::allocate_data()
{
  _data = new T[_size];
  assert(_data);
}

template<class T>
T& array<T>::operator[](int i)
{
  if (i >= _size)
    grow(i - _size + 1);
  assert(i >= 0);
  
  return _data[i];
}
  
template<class T>
void array<T>::set_element(T d, int index)
{
  if (index >= _size)
    grow(index - _size + 1);
  
  assert(index >= 0);
    
  _data[index] = d;
}

template<class T>
T array<T>::get_element(int index)
{
  assert(index >= 0 && index < _size);
    
  return _data[index];
}

template<class T>
void array<T>::grow(int howmuch)
{
  T * new_data = new T[_size + howmuch];
  assert(new_data);
  
  int i;

  for ( i = 0; i < _size && i < _size + howmuch; i++)
    new_data[i] = _data[i];

  _size += howmuch;

  delete [] _data;

  _data = new_data;
}

template<class T>
void array<T>::shrink(int howmuch)
{
  grow(-howmuch);
}

template<class T>
void array<T>::read(istream & in)
{
  int num,i;
  
  in>>num;

  grow(num - _size);

  for (i = 0; i < _size; i++)
    in>>_data[i];
}

template<class T>
void operator>>(istream & in, array<T> & a)
{
  int num, i;

  in>>num;
  a.grow(num - a._size);
  
  for (i = 0; i < a._size; i++)
    in>>a._data[i];
}

template<class T>
void array<T>::print(ostream & out)
{
  int i;
  
  out<<_size;

  for (i = 0; i < _size; i++)
    out<<" "<<_data[i];
  out<<endl;
}

template<class T>
void operator<<(ostream & out, array<T> & a)
{
  int i;
  
  out<<a._size;

  for (i = 0; i < a._size; i++)
    out<<" "<<a._data[i];

  out<<endl;
}
  
template<class T>
void array<T>::copy_in(T * a, int size)
{
  int i;

  if (_data)
    delete [] _data;
  
  _size = size;
  allocate_data();

  for (i = 0; i < _size; i++)
    _data[i] = a[i];
}

template<class T>
void array<T>::copy_in(array<T> * a)
{
  copy_in(a->_data, a->_size);
}

template<class T>
void array<T>::operator=(array<T> & a)
{
  copy_in(a._data, a._size);
}

template<class T>
array<T> * array<T>::clone()
{
  array<T> * r = new array<T>(this);
  assert(r);
  
  return r;
}

template<class T>
void array<T>::sort(int ascending)
{
  int i,j;
  T temp;
  int need_swap;

  for (i = 0; i < _size - 1; i++)
    for (j = i + 1; j < _size; j++)
    {
      need_swap = 0;

      if (ascending && _data[i] > _data[j])
	need_swap = 1;
      if (!ascending && _data[i] > _data[j])
	need_swap = 1;

      if (need_swap)
      {
	temp = _data[i];
	_data[i] = _data[j];
	_data[j] = temp;
      }
    }
}

#endif
