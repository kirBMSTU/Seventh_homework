#include "HW7.hpp"

int main()
{
  size_t size = 5;
  Queue<> *array_of_queue = new Queue<>[size];

  for (size_t i = 0; i < size; i++)
  {
    size_t queue_size = 3 + rand() % 10;
    for (size_t j = 0; j < queue_size; j++)
    {
        array_of_queue[i].Enqueue(-50 + rand() % 100);
    }
  }

  for (size_t i = 0; i < size; i++)
  {
    std:: cout << "arr[" << i << "] = "<< array_of_queue[i];
  }

  std :: cout << "kick_uneven() for everyone in arr\n";
  for (size_t i = 0; i < size; i++)
  {

    kick_uneven<>(array_of_queue[i]);
  }

  for (size_t i = 0; i < size; i++)
  {
    std:: cout << "arr[" << i << "] = "<< array_of_queue[i];
  }

  delete [] array_of_queue;

  //старый пример, демонстрирующий работу +, - и =
  // Queue<int> alpha = Queue<int>();
  // Queue<int> beta = Queue<int>(42);
  //
  // alpha.Enqueue(2);
  // alpha.Enqueue(5);
  // alpha.Enqueue(7);
  //
  // beta.Enqueue(15);
  // beta.Enqueue(21);
  // beta.Enqueue(7);
  // beta.Enqueue(2);
  // beta.Enqueue(5);
  // beta.Enqueue(80);
  // beta.Enqueue(54);
  //
  // Queue<int> teta = Queue<int>(beta);
  // teta.Dequeue();
  //
  // std::cout << "alpha: " << alpha;
  // std::cout << "beta: " << beta;
  // std::cout << "teta: " << teta;
  //
  // teta = alpha + beta;
  //
  // std:: cout << "alpha + beta: " << alpha + beta;
  // std:: cout << "teta = alpha + beta: " << teta;
  //
  // std::cout << "\nalpha: " << alpha;
  // std::cout << "beta: " << beta;
  //
  // teta = alpha - beta;
  // std:: cout << "teta = alpha - beta: " << teta;

  return 0;
}
