#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// Kullanıcı adlarını ve silinme durumunu saklamak için Node yapısı
struct Node {
    char *userName; // Kullanıcı adı
    int deleted; // Silinme durumunu belirten bayrak
};

// Bir sayının asal olup olmadığını kontrol etmek için fonksiyon
int isPrime(int num){
	if(num < 2){
		return 0;
	}
    int sq_root = sqrt(num); // Sayının karekökü alınır
    int i;
    for(i = 2; i <= sq_root; i++) { // 2'den başlanır. Sayının kareköküne kadar gidilir.
        if (num % i == 0) { // Sayının, kendi kareköküne kadar olan sayılardan herhangi birine tam bölünüp bölünmediği kontrol edilir.
            return 0; // Böleni varsa sayı asal değildir.
        }
	}
    return 1; // Sayı asaldır.
}

// Verilen argümandan büyük eşit olan ilk asal sayıyı bulan fonksiyon
int primeM(int M){
	while (!isPrime(M)){ //Sayı asal olmadığı sürece dön
        M++; 
    }   
    return M;
}

// Verilen boyutta bir hash tablosu oluşturmak için fonksiyon
struct Node *createHashTable(int table_size) {
	// struct Node tipinde elemenları tutacak olan, struct Node * tipindeki ve table_size boyutundaki hashTable dizisi için gerekli belleği 'malloc' ile dinamik bir şekilde ayırıyorum.
	struct Node *hashTable = (struct Node *)malloc(table_size * sizeof(struct Node));
	if (hashTable == NULL) { // Eğer bellek ayrılması başarısız olursa
        printf("Hash Tablosu icin bellek ayrilamadi!\n");
        return NULL;
    }
    return hashTable; // Bellek başarıyla ayrıldıysa, oluşturulan hash tablosu döndürülür
}

// Hash tablosunu varsayılan değerlerle başlatmak için fonksiyon
void initializeArray(struct Node *hashTable, int table_size){
	int i;
	for(i=0; i<table_size; i++) { // Tablo boyutu kadar dönülür. hashTable dizisinin her bir elemanı struct Node tipinde. Ve her bir struct Node, char * ve int olmak üzere iki değer tutuyor. Bu değerlere başlangıçta NULL ve -1 atanıyor.
		hashTable[i].deleted = -1; // -1 -> default, 1 -> deleted, 0 -> not deleted
		hashTable[i].userName = NULL;
	}
}

// Horner Kuralını kullanarak hashleme yapan fonksiyon
unsigned int hash(char *key, int isDebugMod){ //Horner's Rule -> Farklı herbir string için unique int değer üretir.
	unsigned int hashVal = 0;
	int i;
	for(i=0; i<strlen(key); i++) // String boyutu kadar dönülür ve her bir harf için Horner Kuralı uyguanır.
		hashVal = 31*hashVal + key[i];
	if(isDebugMod) {
		printf("%d",hashVal);
	}
	return hashVal;
}

// Birincil hash fonksiyonu
int hashFunction1(unsigned int key, int table_size) {
    return ((key) % table_size);
}

// Double hashing için ikincil hash fonksiyonu
int hashFunction2(unsigned int key, int table_size) {
    return 1 + ((key) % (table_size-2)); 
}

// Double hashing fonksiyonu
int doubleHash(unsigned int key, int i, int table_size) {
    return (hashFunction1(key, table_size) + i * hashFunction2(key, table_size)) % table_size;
}

// Kullanıcı adını hash tablosuna eklemek için fonksiyon
void insert(char *userName, int table_size, struct Node *hashTable, int isDebugMod) {
	unsigned int key = hash(userName, isDebugMod); // Kullanıcı adına karşılık gelen int değer alınır.
	int index = hashFunction1(key, table_size); // Bu değere karşılık gelen index bulunur.
	
    if(isDebugMod) {
    	printf("\nh1(\"%s\")= %d\n", userName, index); // hashFunction1 fonksiyonundan dönen değer ekrana yazdırılır.
	}
	
	int i = 1;
	while (hashTable[index].deleted != -1 && strcmp(hashTable[index].userName, userName) && i <= table_size) { //Hash Tablosunda o indexte bir eleman varsa veya silinmişse + bu eleman insert etmek istediğimiz userName'den farklı bir userName'de elemansa bir sonraki indexe bakacak şekilde dön. i <= table_size şartı ise tablo dolu iken eleman eklemeye çalıştığımızda döngüden çıkmamızı sağlar.
        if(isDebugMod) { // Program debug modda ise detaylı ekran çıktıları sunulur.
        	if(i==1) {
        		printf("h2(\"%s\")= %d\n", userName, hashFunction2(key, table_size)); // hashFunction2 fonksiyonundan dönen değer ekrana yazdırılır.
			}
			printf("%d. deneme -> %s elemani %d.adrese yerlestirilemedi.\n", i, userName, index);
		}
		index = doubleHash(key, i, table_size); // doubleHash fonksiyonu ile o key için yeni index değerini hesapla.
        i++;
    }
    if(hashTable[index].deleted == -1){ // O indexe henüz bir eleman eklenmemişse
    	hashTable[index].userName = (char *)malloc((strlen(userName) + 1) * sizeof(char)); // Hash tablosunun o indexindeki kullanıcı adı için yer tahsis et.
    	if (hashTable[index].userName != NULL) { // Bellek başarılı bir şekilde tahsis edilebildiyse
    		strcpy(hashTable[index].userName, userName); // Hash tablosunun o indexindeki kullanıcı adını ata ve eleman eklendiği için deleted = 0 şeklinde güncelle.
		    hashTable[index].deleted = 0;
		    if(isDebugMod) { // Program debug modda ise insert işleminde kaçıncı denemede olduğu ekrana yazdırılır.
		    	printf("%d. deneme -> ", i);
			}
		    printf("%s elemani %d.adrese yerlestirildi.\n", userName, index);
		}
		else { // Bellek ayırma başarısız
			printf("Kullanici adi(userName) icin bellek ayrilamadi!!\n");
		}
    	
	} 
	else if(hashTable[index].deleted == 1 && !strcmp(hashTable[index].userName, userName) ) { // O indexteki silinmiş eleman, tekrar eklenmek istiyorsa
		// strcpy(hashTable[index].userName, userName); // fiziksel bir silme yapmadığımız için isim zaten hashTable[index].userName'de duruyordu.
		hashTable[index].deleted = 0; 
		printf("%d. deneme -> %s elemani %d.adrese yerlestirildi.\n", i, userName, index);
	}
	else if(i > table_size) // Tablo tamamen doluysa
	{
		printf("Hash Tablosunda eleman eklenebilecek yer YOK!\n");
	}
	else { // hashTable[index].deleted == 0 iken strcmp(hashTable[index].userName, userName) == 0 ise eleman zaten önceden tabloya eklenmiş demektir.
		if(isDebugMod) { // Program debug modda ise detaylı ekran çıktısı sunulur.
			printf("%d. deneme -> Eleman tabloda %d. adreste mevcut oldugu icin ekleme islemi yapilmadi.\n", i, index);
		}
		else { // program normal modda ise
			printf("Eleman tabloda mevcut oldugu icin ekleme islemi yapilmadi.\n", index);
		}
	}
}

// Hash tablosunda bir kullanıcı adını aramak için fonksiyon
int search(struct Node *hashTable, int table_size, char *userName, int isDebugMod) {
	unsigned int key = hash(userName, isDebugMod);
	int index = hashFunction1(key, table_size);
	
	if(isDebugMod) { // Program debug modda ise
		printf("\nh1(\"%s\")= %d\n", userName, index); // hashFunction1 fonksiyonundan dönen değer ekrana yazdırılır.
	}
    
	int i = 1; 
    while (hashTable[index].deleted != -1 && i <= table_size) { // O indexte bir eleman olduğu sürece veya o indexte bir elman silinmişse + i <= table_size ise dön
    	if (!strcmp(hashTable[index].userName, userName)) { // O eleman aradığımız eleman mı?
    		if(isDebugMod) {
    			printf("%d. deneme -> ", i);
			}
			if(hashTable[index].deleted == 0) {
				printf("%s elemani %d.adreste bulunmaktadir.\n", userName, index);
    			return index; // Aradığımız elemanı(key) bulduk, elemanı bulduğumuz indexi dönderiyoruz
			}
			else { // hashTable[index].deleted == 1 -> eleman silinmiş
				printf("%s elemani tabloda bulunmuyor.\n", userName); // hashTable[index].deleted == 1 (O gözdeki eleman önceden silinmişse)
    			return -1; // Key bulunamadı
			}    		
		}
		if(isDebugMod) { // Program debug modda ise detaylı ekran çıktısı sunulur.
			if(i==1) {
	        	printf("h2(\"%s\")= %d\n", userName, hashFunction2(key, table_size)); // hashFunction2 fonksiyonundan dönen değer ekrana yazdırılır.
			}
			printf("%d. deneme -> %s elemani %d.adreste bulunamadi.\n", i, userName, index);
		}
        index = doubleHash(key, i, table_size); // indexi güncelliyoruz
        i++;
    }
    
    if(isDebugMod) {
    	printf("%d. deneme -> ", i);
	}
    printf("%s elemani tabloda bulunmuyor.\n", userName); // hashTable[index].deleted == 1 (O gözdeki eleman önceden silinmişse) veya hashTable[index].deleted == -1 (O gözde eklenmiş eleman yoksa)
    return -1; // Key bulunamadı
}

// Hash tablosundan bir kullanıcı adını silmek için fonksiyon
void deletion(struct Node *hashTable, int table_size, char *userName, int isDebugMod) {
	int searchResult = search(hashTable, table_size, userName, isDebugMod); // Silinmek istenen eleman hash tablosunda aranıyor
	if(searchResult != -1) { // Eleman tabloda bulunduysa, searchResult = bulunduğu index
		hashTable[searchResult].deleted = 1; // Elemanın siliğimiz için deleted güncellendi.
		printf("%d adresindeki %s elemani silindi.\n", searchResult, userName);
	}
	// Eleman tabloda yoksa searchResult = -1
}

// Hash tablosu için ayrılan belleği serbest bırakmak için fonksiyon
void freeHashTable(struct Node *hashTable, int table_size) {
	// Hash Tablosunun her bir indexindeki her bir düğümde kullanıcı adı için ayrılan belleği boşaltır
	int i;
	for (i = 0; i < table_size; i++) {
	    free(hashTable[i].userName);
	}
	// Hash Tablosunun kendisini serbest bırakır
	free(hashTable);
}

// Yeni bir boyutla hash tablosunu yeniden düzenlemek için fonksiyon
void rearrangeHashTable(int *M, struct Node **hashTable, int isDebugMod) { // Burada her iki parametrenin de pointer şeklinde alınmasının sebebi M ve hashTable için yapılan değişikliklerin ana fonksiyona da yansıması
	int tmpM = *M; // M değeri değiştirilmeden önce tmpM değişkeninde tutulur. Çünkü eski tablo için ayrılan bellek bölgesinin serbest bırakılması için eski M değerine ihtiyacımız olacak.
	struct Node *tmp_hashTable = *hashTable; // Yine hashTable'ın gösterdiği yeri tmp_hashTable değerine atıyoruz ki sonradan eski hash tablosunu free edebilelim.
	printf("Hash Tablosu icin yeni tablo boyutunu(M) giriniz : ");
	scanf("%d", M); // M değeri girilen yeni değer ile güncellendi.
	
	*hashTable = createHashTable(*M); // Güncel M değeri ile hash tablosu oluşturularak, eski hash tablomun yeni hash tablomu göstermesini sağlıyorum.
    initializeArray(*hashTable, *M); // Yeni/Güncellenmiş hash tablosu için ilk değerlerin atanması
    
	int i;
	for(i=0; i<tmpM; i++) { // Tablonun eski boyutu kadar dönülür.
		if(tmp_hashTable[i].deleted == 0) { // Eski hash tablomda elaman bulunan indisler için
			if(isDebugMod) { // Program debug moddaysa
				printf("\n(Eski hash tablosunda %d. adreste bulunan) ", i);
			}
			insert(tmp_hashTable[i].userName, *M, *hashTable, isDebugMod); // O elemanın yeni hash tablosuna insert işlemi gerçekleştiriliyor.
		}
		// Program debug moddaysa
		else if(isDebugMod && tmp_hashTable[i].deleted == 1){ // Eleman(key) silinmişse
			printf("\n(Eski hash tablosunda %d. adreste bulunan %s elemani silinmis.)\n", i, tmp_hashTable[i].userName);
		}
		//else -> isDebugMod && tmp_hashTable[i].deleted == -1 (Eski Hash Tablosunun bu i.gözüne eleman eklenmemiş.)
	}
	freeHashTable(tmp_hashTable, tmpM); // Eski hash tablosu için bellekte ayrılan alan serbest bırakılıyor.
}

void displayHashTable(struct Node *hashTable, int table_size) {
	int i;
	for (i = 0; i < table_size; i++) {
		if(hashTable[i].deleted == 0) {
			printf("+ %d adresindeki eleman %s\n", i, hashTable[i].userName);
		}
	    else if(hashTable[i].deleted == -1){
	    	printf("- %d adresinde eleman yok\n", i);
		}
		else { // hashTable[i].deleted == 1
			printf("- %d adresindeki eleman (%s) silinmis\n", i, hashTable[i].userName);
		}
	}
}

int main(){
	float LoadFactor;
	int N, M;
	printf("Tabloya eklenebilecek eleman sayisini(N) giriniz : ");
	scanf("%d", &N);
	printf("LoadFactor degerini giriniz : ");
	scanf("%f", &LoadFactor);
	M = (int)(N/LoadFactor);
	printf("(N/LoadFactor): %d\n", M);
	M = primeM(M);
	printf("Hash Tablosunun tablo boyutu (M) : %d\n", M);
	
	struct Node *hashTable = createHashTable(M);
    initializeArray(hashTable, M);
    
	int choice1;
    printf("\nProgrami hangi modda calistirmak istersiniz?"
											"\n1.NORMAL"
											"\n2.DEBUG"
											"\nSeciminiz: ");
	scanf("%d", &choice1);
	int isDebugMod;
	if(choice1 == 1)
		isDebugMod=0;
	else
		isDebugMod=1;
	
	int choice2, flag=0; // Flag menüden çıkış yapabilmek için
	char userName[25]; // Kullanıcının hash tablosu üzerinde ekleme, arama, silme yapmak için gireceği Kullanıcı adı (userName) bilgisini tutması için
	//printf("\nHash Tablosunun C Dilinde Implementasyonu\n\n");
	while(flag == 0) {
		printf("\n***********************************\n");
		printf("MENU-:  \n1.Hash Tablosuna Eleman Ekleme"
						"\n2.Hash Tablosunda Eleman Arama"
                        "\n3.Hash Tablosundan Eleman Silme"
		                "\n4.Hash Tablosunu Yeniden Boyutlandirarak Duzenleme" 
                        "\n5.Hash Tablosunun Boyutunu Ogrenme"
                        "\n6.Hash Tablosunu Goruntuleme"
                        "\n7.Cikis"
		    			"\n\nSeciminiz : ");
		scanf("%d", &choice2);
		switch(choice2) 
        {
			case 1:
				printf("***Hash Tablosuna Eleman Ekleme***\n");
		      	printf("Kullanici adi giriniz :\t");
		      	scanf("%s", userName);
				insert(userName, M, hashTable, isDebugMod);
			    break;
			case 2:
				printf("***Hash Tablosunda Eleman Arama***\n");
		      	printf("Kullanici adi giriniz :\t");
		      	scanf("%s", userName);
				search(hashTable, M, userName, isDebugMod);
			    break;
			case 3:
				printf("***Hash Tablosundan Eleman Silme***\n");
		      	printf("Kullanici adi giriniz :\t");
		      	scanf("%s", userName);
				deletion(hashTable, M, userName, isDebugMod);
			    break;
	 		case 4:
	 			printf("***Hash Tablosunu Yeniden Boyutlandirarak Duzenleme***\n");
				rearrangeHashTable(&M, &hashTable, isDebugMod);
			    break;
			case 5:
				printf("***Hash Tablosunun Boyutunu Ogrenme***\n");
				printf("Hash Tablosunun tablo boyutu (M) : %d\n", M);
			    break;
			case 6:
				printf("***Hash Tablosunu Goruntuleme***\n");
				displayHashTable(hashTable, M);
			    break;
			case 7:
				printf("***Cikis***\n");
				flag = 1;
			    break;
			default:
			    printf("Hata! 1-7 arasında bir deger giriniz.\n");
		}
	}
	
	freeHashTable(hashTable, M); // En son kullanılan hash tablosu için ayrılan bellek bölgesinin serbest bırakılması
	return 0;
}
