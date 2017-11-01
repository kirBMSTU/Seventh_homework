#include <iostream>
#include <string.h>

template<T = int> class Queue
{
public:
  Queue();
  Queue(Queue<T> &other);
  Queue(T first);
  void Enqueue(T last);
  T Dequeue();
  T Peek();//просмотр первого элемента без удаления
  size_t Count();

  //T Get(size_t number);
  // void Insert(Queue_node<T> node, size_t number);

  //TODO:
  operator +
  operator -
  operator =
  friend operator <<

  ~Queue();
private:
  size_t head;
  size_t tail;
  size_t capacity;
  size_t size;

  T* array;
  void allocate_new_array();
  size_t get_free_space();// return index of first free place
  //private methods:

};

// template<T = int> struct Queue_node
// {
//   size_t index;
//   T data;
//   size_t index_of_next;
//   bool is;
// };

/*
//TODO: специализация класса

*/
