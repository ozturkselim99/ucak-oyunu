/*********************************************************************************************************************************************************************************
**                                       SAKARYA ÜNİVERSİTESİ BİLGİSAYAR VE BİLİŞİM BİLİMLERİ FAKÜLTESİ
**                                                       BİLGİSAYAR MÜHENDİSLİĞİ BÖLÜMÜ
**                                                          PROGLAMLAMAYA GİRİŞ DERSİ
**
**                                             PROJE ÖDEVİ
**                                             ÖĞRENCİ ADI:AHMET SELİM ÖZTÜRK
**                                             ÖĞRENCİ NUMARASI:G181210082
**                                             DERS GRUBU:A
***********************************************************************************************************************************************************************************/
#include "pch.h"
#include <iostream>
#include<Windows.h>
#include <time.h> 

using namespace std;

const int boy = 20;
const int en = 80;
int düşman_sayac = 0;
int mermi_sayısı = 0;
char sahne[en][boy];
char tuşlar[256];
struct mermi_bilgileri
{
	int x;
	int y;
	char mermi_tipi = 196;
};
struct düşman_bilgileri
{
	int x;
	int y;
	char düşman_tipi = 178;
};

struct uçak_bilgileri
{
	int part1x;
	int part1y;
	int part2x;
	int part2y;
	int part3x;
	int part3y;
	int part4x;
	int part4y;
	int part5x;
	int part5y;

	char part1;
	char part2;
	char part3;
	char part4;
	char part5;

};

uçak_bilgileri uçak;
düşman_bilgileri düşman[500];
mermi_bilgileri mermi[500];
void düşmanoluştur()
{
	srand(time(NULL));
	int l = rand() % 10 +80;
	int f = rand() % 12 + 2;
	düşman[düşman_sayac].x = l;
	düşman[düşman_sayac].y = f;
	düşman_sayac++;
}

void düşmanı_sahneyeyerleştir()
{
	//Rastgele oluşturulan düşmanları oluşturulan düşman sayısına göre sahneye yerleştiriyoruz.
	for (int i = 0; i < düşman_sayac; i++)
	{
		int x = düşman[i].x;
		int y = düşman[i].y;

		sahne[x][y] = düşman[i].düşman_tipi;
	}

}
void düşmanıhareketettir()
{
	//Rastgele oluşturulan düşmanları x ekseni boyunca hareket ettiriyoruz.
	for (int i = 0; i < düşman_sayac; i++)
	{
		//düşmanın x değerinin sınırlarımız içerisinde azalmasını sağlıyoruz.90 dememmizim sebepi rastgele oluşturulan bir düşmanın x değerinin en fazla 90 olması.
		if (düşman[i].x > 0 && düşman[i].x < 90)
		{
			düşman[i].x--;
			//düşmanın x değeri 70'e geldiğinde yeniden düşman oluşturuyoruz. 
			if (düşman[i].x == 55)
			{
				düşmanoluştur();
			}
		}

	}

}

void uçakoluştur()
{
	uçak.part1x = 1;
	uçak.part1y = 9;
	uçak.part2x = 2;
	uçak.part2y = 10;
	uçak.part3x = 3;
	uçak.part3y = 11;
	uçak.part4x = 2;
	uçak.part4y = 12;
	uçak.part5x = 1;
	uçak.part5y = 13;
	uçak.part1 = 219;
	uçak.part2 = 219;
	uçak.part3 = 219;
	uçak.part4 = 219;
	uçak.part5 = 219;
}
void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
	{
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8);
	}
	
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void sahneyiCiz()
{
	//sahnemizin en ve boyunu belirleyip çiziyoruz.
	for (int y = 0; y < boy; y++)
	{
		for (int x = 0; x < en; x++)
		{
			cout << sahne[x][y];
		}

		cout << endl;
	}
}
void sahneyiTemizle()
{
	//sahnemizi temizliyoruz.
	for (int y = 0; y < boy; y++)
	{
		for (int x = 0; x < en; x++)
		{
			sahne[x][y] = ' ';
		}
	}
}
void sinirlariOlustur()
{
	//sahnemizin üst ve alt sınırlarını oluşturuyoruz.
	for (int x = 0; x < en; x++)
	{
		sahne[x][0] = 219;
		sahne[x][boy - 1] = 219;
	}
	//sahnemizin sağ ve sol sınırlarını oluşturuyoruz.
	for (int y = 0; y < boy; y++)
	{
		sahne[0][y] = 219;
		sahne[en - 1][y] = 219;
	}
}

void mermioluştur()
{

	mermi[mermi_sayısı].x = uçak.part3x + 1;
	mermi[mermi_sayısı].y = uçak.part3y;
	mermi_sayısı++;

}
void mermiyi_sahneyeyerleştir() {
	//Oluşan mermileri mermi sayısına göre sahneye yerleştiriyoruz.
	for (int i = 0; i < mermi_sayısı; i++)
	{
		int x = mermi[i].x;
		int y = mermi[i].y;

		sahne[x][y] = mermi[i].mermi_tipi;
	}

}

void mermiyi_hareketettir() {

	//Oluşan mermileri x ekseni boyunca hareket ettiriyoruz.
	for (int i = 0; i < mermi_sayısı; i++)
	{
		//mermin x değeri 80'den küçükse merminin x değerini arttıyoruz.Bunuda merminin sahneden çıktıktan sonra programın hata vermesini önlemek için yapıyoruz.
		if (mermi[i].x < 80)
		{
			mermi[i].x++;
		}
	

	}

}

void klavyeKontrol()
{
	klavyeOku(tuşlar);
	// 'W' bastığımızda uçağın her bir parçasının y değerini 1 azaltıyoruz.
	if (tuşlar['W'] != 0)
	{
		//Uçağın 1.parçasının y değerinin 1 den büyük olduğu durumlarda uçağın y değerini azaltıyoruz.Çünkü uçağımızın yukarı hareketini 1.parça sınırlıyor.
		if (uçak.part1y > 1)
		{
			uçak.part1y--;
			uçak.part2y--;
			uçak.part3y--;
			uçak.part4y--;
			uçak.part5y--;
		}

	}
	// 'S' bastığımızda uçağın her bir parçasının y değerini 1 arttırıyoruz.
	if (tuşlar['S'] != 0)
	{
		//Uçağın 5.parçasının y değerinin 18 den küçük olduğu durumlarda uçağın y değerini arttırıyoruz.Çünkü uçağımızın aşağı hareketini 5.parça sınırlıyor.
		if (uçak.part5y < 18)
		{
			uçak.part1y++;
			uçak.part2y++;
			uçak.part3y++;
			uçak.part4y++;
			uçak.part5y++;

		}
	}
	// 'C' bastığımızda mermi oluşturuyoruz.
	if (tuşlar['C'] != 0)
	{

		mermioluştur();


	}


}
void UçağıSahneyeYerlestir() {
	int part1x = uçak.part1x;
	int part1y = uçak.part1y;

	sahne[part1x][part1y] = uçak.part1;

	int part2x = uçak.part2x;
	int part2y = uçak.part2y;

	sahne[part2x][part2y] = uçak.part2;

	int part3x = uçak.part3x;
	int part3y = uçak.part3y;

	sahne[part3x][part3y] = uçak.part3;

	int part4x = uçak.part4x;
	int part4y = uçak.part4y;

	sahne[part4x][part4y] = uçak.part4;

	int part5x = uçak.part5x;
	int part5y = uçak.part5y;

	sahne[part5x][part5y] = uçak.part5;

}
void etkileşim() {
	//Oluşan düşman sayısı ve mermi sayısına kadar döndüren iki for döngüsü yazıyoruz.(Kontrol için)
	for (int i = 0; i < mermi_sayısı; i++)
	{
		for (int j = 0; j < düşman_sayac; j++)
		{
			//düşmanın x değerinin merminin x değerine eşit olduğu durumlarda ve merminin y değerinin düşmanın y değerine eşit olduğu durumlarda düşman ve mermiyi sahnenin dışına yolluyoruz.
			if (düşman[j].x == mermi[i].x && mermi[i].y == düşman[j].y)
			{
			
				mermi[i].x = 150;
				mermi[i].y = 150;
				düşman[j].x = 150;
				düşman[j].x = 150;
				
			}
		}
	}

}

int main()
{
	kursoruGizle();
	uçakoluştur();
	düşmanoluştur();

	while (true)
	{
		sahneyiTemizle();
		klavyeKontrol();
		UçağıSahneyeYerlestir();
		düşmanı_sahneyeyerleştir();
		düşmanıhareketettir();
		mermiyi_sahneyeyerleştir();
		mermiyi_hareketettir();
		etkileşim();
		sinirlariOlustur();
		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(1);

	}
}

