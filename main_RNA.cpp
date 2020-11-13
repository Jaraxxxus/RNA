#include <iostream>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
 typedef int tip;

//===sizeof int: 4 bytes

class RNA {
  public:	
    int flag=0;
	int *arr;
	int cur;  //кол-во нуклидов обработано
//	int curN=0; // позиция в слове
//	tip curw=0;  // текущее слово, заполняетмя, по заполнению переносится в массив и обнуляется
	int cursize=0;  //выделено байт
	
    enum Nucleotide{
        T, C, G, A
    };






//==========выделяет память массиву   
  void setm (int size) {
   cur= size;
   size = (size/sizeof(int)/8+1)*2;
   cout << "size our arr " << size;
   cout << " " ;
   arr = new int [size];   //в байтах, а не битах!!
    for (int i = 0; i < size; i++) {
        
        arr[i] = 0;
          
    }
    cursize= size;
     flag++; 
  }
  
//==============увеличение размера массива в 2 раза
  void setNewm(int newsize){
        //int oldsize=size;
		cur = newsize;  	
  	    newsize = (newsize/sizeof(int)/8+1)*2;
        int *new_array = new int[newsize];
        for (int i = 0; i < cursize; i++) {
            new_array[i] = arr[i];
        }
        for (int i = cursize; i < newsize; i++) {
            new_array[i] = 0;
        }
        delete arr;
        arr = new_array;
        cursize= newsize;
        flag++;
    
		  
		  
}
		  


 //===========получить   элемент  из массива 
   tip getn (int num) {
   	int m=0; int n =0; tip z=0;int m1 = 0; int n1 = 0;
   	m = (num/(sizeof(tip)*4));  //элемент массива
   	
  
   	n = (num%(sizeof(tip)*4)); //элементе в массиве для поиска
   	n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе массива
   	m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   	//if (n1==0) m1= m1-1;  //деление целочисленное, то работа в текущ байте
   //	if (n==0) m= m-1;
 
   
   	if (m == m1) {
   	
	   z = arr[m];
   	   z= z >> 2*(n1-n-1);
	   return z & 0b00000011;
    }
   	else{
   	
   	//	cout << " n " << n;
   		z = arr[m];
    	z= z >> 2*((sizeof(tip)*4)-n-1);
    	return z & 0b00000011;}
	}
	
	

   
//============переопределение квардратных скобок================

int operator [] (int pos) {
if (cursize==0)
{
	 setm(pos);
	 cur=pos;
	 return 0;
}
else {

   if (pos > cur) pos = cur;
   return getn(pos);
}

};



//===========переопределение = создает копию RNA=============================
 RNA& operator=(const RNA rna) {
  delete arr;
 
  arr = new tip[rna.cur];
  cur = rna.cur;
  cursize = rna.cursize;
  
  for (int i = 0; i < cursize; i++) {
     arr[i] = rna.arr[i];
  }
 return *this;
 }

//=============

//===============



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
    	z = arr[m];
     	cout << " z " << z;
    	cout << " sdvig " << 2*((sizeof(tip)*4)-n-1);
    	z= z >> 2*((sizeof(tip)*4)-n-1);
 	    arr[m] = z;
   }
   cout << " arr res " << arr[m];
   cur = num;
}
//=============== заменяет номер на введенный==================
  
   void changeN (int num, int data ) {
   	//if (num == 0 || cur == 0) cur = 1; 
   	if (num > cur) cur=num;
   	tip mult; 
   	int m = (num/(sizeof(tip)*4));
   	int n = (num%(sizeof(tip)*4));
   	int n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе
   	int m1 = (cur/(sizeof(tip)*4));//последний элемент массива
 /*  	cout << " m-" << m;
   	cout << " n-" << n;
   	cout << " nl-" << n1;
   	cout << " ml-" << m1;
   	cout << "" ;
   	*/
   	tip w = arr[m];
  // 	cout << " word-" << w;
  // 	cout << "" ;*/
   
   
    if (m ==m1) {
   
   	   mult=3 << 2*(n1-n-1);
   	   
   	   data= data<<2*(n1-n-1);
   	   cout << "!! " << data; ;
      }
	else {
	
   		mult=3 << 2*((sizeof(tip)*4)-n-1);
   		data= data<<2*((sizeof(tip)*4)-n-1);
      }
   	mult =~mult;
   	w=w& mult;
   	w=w|data;
   	arr[m]=w;
   //	cout << " res!!- " << arr[m];
   	
    }

//===========
bool operator==(const RNA rna) const{
	if (cur != rna.cur) return false; 
        for (int i = 0; i < cursize; i++) {
            if (arr[i] != rna.arr[i]) return false;
        }
        return true;
}
bool operator!=(const RNA rna) const{
	if (cur != rna.cur) return true; 
        for (int i = 0; i < cursize; i++) {
            if (arr[i] != rna.arr[i]) return true;
        }
        return false;
}

RNA (int size) {
	setm(size);
	cur=size;
}
RNA (RNA&);


//=====================Здесь  после реализации квадр скобки изменения элемента, пока не работает. 
 RNA& operator+=(RNA rna){
        int a;
		int tmp = cur, data;
        int newcur = tmp+rna.cur;
        if (cursize < newcur){
        	setNewm(newcur);

		}
		
        for (int i = 0; i < rna.cur; i++){
        	a = rna.getn(i);
        	changeN(tmp+i, a);
        }
        cur=newcur;
 return *this;
 }



~RNA(){
	delete arr;	
}

};



   
   
   
   
int main(int argc, char** argv) {
	int i=0;
	int n;
	int ch;
	tip c;
	RNA BB(10), CC(10);
	cout << " Dlina chepochki: ";
	cin >> n;
//	BB.setm (n );
	 cout << "cepochka: " ;
	 c = BB.arr[0];
	 cout << c ;
	 int z = n;
	for (i =0; i < n; i++) {
	
	   cout << i+1 << " ) ";
	   cin >> ch;
	  // BB.readb(ch, n);
	   BB.changeN(i, ch);
	  /* cout << " slovo " << BB.arr[0];
	   	cout << " nomer: ";
	    cin >> i;
	*/
	
	  //  c=   BB[i]; //BB.getn(i);
	  //  cout << " find  " << c << " ";
	   
       }
       /* c = BB.arr[0];
        cout << "resultat " ;
	    cout << c ;*/
     //   cout << " massiv " << BB.arr[0];
   /* while (n>0){
    	n--;
    	
    	cout << " nomer: ";
	    cin >> i;
	
	
	 c=   BB[i]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	
    }*/
	
	
	 
/*     cout << " change nomer: ";
	 cin >> i;
	 cout << " change on: ";
	 cin >> ch;*/
	
/*	 cout << " change s nomer: ";
	 cin >> i;
	 cout << " change on value: ";
	 cin >> c;
	  BB.changeN(i, c);*/
	  CC=BB;
//	  cout << " massiv2 " << CC.arr[0];
      int hh;
	//  cout << " del with nomer: ";
	  
//	   cin >> hh;
	  
	  
	//  CC+=BB;
	 // cout << " massiv3 " << CC.arr[0];
        BB.delp(3);
  /*       while (z >=0){
    	
    	
    		
	
	 c=   BB[z]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	z--;
    }*/
    z=0;
    //BB+=CC;
    while (z <=10){
    	
    	
    		
	
	 c=   BB[z]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	z++;
    }
    
/*	if (BB!=CC) hh=1;
    cout << " eq " <<  hh;
        */
//	 cout << " res: ";
	// int ccc = BB[2];
//	 cout << "res del" << BB.arr[0];
	// cout << "  EHU " << BB[i];
	
	return 0;
}
