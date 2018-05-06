#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template <class T>
class List
{
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } _form;
	Node<T> * head, *tail;			// Zeiger auf Kopf- und End-Element
	int _size;						// Länge der Kette
	bool temp;						// normalerweise false; ist true, wenn es sich um eine temoräre Liste handelt
									// die innerhalb der überladenen Operatoren angelegt wird
public:
	List<T>();
	~List<T>();
	void InsertFront(T key);		// Einfügen eines Knotens am Anfang
	void InsertBack(T key);		// Einfügen eines Knotesn am Ende
	bool getFront(T & key);		// Entnehmen eines Knoten am Anfang
	bool getBack(T & key);		// Entnehmen eines Knoten am Ende
	bool del(T key);				// löschen eines Knotens [key]
	bool search(T key);			// Suchen eines Knoten
	bool swap(T key1, T key2);	// Knoten in der Liste vertauschen
	int size(void);					// Größe der Lise (Anzahl der Knoten)
	bool test(void);				// Überprüfen der Zeigerstruktur der Liste
	void format(const std::string & start, const std::string & zwischen, const std::string & ende);	// Mit der format-Methode kann die Ausgabe gesteuert werden: operator <<
	List<T> & operator = (const List<T> & _List);						// Zuweisungsoperator definieren
	List<T> & operator = (const List<T> * _List);						// Zuweisungsoperator definieren
	List<T> & operator + (const List<T> & List_Append);				// Listen zusammenführen zu einer Liste
	List<T> & operator + (const List<T> * List_Append);				// Listen zusammenführen zu einer Liste
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> & Liste);		// Ausgabeoperator überladen
	template <typename Tf>
	friend std::ostream & operator << (std::ostream & stream, const List<Tf> * Liste);		// Ausgabeoperator überladen
};
#endif

template <class T>
List<T>::List()
{
	head = new Node<T>;
	tail = new Node<T>;
	_size = 0;
	temp = false;
	head->next = tail;
	tail->prev = head;
}

template <class T>
List<T>::~List()
{
	Node<T>* tmp = head;
	while (tmp != nullptr)
	{
		head->~Node();
		head = tmp->next;
		tmp = tmp->next;
	}
}

template <class T>
void List<T>::InsertFront(T key)
{
	Node<T>* new_Node = new Node<T>;
	new_Node->key = key;
	new_Node->prev = head;
	new_Node->next = head->next;

	head->next->prev = new_Node;
	head->next = new_Node;
	_size++;
}

template <class T>
void List<T>::InsertBack(T key)
{
	Node<T>* new_Node = new Node<T>;
	new_Node->key = key;
	new_Node->next = tail;
	new_Node->prev = tail->prev;

	tail->prev->next = new_Node;
	tail->prev = new_Node;
	_size++;
}

template <class T>
bool List<T>::getFront(T & key)
{
	if (head->next == tail) return false;
	Node<T>* tmp = head->next;
	key = tmp->key;
	head->next = tmp->next;
	tmp->next->prev = head;
	tmp->~Node();
	_size--;
	return true;
}

template <class T>
bool List<T>::getBack(T & key)
{
	if (head->next == tail) return false;
	Node<T>* tmp = tail->prev;
	key = tmp->key;
	tail->prev = tmp->prev;
	tmp->prev->next = tail;
	tmp->~Node();
	_size--;
	return true;
}

template <class T>
bool List<T>::del(T key)
{
	Node<T> * tmp = head;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
		{
			tmp->~Node<T>();
			_size--;
			return true;
		}
		else if (tmp == tail && tmp->key != key) return false;
		tmp = tmp->next;
	}
}

template <class T>
bool List<T>::search(T key)
{
	Node<T>* tmp = head;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
		{
			return true;
		}
		else if (tmp == tail && tmp->key != key) return false;
		tmp = tmp->next;
	}

}

template <class T>
bool List<T>::swap(T key1, T key2)
{
	Node<T> *tmp1 = head, *tmp2 = head, *tmp3 = new Node<T>;
	while (tmp1 != nullptr)
	{
		if (tmp1->key == key1)
		{
			break;
		}
		else if (tmp1 == tail && tmp1->key != key1) return false;
		tmp1 = tmp1->next;
	}
	while (tmp2 != nullptr)
	{
		if (tmp2->key == key2)
		{
			break;
		}
		else if (tmp2 == tail && tmp2->key != key2) return false;
		tmp2 = tmp2->next;
	}
	
	tmp3->prev = tmp1->prev;
	tmp3->next = tmp1->next;
	tmp1->prev = tmp2->prev;
	tmp1->next = tmp2->next;
	tmp1->prev->next = tmp1;
	tmp1->next->prev = tmp1;
	tmp2->prev = tmp3->prev;
	tmp2->next = tmp3->next;
	tmp2->prev->next = tmp2;
	tmp2->next->prev = tmp2;
	return true;
}

template <class T>
int List<T>::size(void)
{
	int size = 0;
	if (head->next == tail) return size;
	else
	{
		Node<T>* tmp = head->next;
		while (tmp != tail)
		{
			size++;
			tmp = tmp->next;
		}
		return size;
	}
}

template <class T>
bool List<T>::test(void)
{
	Node<T>* tmp = head;
	while (tmp != tail) tmp = tmp->next;
	while (tmp != head) tmp = tmp->prev;
	return true;
}

template <class T>
void List<T>::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	_form.start = start;
	_form.zwischen = zwischen;
	_form.ende = ende;
}

template <class T>
List<T> & List<T>::operator = (const List<T> & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List.head->next;
	while (tmp_node != _List.tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List.temp) delete & _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator = (const List<T> * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node<T> * tmp_node;
	if (_size)
	{
		Node<T> * tmp_del;
		tmp_node = head->next;
		while (tmp_node != tail)		// Alle eventuell vorhandenen Knoten in this löschen
		{
			tmp_del = tmp_node;
			tmp_node = tmp_node->next;
			delete tmp_del;
		}
		_size = 0;
		head->next = tail;
		tail->prev = head;
	}
	tmp_node = _List->head->next;
	while (tmp_node != _List->tail)
	{
		InsertBack(tmp_node->key);
		tmp_node = tmp_node->next;
	}
	if (_List->temp) delete _List;		// ist die Übergebene Liste eine temporäre Liste? -> aus Operator +
	return *this;
}

template <class T>
List<T> & List<T>::operator + (const List<T> & List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

template <class T>
List<T> & List<T>::operator + (const List<T> * List_Append)
{
	Node<T> * tmp_node;
	List * tmp;
	if (temp) {								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail) {
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

template <class Tf>
std::ostream & operator<<(std::ostream  & stream, List<Tf> const & Liste)
{
	stream << Liste._form.start;
	for (Node<Tf> * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

template <class Tf>
std::ostream & operator << (std::ostream & stream, List<Tf> const * Liste)
{
	stream << Liste->_form.start;
	for (Node<Tf> * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}