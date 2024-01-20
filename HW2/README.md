SORU 1:
•	Problem Tanımı:
Many Liars Problemi

•	Problemin Çözümü:
Bir çift kişiye sorduğunuzda üç takım yanıt ortaya çıkabilir:

1. {F, F}
2. {F, T }
3. {T, T}

Hem 1 hem de 2 için, çiftte en az bir yalancı olması gerektiğini biliyoruz. Böylece her ikisini de listeden çıkararak problemi küçültebiliriz. (Recursion) Daha küçük problemde hala yarıdan fazla doğruyu söyleyenler olacaktır.

Ancak durum her ikisinin de yalan veya her ikisinin de doğruyu söylediği 3.durum ile de sonuçlanabilir.

Aslında nihayetinde elimizde doğruyu söyleyenler ve yalancılardan oluşan bir liste oluşur. Ve yalancı çiftlerden çok doğruyu söyleyen çiftlerimiz olmuş olur.

Yani her çiftten bir kişiyi alıp problem boyutunun yarısı boyutunda bir problem elde edilir. (Recursion)
•	Karmaşıklık analizi ve 100 kişi için problemin ele alınması:

100 kişi için doğru söyleyen 1 kişiyi kaç adımda bulabilirsiniz?

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/5503bf65-bf33-4a52-b624-56e841723115)

SORU 2:
•	Problem Tanımı:
Bir kulede bulunan N odayı açmak için farklı büyüklükte N adet anahtar gerekmektedir. Her kilide uyan sadece bir anahtar olduğu bilinmektedir. Anahtarlar ve kilitler farklı büyüklüklerde ve karışık olarak bulunmaktadır. Anahtarlar ve kilitler, sadece kapılara takılarak kontrol edilebilmektedir. Verilen kilitler ve anahtarlar dizilerinde eşleşen çiftleri O(N*log2N) karmaşıklıkla bulacak bir algoritma tasarlanması gerekmektedir.

•	Problemin Çözümü:
Verilen kilitler ve anahtarlar dizilerini karşılaştırarak eşleşen çiftleri bulmak için Quicksort algoritması kullanılabilir. Quicksort algoritması, verilen bir diziyi pivot elemana göre böler ve pivot elemanın doğru konumunu bulur. Bu algoritmanın kilitler dizisine ve anahtarlar dizisine uygulanarak eşleşen çiftler bulunabilir. İlk olarak, bir pivot eleman seçilir ve kilitler dizisi pivot elemana göre bölünür. Pivot elemanın doğru konumu bulunduktan sonra, aynı konumda bulunan anahtar dizisi de pivot elemana göre bölünür. Bu işlem rekürsif olarak tekrarlanır, böylece tüm eşleşen çiftler bulunur.

•	Karmaşıklık Analizi:
Bu sorunun çözümünde bir böl-ve-yönet algoritması olan Quick sort algoritması kullanılmıştır. Temel adımları şu şekildedir:

Bölme (Partitioning): Dizi içinden bir eleman (pivot) seçilir ve pivot elemanın solunda pivot'tan küçük, sağında pivot'tan büyük elemanlar yer alacak şekilde dizi bölünür.

Yeniden Sıralama (Recursively Sort): Pivot eleman hariç, sol ve sağ alt diziler için quick sort algoritması tekrar uygulanır.
Quick sort'un ortalama durum karmaşıklığı şu şekilde açıklanır:

Her aşamada, pivot eleman doğru konumuna yerleştirilir, bu işlem lineer zaman (O(n)) alır.

Diziyi ikiye böldükten sonra her iki alt dizi için quick sort algoritması tekrar çağrılır.
Quick sort, her seviyede diziyi ikiye böler, bu nedenle log(n) seviyede bölünme olur. Her seviyedeki bölme işlemi O(n) zaman alır. Bu durumda, ortalama durumda quick sort'un karmaşıklığı şu şekilde hesaplanır:

T(n) = 2T(n/2) + O(n)

Burada, T(n) dizinin boyutuna bağlı olarak işlem adımı sayısını temsil eder. 

1.yol: Master Teoremi
Bu rekürans bağıntısını çözmek için Master Teoremi kullanılabilir. Master Teoremi'ne göre, 
T(n) = aT(n/b) + f(n) formülünde, a = 2, b = 2, f(n) = O(n) olduğu durumda karmaşıklık şu şekilde hesaplanır:

T(n) = Θ(n log n)

Bu, quick sort algoritmasının ortalama durum karmaşıklığını ifade eder. Ancak, en kötü durumda (örneğin, her zaman en küçük veya en büyük elemanı pivot olarak seçtiğimizde) quick sort'un karmaşıklığı O(n^2) olabilir. En iyi ve ortalama durumda Θ(n log n) karmaşıklığına sahiptir.

2.yol: Backward Subtution

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/06daad75-8902-4eb3-9757-4ca147b31c80)

•	Ekran Çıktıları:
Senryo 1-

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/b813c163-7a38-44b0-89a2-20e5a947945a)

Senaryo 2-

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/eccd5b55-3aa3-431b-9e97-dd7a6374d7b6)

Senaryo 3-

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/2bc53c8d-f41b-4bc9-bd75-ad9742a9c5a7)

Senaryo 4-

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/0ccdc29c-20ee-48e3-9740-10a926384556)
