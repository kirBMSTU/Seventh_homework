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

Queue:: Queue()
{
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}

Queue:: Queue(const Queue<T> &other)
{
  //delete [] this->array;
  this->capacity = other.capacity;
  this->size = other.size;
  this->allocate_new_array();
  memcpy(this->array, other.array, this->capacity);
  this->head = other.head;
  this->tail = other.tail;
}

Queue:: Queue(const T& first)
{
  this->size = 0;
  this->capacity = 0;
  this->head = 0;
  this->tail = 0;
  Enqueue(first);
}

void Queue:: Enqueue(const T& last)
{
  this->size++;
  this->allocate_new_array();
  if (this->tail == this->capacity - 1)
  else if
    this->tail++;
  array[tail] = last;
}

T Queue:: Dequeue()
{
  this->head++;
  this->size--;
  return array[this->head - 1];//не ошибка
}

void Queue:: allocate_new_array()
{
  if(this->capacity == 0)
  {
    this->capacity = 4;
    this->array = new T[this->capacity]
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

T Queue:: Peek()
{
  return array[this->head];//и тут тоже не ошибка
}

size_t Queue:: Count()
{
  return this->size;
}

Queue:: ~Queue()
{
  std:: cout << "~Queue\n";
  delete [] this->array;
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}

const Queue& operator + (const Queue& other) const
{
  size_t prev = this->size;
  this->size += other.size;
  allocate_new_array();
  memcpy(this->array, other.array, prev);
  memcpy(this->array[this->tail + 1], other.array[head], other.size);
  return *this;
}

const Queue& operator - (const Queue& other) const
{
  return *this;
}

const Queue& operator = (const Queue& other) const
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

friend std::ostream& operator << (std::ostream& out, const Queue& other) const
{
  out << "[";
  for (size_t i = other.head; i < other.tail; i++) {
    out << other.array[i] << " "
  }
  out << "]\n";
  return out;
}
