#include "List.h"
List::List()
{
	head = new Node;
	tail = new Node;
	_size = 0;
	temp = false;
	head->next = tail;
	tail->prev = head;
}
List::~List()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		head->~Node();
		head = tmp->next;
		tmp = tmp->next;
	}
}
void List::InsertFront(int key)
{
	Node* new_Node = new Node;
	new_Node->key = key;
	new_Node->prev = head;
	new_Node->next = head->next;	

	head->next->prev = new_Node;
	head->next = new_Node;
	_size++;
}
void List::InsertBack(int key)
{
	Node* new_Node = new Node;
	new_Node->key = key;
	new_Node->next = tail;
	new_Node->prev = tail->prev;

	tail->prev->next = new_Node;
	tail->prev = new_Node;
	_size++;
}
bool List::getFront(int & key)
{
	if (head->next == tail) return false;
	Node* tmp = head->next;
	key = tmp->key;
	head->next = tmp->next;
	tmp->next->prev = head;
	tmp->~Node();
	_size--;
	return true;
}
bool List::getBack(int & key)
{
	if (head->next == tail) return false;
	Node* tmp = tail->prev;
	key = tmp->key;
	tail->prev = tmp->prev;
	tmp->prev->next = tail;
	tmp->~Node();
	_size--;
	return true;
}
bool List::del(int key)
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		if (tmp->key == key)
		{
			tmp->~Node();
			_size--;
			return true;
		}
		else if (tmp == tail && tmp->key != key) return false;
		tmp = tmp->next;
	}
}
bool List::search(int key)
{
	Node* tmp = head;
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
bool List::swap(int key1, int key2)
{
	Node *tmp1 = head, *tmp2 = head, *tmp3;
	while (tmp1 != nullptr)
	{
		if (tmp1->key == key1)
		{
			tmp3 = tmp1;
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
	
	tmp1->prev = tmp2->prev;
	tmp1->next = tmp2->next;
	tmp1->prev->next = tmp1;
	tmp1->next->prev = tmp1;
	tmp2->prev = tmp3->prev;
	tmp2->next = tmp3->next;
	tmp2->prev->next = tmp2;
	tmp2->next->prev = tmp2;
	tmp3->~Node();
	return true;
}
int List::size(void)
{
	int size = 0;
	if (head->next == tail) return size;
	else
	{
		Node* tmp = head->next;
		while (tmp != tail)
		{
			size++;
			tmp = tmp->next;
		}
		return size;
	}
}
bool List::test(void)
{
	Node* tmp = head;
	while (tmp != tail) tmp = tmp->next;
	while (tmp != head) tmp = tmp->prev;
	return true;
}

void List::format(const std::string & start, const std::string & zwischen, const std::string & ende)
{
	_form.start = start;
	_form.zwischen = zwischen;
	_form.ende = ende;
}

List & List::operator = (const List & _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == &_List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
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

List & List::operator = (const List * _List)
{
	// in dem Objekt _List sind die Knoten enthalten, die Kopiert werden sollen.
	// Kopiert wird in das Objekt "this"
	if (this == _List) return *this;	//  !! keine Aktion notwendig
	Node * tmp_node;
	if (_size)
	{
		Node * tmp_del;
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

List & List::operator + (const List & List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append._size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append.head->next;
		while (tmp_node != List_Append.tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append.temp) delete & List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

List & List::operator + (const List * List_Append)
{
	Node * tmp_node;
	List * tmp;
	if (temp){								// this ist eine temporäre Liste und kann verändert werden
		tmp = this;
	}
	else {
		tmp = new List;						// this ist keine temporäre Liste -> Kopie erzeugen
		tmp->temp = true;					// Merker setzten, dass es sich um eine temporäre Liste handelt
		tmp_node = head->next;
		while (tmp_node != tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->_size) {				// anhängen der übergebenen Liste an tmp
		tmp_node = List_Append->head->next;
		while (tmp_node != List_Append->tail){
			tmp->InsertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
	}
	if (List_Append->temp) delete List_Append;		// wurde eine temporäre Liste übergeben, dann wird diese gelöscht							// 
	return *tmp;
}

std::ostream & operator<<(std::ostream  & stream, List const & Liste)
{
	stream << Liste._form.start;
	for (Node * tmp = Liste.head->next; tmp != Liste.tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste.tail ? Liste._form.ende : Liste._form.zwischen);
	if (Liste.temp) delete & Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}

std::ostream & operator << (std::ostream & stream, List const * Liste)
{
	stream << Liste->_form.start;
	for (Node * tmp = Liste->head->next; tmp != Liste->tail; tmp = tmp->next)
		stream << tmp->key << (tmp->next == Liste->tail ? Liste->_form.ende : Liste->_form.zwischen);
	if (Liste->temp) delete Liste;			// wurde eine temporäre Liste übergeben, dann wird diese gelöscht
	return stream;
}