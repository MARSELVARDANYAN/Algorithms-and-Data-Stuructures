#include <iostream>

int partition(int* arr, int low, int hight)
{
    int pivot = arr[hight];

    int j = (low -1);

    for (size_t i = low; i <= hight - 1; i++) {
        if (arr[i] <= pivot) {
            ++j;
            std::swap(arr[i], arr[j]);
        }
        
    }
    std::swap(arr[j + 1], arr[hight]);
    return (j + 1);
}

void quick_sort(int* arr, int low, int hight)
{
    if (low < hight) {
        
        int pi = partition(arr, low, hight);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, hight);
    }
    
}

int main ()
{
    int arr[8] = {9, 7 ,4, 6, 2};
  
      quick_sort(arr, 0, 4);
  
      for(int i = 0; i < 5; ++i){
          std::cout <<  arr[i];
      }
    std::cout << std::endl;

}