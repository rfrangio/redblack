#include <iostream>
#include "redblack.h"

template<typename T>
RedBlackTree<T>::RedBlackTree(int (*func_p) (T *, T *))
{
	m_sentinel.color = BLACK;
	m_sentinel.parent_p = 0;
	m_sentinel.left_p = 0;
	m_sentinel.right_p = 0;
	m_sentinel.fn_p = 0;
	m_sent_p = &m_sentinel;
	m_root_p = m_sent_p;
	m_root_p->parent_p = m_sent_p;
	m_root_p->left_p = m_sent_p;
	m_root_p->right_p = m_sent_p;
	cmp_p = func_p;

}

template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
	T              *fn_p;

	while (m_root_p != m_sent_p) {
		fn_p = TreeDelete(m_root_p);
		if (fn_p) {
			delete		fn_p;
		}
	}


}

template<typename T>
void RedBlackTree<T>::LeftRotate(TNODE<T> *target_p)
{

	m_sent_p->parent_p = target_p;

	TNODE<T> *y_p = target_p->right_p;


	target_p->right_p = y_p->left_p;

	if (y_p->left_p != m_sent_p)
		y_p->left_p->parent_p = target_p;

	y_p->parent_p = target_p->parent_p;

	if (target_p->parent_p == m_sent_p) {
		m_root_p = y_p;

	} else if (target_p == target_p->parent_p->left_p) {
		target_p->parent_p->left_p = y_p;
	} else {
		target_p->parent_p->right_p = y_p;
	}

	y_p->left_p = target_p;
	target_p->parent_p = y_p;

}

template<typename T>
void RedBlackTree<T>::RightRotate(TNODE<T> *target_p)
{
	m_sent_p->parent_p = target_p;

	TNODE<T> *x_p = target_p->left_p;


	target_p->left_p = x_p->right_p;

	if (x_p->right_p != m_sent_p)
		x_p->right_p->parent_p = target_p;

	x_p->parent_p = target_p->parent_p;

	if (target_p->parent_p == m_sent_p) {
		m_root_p = x_p;

	} else if (target_p == target_p->parent_p->right_p) {
		target_p->parent_p->right_p = x_p;
	} else {
		target_p->parent_p->left_p = x_p;
	}

	x_p->right_p = target_p;
	target_p->parent_p = x_p;

}

template<typename T>
int	RedBlackTree<T>::TreeInsert(TNODE<T> *target_p)
{
	TNODE<T> *y_p = m_sent_p, *trv_p = m_root_p;
	m_sent_p->parent_p = m_sent_p;
	int		ret;


	while (trv_p != m_sent_p) {
		y_p = trv_p;
		ret = cmp_p(target_p->fn_p, trv_p->fn_p);
		if (ret == -1) {
			trv_p = trv_p->left_p;
		} else if (ret == 1) {
			trv_p = trv_p->right_p;
		} else {
			return 0;
		}
	}

	target_p->parent_p = y_p;
	if (y_p == m_sent_p) {
		m_root_p = target_p;

	} else if (cmp_p(target_p->fn_p, y_p->fn_p) == -1) {
		y_p->left_p = target_p;
	} else {
		y_p->right_p = target_p;
	}
	return 1;
}


template<typename T>
int	RedBlackTree<T>::Insert(T * fn_p)
{

	TNODE<T> *target_p = new TNODE<T>, *temp_p = m_sent_p;


	target_p->left_p = m_sent_p;
	target_p->right_p = m_sent_p;
	target_p->parent_p = m_sent_p;

	target_p->fn_p = fn_p;

	m_sent_p->parent_p = target_p;

	if (!TreeInsert(target_p)) {
		delete		target_p;
//Error dup - std::cout << "Error\n";
		return 0;
	}
	m_sent_p->parent_p = target_p;

	target_p->color = RED;

	while (target_p != m_root_p && target_p->parent_p->color == RED) {

		if (target_p->parent_p == target_p->parent_p->parent_p->left_p) {

			temp_p = target_p->parent_p->parent_p->right_p;

			if (temp_p->color == RED) {
				target_p->parent_p->color = BLACK;
				temp_p->color = BLACK;
				target_p->parent_p->parent_p->color = RED;
				target_p = target_p->parent_p->parent_p;
			} else if (target_p == target_p->parent_p->right_p) {
				target_p = target_p->parent_p;
				LeftRotate(target_p);

			} else {
				target_p->parent_p->color = BLACK;
				target_p->parent_p->parent_p->color = RED;
				RightRotate(target_p->parent_p->parent_p);
			}

		} else {

			temp_p = target_p->parent_p->parent_p->left_p;

			if (temp_p->color == RED) {

				target_p->parent_p->color = BLACK;
				temp_p->color = BLACK;
				target_p->parent_p->parent_p->color = RED;
				target_p = target_p->parent_p->parent_p;
			} else if (target_p == target_p->parent_p->left_p) {
				target_p = target_p->parent_p;
				RightRotate(target_p);

			} else {
				target_p->parent_p->color = BLACK;
				target_p->parent_p->parent_p->color = RED;
				LeftRotate(target_p->parent_p->parent_p);
			}

		}
	}

	m_root_p->color = BLACK;
	return 1;
};

template<typename T>
TNODE<T> *RedBlackTree<T>::TreeMinimum(TNODE<T> *target_p)
{

	while (target_p->left_p != m_sent_p) {
		target_p = target_p->left_p;
	}

	return target_p;
}

template<typename T>
T* RedBlackTree<T>::Minimum()
{
	TNODE<T> *target_p = m_root_p;

	while (target_p->left_p != m_sent_p) {
		target_p = target_p->left_p;
	}

	return target_p->fn_p;
}

template<typename T>
TNODE<T> *RedBlackTree<T>::TreeMaximum(TNODE<T> *target_p)
{

	if (m_root_p == m_sent_p)
		return 0;

	while (target_p->right_p != m_sent_p) {
		target_p = target_p->right_p;
	}

	return target_p;
}

template<typename T>
T* RedBlackTree<T>::RemoveMaximum()
{
	TNODE<T> *node_p = TreeMaximum(m_root_p);
	if (node_p == 0)
		return 0;

	T	*fn_p = node_p->fn_p;

	TreeDelete(node_p);

	return fn_p;
}



template<typename T>
T * RedBlackTree<T>::Maximum()
{
	TNODE<T> *target_p = m_root_p;

	while (target_p->right_p != m_sent_p) {
		target_p = target_p->right_p;
	}

	return target_p->fn_p;
}

template<typename T>
TNODE<T> *RedBlackTree<T>::TreeSuccessor(TNODE<T> *target_p)
{
	TNODE<T> *trv_p;

	if (target_p != m_sent_p) {
		return TreeMinimum(target_p->right_p);
	}
	trv_p = target_p->parent_p;
	while (trv_p != m_sent_p && target_p == trv_p->right_p) {
		target_p = trv_p;
		trv_p = trv_p->parent_p;
	}

	return trv_p;
}



template<typename T>
TNODE<T> *RedBlackTree<T>::Search(T * fn_p)
{
	TNODE<T> *trv_p = m_root_p;

	while (trv_p != m_sent_p && cmp_p(fn_p, trv_p->fn_p) != 0) {
		if (cmp_p(fn_p, trv_p->fn_p) == -1) {
			trv_p = trv_p->left_p;
		} else {
			trv_p = trv_p->right_p;
		}
	}

	return trv_p == m_sent_p ? 0 : trv_p;
}

template<typename T>
T* RedBlackTree<T>::Delete(T * fn_p)
{
	TNODE<T> *target_p = Search(fn_p), *y_p, *x_p;
	T              *ret_p;


	if (target_p == 0)
		return 0;

	m_sent_p->parent_p = target_p;

	if (target_p->left_p == m_sent_p || target_p->right_p == m_sent_p) {
		y_p = target_p;
	} else {
		y_p = TreeSuccessor(target_p);
	}

	if (y_p->left_p != m_sent_p) {
		x_p = y_p->left_p;
	} else {
		x_p = y_p->right_p;
	}


	x_p->parent_p = y_p->parent_p;


	if (y_p->parent_p == m_sent_p) {
		m_root_p = x_p;

	} else if (y_p == y_p->parent_p->left_p) {
		y_p->parent_p->left_p = x_p;
	} else {
		y_p->parent_p->right_p = x_p;
	}

	if (y_p != target_p) {
		ret_p = target_p->fn_p;
		target_p->fn_p = y_p->fn_p;
	} else {
		ret_p = y_p->fn_p;
	}

	if (y_p->color == BLACK) {
		DeleteFixup(x_p);
	}
	delete		y_p;

	return ret_p;

}

template<typename T>
T* RedBlackTree<T>::TreeDelete(TNODE<T> *target_p)
{
	TNODE<T> *y_p, *x_p;
	T              *ret_p;
	m_sent_p->parent_p = target_p;

	if (target_p == m_sent_p)
		return 0;

	if (target_p->left_p == m_sent_p || target_p->right_p == m_sent_p) {
		y_p = target_p;
	} else {
		y_p = TreeSuccessor(target_p);
	}

	if (y_p->left_p != m_sent_p) {
		x_p = y_p->left_p;
	} else {
		x_p = y_p->right_p;
	}

	x_p->parent_p = y_p->parent_p;

	if (y_p->parent_p == m_sent_p) {
		m_root_p = x_p;

	} else if (y_p == y_p->parent_p->left_p) {
		y_p->parent_p->left_p = x_p;
	} else {
		y_p->parent_p->right_p = x_p;
	}

	if (y_p != target_p) {
		ret_p = target_p->fn_p;
		target_p->fn_p = y_p->fn_p;
	} else {
		ret_p = y_p->fn_p;
	}

	if (y_p->color == BLACK) {
		DeleteFixup(x_p);
	}
	delete		y_p;

	return ret_p;

}

template<typename T>
void RedBlackTree<T>::DeleteFixup(TNODE<T> *target_p)
{
	TNODE<T> *w_p;
	m_sent_p->parent_p = target_p;

	while (target_p != m_root_p && target_p->color == BLACK) {


		if (target_p == target_p->parent_p->left_p) {
			w_p = target_p->parent_p->right_p;
			m_sent_p->parent_p = w_p;

			if (w_p->color == RED) {
				w_p->color = BLACK;
				target_p->parent_p->color = RED;

				LeftRotate(target_p->parent_p);

				w_p = target_p->parent_p->right_p;
				m_sent_p->parent_p = w_p;
			}

			if (w_p->left_p->color == BLACK && w_p->right_p->color == BLACK) {
				w_p->color = RED;
				target_p = target_p->parent_p;
			} else if (w_p->right_p->color == BLACK) {
				w_p->left_p->color = BLACK;
				w_p->color = RED;

				RightRotate(w_p);

				w_p = target_p->parent_p->right_p;
				m_sent_p->parent_p = w_p;
			} else {

				w_p->color = target_p->parent_p->color;
				target_p->parent_p->color = BLACK;
				w_p->right_p->color = BLACK;

				LeftRotate(target_p->parent_p);

				target_p = m_root_p;
				m_sent_p->parent_p = target_p;
			}

		} else {

			w_p = target_p->parent_p->left_p;
			m_sent_p->parent_p = target_p;

			if (w_p->color == RED) {
				w_p->color = BLACK;
				target_p->parent_p->color = RED;

				RightRotate(target_p->parent_p);

				w_p = target_p->parent_p->left_p;
				m_sent_p->parent_p = w_p;

			}

			if (w_p->right_p->color == BLACK && w_p->left_p->color == BLACK) {
				w_p->color = RED;
				target_p = target_p->parent_p;
			} else if (w_p->left_p->color == BLACK) {
				w_p->right_p->color = BLACK;
				w_p->color = RED;

				LeftRotate(w_p);

				w_p = target_p->parent_p->left_p;
				m_sent_p->parent_p = w_p;
			} else {

				w_p->color = target_p->parent_p->color;
				target_p->parent_p->color = BLACK;
				w_p->left_p->color = BLACK;

				RightRotate(target_p->parent_p);

				target_p = m_root_p;
				m_sent_p->parent_p = target_p;
			}

		}

	}

	target_p->color = BLACK;

}

template<typename T>
int	RedBlackTree<T>::NodeCount(TNODE<T> *node_p, int level)
{
	int		i = 1;

	if (node_p == m_sent_p)
		return 0;

	i += NodeCount(node_p->left_p, level + 1);
	i += NodeCount(node_p->right_p, level + 1);

	return i;
}

template<typename T>
int	RedBlackTree<T>::NodeCount()
{
	int		ret = 0;

	ret = NodeCount(m_root_p, 0);
	return ret;

}


template<typename T>
void RedBlackTree<T>::InorderWalk(TNODE<T> *node_p, int level)
{
	if (node_p == m_sent_p)
		return;

	InorderWalk(node_p->left_p, level + 1);
	//std: :cout << "key = " << *(node_p->fn_p) << ", level " << level << " \n";
	InorderWalk(node_p->right_p, level + 1);
}

template<typename T>
void RedBlackTree<T>::DoWalk()
{

	InorderWalk(m_root_p, 0);

}

template<typename T>
void RedBlackTree<T>::GetSubtreeDepths(int *left_tree, int *right_tree)
{
	GetSubtreeDepths(m_root_p, 0, left_tree, 0, right_tree);
}

template<typename T>
void RedBlackTree<T>::GetSubtreeDepths(TNODE<T> *node_p, int left_level, int *left_tree, int right_level, int *right_tree)
{

	if (node_p == m_sent_p)
		return;

	GetSubtreeDepths(node_p->left_p, left_level + 1, left_tree, 0, right_tree);
	GetSubtreeDepths(node_p->right_p, 0, left_tree, right_level + 1, right_tree);

	if (node_p->left_p == m_sent_p && node_p->right_p == m_sent_p) {
		if (left_level > *left_tree)
			*left_tree = left_level;
		if (right_level > *right_tree)
			*right_tree = right_level;
	}
}

