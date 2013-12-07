// LinkedList.h -- class for a linked list as a data structure

#include <iostream>

using namespace std;

template <class DataType>
struct Node {
	DataType info;
	Node<DataType> *next;
};

// LinkedList maintains a current position in list after each function call
// If an object of a struct is used for DataType, the == operator must be 
// overloaded for it; the left and right operands are both DataType objects
// the == comparison is used for finding elements, usually by key value
// For find, retrieve and remove functions, if you are using an object as an element, a 
// typical use would be to set the key of the desired object to find or remove, then pass 
// the object into the function.
// The constructor, copy constructor, overloaded assignment operator, and insert function
// can throw an exception if out of heap memory.

template <class DataType>
class LinkedList
{
public:
	LinkedList( );
	LinkedList( const LinkedList<DataType> & aplist );
	~LinkedList( );
	LinkedList<DataType> & operator =( const LinkedList<DataType> & rlist );
	void insert( const DataType & element ); // no current position after use
	bool first( DataType & listEl );	  // returns first element of list in listEl
										  // and current position is set to this element; 
										  // if list is empty, returns false and there is
										  // no current position; otherwise, returns true
	inline bool getNext( DataType & listEl );	  // retrieves the next element of a linked list
										  // beyond the last element that was retrieved
										  // by first or getNext functions and returns
										  // it in listEl;
										  // current position is set to this element.
										  // if no element exists at this position, 
										  // getNext returns false and there is no 
										  // current position; returns true otherwise	
	bool find ( const DataType & element );  // returns true if element is found
									      // returns false if element is not found
										  // if found, found element becomes current
										  // position in list; if not found, there is
										  // no current position
	bool retrieve( DataType & element );  // like find, except returns found element
	bool replace( const DataType & newElement ); // replaces element at current position 
											   // in list with newElement; returns false if
											  // there is no current position (no list 
											// modification occurs); returns true otherwise 
	bool remove( DataType & element );    // returns true if element is found
										  // returns false if element is not found
										  // if found, element is set to found element;
										  // no current position after use
	bool isEmpty( ) const;				  // returns true if linked list is empty
										  // returns false otherwise; current position
										  // unchanged
	void makeEmpty( );					  // no current position
private:
	Node<DataType> *start;
	Node<DataType> *current;			  // points to node at current position	
	inline void deepCopy( const LinkedList<DataType> & original );
};











// LinkedList.cpp -- function definitions for the linked list data structure



template <class DataType>
LinkedList<DataType>::LinkedList( )
{
	start = current = NULL;
}

template <class DataType>
LinkedList<DataType>::LinkedList( const LinkedList<DataType> & aplist )
{
	deepCopy( aplist );
}

template <class DataType>
LinkedList<DataType>::~LinkedList( )
{
	makeEmpty( );
}

template <class DataType>
LinkedList<DataType> & LinkedList<DataType>::operator =( const LinkedList<DataType> & rlist )
{
	if ( this == &rlist )
		return *this;
	makeEmpty( );
	deepCopy( rlist );
	return *this;
}

// inserts at the beginning of the linked list
// no current position after use		
template <class DataType>
void LinkedList<DataType>::insert( const DataType & element )
{
	current = NULL;
	Node<DataType> *newNode = new Node<DataType>;
	newNode->info = element;
	newNode->next = start;
	start = newNode;
}	

// returns first element of list in listEl and current position is set to this element; 
// if list is empty, returns false and there is no current position; 
// otherwise, returns true
template <class DataType>
bool LinkedList<DataType>::first( DataType & listEl )
{
	if ( start == NULL ) 
		return false;

	current = start;
	listEl = start->info;
	return true;
}

// retrieves the next element of a linked list beyond the last element that was retrieved
// by first or getNext functions and returns it in listEl;
// current position is set to this element.
// if no element exists at this position, getNext returns false and there is no 
// current position; returns true otherwise	
template <class DataType>
inline bool LinkedList<DataType>::getNext( DataType & listEl )				  
{
	if ( current == NULL ) 
		return false;
	if ( current->next == NULL ) {
		current = NULL;
		return false;
		}

	current = current->next;
	listEl = current->info;
	return true;
}


// returns true if element is found; returns false if element is not found
// if found, found element becomes current position in list; 
// if not found, there is no current position
template <class DataType>
bool LinkedList<DataType>::find( const DataType & element )
{
	DataType item;
	if ( !first( item ) )
		return false;
	do if ( item == element ) 
			return true;
	while ( getNext( item ) );

	return false;
}

// returns true if element is found; returns false if element is not found
// if found, found element becomes current position in list; 
// if not found, there is no current position
template <class DataType>
bool LinkedList<DataType>::retrieve( DataType & element )
{
	if ( !find( element ) )
		return false;
	element = current->info;
	return true;
}

// replaces element at current position in list with newElement; 
// returns false if there is no current position (no list modification occurs); 
// returns true otherwise 
template <class DataType>
bool LinkedList<DataType>::replace( const DataType & newElement ) 
{
	if ( current == NULL )
		return false;
	current->info = newElement;
	return true;
}

// returns true if element is found; returns false if element is not found
// if found, element is set to found element;
// no current position after use
template <class DataType>
bool LinkedList<DataType>::remove( DataType & element )
{
	current = NULL;
	if ( start == NULL )
		return false;
	Node<DataType> *ptr = start;
	if ( ptr->info == element ) {
		element = ptr->info;
		start = start->next;
		delete ptr;
		return true;
		}
	while ( ptr->next != NULL ) {
		if ( ptr->next->info == element ) {
			Node<DataType> *tempPtr = ptr->next;
			element = tempPtr->info;
			ptr->next = tempPtr->next;
			delete tempPtr;
			return true;
			}
		ptr = ptr->next;
		}

	return false;
}

template <class DataType>
bool LinkedList<DataType>::isEmpty( ) const				  
{
	return start == NULL;
}

template <class DataType>
void LinkedList<DataType>::makeEmpty( )					  
{
	while ( start != NULL ) {
		current = start;
		start = start->next;
		delete current;
	}

	current = NULL;
}

template <class DataType>
inline void LinkedList<DataType>::deepCopy( const LinkedList<DataType> & original )
{
	start = current = NULL;
	if ( original.start == NULL )
		return;
	Node<DataType> *copyptr = start = new Node<DataType>;
	Node<DataType> *originalptr = original.start;
	copyptr->info = originalptr->info;
	if ( originalptr == original.current )
		current = copyptr;
	while ( originalptr->next != NULL ) {
		originalptr = originalptr->next;
		copyptr->next = new Node<DataType>;
		copyptr = copyptr->next;
		copyptr->info = originalptr->info;
		if ( originalptr == original.current )
			current = copyptr;
	}
	copyptr->next = NULL;
}




