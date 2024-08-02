#include "../Headers/queue.h"

int main() 
{
   Queue<int> ob; 
   Queue<int> obj{1, 3, 4, 6};
   Queue<int> ob2(obj);

   ob = obj;

   int x = obj.front();
   std::cout << x << std::endl;

   obj.push(8);
   obj.pop();

   bool i = obj < ob;
   std::cout << i << std::endl;

   int sz = ob2.size();

}