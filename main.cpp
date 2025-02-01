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

	cout << "Kay�t Olma B�l�m�ne Ho�geldiniz" << endl;
	cout << "L�tfen Kullanmak istedi�iniz Kullan�c� Ad�n� Giriniz: ";
	cin >> kullaniciAdi;

	cout << "L�tfen Kullanmak �stedi�iniz Parolay� Giriniz: ";
	cin >> kullaniciParolasi;

	usersfile.open("kullanicilar.txt", ios::out | ios::app);
	if (usersfile.is_open())
	{
		string kayitlar;
		kayitlar = kullaniciAdi + ";" + kullaniciParolasi;
		usersfile << kayitlar << endl;

		cout << "Kay�t ��lemi Ba�ar�yla Tamamland�" << endl;
		usersfile.close();
	}
	else
	{
		cout << "Dosya A��lamad�!" << endl;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void ilacEkle() {
	medsfile.open("ilaclar.txt", ios::in);

	if (medsfile.is_open()) {
		string ilacAdi;
		int ilacAdedi;
		int ilacFiyati;

		cout << "�la� Ad�n� Giriniz: " << endl;
		cin >> ilacAdi;

		// Dosyada ila� kontrol�
		string line;
		while (getline(medsfile, line)) {
			if (line.find(ilacAdi + ";") != string::npos) {
				cout << "Girdi�iniz ila� zaten mevcut. Bilgileri g�ncellemek ister misiniz? (E/H)" << endl;
				char cevap;
				cin >> cevap;

				if (cevap == 'E' || cevap == 'e') {
					// �la� bilgilerini g�ncellemek i�in e�er ayn� isimde bir ila� varsa
					

					cout << "�la� ba�ar�yla g�ncellendi." << endl;
					medsfile.close();
					return;
				}
				else {
					cout << "��lem iptal edildi." << endl;
					medsfile.close();
					return;
				}
			}
		}

		medsfile.close(); 

		cout << "L�tfen �la� Adedini Giriniz: ";
		cin >> ilacAdedi;

		cout << "L�tfen �la� Fiyat�n� Giriniz: ";
		cin >> ilacFiyati;

		medsfile.open("ilaclar.txt", ios::out | ios::app);

		string ilacAdedi_str = to_string(ilacAdedi);
		string ilacFiyati_str = to_string(ilacFiyati);
		string kayitekle = ilacAdi + ";" + ilacAdedi_str + ";" + ilacFiyati_str;

		medsfile << kayitekle << endl;
		cout << "�la� Sto�a Giriliyor..." << endl;
		medsfile.close();
		cout << "�la� Ba�ar�yla Sto�a Eklenmi�tir"<<endl;
	}
	else {
		cout << "Dosya A��lamad� !!" << endl;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void ilacSil() {
	string ilacAdi;
	cout << "L�tfen Silmek �stedi�iniz �lac�n Ad�n� Giriniz: " << endl;
	cin >> ilacAdi;
	// T�MESLEEP
	cout << "Se�ti�iniz �la� Stokta Aran�yor" << endl;
	// T�MESLEEP
	ifstream eskidosya("ilaclar.txt");
	ofstream yenidosya("temp.txt");

	if (!eskidosya.is_open() || !yenidosya.is_open()) {
		cout << "Dosya A��lamad�!" << endl;
		return;
	}

	string line;
	bool bulunduMu = false;

	while (getline(eskidosya, line)) {

		size_t foundPos = line.find(ilacAdi + ";");
		if (foundPos != string::npos && (foundPos == 0 || line[foundPos - 1] == ';')) {
			bulunduMu = true;
			cout << "Girdi�iniz �la� Stokta Bulundu"<<endl;
		}
		else {
			yenidosya << line << endl;
		}
	}

	eskidosya.close();
	yenidosya.close();

	remove("ilaclar.txt");     // Orijinal dosyay� sil
	rename("temp.txt","ilaclar.txt");  // Temp dosyas�n� orijinal dosya ad�na yeniden adland�r

	if (bulunduMu) {
		cout << "�la� ba�ar�yla silindi." << endl;
	}
	else {
		cout << "�la� bulunamad�." << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ilaclariListele()
{
	string kayitlar;

	medsfile.open("ilaclar.txt", ios::in);
	if (!medsfile.is_open()) {
		cout << "Dosya A��l�rken Bir Hata �le Kar��la��ld�.." << endl;
		return;
	}

	cout << "�la�lar Listeleniyor..." << endl;
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
		cout << "Dosya A��lamad�!" << endl;
		return false;
	}
	cout << "Kontrol Sa�lan�yor...";
	//T�MESLEEP
	string satir;
	while (getline(usersfile, satir)) {
		size_t pos = satir.find(kullaniciAdi + ";" + sifre);
		if (pos != string::npos) {
			usersfile.close();
			cout << "E�le�me Sa�land� !!" << endl;
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
	cout << "L�tfen Sorgulamak �stedi�iniz �lac�n Ad�n� Giriniz: ";
	cin >> ilacadi;

	cout << "�la� Stokta Aran�yor..."<<endl;
	cout << "**********************************************" << endl;

	medsfile.open("ilaclar.txt", ios::in);
	if (!medsfile.is_open()) {
		cout << "Dosya A��lamad�!" << endl;
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
		medsfile.close();  // Dosyay� d�ng�n�n d���nda kapat
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////7


int main()
{
	setlocale(LC_ALL, "Turkish");
	// Kullan�c� Giri�i 
	string kullaniciadi;
	string sifre;
	bool isLogined = false;
	bool isAdmin = false;
	int kontrol;

	cout << "Kullan�c� Giri�i ��in 1'i " << endl << "Kaydolmak ��in 2 Rakam�n� Giriniz: ";
	cin >> kontrol;

	if (kontrol == 1) {
		do {
			cout << "Ho�geldiniz L�tfen Giri� Yap�n�z.." << endl;
			cout << "Kullan�c� Ad�: ";
			cin >> kullaniciadi;
			//T�MESLEEP
			cout << "Parola: ";
			cin >> sifre;
			//T�MESLEEP
		} while (!kullaniciKontrol(kullaniciadi, sifre));
		cout << "Ba�ar�yla Giri� Yap�ld� ! " << endl <<"**********************************************" << endl<< "Ho�geldiniz " << kullaniciadi << endl;
		isLogined = true;
	}

	else if (kontrol == 2) {
		kullaniciEkle(); // Yeni bir kullan�c� ekler
		cout << "Ba�ar�yla Kaydoldunuz! L�tfen Giri� Yap�n�z.." << endl;

		// Yeni kullan�c�n�n bilgilerini tekrar girmesine gerek yok
		do {
			cout << "Ho�geldiniz L�tfen Giri� Yap�n�z.." << endl;
			cout << "Kullan�c� Ad�: ";
			cin >> kullaniciadi;
			cout << "Parola: ";
			cin >> sifre;
		} while (!kullaniciKontrol(kullaniciadi, sifre));

		cout << "Ba�ar�yla Giri� Yap�ld� ! " << endl << "Ho�geldiniz " << kullaniciadi << endl;
		isLogined = true;
	}

	
	if (isLogined)
	{

		while (isLogined)
		{
			int secim;
			cout << "L�tfen yapmak istedi�iniz i�lemi giriniz:\n1-�la� Sorgula\n2-�la� Ekle\n3-�la� Sil\n4-T�m Sto�u Listele\n5-Kullan�c� Ekle\n6-��k��" << endl;
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
				cout << "L�tfen Do�ru Bir Tu�lama Yap�n�z!!!";
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
		cout << "��lem Ger�ekle�tirmek ��in Giri� Yap�lmal�d�r.";
	}
	
	
	
	
	
	
	
	return 0;


}

