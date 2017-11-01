#include "HW7.hpp"

Queue:: Queue()
{
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}

Queue:: Queue(Queue<T> &other)
{
  delete [] this->array;
  this->capacity = other.capacity;
  this->size = other.size;
  this->allocate_new_array();
  memcpy(this->array, other.array, this->size);
  this->head = other.head;
  this->tail = other.tail;
}

Queue:: Queue(T first)
{
  this->size = 0;
  this->capacity = 0;
  Enqueue(first);
}

void Queue:: Enqueue(T last)
{
  this->size++;
  this->allocate_new_array();
  this->tail++;
  array[tail] = last;
}

T Queue:: Dequeue()
{
  this->head++;
  this->size--;
  return array[this->head - 1];
}

void Queue:: allocate_new_array()
{
  this->size == 0 ? this->capacity = 4 :
  {
    if (this->size == this->capacity)
    {

    }
  }
}
