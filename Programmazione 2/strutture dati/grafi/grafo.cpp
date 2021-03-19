#include <iostream>
using namespace std;


/****************************************************LISTA*************************************************/
template <class H> struct Nodo
{
	H valore;
	Nodo<H>* succ;
};

template <class H> class Lista
{
	private:
	    Nodo<H>* testa;
	public:
	    Lista() {testa=NULL;}
		~Lista();
		void print();
		void insert(H x);
		Nodo<H>* rivela_testa();
		Nodo<H>* ricerca(H x);
};

template <class H> Lista<H>::~Lista()
{
	Nodo<H>* iter=testa;
	
	while(iter!=NULL)
	{
		Nodo<H>* aux=iter->succ;
		delete iter;
		iter=aux;
	}
}

template <class H> void Lista<H>::insert(H x)
{
	Nodo<H>* nuovo=new Nodo<H>;
	nuovo->valore=x;
	nuovo->succ=testa;
	testa=nuovo;
}


template <class H> Nodo<H>* Lista<H>::rivela_testa()
{
	return testa;
}


template <class H> Nodo<H>* Lista<H>::ricerca(H x)
{
	Nodo<H>* iter;
	for(iter=testa; iter!=NULL ; iter=iter->succ)
	{
		if(iter->valore==x)
			return iter;
	}
	return NULL;
}

template <class H> void Lista<H>::print()
{
	Nodo<H>* iter=testa;
	while(iter!=NULL)
	{
		cout<<iter->valore<<" ";
		iter=iter->succ;
	}
	cout<<endl;
}
/****************************************************LISTA*************************************************/




/****************************************************LGRAFO*************************************************/
template <class H> class LGrafo
{
	private:
	    int len , n , m;  //len nodi massimi, n numero di nodi presenti, m numero di archi presenti
		H** K;
		Lista<int>** Adj;
		int trova_indice(H k)
		{
			for(int i=0; i<n ; i++)
				if(*K[i]==k) return i;
			return -1; //non trovato
		}
		
	public:
	    LGrafo(int lung);
		LGrafo<H>* addNode(H k);  //aggiunge nodo k(se non c'è già e se non sono arrivato al limite len)
		LGrafo<H>* addEdge(H x, H y); //aggiunge arco che collega x e y se essi sono presenti e se non c'è già
		void print();
};

template <class H> LGrafo<H>::LGrafo(int lung)
{
	n=0;
	m=0;
	len=lung;
	
	K=new H*[len];
	for(int i=0; i<len; i++) K[i]=NULL;
	
	Adj=new Lista<int>*[len];
	for(int i=0; i<len; i++) Adj[i]=new Lista<int>();
}

template <class H> LGrafo<H>* LGrafo<H>::addNode(H k)
{
	if(n==len) return this; //siamo al limite
	if(trova_indice(k)>=0) return this; //il nodo esiste già
	K[n]=new H(k);
	n++;
	return this;
}

template <class H>LGrafo<H>* LGrafo<H>::addEdge(H x, H y)
{
	int i=trova_indice(x);
	int j=trova_indice(y);
	if(i<0 || j<0) return this; //almeno uno dei due non c'è
	if(!Adj[i]->ricerca(j))
	{
		Adj[i]->insert(j);
		m++;
	}
	return this;
}

template <class H> void LGrafo<H>::print()
{
	for(int i=0; i<n ; i++)
	{
		cout<<"("<<i<<","<< *K[i]<<") : ";
		//Adj[i]->print();
		
		Nodo<int>* t=Adj[i]->rivela_testa();
		while(t!=NULL)
		{
	        cout<<*K[t->valore]<<" ";
			t=t->succ;
		}
		cout<<endl;
	}
	cout<<endl<<endl;
}
/****************************************************LGRAFO*************************************************/




/*****************************************CODA PER MGRAFO***********************************************************/
class Coda {
private: 
	int* VettoreCoda;
	int DimCoda; 
	int testa;
	int fine; 
	int num_elementi;	
public:
	Coda(int DimCoda); //Costruttore della coda
	void Enqueue(int elemento); //Inserisce un elemento nella coda
	int Dequeue();  //Estrae un elemento dalla coda
	int Testa(); // Legge l'elemento in testa alla coda senza estrarlo 
	int CodaVuota() {return (num_elementi==0);} // Verifica se la coda è vuota
	int CodaPiena() {return (num_elementi==DimCoda);} // Verifica se la coda è piena
}; 

Coda::Coda(int len) {
	DimCoda=len; 
	VettoreCoda = new int[len]; 
	testa=0; fine=-1; num_elementi=0;
} 

void Coda::Enqueue(int x) 
{	
	if (this->CodaPiena())
		cerr << "Coda piena! \n";  	
	else {  
		fine=(fine + 1) % DimCoda; 
		VettoreCoda[fine]=x;
		num_elementi++;
		}
}

int Coda::Testa()
{
	return testa;  
}


int Coda::Dequeue()
{	int x;
	
	if (CodaVuota()) {
		cerr << "Coda Vuota!" << endl; 
		return -1;  }
	else 	{ 
		x=VettoreCoda[testa];
		testa=(testa+1) % DimCoda;
		num_elementi--;
		return x; 
		}
}
/****************************************************CODA *************************************************/




/**********************************************MGRAFO***********************************************/
template <class H> class Mgrafo
{
	private:
	    int len,n,m;  //len è numero massimo di nodi possibili, n è il numero effettivo, m è il numero effettivo di archi 
	
	bool **M;  //matrice di adiacenza
	H **K;
	
	int *distanze,*predecessoi;
	int* colori;
	int* radici;
	int current_root;
	
	bool **tM;
	
	int t;
	int* marche_temp_entrate;
	int* marche_temp_uscite;
	
	int trova_indice(H x)
	{
		for(int i=0; i<n;i++)
		{
			if(*K[i]==x) return i;
		}
		return -1;
	}
	

	public:
	    Mgrafo(int lung);
		Mgrafo<H>* addNode(H x);
		Mgrafo<H>* addEdge(H x, H y);
		void BFS(int i);
		int BFS(H x);
		void print();
		
		void print_path(int i)
	    {
		    if(i==-1) return;
		    else if(predecessoi[i]==-1) cout<<i;
		    else
		    {
			    print_path(predecessoi[i]);
			    cout<<"->"<<i;
		    }
	    }
		
		void DFS_visit(int s);
		void DFS();
		
		
		int _DFS_visit(int s);
		int _DFS();
		void topsort();
		void sort(int* a,int n,int* f)
		{
			for(int i=1; i<n; i++)
			{
				int j=i-1;
				while(j>=0 && f[a[j+1]] > f[a[j]])
				{
					int tmp=a[j+1];
					a[j+1]=a[j];
					a[j]=tmp;
					j--;
				}
			}
		}
		
		void transpose()
		{
			for(int i=0;i<len;i++)
			{
                for(int j=0;j<len;j++)
				{
                    tM[i][j] = M[j][i];
                }
            }
		}
		void tDFSvisit(int s);
		void tDFS();
		
		void printSSC();
};

template <class H> Mgrafo<H>::Mgrafo(int lung)
{
	len=lung;
	n=0;
	m=0;
	M=new bool*[len];
	tM=new bool*[len];
	distanze=new int[len];
	predecessoi=new int[len];
	colori=new int[len];
	radici=new int[len];
	
	marche_temp_entrate=new int[len];
	marche_temp_uscite=new int[len];
	
	for(int i=0; i<len;i++)
	{
		M[i]=new bool[len];
		tM[i]=new bool[len];
		for(int j=0; j<len; j++)
		{
			M[i][j]=false;
			tM[i][j]=false;
		}
	}
	K=new H*[len];
	for(int i=0; i<len; i++) K[i]=NULL;
}

template <class H> Mgrafo<H>* Mgrafo<H>::addNode(H x)
{
	if(n==len) return this; //siamo arrivati al massimo di nodi
	else if(trova_indice(x)>=0) return this;  //il nodo c'è già,non possiamo metterlo
	else K[n]=new H(x); n++; return this;
}

template <class H> Mgrafo<H>* Mgrafo<H>::addEdge(H x, H y)
{
	int i=trova_indice(x);
	int j=trova_indice(y);
	
	if(i<0 || y<0) return this; // se almeno uno tra x e y non c'è non possiamo creare l'arco
	else if(!M[i][j])
	{
		M[i][j]=true;
		m++;
	}
	return this;
}

template <class H> void Mgrafo<H>::print()
{
	for(int i=0; i<n;i++)
	{
		cout<<"("<<i<<","<<*K[i]<<") : ";
		for(int j=0; j<n; j++)
		{
			if(M[i][j]) cout<<*K[j]<<" ";
		}
		cout<<endl;
	}
}

template <class H> void Mgrafo<H>::BFS(int s)
{
	int W=0;
	int G=1;
	int B=2;
	int inf=len+1;
	
	Coda* Q=new Coda(len);
	for(int i=0; i<n; i++) //fare attenzione a fare n e non len
	{
		colori[i]=W;
		predecessoi[i]=-1;
		distanze[i]=inf; 
	}
	
	colori[s]=G;
	distanze[s]=0;
	
	Q->Enqueue(s);
	
	while(!Q->CodaVuota())
	{
		int x=Q->Dequeue();
		for(int i=0; i<n;i++)
		{
			if(M[x][i])
			{
				if(colori[i]==W)
				{
					colori[i]=G;
					Q->Enqueue(i);
					predecessoi[i]=x;
					distanze[i]=distanze[x]+1;
				}
			}
		}
		colori[x]=B;
	}
	for(int i=0; i<n;i++)
	{
		cout<<"["<<i<<"] ->";
		if(distanze[i]==inf) cout<<"non raggiungibile"<<endl;
		else cout<<distanze[i]<<endl;
	}
}


template <class H> int Mgrafo<H>::BFS(H x)
{
	int s=trova_indice(x);
	if(s>=0) BFS(s);
	return s;
}


template <class H> void Mgrafo<H>::DFS_visit(int v)
{
	int W=0;
	int G=1;
	int B=2;
	
	colori[v]=G;
	marche_temp_entrate[v]=t;
	t++;
	radici[v]=current_root;
	
	for(int i=0; i<n;i++)
	{
		if(M[v][i])
		{
			if(colori[i]==W)
			{
				predecessoi[i]=v;
				DFS_visit(i);
			}
		}
	}
	
	colori[v]=B;
	marche_temp_uscite[v]=t;
	t++;
	
//	stack.Push(v); //modifica aggiunta per utilizzare questo stack per la SSC
}
template <class H> void Mgrafo<H>::DFS()
{
	t=0;
	int W=0;
	
	for(int i=0; i<n;i++)
	{
		colori[i]=W;
		predecessoi[i]=-1;
	}
	
	for(int i=0; i<n;i++)
	{
		if(colori[i]==W)
		{
			current_root=i;
			DFS_visit(i);
		}
	}
	
}

//modifichiamo le due procedure per la DFS,così oltre a svolgere la DFS riuscirà a "comunicarci" se nel grafo c'è un ciclo

template <class H> int Mgrafo<H>::_DFS_visit(int v)
{
	int W=0;
	int G=1;
	int B=2;
	
	int cycle=0;
	
	colori[v]=G;
	marche_temp_entrate[v]=t;
	t++;
	radici[v]=current_root;
	
	for(int i=0; i<n;i++)
	{
		if(M[v][i])
		{
			if(colori[i]==W)
			{
				predecessoi[i]=v;
			    cycle|=_DFS_visit(i);
			}
			
			if(colori[i]==G) cycle = 1;
		}
	}
	
	colori[v]=B;
	marche_temp_uscite[v]=t;
	t++;
	return cycle;
}
template <class H> int Mgrafo<H>::_DFS()
{
	t=0;
	int W=0;
	int cycle=0;
	for(int i=0; i<n;i++)
	{
		colori[i]=W;
		predecessoi[i]=-1;
	}
	
	for(int i=0; i<n;i++)
	{
		if(colori[i]==W)
		{
			current_root=i;
			cycle|=_DFS_visit(i);
		}
	}
	return cycle;
}


template <class H> void Mgrafo<H>::topsort()
{
	int cycle=_DFS();
	
	if(cycle==1){cout<<"c'è un ciclo"<<endl; return;}
	else 
	{
		int* indici=new int[n];
		for(int i=0; i<n;i++) indici[i]=i;
		
		sort(indici,n,marche_temp_uscite);
		
		for(int i=0; i<n;i++)
		{
			cout<<indici[i]<<" "<<marche_temp_uscite[indici[i]]<<" -> ";
		}
		cout<<endl;
	}
	
}


template <class H> void Mgrafo<H>::tDFS() //non ci interessano le marche temporali
{
	int W=0;
	for(int i=0;i<n;i++)
	{
		colori[i]=W;
		predecessoi[i]=-1;
	}
	
	for(int i=0; i<n;i++)
	{
		if(colori[i]==W)
		{
			current_root=i;
			tDFSvisit(i);
		}
	}
}


template <class H> void Mgrafo<H>::tDFSvisit(int s)
{
	int W=0;
	int G=1;
	int B=2;
	
	colori[s]=G;
	radici[s]=current_root;
	
	for(int i=0; i<n;i++)
	{
		if(tM[s][i])
		{
			if(colori[i]==W)
			{
				predecessoi[i]=s;
				tDFSvisit(i);
			}
		}
	}
	colori[s]=B;
}

template <class H> void Mgrafo<H>::printSSC()	
{
	cout << "Componenti fortemente connesse: \n";
	int flag=0;
		
    for (int i=0; i<n; i++)	
	{
	    for(int j=0; j<n;j++)
			if (radici[j]==i) { flag=1; cout << j << " ";} 
		
			if (flag) 
			{
				cout <<endl; 
				flag=0; 
			}
	}
}


/****************************************************MGRAFO*************************************************/





int main()
{
	if(1)
	{
	cout<<"**************GRAFO LISTA**************"<<endl;
	LGrafo<char> *Gr = new LGrafo<char>(9);
	Gr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Gr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Gr->addNode('I');
	
	Gr->addEdge('A','H')->addEdge('A','B');
	Gr->addEdge('B','H');
	Gr->addEdge('C','D');
	Gr->addEdge('D','E')->addEdge('D','I')->addEdge('D','H');
	Gr->addEdge('E','D')->addEdge('E','A');
	Gr->addEdge('G','G')->addEdge('G','E');
	Gr->addEdge('H','F');
	Gr->addEdge('I','B');
	Gr->print();
	
	cout<<"\n \n";
	cout<<"**************GRAFO MATRICE**************"<<endl;
	}
	Mgrafo<char> *Mr = new Mgrafo<char>(9);
	Mr->addNode('A')->addNode('B')->addNode('C')->addNode('D');
	Mr->addNode('E')->addNode('F')->addNode('G')->addNode('H');
	Mr->addNode('I');
	
	Mr->addEdge('A','H')->addEdge('A','B');
	Mr->addEdge('B','H');
	Mr->addEdge('C','D');
	Mr->addEdge('D','E')->addEdge('D','I')->addEdge('D','H');
	Mr->addEdge('E','D')->addEdge('E','A');
	Mr->addEdge('G','E');
	Mr->addEdge('H','F');
	Mr->addEdge('I','B');
	Mr->print();
	
	int ind=Mr->BFS('D');  //restituisce l'indice di D,e calcola le distanze minime fino ad ogni altro vertice
	Mr->print_path(ind);
	cout<<endl;
	cout<<"processo di top_sort"<<endl;
	Mr->topsort();
	
	Mr->DFS;
	Mr->transpose();
	Mr->tDFS();
	Mr->printSSC();
	
	cout<<"\n \n";
	cout<<"**************GRAFO MATRICE**************"<<endl;
	
	Mgrafo<char> *Gr = new Mgrafo<char>(9);
	Gr->addNode('0')->addNode('1')->addNode('2')->addNode('3');
	Gr->addNode('4')->addNode('5')->addNode('6')->addNode('7');
	Gr->addNode('8');
	
	Gr->addEdge('0','8')->addEdge('0','1');
	Gr->addEdge('1','8');
	Gr->addEdge('2','4');
	Gr->addEdge('3','5')->addEdge('3','6')->addEdge('3','7');
	Gr->addEdge('4','3')->addEdge('4','0');
	Gr->addEdge('5','6')->addEdge('5','3');
	Gr->addEdge('6','5');
	Gr->addEdge('8','2');
	Gr->print();
	
	
	Gr->DFS();
	Gr->transpose();    //4 passaggi fondamentali per la SSC
	Gr->tDFS(); 
	Gr->printSSC();	
	return 0;
	
	
	
}








