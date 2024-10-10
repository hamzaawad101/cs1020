#ifndef NODE_H
#define NODE_H
 
template<class T> class BinarySearchTree; // declaration for friend statement below
template<class T> class Position; // declaration for friend statement below

template<class T>
class Node {
	public:
		Node(); // default constuctor
		// constructor that takes node’s dat
		Node( const T& );
		// copy constructor.
		Node( const Node<T>& );
		virtual ~Node<T>() {} // destructor
		
		void setItem( const T& );
		T getItem() const { return item; }
		
		Node<T>& operator=( const Node<T>& );
		
		friend class BinarySearchTree<T>;
		friend class Position<T>; // Position is an iterator class
	private:
		Node<T>* leftPtr;
		Node<T>* rightPtr;
		Node<T>* parentPtr;
		T item;
};

/* default constructor sets pointers to NULL
*/
template<class T>
Node<T>::Node(){
	leftPtr = rightPtr = parentPtr = NULL;
	item =T();
}

/* copy constructor. Creates a node from another node.
	*/
template<class T>
Node<T>::Node( const Node<T>& n ) {
	leftPtr = rightPtr = parentPtr = NULL;
	*this = n; 	
}

/* 1-arg ctor that creates a node from an item type in the
	node. Sets left, right, and parent pointers to NULL
	* Precondition: class T has overloaded operator= that
	performs deep copy if T dynamically allocates memory
	*/
template<class T>
Node<T>::Node( const T& n ) {
	leftPtr = NULL;
	rightPtr = NULL;
	parentPtr = NULL;
	item = n.item;
}

/* setItem sets the item data values in the node
Parameter
i the item
Pre-condition: T has defined operator=
Returns: nothing
*/
template<class T>
void Node<T>::setItem( const T& i ) {
	this->item = i;
}

/* operator= sets this' node’s item values to n’s item values
and this' pointers to NULL
Parameter
n the source node to copy from
Pre-condition: T has defined operator=
Returns: a reference to the destination node copied to
*/
template<class T>
Node<T>& Node<T>::operator=( const Node<T>& n ) {
	leftPtr = rightPtr = parentPtr = NULL;
	item = n.item;
	return *this; 	
}

#endif