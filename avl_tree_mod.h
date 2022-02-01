#ifndef AVL_TREE_MOD_H
#define AVL_TREE_MOD_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( ) --> Return smallest item
// Comparable findMax( ) --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
int removes=0;
public:
    AvlTree( ) : root{ nullptr }
      { }
  
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
  
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
      
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
      
        return *this;
    }
  
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
   
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const {
        return contains( x, root );
    }


    /*****************************************************/
    // START part 2:

    void search( const Comparable & x ) {
        search( x, root );//call another search function
    }
    int NodesCount() {
        return NodesCount(root);//return itself
    }
    float PathsCount() {
        float Tracker = 0;//declare pathtracker for tracking
        return PathsCount(root, Tracker);//return itself
    }
    bool contains( const Comparable & x, float &recursionCalls) {
        return contains( x, root, recursionCalls);//return another contain function
    }
    void remove(const Comparable & x, float &recursionCalls, bool &removedNode) {
        remove(x, root, recursionCalls, removedNode);//call another remove function
    }

    //END part 2

        // Functions made for the assignment
        const Comparable getNode( const Comparable& n){ // Get nodes from root to n
            return Noder( n, root );
        }

        int totalNodes()
        { 
            return NodesCount(root);    
        }
        double totalDepth()
        { 
            return gettotalDepth(root,0); 
        }
        double find( const Comparable & x ) 
        { 
            return find( x, root, 0 ); 
        }
        int delete_calls()
        { 
            return deletecalls; 
        }

        bool String( string x, Comparable *c)
        {
            return String(x, root, c);
        }
            
        bool String( string x){
            Comparable c;
        bool value = String(x, root, &c);
        //Comparable *temp = &c;
        //delete temp;
        return value;
    }
    int delete_calls(const Comparable & x){
        return delete_calls(x, root, 1);
    }




private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
      
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;
    int deletecalls = 0;//create a delete_calls

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            t->element.Merge(x);
      
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            t->element.Merge(x);
      
        balance( t );
    }
   

  
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
      
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
              
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }
  
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }


    /*****************************************************/
    // start part 2

    // Print the enzyme and recognition sequence that matches
    void search( const Comparable & x, AvlNode * & t ) const
    {
        if( x < t->element )//if x is less than t element
            return search( x, t->left );//t return to left 
        else if( t->element<x )//if not, x is bigger than t element
            return search( x, t->right );//t return right
        else {
            t->element.printenzyme_acronyms_();    // if not, it match and print
        }
    }

    // Get the number of Nodes in the tree
    int NodesCount (AvlNode *t) const {
        if (t == nullptr) {//if t is nullpointer
            return 0;//return nothing
        }
        else {//if not
            return 1 + NodesCount(t->left) + NodesCount(t->right);//it return the number 1 plus number of numbers of left and right node.
        }
    }

    // get the number of paths in tree
    float PathsCount (AvlNode *t, float pathsTracker) const {
        if (t == nullptr) {//if t is nullpointer
            return 0;//return nothing
        }
        else {//if not
            return pathsTracker + PathsCount(t->left, pathsTracker + 1) + PathsCount(t->right, pathsTracker + 1);//it return the parameter plus the numbers of left and right path
        }
    }

    // Search whether the SequenceMap object is in the tree or not,
    // Also updates the total number of recursion calls
    bool contains( const Comparable & x, AvlNode *t, float &recursionCalls) {
        if( t == nullptr )// if t is nullpointer
            return false;//it return not
        else if( x < t->element ) {//if not, x is less than t of elemen
            recursionCalls++;//the recursion call plus
            return contains( x, t->left, recursionCalls);//return to itself and left side
        }
        else if( t->element < x ) {//if not, x is larger than x
            recursionCalls++;//the recursioncall plus
            return contains( x, t->right, recursionCalls);//return to itself and right side
        }
        else
            return true;    // return yes
    }
  
    // Remove the node that matches this node
    // Also renew the total number of recursion calls
    void remove( const Comparable & x, AvlNode * & t, float &recursionCalls, bool &removedNode)
    {
        if( t == nullptr ){//if t is nullpointer
            return;//it only return
        }
        if( x < t->element ) {//if not and x less than t
            recursionCalls++;// recursioncall plus
            remove( x, t->left, recursionCalls, removedNode);//it return to itself and t to left side
        }
        else if( t->element < x ) {//if x is larger than t
            recursionCalls++;//recursioncall plus
            remove( x, t->right, recursionCalls, removedNode);//it return to itself and t to right side
        }
        else if( t->left != nullptr && t->right != nullptr ) // if two children are not nullpointer
        {
            t->element = findMin( t->right )->element;//assign findmin function to t
            recursionCalls++;//recursioncall plus
            remove( t->element, t->right, recursionCalls, removedNode);//return itself and t to right side
        }
        else//if not
        {
            removedNode = true;//removed node is yes
            AvlNode *oldNode = t;//create a previous node that assign t 
            t = ( t->left != nullptr ) ? t->left : t->right;//when t assign to the function t not on left side, if yes, it go to left and if not, it go to right
            delete oldNode;//delete the previous node
        }
      
        balance( t );//t assign to balance function
    }

    
    const Comparable Noder( const Comparable& x, AvlNode* t ){ // look like to contain() but returns Comparable
            if( t == nullptr ){ return Comparable(); }
            else if( x < t->element )
                return Nodeer( x, t->left );
            else if( t->element < x )
                return Noder( x, t->right );
            else{ return t->element; }
        }
    double find( const Comparable & x, AvlNode *t, int totalCalls ) {
            totalCalls++;//totalcalls plus one
            if( t == nullptr )//if t is nullpointer
                return 1;//it means that not run successful
            else if( x < t->element )//if not, x is less than t
                return find( x, t->left, totalCalls );//it return to itself and t to left side
            else if( t->element < x )//if not, x is large than t
                return find( x, t->right, totalCalls );//it return to itself and t to right side
            return totalCalls;    // return to the total calls
        }
    double gettotalDepth( AvlNode* t, int counter){ // internal path length
            if( t == nullptr ){ return 0; }//if t is nullpointer, it will return nothing
            else return ( counter + ( gettotalDepth( ( t-> left),counter + 1) ) + gettotalDepth( ( t-> right),counter + 1) );//if not, it return it self of both side
        }
    bool String( const string x, AvlNode *t, Comparable *c ) const
    {
        if( t == nullptr )//if t is nullpointer
            return false;//return false(stop)
        else if( x < t->element.getRecognitionSequence() )//if not, x is less than t
            return String( x, t->left, c );//return itself and t to left side
        else if( t->element.getRecognitionSequence() < x )//if not, x is large than t
            return String( x, t->right, c );//return itself and t to right side
        else{
            *c = t->element;//t is assign to the pointer 
            return true;    // it will get the result
        }
    }
   int delete_calls( const Comparable & x, AvlNode * & t, int calls )
    {
        calls++;//call plus
        if( t == nullptr )//if t is a nullpointer
            return calls;   // return to call  
        if( x < t->element )//if x is less than t
            return delete_calls( x, t->left, calls );//return itself and t to left
        else if( t->element < x )//if not, x is large than t
            return delete_calls( x, t->right, calls );//return to itself and t to right
        else if( t->left != nullptr && t->right != nullptr ) // if not, two children are not pointer
        {
            t->element = findMin( t->right )->element;//findmin fucntion assign to t
            return delete_calls( t->element, t->right, calls );//remove to itself and t to right
        }
        else//if not
        {
            removes++;//remove plus
            AvlNode *oldNode = t;//t assign to create the old node
            t = ( t->left != nullptr ) ? t->left : t->right;//if the function t to left side is not a nullpointer assign to t,yes, it will go to left side and no, it will go to right side.
            delete oldNode;//delete the pointer
        }
      
        balance( t );//t to balance function
        return calls;//return to calls
    }


};

#endif
