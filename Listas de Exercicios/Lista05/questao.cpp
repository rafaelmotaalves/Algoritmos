#include <bits/stdc++.h>

using namespace std;

struct node
{
	int v;
	int peso;
	node *next;
};

node* insert(node* curr,int v,int p){
	node* n = new node;
	n->v = v;
	n->peso = p;
	n->next = curr->next;
	curr->next = n;
	return curr;
}

struct heap_node
{
	int p;
	int v;
	
};

class Min_heap
{
private:
	int heap_size;
	int array_size;
	heap_node *prioritys;
	int *values;
public:


Min_heap(int size){
	heap_size = 0;
	array_size = size;
	prioritys = new heap_node[size];
	values = new int[size];
	for(int i = 0 ; i < size; i++){
		values[i] = -1;
	}
}


~Min_heap(){
	delete[] values;
	delete[] prioritys;
}

void insert(int v, int p){
	values[v] = heap_size;
	prioritys[heap_size].p = p;
	prioritys[heap_size].v = v;
	heap_size++;
	bubbleup();

}

void bubbleup(){
	int i = heap_size - 1;
	while(i>0 && prioritys[i].p <= prioritys[(int)floor((i-1)/2)].p){
			values[prioritys[i].v] = (int)floor((i-1)/2);
			values[prioritys[(int)floor((i-1)/2)].v] = i;
			heap_node aux = prioritys[i];
			prioritys[i] = prioritys[(int)floor((i-1)/2)];
			prioritys[(int)floor((i-1)/2)] = aux;
			i = floor((i-1)/2);
	}

}

void heapify(int i){
	int l = 2*i + 1;
	int r = 2*i + 2;
	int m = i;
	if(l < heap_size && prioritys[l].p <= prioritys[m].p){
		m = l;
	}
	if(r < heap_size && prioritys[r].p <= prioritys[m].p){
		m = r;
	}
	if(m != i){
		values[prioritys[m].v] = i;
		values[prioritys[i].v] = m;
		heap_node aux = prioritys[i];
		prioritys[i] = prioritys[m];
		prioritys[m] = aux;
		heapify(m);
	}
}

heap_node extract(){
	heap_node r;
	if(heap_size != 0){
		r = prioritys[0];
		values[prioritys[0].v] = -1;
		values[prioritys[heap_size-1].v] = 0;
		prioritys[0] = prioritys[heap_size-1];
		heap_size--;
		heapify(0);
	}
	return r;
}

void heap_update(int v , int p ){
	if(values[v] == -1){
		insert(v,p);
	}else{
		prioritys[values[v]].p = p;
		bubbleup();
	}
}

};



class Grafo{
private:
	node **e;
	int size;
public:
	Grafo(int size){
		this->size = size;
		e = new node*[size];
		for(int i = 0 ; i< size; i++){
			e[i] = new node;
		}
	}

	void inserirAresta(int a,int b,int peso){
		insert(e[a],b,peso);
		insert(e[b],a,peso);

	}

	void dijkstraS(int s,int cidades[], int tarifas[],int destino){
		int *d = new int[size];
		int *p = new int[size];
		for(int i = 0 ; i < size ; i++){
			d[i] = 0x3f3f3f3f;
			p[i] = 0;
		}
		d[s] = 0;
		p[s] =0;
		Min_heap *h = new Min_heap(size);
		h->insert(s,0);
		for(int i = 0 ; i < size ; i++){
			heap_node a = h->extract();
			int u = a.v;
			node *curr = e[u]->next;
			while( curr != NULL){
				if( d[u] + curr->peso <= d[curr->v]){
					d[curr->v] = (d[u] + curr->peso);
					p[curr->v] = p[u] + (curr->peso * tarifas[cidades[u]]);
					h->heap_update(curr->v,d[curr->v]);
				}
				curr = curr->next;
			}
		}

		delete h;
		cout << d[destino] << " " << p[destino] << endl;
		delete[] d;
		delete[] p;

	}

	void dijkstraE(int s,int cidades[], int tarifas[],int destino){
		int *d = new int[size];
		int *p = new int[size];
		for(int i= 0 ; i < size ; i++ ){
			p[i] = 0x3f3f3f3f;
		}
		d[s] = 0;
		p[s] = 0;
		Min_heap *h = new Min_heap(size);
		h->insert(s,0);
		for(int i =0 ; i < size ; i++){
			heap_node a = h->extract();
			int u = a.v;
			node* curr = e[u]->next;
			while(curr != NULL){
				if(p[u] + curr->peso*tarifas[cidades[u]] <=  p[curr->v]){
					d[curr->v] = d[u] + curr->peso;
					p[curr->v] =  p[u] + curr->peso*tarifas[cidades[u]];
					h->heap_update(curr->v,p[curr->v]);
				}
				curr = curr->next;
			}
		}

		delete h;

		cout << d[destino] << " " << p[destino] << endl;

		delete[] d;
		delete[] p;
	}


};


int main(){
	int m;//numero de cidades
	cin >> m;
	int tarifas[m];
	for(int i = 0 ; i < m ; i++){
		cin >>tarifas[i];//tarifa por cidade; 
	}
	int n;//quantidade de pontos(tamanho do grafo)
	cin >> n;
	Grafo *gr = new Grafo(n);
	int cidades[n];
	for(int i = 0; i < n ; i++){
		cin >> cidades[i];//cidade em que cada ponto de encontra
	}
	int w;
	cin >> w;
	for(int i = 0 ; i < w ; i++){
		int a,b,p;
		cin >> a;
		cin >> b;
		cin >> p;
		gr->inserirAresta(a,b,p);
	}
	string func;
	while(cin >> func){
		if(func == "UPDA"){
			int j , r;
			cin >> j;
			cin >> r;
			tarifas[j] = r;
		}else if(func == "RIDE"){
			int c , d;
			char o;
			cin >> c;
			cin >> d;
			cin >> o;
			if(o == 'S'){
				gr->dijkstraS(c,cidades,tarifas,d);
			}else if(o == 'E'){
				gr->dijkstraE(c,cidades,tarifas,d);
			}
		}

	}

	return 0;
 }