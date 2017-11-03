#include "HW7.hpp"

//ОТКРОЙ МЕНЯ!!!!
// была идея реализовать кольцевое хранение в массиве, но было бы проблемно расширять его.
// отказался в пользу перемещения всех элементов к 0 при аллокации нового массива
// [1 2 3 4 5 6 * * *]
// [1 2 3 4 5 6 7 * *]
// [1 2 3 4 5 6 7 8 *] Dequeue()
// [* 2 3 4 5 6 7 8 *] Dequeue()
// [* * 3 4 5 6 7 8 *] Enqueue(9)                [* * 3 4 5 6 7 8 *] Dequeue()
// [3 4 5 6 7 8 9 * * * * * * * * * * *]         [* * * 4 5 6 7 8 *] Dequeue()
// изменился размер массива                      [* * * * 5 6 7 8 *] Dequeue()
// а также произошло смещение                    [* * * * * 6 7 8 *] Enqueue(9)
//                                               [6 7 8 9 * * * * *]
                                                 // то есть размер массива не изменился,
                                                 // произошло лишь смещение

template<class T>
Queue<T>:: Queue()
{
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}

template<class T>
Queue<T>:: Queue(const Queue &other)
{
  //delete [] this->array;
  this->capacity = other.capacity;
  this->size = other.size;
  this->allocate_new_array();
  memcpy(this->array, other.array, this->capacity);
  this->head = other.head;
  this->tail = other.tail;
}

template<class T>
Queue<T>:: Queue(const T& first)
{
  this->size = 0;
  this->capacity = 0;
  this->head = 0;
  this->tail = 0;
  Enqueue(first);
}

template<class T>
void Queue<T>:: Enqueue(const T& last)
{
  this->size++;
  this->allocate_new_array();
  array[this->tail] = last;
}

template<class T>
T Queue<T>:: Dequeue()
{
  this->head++;
  this->size--;
  return array[this->head - 1];//не ошибка
}

template<class T>
void Queue<T>:: allocate_new_array()
{
  if(this->capacity == 0)
  {
    this->capacity = 4;
    this->array = new T[this->capacity];
    return;
  }
  if (this->tail + this->size >= this->capacity - 1)
  {
    if (this->size < this->capacity / 2)
    {
      memcpy(this->array, this->array[this->head], this->size);//просто сдвигаем все элементы в начало
      this->head = 0;
      this->tail = this->size - 1;
    }
    else
    {
      T *temp = new T[this->capacity*2];
      memcpy(temp, this->array[this->head], this->size);
      delete [] this->array;
      this->array = temp;
      this->head = 0;
      this->tail = this->size - 1;
      this->capacity *= 2;
    }
  }
  else
  {
    this->tail = this->head + this->size;
  }
}

template<class T>
T Queue<T>:: Peek()
{
  return array[this->head];//и тут тоже не ошибка
}

template<class T>
size_t Queue<T>:: Count()
{
  return this->size;
}

template<class T>
Queue<T>:: ~Queue<T>()
{
  std:: cout << "~Queue\n";
  delete [] this->array;
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}

template<class T>
const Queue<T>& Queue<T>::operator + (const Queue<T>& other) const
{
  size_t prev = this->size;
  this->size += other.size;
  allocate_new_array();
  memcpy(this->array, other.array, prev);
  memcpy(this->array[this->tail + 1], other.array[head], other.size);
  return *this;
}

template<class T>
const Queue<T>& Queue<T>::operator - (const Queue<T>& other) const
{
  return *this;
}

template<class T>
const Queue<T>& Queue<T>::operator = (const Queue<T>& other) const
{
  this->head = other.head;
  this->tail = other.tail;
  this->size = other.size;
  this->capacity = other.capacity;
  delete [] this->array;
  this->array = new T[this->capacity];
  memcpy(this->array, other.array, this->capacity);
  return *this;
}

template<class T>
std::ostream& operator << (std::ostream& out, const Queue<T>& other)
{
  out << "[";
  for (size_t i = other.head; i < other.tail; i++) {
    out << other.array[i] << " ";
  }
  out << "]\n";
  return out;
}
