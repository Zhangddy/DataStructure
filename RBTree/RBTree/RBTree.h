#pragma once

enum Colour
{
	BLACK,
	RED,
};

template <class T>
struct RBTreeNode
{
	RBTreeNode<T>* _left;
	RBTreeNode<T>* _right;
	RBTreeNode<T>* _parent;

	T _data;
	Colour _col;
};

template <class K, class V>
class RBTree
{
	typedef RBTreeNode<pair<K, V>> Node;
public:

};
