1-	Problem Tanımı:
Bu ödevde verilen iki string içerisine şifre olarak yerleştirilmiş birden fazla en uzun sekansa sahip ifadeler “Dinamik Programlama” yaklaşımı kullanılarak bulunacaktır.
1. Dışarıdan farklı uzunluklarda verilen iki adet string bilgisi okunacaktır.
2. Verilen string’ler üzerinde ortak olan en uzun ifade(ler)in boyutu hesaplanacaktır.
3. Aynı uzunluğa sahip tüm ifadeler ekrana yazdırılacaktır.

2-	Problemin Çözümü:
Problemin çözümü için dinamik programlama yaklaşımı kullanılarak iki farklı string arasındaki en uzun ortak alt dizileri bulan ve geriye doğru bir yol izleyerek olası tüm en uzun alt dizileri tespit eden bir çözüm oluşturulmuştur. 
Kullanıcı Girişi: İlk olarak, iki farklı string kullanıcıdan alınıyor: X ve Y.
LCS Fonksiyonu: LCS fonksiyonu, en uzun ortak alt dizi (LCS) uzunluğunu hesaplamak için dinamik programlama yöntemini kullanır. Bu işlem şu adımları takip eder:
DP ve İşaret Matrislerinin Oluşturulması: İki string arasındaki en uzun ortak alt dizi için bir DP (dynamic programming) matrisi ve bir işaret matrisi oluşturulur. DP matrisi, her adımda en uzun alt dizi uzunluğunu saklar. İşaret matrisi ise hangi karakterlerin seçildiğini belirtir.
İlk Durumun Başlatılması: Matrislerin ilk satırı ve sütunu sıfırlarla doldurulur.
Karakter Eşleşmesi Kontrolü: Her iki stringin karakterleri karşılaştırılır. Eşleşme durumunda, DP matrisinde ilgili hücreye bir eklenerek en uzun alt dizi uzunluğu güncellenir ve işaret matrisinde ilgili hücre işaretlenir.
Eşleşmeme Durumu: Eğer karakterler eşleşmiyorsa, en uzun alt dizi uzunluğu daha önceki adımlardaki en büyük değere eşitlenir ve işaret matrisinde ilgili hücre işaretlenmez.
Matrislerin Güncellenmesi: Her adımda DP ve işaret matrisleri güncellenir, sonuçlar ekrana yazdırılır.
printAllLCS Fonksiyonu: Bu fonksiyon, DP matrisindeki bilgileri kullanarak en uzun ortak alt dizileri bulur ve ekrana yazdırır. Bu işlem, geriye doğru bir yol izleyerek olası tüm en uzun alt dizileri tespit eder.
printMatrix Fonksiyonu: Bu fonksiyon, verilen bir matrisi ekrana yazdırmak için kullanılır. DP ve işaret matrislerinin adımları üzerindeki durumlarını görselleştirmek için kullanılır.
Bu adımların sonucunda, en uzun ortak alt dizilerin uzunluğu hesaplanır ve bu alt diziler ekrana yazdırılır.



3-	Karşılaşılan Sorunlar:
Verilen string’ler üzerinde ortak olan en uzun ifade(ler) bulunup ekrana bastırlırken aynı ifadenin farklı yollardan elde edilebildiğini fark ettim. Bu nedenle ifadeler tekrarlı olarak ekrana bastırılabiliyordu. Bu problemi çözmek için “uniqueResults” isimli, string tutan bir matris tanımlayarak her bir ifadenin sadece bir kere bu matrise eklenmesi ile ve bu sayede ekrana sadece bir kere basılabilmesi ile bu problemi çözmüş oldum.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/6995e880-9572-45d8-9dbd-3942130a2cd4)

4-	Karmaşıklık Analizi:
LCS Fonksiyonu:
DP ve İşaret Matrislerinin Oluşturulması: Bu adım iki döngü içerir: İlk döngü, n kez (string X uzunluğu), ikinci döngü ise m kez (string Y uzunluğu) döner. Bu durumda bu adımın karmaşıklığı O(n * m) olur.
Karakter Eşleşmesi Kontrolü: Bu adım, iç içe iki döngü içerir, yani n kez m işlem yapılır. Karmaşıklığı O(n * m) olur.
Matrislerin Güncellenmesi: Bu da iç içe iki döngü içerir, yani n kez m işlem yapılır. Karmaşıklığı yine O(n * m) olur.
Bu durumda, LCS fonksiyonunun toplam karmaşıklığı O(n * m) olur.
printAllLCS Fonksiyonu:
Bu fonksiyon, tüm en uzun alt dizileri bulmak için kullanılır. Ancak bu alt dizilerin sayısı ve uzunlukları, genellikle çıktıya bağlıdır. En kötü durumda, tüm alt dizileri yazdırmak O(2^k) olabilir, burada k, en uzun alt dizi uzunluğudur. Ancak, genellikle çoğu durumda bu karmaşıklık özellikle uzun diziler için oldukça yüksek olabilir.
Genel olarak, bu algoritmanın karmaşıklığı string uzunlukları n ve m için O(n * m) düzeyindedir. Ancak alt dizilerin yazdırılması için kullanılan printAllLCS fonksiyonu, alt dizilerin sayısına bağlı olarak daha yüksek bir karmaşıklık gösterebilir.
5-	Ekran Çıktıları:

I)

ABCDZB

BACEDAB

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/4446fe18-ee42-458c-b8bd-31e8b5448e28)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/3fdd61b4-8f47-46ad-83b7-f1a592702759)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/2a923c17-eb4c-4a60-a89a-820eb49e7e3f)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/84fb6e71-4dd8-4861-babe-3d7003157515)

II)

MAERBPHCAPPBA

AMRRERCHAZBZA

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/1c6cd313-344b-488f-a95c-939005577d7b)

.
.
.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/44877e7f-c9fa-46e0-bedd-1671a43cca7c)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/8323fdfb-2b27-4d7b-be9a-f9b27ded01ba)

III)

RSBECGREEAT

KRESLGECRFET

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/254dea99-a26e-4077-8e7f-289ba2b0bd24)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/0a7c7a9f-2725-48d9-b986-e024983b2b34)

...

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/f85481d0-a3a9-42ea-909e-344a046c3a89)

IV)

ABCD

ABCD

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/5305d89e-230f-4066-8c43-8511229420d5)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/2deaa7da-37f6-4aec-a0f3-ccb6544129c7)
