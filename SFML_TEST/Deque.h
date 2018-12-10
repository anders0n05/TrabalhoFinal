#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <string.h>

using namespace std;

template <typename TYPE>
struct TData {
	TYPE data;
	TData<TYPE> *next;
	TData<TYPE> *previous;
};

template <typename TYPE>
struct TDQueue {
	TData<TYPE> * begin;
	TData<TYPE> * last;
};

template <typename TYPE>
void inicialize_Dqueue(TDQueue<TYPE> &Dqueue) {// Função para inicializar ou reiniciar a estrutura.

	Dqueue.begin = NULL; // Seta o inicio como NULL.
	Dqueue.last = NULL; // Seta o fim como NULL.
}

template <typename TYPE>
TData<TYPE> *new_date(TYPE data) {// Função para a criação de um novo elemento.

	TData<TYPE> *new_data = new TData<TYPE>; // Cria um elemento tipo Tdata<TYPE>.
	new_data->data = data; // Seta o valor do dado com o TYPE data. 
	new_data->next = NULL; // Seta NULL para o proximo do new_data.
	new_data->previous = NULL; // Seta NULL para o anterior do new_data.
	return new_data;
}

template <typename TYPE>
bool insert_begin(TDQueue<TYPE> &Dqueue, TYPE data) {// Função que insere no começo da estrutura.

	if (Dqueue.begin == NULL && Dqueue.last == NULL) {// Caso a estrutura esteje vazia.

		TData<TYPE> *new_data = new_date(data); // Cria um novo elemento.
		Dqueue.begin = new_data; // Seta o inicio da estrutua com o novo elemento.
		Dqueue.last = new_data; // Seta o fim da estrutura com o novo elemento.
		new_data->next = Dqueue.begin; // O proximo do novo elemento é o inicio da estrutura.
		new_data->previous = Dqueue.last; // O anterior do novo elemento é o fim da estrutura.

		return true;
	}
	else {// Caso ja possua elementos na estrutura.

		TData<TYPE> *new_data = new_date(data); // Cria um novo elemento.
		new_data->next = Dqueue.begin; // O novo elemento recebe o inicio da estrutura no seu proximo.
		new_data->previous = Dqueue.last; // O novo elemento recebe o fim da estrutura no seu anterior.
		Dqueue.last->next = new_data; // O proximo do fim da estrutura recebe o novo elemento.
		Dqueue.begin = new_data; // O inicio da estrutura é setado como o novo elemento.
		Dqueue.begin->next->previous = new_data; // O a anterior do proximo elemento do inicio é setado com o novo elemento.

		return true;
	}
}

template <typename TYPE>
bool insert_last(TDQueue<TYPE> &Dqueue, TYPE data) {// Função que insere no fim da estrutura.

	if (Dqueue.begin == NULL && Dqueue.last == NULL) {// Caso a estrutura esteje vazia.

		TData<TYPE> *new_data = new_date(data); // Cria um novo elemento.
		Dqueue.begin = new_data; // Seta o inicio da estrutua com o novo elemento.
		Dqueue.last = new_data; // Seta o fim da estrutura com o novo elemento.
		new_data->next = Dqueue.begin; // O proximo do novo elemento é o inicio da estrutura.
		new_data->previous = Dqueue.last; // O anterior do novo elemento é o fim da estrutura.

		return true;
	}
	else {// Caso a estrutura possua elementos.

		TData<TYPE> *new_data = new_date(data); // Cria um novo elemento.
		Dqueue.last->next = new_data; // O proximo do fim da estrutura recebe o novo elemento.
		new_data->next = Dqueue.begin; // O proximo do novo elemento recebe o começo da estrutura.
		Dqueue.begin->previous = new_data; // O anterior do inicio da estrutura recebe o novo elemento.
		new_data->previous = Dqueue.last; // O anterior do novo elemento recebe o fim da estrutura.
		Dqueue.last = new_data; // O fim da estrutura é setado como o novo elemento.

		return true;
	}
}

template <typename TYPE>
bool remove_begin(TDQueue<TYPE> &Dqueue) {// Função que remove do inicio da estrutura.

	if (Dqueue.begin == NULL && Dqueue.last == NULL) {// Caso a estrutura já esteje vazia.

		return false;
	}
	else if (amount(Dqueue) == 1) {

		Dqueue.begin = NULL;
		Dqueue.last = NULL;
	}
	else {// Se possuir elementos.

		Dqueue.begin->next->previous = Dqueue.last; // O anterior do proximo do inicio da estrutura recebe o fim da estrutura.
		Dqueue.last->next = Dqueue.begin->next; // O proximo do fim da estrutura recebe o proximo do inicio da estrutura.
		Dqueue.begin = Dqueue.begin->next; // O inicio da estrutura é setado como o proximo do inicio da estrutura.

		return true;
	}
}

template <typename TYPE>
bool remove_last(TDQueue<TYPE> &Dqueue) {// Função que remove do final da estrutura.

	if (Dqueue.begin == NULL && Dqueue.last == NULL) {// Caso a estrutura já esteje vazia.

		return false;
	}
	else {// Se possuir elementos.

		Dqueue.last->previous->next = Dqueue.begin; // O proximo do anterior do fim da estrutura recebe o começo da estrutura.
		Dqueue.begin->previous = Dqueue.last->previous; // O anterior do inicio da estrutura receber o anterior do fim da estrutura.
		Dqueue.last = Dqueue.last->previous; // O fim da estrutura é setado com o anterior do fim da estrutura.

		return true;
	}
}

template <typename TYPE>
bool remove_position(TDQueue<TYPE> &Dqueue, int pos) {

	int i = 1;

	if (Dqueue.begin == NULL && Dqueue.last == NULL) {

		cout << "A LISTA ESTA VAZIA" << endl;
		return false;
	}
	else if (pos == 1 && amount(Dqueue) == 1) {

		Dqueue.begin = NULL;
		Dqueue.last = NULL;
		return true;

	}
	else if (pos == amount(Dqueue)) {

		remove_last(Dqueue);
		return true;
	}
	else if (pos == 1) {

		remove_begin(Dqueue);
		return true;
	}
	else if (pos > amount(Dqueue)) {

		cout << "A POSICAO E MAIOR QUE A ESTRUTURA" << endl;
		return false;
	}
	else if (pos > 1 && pos < amount(Dqueue)) {

		TData<TYPE> *nav = Dqueue.begin;

		while (i != pos) {
			nav = nav->next;;
			i++;
		}

		TData<TYPE> aux;
		aux.next = nav->next;
		aux.previous = nav->previous;
		nav->next->previous = aux.previous;
		nav->previous->next = aux.next;
		return true;
	}
}

template <typename TYPE>
int amount(TDQueue<TYPE> &Dqueue) {// Função que retorna a quantidade de elementos da estrutura.

	TDQueue<TYPE> swap = Dqueue; // Cria um auxiliar para o while.
	if (swap.begin == NULL && swap.last == NULL) {// Caso a estrutura esteje vazia.

		cout << "Não possui elementos"; // Print da condição da estrutura.
	}
	else {// Caso possua elementos na estrutura.

		int i = 1; // Minimo de elementos na estrutura.
		while (swap.begin != swap.last) {// LOOP até o inicio da estrutura ser igual ao fim da mesma.

			i++; // Incrimenta o i.
			swap.begin = swap.begin->next; // Passa o navegador para o proximo.
		}

		return i; // Sendo "i" a variavel com a quantidade de elementos.
	}
}

template <typename TYPE>
void print_Dqueue(TDQueue<TYPE> &Dqueue) {// Função que printa a estrutura.

	TDQueue<TYPE> swap = Dqueue;
	if (swap.begin == NULL && swap.last == NULL) {// Caso a estrutura esteje vazia.

		cout << "Nao possui elementos"; // Print da condição da estrutura.
	}
	else {// Caso possua elementos na estrutura.

		for (int i = 0; i < amount(Dqueue); i++) {// LOOP até a quantidade de elementos na estrutura.

			cout << swap.begin->data << " "; // Print da estrutura.
			swap.begin = swap.begin->next; // Passa o navegador para o proximo.
		}
	}
}

#endif /* DEQUE_H */