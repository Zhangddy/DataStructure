#pragma once

template <class T>
class AVLTreeNode
{
public:
	AVLTreeNode(T data)
		: _data(data)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _bf(0)
	{ }

	T _data;
	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	int _bf;	// 该节点平衡因子
};

template <class T>
class AVLTree
{
public:
	AVLTree()
		: _pRoot(nullptr)
	{ }
	typedef AVLTreeNode<T> Node;
	bool insert(const T& data)
	{
		/*
		AVL树的插入过程可以分为两步：
		1. 按照二叉搜索树的方式插入新节点
		2. 调整节点的平衡因子
			• 新增节点的平衡因子是0, 新增节点的祖先平衡因子可能受影响
				1. 新增在parent的右子树, parent->bf + = 1
				2. 新增在parent的左子树, parent->bf - = 1
			• 通过cur的位置更新parent的平衡因子, 更新完成后
				1. 如果parent->bf == 1 / -1, 说明parent为根的子树的高度变了, 继续向上更新
				2. 如果parent->bf == 2 / -2, 说明parent为根的子树已经不平衡, 需要旋转处理
				3. 如果parent->bf == 0, 说明parent所在的子树原来高度是 1/-1,
				   现在把矮的补齐, parent所在的子树高度不变, 停止更新
		*/

		// 如果树内无节点
		if (_pRoot == nullptr)
		{
			_pRoot = new Node(data);
			return true;
		}
		// 1. 按照二叉搜索树的方式插入新节点
		Node* pCur = _pRoot;
		Node* parent = nullptr;
		while (pCur)
		{
			parent = pCur;
			if (data < pCur->_data)
			{
				pCur = pCur->_pLeft;
			}
			else if (data > pCur->_data)
			{
				pCur = pCur->_pRight;
			}
			else
			{
				// 插入相同节点, 返回失败
				return false;
			}
		}
		pCur = new Node(data);
		if (parent->_data < data)
		{
			parent->_pRight = pCur;
		}
		else
		{
			parent->_pLeft = pCur;
		}
		pCur->_pParent = parent;

		// 2. 调整节点的平衡因子
		while (parent != nullptr)
		{
			if (parent->_pLeft == pCur)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				pCur = parent;
				parent = pCur->_pParent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				if (parent->_bf == -2 && pCur->_bf == -1)
				{
					RotateR(parent);
				}
				else if (parent->_bf == 2 && pCur->_bf == 1)
				{
					RotateL(parent);
				}
				else if (parent->_bf == -2 && pCur->_bf == 1)
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && pCur->_bf == -1)
				{
					RotateRL(parent);
				}
				else
				{
					assert(false);
				}
				break;
			}
		}
		return true;
	}

	void RotateR(Node* parent)
	{
		Node* pSubL = parent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pSubL->_pRight = parent;
		Node* pParent = parent->_pParent;
		parent->_pParent = pSubL;

		if (pSubLR != nullptr)
		{
			pSubLR->_pParent = parent;
		}
		parent->_pLeft = pSubLR;

		if (parent == _pRoot)
		{
			_pRoot = pSubL;
			pSubL->_pParent = nullptr;
		}
		else
		{
			if (pParent->_pLeft == parent)
			{
				pParent->_pLeft = pSubL;
			}
			else
			{
				pParent->_pRight = pSubL;
			}
			pSubL->_pParent = pParent;
		}
		
		parent->_bf = pSubL->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		Node* pSubR = parent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pSubR->_pLeft = parent;
		Node* pParent = parent->_pParent;
		parent->_pParent = pSubR;

		parent->_pRight = pSubRL;
		if (pSubRL != nullptr)
		{
			pSubRL->_pParent = parent;
		}
		if (parent == _pRoot)
		{
			_pRoot = pSubR;
			pSubR->_pParent = nullptr;
		}
		else
		{
			if (pParent->_pRight == parent)
			{
				pParent->_pRight = pSubR;
			}
			else
			{
				pParent->_pLeft = pSubR;
			}
			pSubR->_pParent = pParent;
		}
		parent->_bf = pSubR->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* pSubL = parent->_pRight;
		Node* pSubLR = pSubR->_pLeft;
		int bf = pSubLR->_bf;

		RotateL(parent->_pLeft);
		RotateR(parent);

		if (bf == 1)
		{
			parent->_bf = 0;
			pSubL->_bf = 1;
			pSubLR->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 1;
			pSubL->_bf = 0;
			pSubLR->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			pSubL->_bf = 0;
			pSubLR->_bf = 0;
		}
	}

	void RotateRL(Node* parent)
	{
		Node* pSubR = parent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateR(parent->_pRight);
		RotateL(parent);

		if (bf == 1)
		{
			parent->_bf = -1;
			pSubR->_bf = 0;
			pSubRL->_bf = 0;
		}
		else if (bf == -1)
		{
			parent->_bf = 0;
			pSubR->_bf = 1;
			pSubRL->_bf = 0;
		}
		else
		{
			parent->_bf = 0;
			pSubR->_bf = 0;
			pSubRL->_bf = 0;
		}
	}

	int Height(Node* root)
	{
		if (root == nullptr)
		{
			return 0;
		}

		int leftHight = Height(root->_pLeft);
		int rightHight = Height(root->_pRight);

		return leftHight > rightHight ? leftHight + 1 : rightHight + 1;
	}

	bool dealIsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHight = Height(root->_pLeft);
		int rightHight = Height(root->_pRight);
		
		if (rightHight - leftHight != root->_bf)
		{
			cout << root->_bf << ": bf error!" << endl;
		}

		return abs(rightHight - leftHight) < 2
			&& dealIsBalance(root->_pLeft)
			&& dealIsBalance(root->_pRight);
	}

	bool IsBalance()
	{
		return dealIsBalance(_pRoot);
	}

private:
	AVLTreeNode<T>* _pRoot;
};


