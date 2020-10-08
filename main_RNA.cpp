#include <iostream>
#include <string>
#include <bitset>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 enum NUKL {A, G, C , T};
 typedef unsigned int tip;

class RNA {
  public:	
	tip *arr;
	int cur=0;  //кол-во нуклидов обработано
	int curN=0; // позиция в слове
	tip curw=0;  // текущее слово, заполняетмя, по заполнению переносится в массив и обнуляется
	int curpos=0;  //номер элемента массива arr
  
   void findN (int data) {
   	while (data > 0)
  	curw=curw>>2;
  	curw=curw|data;
  	cur++;
   }
  
 //============добавляет очередное значение в слово, которое позже перенесется при достижении полного размера 
   void construct (int data1) {
  	curw=curw<<2;
  	curw=curw|data1;
  	cur++;
   }

//==========выделяет память массиву   
  void setm (int size) {
  	size=size*2;
   arr = new tip [size];
    for (int i = 0; i < size; i++) {
        
        arr[i] = 0;
          
    }
  }
//==============  вызов заполения слова данными или перенос из слова в элемент массива данных
  void readb (int data, int size) {
  curN++;
  
  if (curN > (sizeof(tip)*4)-1 || (cur==size-1))  {
  		construct (data);
   		curN=0;
   		
   		arr[curpos]=curw;
   	//	cout << " arr  ";
     //   cout << arr[curpos];
     //   cout << " curpos  ";
     //   cout << curpos;
   		curpos++;
   		curw =0;
   	
   	}
   	else
	   construct (data);

  }
 
 //===========получить   элемент  из массива 
   tip getn (int num) {
   	int m=0; int n =0; tip z=0;int m1 = 0; int n1 = 0;
   	m = (num/(sizeof(tip)*4));  //элемент массива
   	
  // 	cout << " m " << m;
   	n = (num%(sizeof(tip)*4)); //элементе в массиве для поиска
   	n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе массива
   	m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   	if (n1==0) m1= m1-1;  //деление целочисленное, то работа в текущ байте
   	if (n==0) m= m-1;
 /*  	cout << " n "<< n;
   	cout << " n1 "<< n1;
   	cout << " m "<< m;
   cout << " m1 "<< m1;*/
   
   	if (m == m1) {
   	//cout << " !! ";
	   z = arr[m];
   	 //  cout << " z " << z;
	 //  cout << " sdvig " << 2*(n1-n);
    	z= z >> 2*(n1-n);
	  // tip k= z&3;
	 //  cout << " ono " << z ;
	   return z & 0b00000011;
    }
   	else{
   	
   		cout << " n " << n;
   		z = arr[m];
    //	cout << " z " << z;
    //	cout << " sdvig " << 2*(16-n);
    	z= z >> 2*(16-n);
	//	cout << " ono " << z ;
    	return z & 0b00000011;}
	}
   
//========удаляет хвост с номера=============
   void delp (int num ) {
   int m=0; int n =0; tip z=0;int m1 = 0; int n1 = 0;
  	m = (num/(sizeof(tip)*4));  //элемент массива
   	n = (num%(sizeof(tip)*4)); //сдвиг в элементе
   	n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе
   	m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   	
   if (n1==0) m1= m1-1;  //деление целочисленное, то работа в текущ байте
   	if (n==0) m= m-1;
   	if (m==m1) {
   	cout << " !!m " << m;
   		 z = arr[m];
   	   cout << " z " << z;
	   cout << " sdvig " << 2*(n1-n);
    	z= z >> 2*(n1-n);
	    arr[m]=z;
	   
    }
   	else{
   	
   		cout << " m " << m;
		//cout << " n " << n;
    	z = arr[m];
     	cout << " z " << z;
    	cout << " sdvig " << 2*(16-n);
    	z= z >> 2*(16-n);
 	    arr[m] = z;
   }
   cout << " arr res " << arr[m];
}
//=============== заменяет номер на введенный==================
  
   void changeN (int num, int data ) {
   	tip mult;
   	int m = (num/(sizeof(tip)*4));
   	int n = (num%(sizeof(tip)*4));
   	int n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе
   	int m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   	tip w = arr[m];
   	if (m==m1) {
   
   	   mult=3 << 2*(n1-n);
   	   
   	   data= data<<2*(n1-n);
      }
	else {
	
   		mult=3 << 2*(16-n);
   		data= data<<2*(16-n);
      }
  // 	cout << " mult " << mult;
   	mult =~mult;
   //	cout << " anti mult " << mult;
   	w=w& mult;
  // 	cout << " mult&w " << w;
   	w=w|data;
   //	cout << " w|data " << w;
   	arr[m]=w;
   	cout << " arr res " << arr[m];
    }
};
   
//============ ОСВОБОЖДЕНИЕ ПАМЯТИ   
   
   
   
   
int main(int argc, char** argv) {
	int i=0;
	int n;
	int ch;
	tip c;
	RNA BB;
	
	cout << "Dlina chepochki: ";
	cin >> n;
	BB.setm(n);
	 cout << "cepochka: " ;
	 c = BB.arr[0];
	 cout << c ;
	for (i =0; i < n; i++) {
	
	   cout << i+1 << " ) ";
	   cin >> ch;
	   BB.readb(ch, n);
	 //  cout << "slovo " << BB.curw;
	   
       }
       /* c = BB.arr[0];
        cout << "resultat " ;
	    cout << c ;*/
        cout << "massiv " << BB.arr[0];
 /*    cout << "nomer: ";
	 cin >> i;*/
	// c= BB.getn(i);
/*	cout << " find  " << c;
     cout << " change nomer: ";
	 cin >> i;
	 cout << " change on: ";
	 cin >> ch;*/
	 BB.changeN(i, ch);
	 cout << " del s nomer: ";
	 cin >> i;
	 BB.delp(i);
	
	return 0;
}
