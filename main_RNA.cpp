#include <iostream>
#include <string>

using namespace std;
 typedef int tip;

//===sizeof int: 4 bytes

class RNA {
  public:	

    enum Nucleotide{
        T, C, G, A
    };
 /*   int *arr;
	int cursize;  //выделено байт
	int cur;  //посл нуклеотид  
	int flag;*/

//----------------
  private:
    int *arr;
	int cursize;  //выделено байт
	int cur;  //посл нуклеотид  
	int flag;   

	
    class reference {
     private:
        int pos;
		int *pt;
        

 //---------------
	 
//--------------------------	 
	    void setBit(int data){
        	int mult=3 << 2*((sizeof(int)*4)-pos-1);
   		    data= data<<2*((sizeof(int)*4)-pos-1);
   	        mult =~mult;
   	        *pt=(*pt& mult) | data;
        }
        int getBit() const{
            int sdvig = 2*((sizeof(int)*4)-pos-1);
            return ((*pt >> sdvig) & 0b00000011);
        }
     public:
        reference(int Npos, int *Npt){
            pos = Npos;
            pt = Npt;            
        }
        Nucleotide operator!() const{
            return (Nucleotide) (0b00000011 - getBit());
        }
        reference& operator=(int nucleotide){
            setBit(nucleotide);
            return *this;
        }
        reference& operator=(reference& ref){
            setBit(ref.getBit());
            return *this;
        }
        bool operator==(const reference& ref) const{
            return getBit() == ref.getBit();
        }
        operator Nucleotide() const{
            return (Nucleotide) getBit();
        }
        
    };

reference operator()(int pos) const{
       
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i,&arr[j]);
      return ref;
 }
//----------------


public:
    


//==========выделяет память массиву   
  void setm (int size) {
  	   if (!size) size=1;
       cur= size;
       size = (size/sizeof(int)/8+1)*2;
       arr = new int [size];   //в байтах, а не битах!!
       for (int i = 0; i < size; i++) { 
        arr[i] = 0;         
       }
       cursize= size;
       flag++; 
  }
  
//==============увеличение размера массива 
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
   	if (num <=0 && num >= cursize) return 0;
   	int m=0; int n =0; tip z=0;int m1 = 0; int n1 = 0;
   	m = (num/(sizeof(tip)*4));  //элемент массива
   	
  
   	n = (num%(sizeof(tip)*4)); //элементе в массиве для поиска
   	n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе массива
   	m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   
   	if (m == m1) {
   	
	   z = arr[m];
   	   z= z >> 2*(n1-n-1);
	   return z & 0b00000011;
    }
   	else{

   		z = arr[m];
    	z= z >> 2*((sizeof(tip)*4)-n-1);
    	return z & 0b00000011;}
	}
	
	

   
//============переопределение квардратных скобок================

//---------------------
 reference& operator[](int pos) {
        if ((pos / (4 * sizeof(int))) + 1 > cursize) {
            if (!flag) setm(pos+1);
			else setNewm(pos+1);

        }
        if (pos < 0) pos=0;
        if (pos > cur) cur = pos;
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i,&arr[j]);
        return ref;
    }
/*
const reference& operator[](int pos) const {
       
        
        int i= pos % (4 * sizeof(int));
        int j= pos / (4 * sizeof(int));
        reference ref(i,&arr[j]);
        return ref;
    }*/


//===========переопределение = создает копию RNA=============================
 RNA& operator =(const RNA rna) {
    arr = new int[rna.cursize];
    cur = rna.cur;
    cursize = rna.cursize;
  
    for (int i = 0; i < cursize; i++) {
       arr[i] = rna.arr[i];
    }
    return *this;
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
   		z = arr[m];
    	z= z >> 2*(n1-n);
	    arr[m]=z;
	   
    }
   	else{
    	z = arr[m];
    	z= z >> 2*((sizeof(tip)*4)-n-1);
 	    arr[m] = z;
   }
   cur = num;
}
//=============== заменяет номер на введенный==================
  
 void changeN (int num, int data ) {
   	//if (num == 0 || cur == 0) cur = 1; 
   	if (num > cur) cur=num;
   	int mult; 
   	int m = (num/(sizeof(tip)*4));
   	int n = (num%(sizeof(tip)*4));
   	int n1 = (cur%(sizeof(tip)*4)); //колво нуклидов в последненм элементе
   	int m1 = (cur/(sizeof(tip)*4));//последний элемент массива
   	int w = arr[m];
   
   
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
	flag=0;
	setm(size);

}


RNA() {
 
  cursize = 0;
  cur = 0;
  flag = 0;

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



//--------------------

//-----------------
};   
   
   
int main(int argc, char** argv) {
	int i=0;
	int n=3;
	int ch;
	int c;
	RNA BB;
//	cout << " Dlina chepochki: ";
//	cin >> n;
//	BB.setm (n );
//	 cout << "cepochka: " ;
	 //c = BB.arr[0];
	// cout << c ;
    int z = n;
	for (i =0; i < n; i++) {
	
	   cout << i+1 << " ) ";
	   cin >> ch;
	   BB[i]= ch;
	   cout << " BB[i]- " << BB[i];
	   
       }

 /*    z=BB.cur;
    while (z>=0){
    	z--;
    	
    	cout << " nomer: ";
	    cin >> z;
	
	
	 c=   BB[z]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	
    }
	
	*/
	 
/*     cout << " change nomer: ";
	 cin >> i;
	 cout << " change on: ";
	 cin >> ch;*/
	
/*	 cout << " change s nomer: ";
	 cin >> i;
	 cout << " change on value: ";
	 cin >> c;
	  BB.changeN(i, c);*/
//	  CC=BB;
//	  cout << " massiv2 " << CC.arr[0];
      int hh;
	//  cout << " del with nomer: ";
	  
//	   cin >> hh;
	  
	  
	//  CC+=BB;
	 // cout << " massiv3 " << CC.arr[0];
//        BB.delp(3);
  /*       while (z >=0){
    	
    	
    		
	
	 c=   BB[z]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	z--;
    }*/
        //BB+=CC;
 /*   z=0;

    while (z <=n){
    	
    	
    		
	
	 c=   BB[z]; //BB.getn(i);
	  cout << " find  " << c;
    	
    	z++;
    }*/
    
/*	if (BB!=CC) hh=1;
    cout << " eq " <<  hh;
        */
//	 cout << " res: ";
	// int ccc = BB[2];
//	 cout << "res del" << BB.arr[0];
	// cout << "  EHU " << BB[i];
	
	return 0;
}
