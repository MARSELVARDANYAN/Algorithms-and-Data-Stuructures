void selection_sort(int* arr, int n)
{
    for (size_t i = 0; i < n - 1; i++) {
        int min = i;
        
        for (size_t j = i + 1; j < n; j++) {
            if (arr[min] > arr[j]) {
                min = j;
            }
            
        }
        if (min != i) {        
            std::swap(arr[min], arr[i]);
        }
        
    }
    
}
