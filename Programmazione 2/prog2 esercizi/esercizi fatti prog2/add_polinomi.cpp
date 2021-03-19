#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class monomio
{
	public:
	    int coefficente;
		int esponente;
		
		monomio(int c, int e)
		{
			coefficente=c;
			esponente=e;
		}
};

struct Nodo
{
	monomio* val;
	Nodo* succ;
};

class Lista
{
	public:
	    Nodo* testa;
		int elementi;
		Lista() {testa=NULL; elementi=0;}
		void insert(monomio x);
		Nodo* return_testa()  {return testa;}
	    int num_elementi()   {return elementi;}
		Lista operator+(Lista b)
		{
			Nodo* iter1=(*this).return_testa();
			Nodo* iter2=b.return_testa();
			Lista result;
			while(iter1!=NULL || iter2!=NULL)
			{
				if(iter1==NULL && iter2!=NULL)
				{
					monomio x(iter2->val->coefficente, iter2->val->esponente);
					result.insert(x);
					iter2=iter2->succ;
				}
				
				else if(iter1!=NULL && iter2==NULL)
				{
					monomio x(iter1->val->coefficente, iter1->val->esponente);
					result.insert(x);
					iter1=iter1->succ;
				}
				else if(iter1->val->esponente==iter2->val->esponente)
				{
					int nuovo_coeff=iter1->val->coefficente + iter2->val->coefficente;
					if(nuovo_coeff!=0)
					{
						monomio x(nuovo_coeff,iter1->val->esponente);
						result.insert(x);
					}
					iter1=iter1->succ;
					iter2=iter2->succ;
				}
				else
				{
					if(iter1->val->esponente > iter2->val->esponente)
					{
						monomio x(iter2->val->coefficente, iter2->val->esponente);
						result.insert(x);
						iter2=iter2->succ;
					}
					else
					{
					    monomio x(iter1->val->coefficente,iter1->val->esponente);
						result.insert(x);
						iter1=iter1->succ;
					}
				}
				
			}
			return result;
		}
};

void Lista::insert(monomio x)
{
	Nodo* nuovo=new Nodo;
	monomio* mon=new monomio(x.coefficente,x.esponente);
	nuovo->val=mon;
    nuovo->succ=NULL;
	if(testa!=NULL && mon->esponente < testa->val->esponente)
	{
		Nodo* tmp=testa;
		testa=nuovo;
		testa->succ=tmp;
	}
	else if(testa==NULL)
	{
		testa=nuovo;
		testa->succ=NULL;
	}
	else if(testa->succ==NULL)
	{
		if(testa->val->esponente > nuovo->val->esponente)
		{
			Nodo* tmp=testa;
			testa=nuovo;
			nuovo->succ=tmp;
			nuovo->succ->succ=NULL;
			cout<<testa->val->esponente<<" "<<testa->succ->val->esponente<<endl;
		}
		else
		{
			testa->succ=nuovo;
			nuovo->succ=NULL;
		}
	}
	else
	{
		Nodo* iter1=testa;
		Nodo* curr=iter1;
		while(iter1->succ!=NULL && nuovo->val->esponente > iter1->val->esponente) 
		{ 
			curr=iter1;
			iter1=iter1->succ;
		}
		if(iter1->succ==NULL) //lo inseriamo in coda
		{
			iter1->succ=nuovo;
		}
		else
		{
			curr->succ=nuovo;
			nuovo->succ=iter1;
		}
	}
	elementi++;
}


int main()
{
	fstream miofile("input28.txt",fstream::in);
	fstream outfile("output.txt",fstream::out);
	
	for(int riga=0; riga<100; riga++)
	{
		int num_polinomi;
		miofile>>num_polinomi;
	
		Lista result;
		bool cambio_segni=false;
		for(int i=0; i<num_polinomi;i++)
		{
			string a;
			miofile>>a;
			Lista pol;
			/*****************salvataggio di un monomio*************/
			int car=1;
			while(a[car]!=')')
			{
			    stringstream s;
			    int coeff=1;
			    int exp=0;
				bool no_c=true;
			    while(a[car]!='x' && a[car]!=')')
			    {
				    s<<a[car];
				    car++;
			    }

				if(a[car]=='x')
				{
			        car++;
					exp=1;
					if(a[car-2]=='-'){ coeff=-1;no_c=false;}
					else if(a[car-2]=='+' || a[car-2]=='(') {coeff=1;no_c=false;}
					else 
					{
						s>>coeff;
						no_c=false;
					}
					
					if(car-1==1)
						coeff=1;
				}
				
				if(no_c)
				{
					s>>coeff;
				}
				
			    bool exp_magg_1=(a[car]=='^');
			    if(exp_magg_1)
			    {
					car++;
				    stringstream ss;
				    while(a[car]!='+' && a[car]!='-' && a[car]!=')')
				    {
					    ss<<a[car];
					    car++;
				    }
				    ss>>exp;
			    }
				if(cambio_segni)
				{
					coeff=-1*coeff;
				}
				monomio x(coeff,exp);
				pol.insert(x);
				
		    }
			result=result+pol;
			cambio_segni=false;
			if(i!=num_polinomi-1)
			{
			    char b;
			    miofile>>b;
			    if(b=='-')
				{
					cambio_segni=true;
				}
			}
		}
		string arr[result.num_elementi()];
		int i=0;
		Nodo*t=result.return_testa();
		while(t!=NULL)
		{
		    int c=t->val->coefficente;
		    int e=t->val->esponente;
			if(e==0)
			{
				arr[i]=to_string(c);
			}
			else if(e==1)
			{
				if(c==-1)
				{
					arr[i]="-x";
				}
				else if(c==1)
				{
					if(i!=0)
					    arr[i]="x";
				    else
						arr[i]="+x";

				}
				else
				{
				    arr[i]=to_string(c) + "x";
				}
		    }
			else
			{
				if(c==-1) 
				{
					arr[i]= "-x^" + to_string(e);
				}
				else if(c==1)
				{
					if(i==result.num_elementi()-1) arr[i]="x^" + to_string(e);
					else arr[i]="x^" + to_string(e);
				}
				else
				{
				    arr[i]=to_string(c) + "x^" + to_string(e);
				}
			}
			t=t->succ;
			i++;
		}
		int j=result.num_elementi()-1;
		for(j; j>0; j--)
		{
			outfile<<arr[j];
			if((arr[j-1])[0]!='-')
				outfile<<'+';
		}
		outfile<<arr[j]<<endl;
	}
	return 0;
}







