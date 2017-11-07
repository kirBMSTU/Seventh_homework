#include <iostream>
#include <string.h>
#include <fstream>


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


template<class T =  int>
class Queue;

template<class T>
std::ostream& operator << (std::ostream& out, const Queue<T>& other)
{
  out << "[";
  if (other.size != 0)
  {
    for (size_t i = other.head; i <= other.tail; i++) {
      out << other.array[i] << " ";
    }
  }
  out << "]\n";
  return out;
}

template<class T>
const Queue<T> operator + (const Queue<T>& left, const Queue<T>& right)
{
  Queue<T> result = Queue<T>(left);
  result.size += right.size;
  result.allocate_new_array();
  memcpy(&(result.array[result.head + left.size]), &(right.array[right.head]), sizeof(T) * right.size);
  return result;
}

template<class T>
const Queue<T> operator - (const Queue<T>& left, const Queue<T>& right)
{
  Queue<T> new_left = Queue<T>(left);
  Queue<T> new_right = Queue<T>(right);
  Queue<T> result = Queue<T>();
  size_t left_size = left.Count();
  size_t right_size = right.Count();

  for (size_t i = 0; i < left_size; i++) {
    bool is = 0;
    for (size_t j = 0; j < right_size; j++)
    {
      if (new_left.Peek() == new_right.Dequeue())
      {
        is = 1;
        break;//или continue
      }
    }
    if (is)
    {
      new_left.Dequeue();
    }
    else
    {
      result.Enqueue(new_left.Dequeue());
    }
    new_right = Queue<T>(right);
  }
  return result;
}

template<class T>
const Queue<T> kick_uneven(Queue<T>& other)
{
  Queue<T> result;
  size_t count = other.Count();
  for (size_t i = 0; i < count; i++) {
    if (i % 2 == 1)
    {
      result.Enqueue(other.Dequeue());
    }
    else
    {
      other.Dequeue();
    }
  }
  other = result;
  return other;
}


template<class T>
class Queue
{
public:
  Queue();
  Queue(const Queue &other);
  Queue(const T& first);
  void Enqueue(const T& last);
  T Dequeue();
  T Peek() const;//просмотр первого элемента без удаления
  size_t Count() const;

  const Queue operator = (const Queue& other);
  friend const Queue operator +<T> (const Queue& left, const Queue& right);
  friend const Queue operator -<T> (const Queue& left, const Queue& right);
  friend std::ostream& operator <<<T> (std::ostream& out, const Queue& other);

  friend const Queue kick_uneven(Queue& other);

  ~Queue();
private:
  size_t head;
  size_t tail;
  size_t capacity;
  size_t size;

  T* array;
  void allocate_new_array();
};

template<class T>
Queue<T>:: Queue()
{
  //std:: cout << "Queue()\n";
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
  this->allocate_new_array();
}

template<class T>
Queue<T>:: Queue(const Queue &other)
{
  //std:: cout << "Queue(other)\n";
  this->capacity = other.capacity;
  this->size = other.size;
  this->head = other.head;
  this->tail = other.tail;
  this->array = new T[this->capacity];
  memcpy(this->array, other.array, sizeof(T) * this->capacity);
}

template<class T>
Queue<T>:: Queue(const T& first)
{
  //std:: cout << "Queue(first)\n";
  this->size = 0;
  this->capacity = 0;
  this->head = 0;
  this->tail = 0;
  Enqueue(first);
  //std::cout << "Queue(first) - end\n";
}

template<class T>
void Queue<T>:: Enqueue(const T& last)
{
  //std::cout << "Enqueue() - start {we will add elem = " << last << "}\n";
  this->size++;
  this->allocate_new_array();
  //std::cout << "sizeof(array) = " << sizeof(this->array) / sizeof(T) << "\nthis->size = " << this->size << "\nthis->head = " << this->head << "\nthis->tail = " << this->tail << "\nthis->capacity = " << this->capacity << "\n";
  this->array[this->tail] = last;
  //std::cout << "Enqueue() - end {" << this->head << "; " << this->tail <<"}\nadded_elem = " << this->array[this->tail] << "\n";

}

template<class T>
T Queue<T>:: Dequeue()
{
  if (this->size >= 1)
  {
    this->head++;
    this->size--;
    return this->array[this->head - 1];//не ошибка
  }
  else
    return 0;
}

template<class T>
void Queue<T>:: allocate_new_array()
{
  //std::cout << "allocate_new_array() - start\n";
  if(this->capacity == 0)
  {
    this->capacity = 4;
    this->array = new T[this->capacity];
    memset(this->array, 0, sizeof(T) * this->capacity);
    //std::cout << "allocate_new_array() - end_first\n";
    return;
  }
  if (this->head + this->size >= this->capacity - 1)//если уперлись в правый край массива
  {
    if (this->size <= this->capacity / 2)
    {
      memcpy(this->array, &(this->array[this->head]), sizeof(T) * this->size);//просто сдвигаем все элементы в начало
      this->head = 0;
      this->tail = this->size - 1;
      //std::cout << "allocate_new_array() - end_second\n";
      return;
    }
    else
    {
      this->capacity *= 2;
      T *temp = new T[this->capacity];
      memset(temp, 0, sizeof(T) * this->capacity);
      memcpy(temp, &(this->array[this->head]), sizeof(T) * this->size);
      delete [] this->array;
      this->array = new T[this->capacity];//
      memcpy(this->array, temp, sizeof(T) * this->capacity);//
      delete [] temp;//
      this->head = 0;
      this->tail = this->head + this->size - 1;
      //std::cout << "allocate_new_array() - end_third\n";
    }
  }
  else
  {
    this->tail = this->head + this->size - 1;
    //std::cout << "allocate_new_array() - end_fourth\n";
    return;
  }
}

template<class T>
T Queue<T>:: Peek() const
{
  return this->array[this->head];//и тут тоже не ошибка
}

template<class T>
size_t Queue<T>:: Count() const
{
  return this->size;
}

template<class T>
Queue<T>:: ~Queue<T>()
{
  //std:: cout << "~Queue\n";
  delete [] this->array;
  this->capacity = 0;
  this->size = 0;
  this->head = 0;
  this->tail = 0;
}


template<class T>
const Queue<T> Queue<T>::operator = (const Queue<T>& other)
{
  this->head = other.head;
  this->tail = other.tail;
  this->size = other.size;
  this->capacity = other.capacity;
  delete [] this->array;
  this->array = new T[this->capacity];
  memcpy(this->array, other.array, sizeof(T) * this->capacity);
  return *this;
}
