#include <iostream>
#include <fstream>
#include <string>
using namespace std;

fstream medsfile;
fstream usersfile;


////////////////////////////////////////////////////////////////////////////////////////////////////

void kullaniciEkle()
{
	string kullaniciAdi;
	string kullaniciParolasi;

	cout << "Kayýt Olma Bölümüne Hoþgeldiniz" << endl;
	cout << "Lütfen Kullanmak istediðiniz Kullanýcý Adýný Giriniz: ";
	cin >> kullaniciAdi;

	cout << "Lütfen Kullanmak Ýstediðiniz Parolayý Giriniz: ";
	cin >> kullaniciParolasi;

	usersfile.open("kullanicilar.txt", ios::out | ios::app);
	if (usersfile.is_open())
	{
		string kayitlar;
		kayitlar = kullaniciAdi + ";" + kullaniciParolasi;
		usersfile << kayitlar << endl;

		cout << "Kayýt Ýþlemi Baþarýyla Tamamlandý" << endl;
		usersfile.close();
	}
	else
	{
		cout << "Dosya Açýlamadý!" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ilacEkle() {
	medsfile.open("ilaclar.txt", ios::in);

	if (medsfile.is_open()) {
		string ilacAdi;
		int ilacAdedi;
		int ilacFiyati;

		cout << "Ýlaç Adýný Giriniz: " << endl;
		cin >> ilacAdi;

		// Dosyada ilaç kontrolü
		string line;
		while (getline(medsfile, line)) {
			if (line.find(ilacAdi + ";") != string::npos) {
				cout << "Girdiðiniz ilaç zaten mevcut. Bilgileri güncellemek ister misiniz? (E/H)" << endl;
				char cevap;
				cin >> cevap;

				if (cevap == 'E' || cevap == 'e') {
					// Ýlaç bilgilerini güncellemek için eðer ayný isimde bir ilaç varsa
					

					cout << "Ýlaç baþarýyla güncellendi." << endl;
					medsfile.close();
					return;
				}
				else {
					cout << "Ýþlem iptal edildi." << endl;
					medsfile.close();
					return;
				}
			}
		}

		medsfile.close(); 

		cout << "Lütfen Ýlaç Adedini Giriniz: ";
		cin >> ilacAdedi;

		cout << "Lütfen Ýlaç Fiyatýný Giriniz: ";
		cin >> ilacFiyati;

		medsfile.open("ilaclar.txt", ios::out | ios::app);

		string ilacAdedi_str = to_string(ilacAdedi);
		string ilacFiyati_str = to_string(ilacFiyati);
		string kayitekle = ilacAdi + ";" + ilacAdedi_str + ";" + ilacFiyati_str;

		medsfile << kayitekle << endl;
		cout << "Ýlaç Stoða Giriliyor..." << endl;
		medsfile.close();
		cout << "Ýlaç Baþarýyla Stoða Eklenmiþtir"<<endl;
	}
	else {
		cout << "Dosya Açýlamadý !!" << endl;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void ilacSil() {
	string ilacAdi;
	cout << "Lütfen Silmek Ýstediðiniz Ýlacýn Adýný Giriniz: " << endl;
	cin >> ilacAdi;
	// TÝMESLEEP
	cout << "Seçtiðiniz Ýlaç Stokta Aranýyor" << endl;
	// TÝMESLEEP
	ifstream eskidosya("ilaclar.txt");
	ofstream yenidosya("temp.txt");

	if (!eskidosya.is_open() || !yenidosya.is_open()) {
		cout << "Dosya Açýlamadý!" << endl;
		return;
	}

	string line;
	bool bulunduMu = false;

	while (getline(eskidosya, line)) {

		size_t foundPos = line.find(ilacAdi + ";");
		if (foundPos != string::npos && (foundPos == 0 || line[foundPos - 1] == ';')) {
			bulunduMu = true;
			cout << "Girdiðiniz Ýlaç Stokta Bulundu"<<endl;
		}
		else {
			yenidosya << line << endl;
		}
	}

	eskidosya.close();
	yenidosya.close();

	remove("ilaclar.txt");     // Orijinal dosyayý sil
	rename("temp.txt","ilaclar.txt");  // Temp dosyasýný orijinal dosya adýna yeniden adlandýr

	if (bulunduMu) {
		cout << "Ýlaç baþarýyla silindi." << endl;
	}
	else {
		cout << "Ýlaç bulunamadý." << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ilaclariListele()
{
	string kayitlar;

	medsfile.open("ilaclar.txt", ios::in);
	if (!medsfile.is_open()) {
		cout << "Dosya Açýlýrken Bir Hata Ýle Karþýlaþýldý.." << endl;
		return;
	}

	cout << "Ýlaçlar Listeleniyor..." << endl;
	cout << "**********************************************" << endl;

	medsfile.seekg(0, ios::beg);

	while (getline(medsfile, kayitlar))
	{
		cout << kayitlar << endl;
		cout << "------------------------------------" << endl;
	}

	medsfile.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool kullaniciKontrol(string kullaniciAdi,string sifre) {
	usersfile.open("kullanicilar.txt", ios::in);
	if (!usersfile.is_open()) {
		cout << "Dosya Açýlamadý!" << endl;
		return false;
	}
	cout << "Kontrol Saðlanýyor...";
	//TÝMESLEEP
	string satir;
	while (getline(usersfile, satir)) {
		size_t pos = satir.find(kullaniciAdi + ";" + sifre);
		if (pos != string::npos) {
			usersfile.close();
			cout << "Eþleþme Saðlandý !!" << endl;
			return true;
		}
	}

	usersfile.close();
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ilacSorgula()
{
	string ilacadi;
	cout << "Lütfen Sorgulamak Ýstediðiniz Ýlacýn Adýný Giriniz: ";
	cin >> ilacadi;

	cout << "Ýlaç Stokta Aranýyor..."<<endl;
	cout << "**********************************************" << endl;

	medsfile.open("ilaclar.txt", ios::in);
	if (!medsfile.is_open()) {
		cout << "Dosya Açýlamadý!" << endl;
	}
	else
	{
		string satir;
		while (getline(medsfile, satir)) {
			if (satir.find(ilacadi + ";") != string::npos) {
				cout << satir << endl;  
				cout << "**********************************************" << endl;
			}
		}
		medsfile.close();  // Dosyayý döngünün dýþýnda kapat
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////7


int main()
{
	setlocale(LC_ALL, "Turkish");
	// Kullanýcý Giriþi 
	string kullaniciadi;
	string sifre;
	bool isLogined = false;
	bool isAdmin = false;
	int kontrol;

	cout << "Kullanýcý Giriþi Ýçin 1'i " << endl << "Kaydolmak Ýçin 2 Rakamýný Giriniz: ";
	cin >> kontrol;

	if (kontrol == 1) {
		do {
			cout << "Hoþgeldiniz Lütfen Giriþ Yapýnýz.." << endl;
			cout << "Kullanýcý Adý: ";
			cin >> kullaniciadi;
			//TÝMESLEEP
			cout << "Parola: ";
			cin >> sifre;
			//TÝMESLEEP
		} while (!kullaniciKontrol(kullaniciadi, sifre));
		cout << "Baþarýyla Giriþ Yapýldý ! " << endl <<"**********************************************" << endl<< "Hoþgeldiniz " << kullaniciadi << endl;
		isLogined = true;
	}

	else if (kontrol == 2) {
		kullaniciEkle(); // Yeni bir kullanýcý ekler
		cout << "Baþarýyla Kaydoldunuz! Lütfen Giriþ Yapýnýz.." << endl;

		// Yeni kullanýcýnýn bilgilerini tekrar girmesine gerek yok
		do {
			cout << "Hoþgeldiniz Lütfen Giriþ Yapýnýz.." << endl;
			cout << "Kullanýcý Adý: ";
			cin >> kullaniciadi;
			cout << "Parola: ";
			cin >> sifre;
		} while (!kullaniciKontrol(kullaniciadi, sifre));

		cout << "Baþarýyla Giriþ Yapýldý ! " << endl << "Hoþgeldiniz " << kullaniciadi << endl;
		isLogined = true;
	}

	
	if (isLogined)
	{

		while (isLogined)
		{
			int secim;
			cout << "Lütfen yapmak istediðiniz iþlemi giriniz:\n1-Ýlaç Sorgula\n2-Ýlaç Ekle\n3-Ýlaç Sil\n4-Tüm Stoðu Listele\n5-Kullanýcý Ekle\n6-Çýkýþ" << endl;
			cin >> secim;
			switch (secim)
			{
			case 1:
				ilacSorgula();
				break;
			case 2:
				ilacEkle();
				break;
			case 3:
				ilacSil();
				break;
			case 4:
				ilaclariListele();5
				break;
			case 5:
				kullaniciEkle();
				break;
			case 6:
				break;
			default:
				cout << "Lütfen Doðru Bir Tuþlama Yapýnýz!!!";
				break;

			}
			if (secim == 6) {
				break;
			}

			if (secim == 6)
				break;


		}


	}
	else
	{
		cout << "Ýþlem Gerçekleþtirmek Ýçin Giriþ Yapýlmalýdýr.";
	}
	
	
	
	
	
	
	
	return 0;


}

