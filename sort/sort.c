#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Biblioteca para medir o tempo

// Função para mesclar dois subarrays (Merge Sort)
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Arrays temporários
    int L[n1], R[n2];

    // Copiando os dados para os arrays temporários
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Mesclando os arrays temporários
    i = 0; 
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Função de Merge Sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mescla as duas metades ordenadas
        merge(arr, left, mid, right);
    }
}

// Função de particionamento do Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivô
    int i = (low - 1);     // Índice do menor elemento

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Função de Quick Sort
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        // Ordena recursivamente as duas metades
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Função para ler números de um arquivo e armazená-los em um array
int* readFile(char* fileName, int* size) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", fileName);
        exit(1);
    }

    int capacity = 10;
    int* arr = (int*)malloc(capacity * sizeof(int));
    *size = 0;

    while (fscanf(file, "%d", &arr[*size]) == 1) {
        (*size)++;
        if (*size >= capacity) {
            capacity *= 2;
            arr = (int*)realloc(arr, capacity * sizeof(int));
        }
    }

    fclose(file);
    return arr;
}

// Função para escrever um array ordenado em um arquivo
void writeFile(char* fileName, int arr[], int size) {
    FILE* file = fopen(fileName, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", fileName);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    char inputFileName[100], outputFileNameMerge[100], outputFileNameQuick[100];
    int *arrMerge, *arrQuick;
    int size;

    // Lê o nome dos arquivos
    printf("Digite o nome do arquivo de entrada (.in): ");
    scanf("%s", inputFileName);

    printf("Digite o nome do arquivo de saída para o Merge Sort: ");
    scanf("%s", outputFileNameMerge);

    printf("Digite o nome do arquivo de saída para o Quick Sort: ");
    scanf("%s", outputFileNameQuick);

    // Medição do tempo
    clock_t startMerge, endMerge, startQuick, endQuick;
    double timeMergeSort, timeQuickSort;

    // Lê os números do arquivo de entrada para ambos os algoritmos
    arrMerge = readFile(inputFileName, &size);
    arrQuick = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        arrQuick[i] = arrMerge[i];  // Copia o array original para o Quick Sort
    }

    // Merge Sort
    startMerge = clock();
    mergeSort(arrMerge, 0, size - 1);
    endMerge = clock();
    timeMergeSort = ((double)(endMerge - startMerge)) / CLOCKS_PER_SEC;

    // Escreve o resultado do Merge Sort
    writeFile(outputFileNameMerge, arrMerge, size);
    free(arrMerge);

    // Quick Sort
    startQuick = clock();
    quickSort(arrQuick, 0, size - 1);
    endQuick = clock();
    timeQuickSort = ((double)(endQuick - startQuick)) / CLOCKS_PER_SEC;

    // Escreve o resultado do Quick Sort
    writeFile(outputFileNameQuick, arrQuick, size);
    free(arrQuick);

    // Exibe os tempos de execução
    printf("Tempo de execução do Merge Sort: %f segundos\n", timeMergeSort);
    printf("Tempo de execução do Quick Sort: %f segundos\n", timeQuickSort);

    // Comparação dos tempos
    if (timeMergeSort < timeQuickSort) {
        printf("Merge Sort foi mais rápido.\n");
    } else if (timeMergeSort > timeQuickSort) {
        printf("Quick Sort foi mais rápido.\n");
    } else {
        printf("Ambos os algoritmos tiveram o mesmo tempo de execução.\n");
    }

    return 0;
}
