#include <stdio.h>

// Bu fonksiyon, bir dizideki iki elemanın yerlerini değiştirmek için kullanılır.
void swap(int *array, int i, int j) {
    int temp = array[i]; // Eleman i'nin değerini geçici bir değişkende saklar.
    array[i] = array[j]; // Eleman i'nin değerini eleman j'nin değeriyle değiştirir.
    array[j] = temp;      // Eleman j'nin değerini geçici değişkendeki değerle değiştirir, böylece swap işlemi tamamlanmış olur.
}

// Bu fonksiyon, verilen bir diziyi pivot elemana göre böler ve pivot elemanın doğru konumunu döndürür.
int partition(int *array, int low, int high, int pivot) {
    int i = low;  // Dizinin başlangıç indisini temsil eden değişken.
    int j = high; // Dizinin son indisini temsil eden değişken.

    while (i <= j) {
        // Dizinin sonundan başlayarak pivottan büyük elemanlar olduğu sürece dönmeye devam eder. Ayrıca pivot değerine eşit olan elemanları bulur ve high ile yer değiştirir.
        while (j >= 0 && array[j] >= pivot) {
            if (array[j] == pivot) {
                swap(array, j, high);
            }
            j--;
        }
        // Pivot değerinden küçük olan bir eleman bulur.
        while (array[i] < pivot) {
            i++;
        }
        // Bu iki elemanın yerlerini değiştirir.
        swap(array, i, j);
    }

    // Pivot elemanın doğru konumunu bulduktan sonra, pivot elemanı ile i'nin yerini değiştirir.
    swap(array, i, j);
    swap(array, i, high);

    // Pivot elemanın doğru konumunu döndürür.
    return i;
}

// Bu fonksiyon, verilen kilitler ve anahtarlar dizilerini karşılaştırarak eşleşenleri bulur.
void nutAndBoltMatch(int *locks, int *keys, int low, int high) {
    if (low < high) {
        // Anahtar dizisindeki son elemanı pivot olarak seçip, kilit dizisini böler.
        int pivotLoc = partition(locks, low, high, keys[high]);
        // Pivot elemanın konumunu kullanarak anahtar dizisini böler.
		partition(keys, low, high, locks[pivotLoc]);

		// Pivottan daha küçük elemanları içeren alt diziyi ve daha büyük elemanları içeren üst diziyi tekrar böler.
        nutAndBoltMatch(locks, keys, low, pivotLoc - 1);
        nutAndBoltMatch(locks, keys, pivotLoc + 1, high);
    }
}

// Method to print the array
void printArray(int *arr, int n) {
	int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int lock[] = {4, 2, 5, 1, 6, 10, 3, 7}; // Kilitler dizisi
    int key[] = {10, 1, 6, 7, 5, 2, 4, 3}; // Anahtarlar dizisi
    int size = sizeof(lock) / sizeof(lock[0]); // Dizilerin boyutunu hesaplar
	int i;
	
	// Eşleşmeden önce kilitler ve anahtarların ilk halini ekrana yazdırılır.
	printf("Locks and keys before matching:\n");
	printArray(lock, size);
    printArray(key, size);
	
	// Kilitler ve anahtarlar eşleştirilir.
    nutAndBoltMatch(lock, key, 0, size - 1);
    
	// Eşleşen kilitler ve anahtarlar ekrana yazdırılır.
    printf("Locks and keys after matching:\n");
    printArray(lock, size);
    printArray(key, size);
   
    return 0;
}
