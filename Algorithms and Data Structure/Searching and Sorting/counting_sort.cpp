void count_sort(int arr[], int n) {
     int min = *std::min_element(arr, arr + n);//0
     int max = *std::max_element(arr, arr + n);//88
     int range = max - min + 1;
     int count[range]{};
     int output[n];
 
     for(int i = 0; i < n; ++i) {
         count[arr[i] - min]++;
     }
 
     for(int i = 1; i < range; ++i) {
         count[i] += count[i - 1];
     }
 
     for(int i = n - 1; i >= 0; --i) {
         output[count[arr[i] - min] - 1] = arr[i];
         count[arr[i] - min]--;
     }
 
     for(int i = 0; i < n; ++i) {
         arr[i] = output[i];
     }
 }

