1-	Problem Tanımı:
Bu ödevde bir sistemde bulunan kullanıcı isimlerini saklayan, ekleme, arama ve silme işlemleri yapılabilen ve yeni tablo boyutu ile yeniden düzenlenebilen bir hash tablosu hazırlanmıştır. 
Tabloya yerleştirilecek kullanıcı isimlerinin sayı karşılığı Horner Kuralı kullanılarak hesaplanmıştır. 
Hash tablosu oluşturulurken openaddress, çakışma problemini çözmek için double hashing yöntemi kullanılmıştır. Hash fonksiyonu olarak bölme (division) yöntemi kullanulmıştır. 
Kullanılacak Hash fonksiyonları:
h(key, i) = (h1(key) + i*h2(key)) % m
h1(key) = key % m
h2(key) = 1 + (key % m2)     	->    		(m2 = m-2) 
2-	Problemin Çözümü:
Problemin çözümünde hash tablosu girilen N ve LoadFactor değerine göre hesaplanan M değeri boyutunda dinamik olarak tahsis edilmiştir.
Bizden “kullanıcı adı” ve “deleted” şeklinde o kullanıcının silinip silinmediğini anlamamıza yarayacak bir değişken tutmamız istenmişti. Bu nedenle bu iki değişkeni tutan bir sturct Node yapısı oluşturulmuştur.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/033dd3d3-e94c-4f8c-b367-f486ebe3c3fb)

Her bir elemanı struct Node türünde olacak şekilde struct Node * tipinde bir hash tablosu M boyutunda olacak şekilde dinamik olarak tahsis edilmiştir.
(Hash tablosu elemanları structure olan bir dizidir.)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/88ceefdf-72dd-43d3-9af8-2039a736b3a9)

Oluşturulan bu hash tablosuna ilk değerler atandıktan sonra kullanıcının hash tablosu üzerinde ekleme, arama, silme, düzenleme işlemlerini yapabilmesi için uygun fonksiyonlar yazılmıştır.

--------------------------------------------------------------------------------------------
void initializeArray(struct Node *hashTable, int table_size);

void insert(char *userName, int table_size, struct Node *hashTable, int isDebugMod);

int search(struct Node *hashTable, int table_size, char *userName, int isDebugMod);

void deletion(struct Node *hashTable, int table_size, char *userName, int isDebugMod);

void rearrangeHashTable(int *M, struct Node **hashTable, int isDebugMod);

--------------------------------------------------------------------------------------------

Kullanıcıdan alınan “kullanıcı adı” bilgisine göre hash tablosu üzerinde yukarıdaki işlem yapılacağından isimlerinin sayı karşılığı Horner Kuralı kullanılarak hesaplanmıştır. 

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/e8384f23-e82d-4255-96d4-86159ea9ab53)

Hash tablosu oluşturulurken openaddress, çakışma problemini çözmek için double hashing yöntemi kullanılmıştır.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/5a0a1f54-953c-4e81-abba-a5235b6529d9)

Kullanıcı programı debug ve normal mod olmak üzere iki modda çalıştırabilmektedir.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/ac00343a-60ab-4072-b6b3-9706bd3af33a)

Kullanıcının yapmak istediği işlemi seçmesi için bir MENÜ sunulmuştur.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/959a97e7-bbd4-4912-8bba-48eb10967aa2)

Program sonlandırılmadan önce kullanılan hash tablosu için tahsis edilen bellek bölgesinin serbest bırakılması sağlanmıştır.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/9cd3d913-693b-4143-9923-cebc10b444bb)

3-	Karmaşıklık Analizi:
Problemin çözümünde ekleme, arama ve silme işlemleri için hash tablosu oluşturulurken openaddress, çakışma problemini çözmek için double hashing yöntemi kullanılmıştır. Bu nedenle çözümümüzün karmaşıklığı double hashing algoritmasının karmaşıklığı ile belirlenmektedir.
Double hashing'in karmaşıklığı genellikle çakışmaların derecesine bağlıdır. En iyi, ortalama ve en kötü durum için karmaşıklıklar şu şekilde açıklanabilir:

En İyi Durum:
En iyi durumda, çakışma olmaz ve her bir eleman için bir hash değeri atanırken boş hücrelere kolayca yerleştirilebilirler. Bu durumda, ekleme, erişim ve silme işlemleri genellikle O(1) karmaşıklığında gerçekleşir.

Ortalama Durum:
Ortalama durumda, çakışmalar rastgele dağılır ve tablonun doluluk oranı görece düşüktür. İdeal olarak, çakışmaların minimum olması için hash fonksiyonları eşit derecede dağıtılmış bir şekilde çalışmalıdır. Bu durumda, double hashing genellikle O(1) karmaşıklığına yakın bir performans gösterebilir, ancak çakışma sayısı ve doluluk oranı arttıkça bu karmaşıklık biraz yükselir.

En Kötü Durum:
En kötü durumda, çakışmaların çok fazla olduğu veya çakışmaların çözümü için yapılan ikinci hash işlemlerinin başka çakışmalara yol açtığı durumlar söz konusu olabilir. Bu durumda, en kötü durumda double hashing'in karmaşıklığı O(n) olabilir, çünkü her elemanı yerleştirmek veya erişmek için lineer bir arama yapılabilir.
Double hashing, genellikle iyi seçilmiş hash fonksiyonları ile birlikte kullanıldığında iyi performans gösterir. Ancak, kötü bir hash fonksiyonu veya yüksek doluluk oranları gibi durumlar, bu yöntemin karmaşıklığını artırabilir ve performansını düşürebilir.
Burada doluluk oranı dediğimiz şey "load factor" ile ifade edilir. Yani double hashing'in karmaşıklığı, load factor ile doğrudan ilişkilidir. Load factor ne kadar yüksekse, çakışma olasılığı da o kadar artar.

Load Factor = (Eleman Sayısı) / (Tablo Boyutu)

Double hashing'in performansı load factor ile doğrudan ilişkilidir çünkü çakışmaların olasılığı tablo doluluk oranıyla artar. Daha yüksek bir load factor, daha fazla çakışma olasılığına ve çakışma çözme sürecinin daha zor olmasına yol açabilir.

Load factor arttıkça çakışma olasılığı artar ve bu da ikinci hash fonksiyonunun daha fazla kullanılması gerektiği anlamına gelir. Çakışma sayısı arttıkça çözüm süresi ve işlemlerin karmaşıklığı artabilir. Bu durumda, load factor düşürülerek tablo boyutu artırılabilir veya çakışmaları azaltacak daha etkili hash fonksiyonları kullanılabilir, bu da performansı iyileştirebilir. Bu nedenle, hash tablolarında load factor genellikle performans optimizasyonu için dikkate alınır ve yönetilir.
