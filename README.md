Linux Syslog Yönetim Sistemi (Bağlı Liste Uygulaması)
Proje Hakkında
Bu çalışma, Linux işletim sistemindeki sistem günlüklerinin (syslog) çalışma mantığını anlamak ve bu verileri veri yapıları dersinin temel konularından biri olan Bağlı Liste (Linked List) yapısı ile simüle etmek amacıyla geliştirilmiştir.

Proje, sistemde oluşan olayları kronolojik bir sırada tutar, dinamik bellek yönetimi kullanarak verimli bir depolama sağlar ve C dilinde modüler bir yapıda tasarlanmıştır.

Teknik Detaylar
1. Syslog Mekanizması
Syslog, sistemde meydana gelen kernel hataları, kullanıcı girişleri ve servis uyarıları gibi olayların kaydedildiği standart bir protokoldür. Bu projede kullanılan temel birimler:

KERNEL: Donanım ve çekirdek seviyesindeki olaylar.

AUTH: Kullanıcı yetkilendirme ve güvenlik işlemleri.

NETWORK: Ağ bağlantısı ve yapılandırma olayları.

CRON: Zamanlanmış görevlerin takibi.

2. Veri Yapısı Seçimi: Neden Bağlı Liste?
Bu projede Tek Yönlü Bağlı Liste (Singly Linked List) tercih edilmiştir. Tercih nedenleri şunlardır:

Dinamik Bellek Yönetimi: Log dosyalarının boyutu önceden kestirilemez. Bağlı liste sayesinde dizi boyutunu önceden belirlemek zorunda kalmadan, her yeni log için malloc ile çalışma zamanında yer ayrılır.

Esneklik: Yeni bir log kaydı eklendiğinde mevcut verilerin kaydırılmasına gerek duyulmaz; sadece işaretçiler (pointers) güncellenerek hızlı bir ekleme yapılır.

Sıralı Erişim: Günlük kayıtları doğası gereği sıralı (kronolojik) bir yapıdadır. Bağlı liste yapısı bu akışı korumak için en uygun modellerden biridir.

Kodun Fonksiyonel Yapısı
Yazılan program şu temel bileşenlerden oluşmaktadır:

GunlukDugumu Yapısı: Her bir log kaydının zamanını, birim adını ve mesajını tutan struct yapısıdır.

yeni_gunluk_olustur(): Bellekten yer ayırarak verileri bir düğüm içine paketleyen fonksiyondur.

gunluk_ekle(): Oluşturulan düğümü listenin sonuna ekleyerek zaman sırasını koruyan fonksiyondur.

gunlukleri_listele(): Listedeki tüm verileri formatlı bir tablo şeklinde kullanıcıya sunar.

bellegi_bosalt(): Program sonlanırken kullanılan tüm RAM alanını sisteme geri iade ederek "Memory Leak" (bellek sızıntısı) oluşmasını engeller.

Nasıl Çalıştırılır?
Proje herhangi bir standart C derleyicisi (GCC, Clang vb.) veya CLion IDE'si ile çalıştırılabilir.

Terminali açın.

Dosyanın bulunduğu dizine gidin.

Aşağıdaki komutu yazarak derleyin:
gcc main.c -o syslog_uygulamasi

Programı çalıştırın:
./syslog_uygulamasi

Geliştirici Bilgileri
Ad Soyad: Şeymanur Eke
Proje: Veri Yapıları Ödevi - Linux Syslog Simülasyonu
