#include <iostream>

void merge(int start, int mid, int end, int* arr) 
{
    int tmp_arr[end - start + 1];
    
    int tmp_start = start;
    int tmp_end = mid;
    
    int tmp_start2 = mid + 1;
    int tmp_end2 = end;
    
    int index{};
    
    while (tmp_start <= tmp_end && tmp_start2 <= tmp_end2) {
        if (arr[tmp_start] < arr[tmp_start2]) {
            tmp_arr[index++] = arr[tmp_start++];
        }else {
            tmp_arr[index++] = arr[tmp_start2++];
        }
        
    }
    
    
    while(tmp_start <= tmp_end){
        tmp_arr[index++] = arr[tmp_start++];
    }
    
    while(tmp_start2 <= tmp_end2){
        tmp_arr[index++] = arr[tmp_start2++];
    }
    
    for(int i = 0; i < index; ++i){
        arr[start++] = tmp_arr[i];
    }
    
}

void mergeSort(int start, int end, int* arr)
{
    if(start < end){
        int mid = start + (end - start) / 2;
        
        mergeSort(start, mid, arr);
        mergeSort(mid + 1, end, arr);
        merge(start, mid, end, arr);
    }
}





int main()
{
    int arr[8] = {9, 7 ,4, 6, 2, 3, 0, 5};
    
    mergeSort(0, 7, arr);
    
    for(int i = 0; i < 8; ++i){
        std::cout <<  arr[i];
    }


    return 0;
}
