1-	Problem Tanımı:
Verilen bir sosyal ağ grafiği içerisinde topluluk tespiti yapacak bir algoritma tasarlanması istenmektedir. Bu algoritma, ağ içerisindeki grupları (toplulukları) ve bu topluluklara ait düğümleri belirlemeyi amaçlamaktadır.
Algoritma, kenarların ara kesici değerlerini hesaplar, en yüksek ara kesici değere sahip kenarı kaldırarak toplulukları belirler. Belirli koşullara göre işlemleri tekrarlar ve belirli durma koşullarını sağladığında sonuçları ekrana yazdırır.

2-	Problemin Çözümü:
Yazdığım kod, bir sosyal ağ grafiği içerisinde toplulukları tespit etmek için tasarlanmıştır. Bu çözüm algoritması, ağ yapısını manipüle ederek belirli bir ara kesici değer üzerinden kenarları kaldırarak toplulukları belirler ve belirli durma koşullarına göre işlemleri tekrarlar.
Ana Akış:
Dosyadan giriş alınır (input.txt).
Belirli iterasyonda algoritma çalıştırılır:
En yüksek ara kesici değere sahip kenar kaldırılır.
Sonda topluluk sayısı ve üyeleri ekrana yazdırılır.
Bu çözüm, sosyal ağ grafiğinde toplulukları belirlemek için ara kesici değerler üzerinden kenar kaldırma yöntemini kullanır ve belirli durma koşullarına bağlı olarak çalışır. Her adımda toplulukları tespit ederek, koşullar sağlandığında sonuçları ekrana yazdırır.

3-	Ekran Çıktıları:
Verilen örenklerden girdi 1 için kodumu çalıştırdım.

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/32f674db-a18f-4780-a5a8-8def74464829)

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/329d2607-95f9-46b4-aefa-1cf2c548d094)

Bu graf için input.txt dosyam: Burada bu graftaki düğüm sayısı ve grafın komşuluk matrisi var.
Düğüm sayısı : 5
Düğümler: 0 1 2 3 4 düğümler olacak şekilde algoritmayı oluşturdum. (Sırasıyla A B C D E değerlerine karşılık olarak )

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/5a7f7785-8b38-4a91-89e8-8c5d6d7dc65b)

1.iterasyonda:

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/356dbe0c-9922-4aa7-a83f-deae69d47735)

Bu çıktıyı örnek girdinin çıktısı ile karşılaştırdığınıza doğru olduğunu görebilirsiniz. 
Bir iterasyon sonra topluluklara bakalım:
2.iterasyonda

![image](https://github.com/Sevda-Karahan/Algorithm-Analysis/assets/116480291/1df2d178-c3e7-45a8-8041-f2065d079277)
