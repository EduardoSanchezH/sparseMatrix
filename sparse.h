#ifndef SPARSE
#define SPARSE

#include <iostream>
using namespace std;

int min(int a, int b){
	if(a<b) return a;
	return b;
}

int ma=0;
//template<class T>
class node
{
private:
	int value;
	int col;
	int row;
	node* d;
	node* l;
	friend class sparse;
public:
	node(){
		value=ma;
		col=0;
		row=0;
		ma++;
	}
	node(int f,int c, int v){
		row=f;
		col=c;
		value=v;
	}
	void print(){
		cout<<row<<" "<<col<<" "<<value<<endl;
	}
	bool operator==(const node& a) const{
		return (this->row==a.row && this->col==a.col && this->value==a.value);
	}

	~node(){
		//delete d;
		d=NULL;
		//delete l;
		l=NULL;
	}
};

//template<class T>
class sparse
{
private:
	node* head;
	int row;
	int col;
public:
	sparse(int f, int c){
		row=f;
		col=c;
		head = new node(0,0,0);
		node* aux;
		node* taux=head;
		for (int i = 0; i < c; ++i)
		{
			aux=new node(0,i+1,0);
			aux->d=NULL;
			taux->l=aux;
			taux=aux;
		}
		taux=head;
		for (int i = 0; i < f; ++i)
		{
			aux=new node(i+1,0,0);
			aux->l=NULL;
			taux->d=aux;
			taux=aux;	
		}
	}

	void prue(){
		node* aux=head;
		for (int i = 0; i < col+1; ++i)
		{
			aux->print();
			aux=aux->l;
		}
		cout<<endl;
		aux=head;
		for (int i = 0; i < row+1; ++i)
		{
			aux->print();
			aux=aux->d;
		}
		cout<<endl;
	}

	void put(int f, int c, const int& v){
		if(f>row || c>col){
			cout<<"Ingrese posicion correcta"<<endl;
			return;
		}
		node* nuevo=new node(f,c,v);
		node* faux=head;
		node* caux=head;
		for (int i = 0; i < f; ++i)
		{
			faux=faux->d;
		}
		//cout<<faux->value<<" ";
		for (int i = 0; i < c; ++i)
		{
			caux=caux->l;
		}
		//cout<<caux->value<<endl;
		while(faux->l!=NULL){
			if(faux->l->col>c) break;
			faux=faux->l;
		}
		nuevo->l=faux->l;
		faux->l=nuevo;

		while(caux->d!=NULL){
			if(caux->d->row>f) break;
			caux=caux->d;
		}
		nuevo->d=caux->d;
		caux->d=nuevo;
	}

	void print(){
		node* daux=head;
		node* aux;
		daux=daux->d;
		while(daux!=NULL){
			aux=daux;
			aux=aux->l;
			while(aux!=NULL){
				aux->print();
				aux=aux->l;
			}
			daux=daux->d;
		}
		cout<<endl;
	}

	void make_zero(int f, int c){
		if(f>row || c>col){
			cout<<"Ingrese posicion correcta"<<endl;
			return;
		}
		node* aux=head;
		for (int i = 0; i < f; ++i)
		{
			aux=aux->d;
		}
		node* taux=aux;
		while(aux!=NULL && aux->col < c){
			taux=aux;
			aux=aux->l;
		}
		if(aux!=NULL && aux->col==c){
			taux->l=aux->l;
			delete aux;
		}
		cout<<"Fila "<<f<<" Columna "<<c<<" borrado"<<endl;
	}

	void resize(int f, int c){
		node* aux=head;
		node* n;
		node* taux;
		if(f>row){
			for (int i = 0; i < row; ++i)
			{
				aux=aux->d;
			}
			for (int i = 0; i < f-row; ++i)
			{
				n=new node(i+1+row,0,0);
				aux->d=n;
				aux=n;
			}
		}
		else if(f<row){
			n=head;
			for (int i = 0; i < col; ++i)
			{
				aux=n;
				while(aux->d!=NULL && aux->d->row <= f){
					aux=aux->d;
					//aux->print();
				}
				taux=aux->d;
				aux->d=NULL;
				delete taux;
				n=n->l;
			}
		}
		aux=head;
		if(c>col){
			for (int i = 0; i < col; ++i)
			{
				aux=aux->l;
			}
			for (int i = 0; i < c-col; ++i)
			{
				n=new node(0,i+1+col,0);
				aux->l=n;
				aux=n;
			}
		}
		else if(c<col){
			n=head;
			for (int i = 0; i < row; ++i)
			{
				aux=n;
				while(aux->l!=NULL && aux->l->col <= c){
					aux=aux->l;
					//aux->print();
				}
				taux=aux->l;
				aux->l=NULL;
				delete taux;
				n=n->d;
			}
		}
		this->row=f;
		this->col=c;
	}

	bool is_zero(int f, int c)const{
		if(f>row || c>col){
			cout<<"Ingrese posicion correcta"<<endl;
			return true;
		}
		node* aux=head;
		for (int i = 0; i < f; ++i)
		{
			aux=aux->d;
		}
		while(aux->l!=NULL && aux->l->col <= c){
			aux=aux->l;
		}
		return aux->col != c;
	}

	int get(int f, int c)const{
		if(f>row || c>col){
			cout<<"Ingrese posicion correcta"<<endl;
			return 0;
		}
		node* aux=head;
		for (int i = 0; i < f; ++i)
		{
			aux=aux->d;
		}
		while(aux->l!=NULL && aux->l->col <= c){
			aux=aux->l;
		}
		if(aux->col == c) return aux->value;
		return 0;
	}

	int num_rows()const{return row;}
	int num_cols()const{return col;}

	sparse operator+(const sparse& rhs) const{
		if(row == rhs.num_rows() && col == rhs.num_cols()){
			sparse r(row,col);
			for (int i = 1; i <= row; ++i)
			{
				for (int j = 1; j <= col; ++j)
				{
					if(this->is_zero(i,j)==0 || rhs.is_zero(i,j)==0){
						r.put(i,j,this->get(i,j)+rhs.get(i,j));
					}
				}
			}
			return r;
		}
		cerr<<"No se puede sumar"<<endl;
	}

	bool operator==(const sparse& rhs) const{
		node* daux=head;
		node* aux;
		daux=daux->d;

		node* daux2=rhs.head;
		node* aux2;
		daux2=daux2->d;
		while(daux!=NULL && daux2!=NULL){
			aux=daux;

			aux2=daux2;
			while(aux!=NULL && aux2!=NULL){
				aux=aux->l;

				aux2=aux2->l;
				if(aux2==NULL && aux==NULL)break;
				if((aux2==NULL && aux!=NULL) || (aux2!=NULL && aux==NULL))
					return false;
				if((*aux == *aux2)==0)return false;
			}
			daux=daux->d;

			daux2=daux2->d;
		}
		return true;
	}

};

#endif
