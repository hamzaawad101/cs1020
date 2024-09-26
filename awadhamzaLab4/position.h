
#ifndef POSITION_H
#define POSITION_H

template<class T> class BinarySearchTree; // declaration for friend statement below

template<class T>
class Position {
	public:
		Node<T>& operator*() { return *nodePtr; }
		Position parent() const {
		return Position<T>( this->nodePtr->parentPtr ); }
		Position left() const {
		return Position<T>( nodePtr->leftPtr ); }
		Position right() const {
		return Position<T>( nodePtr->rightPtr ); }
		bool isRoot( ) const {
		// does this iterator point to real root?
		return this->nodePtr->parentPtr->parentPtr == NULL; }
		bool isSuperRoot() const{
		// does this iterator point to fake superroot?
		return this->nodePtr->parentPtr == NULL; }
		bool isExternal() const {
		// is it a fake end node?
		return this->nodePtr->leftPtr == NULL &&
		this->nodePtr->rightPtr == NULL; }
		bool isInternal() const { return !(isExternal() ); }
		bool operator==( const Position& p ) {
		return this->nodePtr == p.nodePtr; }
		bool operator!=( const Position& p ) {
		return this->nodePtr != p.nodePtr; }
		Position& operator++( ); // inorder traversal
		T getItem() { return nodePtr->item; }
		friend class BinarySearchTree<T>;
	private:
		// only friends like BST can create positions from its nodes
		Position(): nodePtr(NULL) { }
		Position( Node<T>* );
		Node<T>* nodePtr;
};

/*copy constructor set positions nodePtr to what parameters node is
 */
 template<class T>
 Position<T>::Position( Node<T>* n ){
 	nodePtr = n; //n is the nodePtr
}

/* overloaded ++ returns an iterator that points to the next
* node in the tree, in-order traversal.
* Returns Position with NULL nodePtr if get to end of
* the tree in an in-order traversal
* Precondition: class T has overloaded operator<
*/
template<class T>
Position<T>& Position<T>::operator++( ){
	Position w = right();
	if( w.isInternal() ){	//w is not a fake leaf
		do{
			*this = w.nodePtr;
			w = w.left();
		}while( w.isInternal() );
	}
	else{
		w = parent();
		while( w.nodePtr != NULL && *this == w.right() ){
			*this = w;
			w = w.parent();
		}
		*this = w;
	}
	return *this;
}

#endif