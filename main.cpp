#include "HW7.hpp"

int main()
{
  Queue alpha();
  Queue beta(42);

  alpha.Enqueue(2);
  alpha.Enqueue(5);
  alpha.Enqueue(7);

  beta.Enqueue(15);
  beta.Enqueue(21);
  beta.Enqueue(54);
  beta.Enqueue(11);

  Queue teta(beta);

  std::cout << alpha;
  std::cout << beta;
  std::cout << teta;
  return 0;
}
