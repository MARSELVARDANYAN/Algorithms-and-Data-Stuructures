int binary_search(const std::vector<int>& arr, int start, int end, int key)
{
    while (start <= end){
        int mid = start + (end - start) / 2;

        if (arr[mid] == key)
        {
            return arr[mid];
        }

        if (key > arr[mid])
        {
            start = mid + 1;
        }
        
        if (key < arr[mid])
        {
            end = mid - 1;
        }
        

    }
    return -1;
}
