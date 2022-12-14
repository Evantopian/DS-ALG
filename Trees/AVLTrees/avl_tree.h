#ifndef AVL_TREE_H
#define AVL_TREE_H

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
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:

    // The Big Five
    AvlTree() : root{nullptr} {}

    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Deep copy.
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }


    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root, 0)->element;
    }


    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }


    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }


    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }


    /**
	 * Print the tree contents in sorted order.
	 */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }


    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }


    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }


    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }


    /**
     * Finds or searches for value of x.
     * Returns the element matching the recognition sequence of x (if found).
     * Returns nullptr if no element was found.
     */
    Comparable &find(const Comparable &x)
    {
        int count = 0;
        return *find(x.get_reco_seq(), root, count);
    }


    /**
     * Finds or searches for value of x.
     * Returns the amount of recursive calls to find x.
     * Returns -(amount of calls) if x is not found.
     */
    int find(string &x)
    {
        int count = 0;
        find(x, root, count);
        return count;
    }


    /**
     * Remove x from the tree. 
     * X is not removed if nothing is found.
     * Returns the amount of recursive calls given x.
     */
    int remove(const Comparable &x)
    {
        int count = 0;
        remove(x, root, count);
        return count;
    }


    // Accessor methods
    double getHeight()
    {
        return Height(root);
    }


    // returns the average depth 
    // (sum of n nodes depths in tree)/the size of the tree
    double get_avg_depth()
    {
        return sum_depths(root)/tree_size_;
    }


    double GetNumberofNodes()
    {
        return NumberOfNodes(root);
    }


    size_t get_size()
    {
        return tree_size_;
    }


    int get_rev_calls()
    {
        return remove_calls_;
    }


private:
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };


    AvlNode *root;
    // size of the tree, updates with each successful insert and remove
    size_t tree_size_ = 0; 
    // number of total successful remove() calls.
    int remove_calls_ = 0;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, nullptr, nullptr};
            tree_size_++;
        }
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            t->element.Merge(x);

        balance(t);
    }


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{std::move(x), nullptr, nullptr};
            tree_size_++;
        }
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
            t->element.Merge(x);

        balance(t);
    }


	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
     * Each recursive call increments count.
	 */
    void remove(const Comparable &x, AvlNode *&t, int &count)
    {
        if (t == nullptr)
            return; 
        if (x < t->element)
        {
            count++;
            remove(x, t->left, count);
        }
        else if (t->element < x)
        {
            count++;
            remove(x, t->right, count);
        }
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            count++;
            t->element = findMin(t->right, count)->element;
            remove(t->element, t->right, count);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            tree_size_--;
            remove_calls_++;
        }
        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;


    // Assume t is balanced or within one of being balanced
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else
        {
            if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
            {
                if (height(t->right->right) >= height(t->right->left))
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }


    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t, int &count) const
    {
        count++;
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;
        return findMin(t->left, count);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode *findMax(AvlNode *t) const
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * count is the number of recursiion calls that the function uses.
     */

    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
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
    void makeEmpty(AvlNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AvlNode *t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            cout << t->element;
            printTree(t->right);
        }
    }


	// Avl manipulations

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }


    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }


    /**
     * Internal method to find if an element is in the tree.
     * x is item to search for.
     * t is the node that roots the subtree.
     * count is the number of recursive calls that the function uses.
     */
    Comparable *find(const string &x, AvlNode *t, int &count)
    {
        if (t == nullptr)
        {
            count *= -1;
            return nullptr;
        }
        else if (x < t->element.get_reco_seq())
        {
            count++;
            return find(x, t->left, count);
        }
        else if (t->element.get_reco_seq() < x)
        {
            count++;
            return find(x, t->right, count);
        }
        else
            return &t->element; // Match
    }


    /**
     * Internal method to sum the depths of each node.
     * t is the node that roots the subtree.
     * traverses left and right of the tree while decrementing 
     * the total depth count of tree to "sum" the depth of the tree.
     */
    double sum_depths(AvlNode *&t)
    {
        if (t == nullptr)
            return 0;
        else
            return sum_depths(t->left) + sum_depths(t->right) + (count_nodes(t) - 1);
    }

    
    // Method for reutnring the total number of nodes in the tree.
    double count_nodes(AvlNode *&t)
    {
        if (t == nullptr)
            return 0;
        else
            return count_nodes(t->left) + count_nodes(t->right) + 1;
    }

    // Rotation Stuff

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif
