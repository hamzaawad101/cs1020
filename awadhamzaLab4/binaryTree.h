 
#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include<algorithm>
#include "node.h"
#include <fstream> 
#include "participant.h"
using std::max;
using std::cout;
using std::endl;
using std::ofstream;

// declaration for friend statement below
template<class T> class Position;

const int PREORDER = 1;
const int INORDER = 2;
const int POSTORDER = 3;

template<class T>
class BinarySearchTree {
	public:
		BinarySearchTree();
		BinarySearchTree( const BinarySearchTree& );
		
		// returns num nodes in tree
		int size() const { return numNodes; }
		
		// returns true if tree empty of real nodes
		bool empty() const { return numNodes == 0; }
		
		// superroot right pointer always points to real root node
		Position<T> root() const { return Position<T>( superRootPtr->rightPtr ); }
		
		void traverseAndPrint( const Position<T>& p, int type ) const;
		
		int depth( const Position<T>& ) const;
		
		int height( const Position<T>& ) const;
		
		Position<T> begin() const;
		void TraverseAndWrite( const Position<T>& root,ofstream& out ) const;
		ostream& write( ostream& outBin) const;
		
		// returns NULL iterator
		Position<T> end() const { return Position<T>( ); }
		
		Position<T> find( const T& ) const;
		
		Position<T> insert( const T& );
		
		bool erase( const T& );
		
		bool erase( const Position<T>& );
		
		virtual ~BinarySearchTree() { deleteUtility(superRootPtr); }
		
		Node<T>* copyTree( Node<T>* p, Node<T>* n );
		
		BinarySearchTree<T>& operator=( const BinarySearchTree& b );
		
		
		friend class Position<T>;
	private:
		Node<T>* superRootPtr;
		
		// number real nodes in tree, not including fake super
		// root and fake ends nodes
		int numNodes;
		
		void preorderTraverseAndPrint( const Position<T>& ) const; 
		void inorderTraverseAndPrint( const Position<T>& ) const;
		void postorderTraverseAndPrint( const Position<T>& ) const;
		
		// finds item in tree starting at position
		Position<T> findUtility( const T& item, const Position<T>& ) const;
		
		// inserts item into tree
		Position<T> insertUtility( const T& item );
		
		// deletes all nodes in the tree
		void deleteUtility( Node<T>* );
		
		// erases just one node from the tree at position p
		Position<T> eraseUtility( const Position<T>& p);
		
		// insert item data at position p
		void expandExternal( const T& item, Position<T> p);
		
		// remove node above fake leaf node at position p
		Position<T> removeAboveExternal( const Position<T>& p );
};

/* default ctor sets up an empty tree with two nodes:
* fake root whose right ptr points to fake end
*/
template<class T>
BinarySearchTree<T>::BinarySearchTree() {
	superRootPtr = new Node<T>();
	superRootPtr->rightPtr = new Node<T>();
	superRootPtr->rightPtr->parentPtr = superRootPtr;
	superRootPtr->leftPtr = NULL;
	numNodes = 0;
}

/* copy ctor creates another tree from original tree
 */
template<class T>
BinarySearchTree<T>::BinarySearchTree( const BinarySearchTree& b ){
	numNodes = b.numNodes;
	superRootPtr = new Node<T>();
	if( b.empty() == true ){
		superRootPtr->rightPtr = new Node<T>();
		superRootPtr->rightPtr->parentPtr = superRootPtr;
	}
	else { //there is a tree to copy 
		superRootPtr->rightPtr = copyTree( superRootPtr, b.superRootPtr->rightPtr );
	}
}

/* traverseAndPrint prints the data in tree either by pre, in, or post 
 * 	order based on what number type is
 */
template<class T>
void BinarySearchTree<T>::traverseAndPrint( const Position<T>& p, int type ) const {
	switch( type ){
		case PREORDER:
			preorderTraverseAndPrint( p );
			break;
		case INORDER:
			inorderTraverseAndPrint( p );
			break;
		case POSTORDER:
			postorderTraverseAndPrint( p );
			break;
	}
}

/* preorderTraverseAndPrint
 */
template<class T>
void BinarySearchTree<T>::preorderTraverseAndPrint( const Position<T>& root ) const {
	if( root.isInternal() ){
		cout << root.nodePtr->item;
		preorderTraverseAndPrint( root.nodePtr->leftPtr );
		preorderTraverseAndPrint( root.nodePtr->rightPtr );
	}
}

/* inorderTraverseAndPrint
 */ 
 template<class T>
 void BinarySearchTree<T>::inorderTraverseAndPrint( const Position<T>& root ) const{
	if( root.isInternal() ){
 		inorderTraverseAndPrint( root.nodePtr->leftPtr );
 		cout << root.nodePtr->item << " ";
 		inorderTraverseAndPrint( root.nodePtr->rightPtr );
	 }
 }
 
 /* postorderTraverseAndPrint
  */
  template<class T>
  void BinarySearchTree<T>::postorderTraverseAndPrint( const Position<T>& root ) const{
	if( root.isInternal() ){
 		postorderTraverseAndPrint( root.nodePtr->leftPtr );
 		postorderTraverseAndPrint( root.nodePtr->rightPtr );
 		cout << root.nodePtr->item << " ";
	 }
 }

/* depth returns distance from root to node at parameter
* position
* Parameter:
* p position to compute depth of
* Returns depth or -1 if position p is superroot
*/
template<class T>
int BinarySearchTree<T>::depth( const Position<T>& p ) const {
	if ( p.isSuperRoot()) return -1;
	if ( p.isRoot()) return 0;
	else {
		return 1+depth( p.parent() );
	}
}

/* height returns distance from node at parameter position to
* lowest leaf
* Parameter: position to computer height of
*/
template<class T>
int BinarySearchTree<T>::height( const Position<T>& p ) const {
	// if leaf
	if ( p.isExternal() ) return 0;
	int h = 0;
	// h = max of 0 and height of left subtree
	h = max( h, height( Position<T>( p.nodePtr->leftPtr )));
	// h = max of height of left subtree and
	// height of right subtree
	h = max( h, height( Position<T>( p.nodePtr->rightPtr )));
	return 1 + h;
}

/* begin: returns position iterator to first node on tree - the
leftmost
*/
template<class T>
Position<T> BinarySearchTree<T>::begin() const {
	if ( numNodes > 0 ) {
		Position<T> p = root();
		while (p.isInternal()) {
			p = p.left();
		}
		return p.parent();
	}
	else return Position<T>( superRootPtr );
}

/* finds a T object in tree
* Parameters: the object to find
* Pre-condition: class T has overloaded operator==
* Returns iterator to object, superroot iterator if tree
* is empty, fake leaf postion if not found
*/
template<class T>
Position<T> BinarySearchTree<T>::find( const T& item ) const {
	if ( numNodes > 0 ) {
		Position<T> v = findUtility( item, root() );
		return v;
	}
	else return Position<T>(superRootPtr);
}

/* findUtility: recursive utility find function
* Parameters:
* item to look for
* p position to start looking from
* Pre-condition: class T has overloaded operator== and
* operator<, tree not empty of real nodes
* Returns position iterator where found or NULL iterator
*/
template<class T>
Position<T> BinarySearchTree<T>::findUtility( const T& item, const Position<T>& p ) const {
	if( p.isExternal() ) return p;
	if( p.nodePtr->item == item ) return p; //p.nodePtr->item...p.getItem()
	if( item < p.nodePtr->item ){
		return findUtility( item, p.nodePtr->leftPtr ); //creating a new position from leftPtr
	}
	else{
		return findUtility( item, p.nodePtr->rightPtr ); //p.right()
	}
}

/* deleteUtility: deletes subroot passed to function
 * Parameters:  the subroot
 * Returns call to itself going left then right
 */
template<class T>
void BinarySearchTree<T>::deleteUtility( Node<T>* s ){
	if( s != NULL ){
		deleteUtility( s->leftPtr );
		deleteUtility( s->rightPtr );
		delete( s );
	}
}

/* expandExternal - inserts item by copying its data to
* position p and setting position's left and right ptrs
* to end nodes
* Parameters
* item to be inserted
* p fake end node where item will be inserted
* Precondition: p is an external node (a fake leaf) and
* class T has overloaded = operator
*/
template<class T>
void BinarySearchTree<T>::expandExternal( const T& item, Position<T> p ){
	Node<T>* left;
	Node<T>* right;
	left = new Node<T>();
	right = new Node<T>();
	p.nodePtr->leftPtr = left;
	p.nodePtr->rightPtr = right;
	left->parentPtr = p.nodePtr;
	right->parentPtr = p.nodePtr;
	p.nodePtr->item = item;
	numNodes++;
}

/* inserts object T in the binary tree
* Parameter: the object to insert
* Pre-condition: class T has overloaded operator<
* Returns iterator to newly inserted object or superRootPtr
* if item already in tree
*/
template<class T>
Position<T> BinarySearchTree<T>::insert( const T& item ) {
	// root() = superroot's right ptr
	Position<T> p = insertUtility( item );
	// return iterator to position where new node inserted
	return p;
}

/* insertUtility: inserts at position for new node
* Parameters: new node to insert
* Returns iterator to newly inserted object or to superRoot
* fake node if item already in tree
*/
template<class T>
Position<T> BinarySearchTree<T>::insertUtility( const T& item ){
	Position<T> foundPosition;
	foundPosition = findUtility( item, root() );
	if( foundPosition.isExternal() ){
		expandExternal( item, foundPosition );
		return foundPosition; //where item was inserted
	}
	else{
		return Position<T>( superRootPtr ); //item already in tree
		
	}
}

/* removeAboveExternal: removes internal node just above fake
leaf node pointed to by p. Decrements number of nodes
in tree.
Parameter
p leaf node of real node to delete
* Returns position iterator to sibling of node removed
*/
template<class T>
Position<T> BinarySearchTree<T>::removeAboveExternal( const Position<T>& p ){
	Node<T>* siblingPtr, *grandParentPtr, *w, *v;
	w = p.nodePtr;
	v = p.nodePtr->parentPtr;
	if( w == v->leftPtr ){
		siblingPtr = v->rightPtr;
	}
	else siblingPtr = v->leftPtr;
	if( v == superRootPtr->rightPtr ){
		superRootPtr->rightPtr = siblingPtr;
		siblingPtr->parentPtr = superRootPtr;
	}
	else{ //removing a leaf that isn't the actual root
		grandParentPtr = v->parentPtr;
		if( grandParentPtr->leftPtr == v ){
			grandParentPtr->leftPtr = siblingPtr;
		}
		else{
		 	grandParentPtr->rightPtr = siblingPtr;
		}
		siblingPtr->parentPtr = grandParentPtr;
	}
	delete(w);
	delete(v);
	numNodes--;
	return Position<T>( siblingPtr );
}

/* erase removes a node above Position p
* Precondition position p is a valid position in tree
* Returns true if successful
*/
template<class T>
bool BinarySearchTree<T>::erase( const Position<T>& p ) {
	// can't remove superroot or fake external node
	if ( !p.isSuperRoot() && !p.isExternal() ) {
		eraseUtility( p );
		return true;
	}
	else return false;
}
/* eraseUtility determines a leaf node to swap the node to delete
* (if necessary) then calls removeAboveExternal to remove the leaf or node with one subtree
* Parameter p node with key to delete
* Precondition position p is a valid position in tree
* Returns
*/
template<class T>
Position<T> BinarySearchTree<T>::eraseUtility( const Position<T>& p ){
	Position<T> w,u;
	if( p.left().isExternal() ){
		w = p.left();
	}
	else if( p.right().isExternal() ){
		w = p.right();
	}
	else { //two non-empty subtrees
		w = p.right();
		while( w.isInternal() ){
			w = w.left();
		}
		u = w.parent();
		p.nodePtr->item = u.nodePtr->item; //set p's data = u's data
	}
	return removeAboveExternal( w );
}

/* erase removes a node 
 */ 
template<class T>
bool BinarySearchTree<T>::erase( const T& item ) {
	Position<T> p = find( item );
	if( p.isInternal() ){
		erase( p ); 
		return true;
	}
	else{
	 	return false;
	}
}
/* operator= 
 */  
template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=( const BinarySearchTree& b ){
	deleteUtility( b );
	numNodes = b.numNodes;
	superRootPtr = new Node<T>();
	if( b.empty() == true ){
		superRootPtr->rightPtr = new Node<T>();
		superRootPtr->rightPtr->parentPtr = superRootPtr;
	}
	else {
		superRootPtr->rightPtr = copyTree( superRootPtr, b.superRootPtr->rightPtr );
	}
	return b; 
}
template<class T>
Node<T>* BinarySearchTree<T>::copyTree( Node<T>* p, Node<T>* n ){
	Node<T>* newNode;
	if( n != NULL ){
		newNode = new Node<T>(*n); 
		newNode->parentPtr = p; 
		newNode->leftPtr = copyTree( newNode, n->leftPtr );
		newNode->rightPtr = copyTree( newNode, n->rightPtr );
		return newNode;
	}
	else return NULL; 
}

template<class T>
void BinarySearchTree<T>::TraverseAndWrite( const Position<T>& root,ofstream& out ) const {
    if( root.isInternal() ){
        root.nodePtr->item.write(out);
        TraverseAndWrite( root.nodePtr->leftPtr, out );
        TraverseAndWrite( root.nodePtr->rightPtr, out );
    }
}

#endif