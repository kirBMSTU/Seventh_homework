#include <iostream>
#include <string.h>
#include <fstream>

template<T = int> class Queue
{
public:
  Queue();
  Queue(const Queue<T> &other);
  Queue(const T& first);
  void Enqueue(const T& last);
  T Dequeue();
  T Peek();//просмотр первого элемента без удаления
  size_t Count();

  const Queue& operator + (const Queue& other) const;
  const Queue& operator - (const Queue& other) const;
  const Queue& operator = (const Queue& other) const;
  friend std::ostream& operator << (std::ostream& out, const Queue& other) const;

  ~Queue();
private:
  size_t head;
  size_t tail;
  size_t capacity;
  size_t size;

  T* array;
  void allocate_new_array();
};

//TODO: специализация класса
