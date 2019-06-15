#include <iostream>
#include <cstdlib>
#include <fstream>
#include <conio.h>
using namespace std;
struct g{
	char griglia[9][9];
	bool occupato[9][9];
};
g gr[100];
int selezione;
//stampa la griglia del sudoku
void visualizza (int sel){
	system("CLS");
	int j=-1, k=0;
	cout<<endl<<"      ---------------------";
	cout<<endl<<"    |";
	for (int i=0; i<9; i++){
		for (int z=0; z<9; z++){
			j++;
			if (j==3){
				cout<<" |";
				j=0;
			}
			cout<<" "<<gr[sel].griglia[i][z];
		}
		cout<<" |";
		k++;
		if (k==3){
			cout<<endl<<"      ---------------------";
			k=0;
		}
		cout<<endl<<"   ";
	}
}

void carica(){
	char stringa[100];
	ifstream file;
	int tmp=0;
	file.open("Easy.map");
	for (int p=0; p<100; p++){
		file>>stringa;
		tmp=0;
		for (int z=0; z<9; z++){
			for (int i=0; i<9; i++){
				if (stringa[tmp]!='0'){
				gr[p].griglia[i][z]=stringa[tmp];
				gr[p].occupato[i][z]=true;
				}
				else{
				gr[p].griglia[i][z]=0;
				gr[p].occupato[i][z]=false;
				}
				tmp++;
			}
		}
	}
	file.close();
}

void sceltalivello (){
	carica();
	bool conf=false;
	int sel=0;
	int ch;
	do{
		visualizza(sel);
		cout<<endl<<"  LEVEL > "<<sel+1<<endl<<endl<<"  Choose the level with A/D then press ENTER"<<endl<<endl;;
		ch=getch();
		switch (ch){
			case (97): //a
				if (sel>0){ sel--; }
				break;
			case (100): //d
				if (sel<99){ sel++; }
				break;
			case (13): //conf
				conf=true;
				break;
		}
	}
	while (conf==false);
	selezione=sel;
}

// true quando ci sono - false quando non
bool controllotutti(int c[9]){
	int m=1, n=0, cont=0, t=0;
	while (m<9){
    if (c[n]>c[m]) { //Cambiare condizione per ivertire l'ordine
    t=c[n];
    c[n]=c[m];
    c[m]=t;
    t=0;
    n=0;
    m=1;}
    else {
    m++;;
    n++;;}
	}
    for (int i=0; i<9; i++){
    	if (c[i+1]==c[i]+1){
    		cont++;
    	}
    }
    if (cont==8){
    	return true;
    }
    else{
    	return false;
    }
}
// true quando non è piena - false quando è piena
bool controllopieni(){
	for (int i=0; i<9; i++){
		for (int z=0; z<9; z++){
			if (gr[selezione].griglia[i][z]==0 || gr[selezione].griglia[i][z]=='#'){
				return true;
			}
		}
	}
	return false;
}
// true quando no - false quando è si
bool controllocolonne(){
	int ctrl[9];
	int cont=0;
	for (int z=0; z<9; z++){
		for (int i=0; i<9; i++){
			ctrl[i]=gr[selezione].griglia[i][z];
		}
		if (controllotutti(ctrl)==true){
			cont++;
		}
	}
	if(cont==9){
		return false;
	}
	else{
		return true;
	}
}
// true quando no - false quando è si
bool controllorighe(){
	int ctrl[9];
	int cont=0;
	for (int i=0; i<9; i++){
		for (int z=0; z<9; z++){
			ctrl[z]=gr[selezione].griglia[i][z];
		}
		if (controllotutti(ctrl)==true){
			cont++;
		}
	}
	if(cont==9){
		return false;
	}
	else{
		return true;
	}
}
// true quando hai vinto - false quando non vinto
bool controllovincita(){
	if (controllopieni()==false){
		if (controllocolonne()==false){
			if (controllorighe()==false){
					return true;
			}
		}
	}
	return false;
}

int ux[100], uy[100], o=0;;
void mossa(){
	char c;
	int selini=0;
	char symbini;
	int selx=0, sely=0;
	bool moss=true;
	bool tmp=true;
	for (int i=0; i<9 && moss==true; i++){
		for(int z=0; z<9 && moss==true; z++){
			if (gr[selezione].occupato[i][z]==false){
				selx=z;
				sely=i;
				gr[selezione].griglia[i][z]=176;
				moss=false;
			}
		}
	}
	do{
		c=getch();
		switch (c){
			case ('w'):
				selini=sely;
				if (sely>0){
					sely--;
					while (gr[selezione].occupato[sely][selx]==true){
						sely--;
						if (sely==-1){
						sely=selini; 
						break; 
						}
					}
				}
				gr[selezione].griglia[selini][selx]=0;
				gr[selezione].griglia[sely][selx]=176;
				break;
			case ('s'):
				selini=sely;
				if (sely<8){
					sely++;
					while (gr[selezione].occupato[sely][selx]==true){
						sely++;
						if (sely==9){
						sely=selini; 
						break; 
						}
					}
				}
				gr[selezione].griglia[selini][selx]=0;
				gr[selezione].griglia[sely][selx]=176;
				break;
			case ('d'):
				selini=selx;
				if (selx<8){
					selx++;
					while (gr[selezione].occupato[sely][selx]==true){
						selx++;
						if (selx==9){
						selx=selini; 
						break; 
						}
					}
				}
				gr[selezione].griglia[sely][selini]=0;
				gr[selezione].griglia[sely][selx]=176;
				break;
			case ('a'):
				selini=selx;
				if (selx>0){
					selx--;
					while (gr[selezione].occupato[sely][selx]==true){
						selx--;
						if (selx==-1){
						selx=selini; 
						break; 
						}
					}
				}
				gr[selezione].griglia[sely][selini]=0;
				gr[selezione].griglia[sely][selx]=176;
				break;
			case ('1'):
				gr[selezione].griglia[sely][selx]='1';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('2'):
				gr[selezione].griglia[sely][selx]='2';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('3'):
				gr[selezione].griglia[sely][selx]='3';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('4'):
				gr[selezione].griglia[sely][selx]='4';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('5'):
				gr[selezione].griglia[sely][selx]='5';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('6'):
				gr[selezione].griglia[sely][selx]='6';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('7'):
				gr[selezione].griglia[sely][selx]='7';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				moss=true;
				tmp=true;
				break;
			case ('8'):
				gr[selezione].griglia[sely][selx]='8';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				tmp=true;
				moss=true;
				break;
			case ('9'):
				gr[selezione].griglia[sely][selx]='9';
				gr[selezione].occupato[sely][selx]=true;
				ux[o]=selx;
				uy[o]=sely;
				o++;
				for (int i=0; i<9 && tmp==true; i++){
					for(int z=0; z<9 && tmp==true; z++){
						if (gr[selezione].occupato[i][z]==false){
							selx=z;
							sely=i;
							gr[selezione].griglia[i][z]=176;
							tmp=false;
						}
					}
				}
				tmp=true;
				moss=true;
				break;
			case ('r'):
				if(o!=0){
				gr[selezione].griglia[uy[o-1]][ux[o-1]]=0;
				gr[selezione].occupato[uy[o-1]][ux[o-1]]=false;
				o--;}
				break;
		}
	visualizza(selezione);
	cout<<endl<<"  Move with WASD in the box and insert a number"<<endl<<endl<<"  Press r to undo a move"<<endl<<endl;;
	}
	while (moss==false);
}


int main() {
	sceltalivello();
	visualizza(selezione);
	cout<<endl<<"  Move with WASD in the box and insert a number"<<endl<<endl<<"  Press r to undo a move"<<endl<<endl;
	while (controllovincita()==false){
	mossa();
	}
	cout<<"   CONGRATULATION !!!"<<endl<<endl;
	system("PAUSE");
	return 0;
}

