#include<iostream>
#include<random>
#include<chrono>
#include<ctime>

using namespace std;

//SORTS-------------------------------------------------------------------------------------


void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int array[], int const left, int const mid, int const right) {
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0,    // Initial index of first sub-array
         indexOfSubArrayTwo = 0;    // Initial index of second sub-array

    int indexOfMergedArray = left;  // Initial index of merged array

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end) {
    if (begin >= end)
        return; // Returns recursively

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

int partition (int arr[], int low, int high) {
    int pivot = arr[high];  // pivot
    int i = (low - 1);      // Index of smaller element and indicates the right position of pivot found so far
    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            i++; // increment index of smaller element
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort (int arr[], int low, int high) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now at right place */
        int pi = partition(arr, low, high);
        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


//SEARCHS-----------------------------------------------------------------------------

bool Linear_Search (int* vet, int size, int num) {
    for(int i=0; i<size; i++){
        if(vet[i] == num){
            return true;
        }
    }
    return false;
}

bool BinarySearch(int* vet, int pointer, int size, int num) {
    int mid = (pointer+size)/2;

    if(size >= pointer){
        if(vet[mid] == num)
            return true;
        if(vet[mid] < num)
            return BinarySearch(vet, mid+1, size, num);
        if(vet[mid] > num)
            return BinarySearch(vet, pointer, mid - 1, num);
    }
    return false;
}

//MANUPULACAO DE ARRAY-----------------------------------------------------------------

void CriaVetRand (int* vet, int size) {
    random_device rd;
    uniform_int_distribution<int> distNUM(20, 2000000);

    for(int i = 0; i < size;i++){
        vet[i] = distNUM(rd);
    }
}

void PrintArr (int Arr[], int size) {
    for (int i=0; i<size; i++) {
        cout << Arr[i] << " ";
    }
    cout << endl;
}

void SavingVet (int* vet, int* aux, int size) {     // fun��o para conseguir fazer os sorts no mesmo vetor criado inicialmente
    for (int i=0; i<size; i++) {
        aux[i] = vet[i];
    }
}

string PrintTime (int escolha, string nome, int* vet, int size) {     // fun��o para imprimir o tempo dos Sorts e dos Searchs
    double time_spent = 0.0;
    clock_t start = clock();
    switch (escolha) {
    case 1:
        mergeSort(vet, 0, size);
        break;
    case 2:
        quickSort(vet, 0, size);
        break;
    case 3:
        insertionSort(vet, size);
        break;
    case 4:
        BinarySearch(vet, 0, size, 700000);
        break;
    case 5:
        Linear_Search(vet, size, 700000);
        break;
    }
    clock_t end = clock();

    time_spent += (double)(end - start) / CLOCKS_PER_SEC;
    string tempo = to_string(time_spent);

    return "O tempo do " + nome + " foi " + tempo + "\n";
}
