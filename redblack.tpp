template<typename T, typename Compare>
RedBlackTree<T, Compare>::RedBlackTree()
{
	m_sentinel.color = BLACK;
	m_sentinel.parent_p = 0;
	m_sentinel.left_p = 0;
	m_sentinel.right_p = 0;
	m_sentinel_p = &m_sentinel;
	m_root_p = m_sentinel_p;
	m_root_p->parent_p = m_sentinel_p;
	m_root_p->left_p = m_sentinel_p;
	m_root_p->right_p = m_sentinel_p;
}

template<typename T, typename Compare>
RedBlackTree<T, Compare>::~RedBlackTree()
{
	while (m_root_p != m_sentinel_p) {
		TreeDelete(m_root_p, 0);
	}
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::LeftRotate(TNODE<T> *target_p)
{
	m_sentinel_p->parent_p = target_p;

	TNODE<T> *y_p = target_p->right_p;

	target_p->right_p = y_p->left_p;

	if (y_p->left_p != m_sentinel_p)
		y_p->left_p->parent_p = target_p;

	y_p->parent_p = target_p->parent_p;

	if (target_p->parent_p == m_sentinel_p) {
		m_root_p = y_p;
	} else if (target_p == target_p->parent_p->left_p) {
		target_p->parent_p->left_p = y_p;
	} else {
		target_p->parent_p->right_p = y_p;
	}

	y_p->left_p = target_p;
	target_p->parent_p = y_p;
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::RightRotate(TNODE<T> *target_p)
{
	m_sentinel_p->parent_p = target_p;

	TNODE<T> *x_p = target_p->left_p;

	target_p->left_p = x_p->right_p;

	if (x_p->right_p != m_sentinel_p)
		x_p->right_p->parent_p = target_p;

	x_p->parent_p = target_p->parent_p;

	if (target_p->parent_p == m_sentinel_p) {
		m_root_p = x_p;
	} else if (target_p == target_p->parent_p->right_p) {
		target_p->parent_p->right_p = x_p;
	} else {
		target_p->parent_p->left_p = x_p;
	}

	x_p->right_p = target_p;
	target_p->parent_p = x_p;
}

template<typename T, typename Compare>
int RedBlackTree<T, Compare>::TreeInsert(TNODE<T> *target_p)
{
	TNODE<T> *y_p = m_sentinel_p, *trv_p = m_root_p;
	m_sentinel_p->parent_p = m_sentinel_p;
	int ret;

	while (trv_p != m_sentinel_p) {
		y_p = trv_p;
		ret = cmp_(target_p->fn, trv_p->fn) ? -1 : (cmp_(trv_p->fn, target_p->fn) ? 1 : 0);
		if (ret == -1) {
			trv_p = trv_p->left_p;
		} else if (ret == 1) {
			trv_p = trv_p->right_p;
		} else {
			return 0;
		}
	}

	target_p->parent_p = y_p;
	if (y_p == m_sentinel_p) {
		m_root_p = target_p;
	} else if (cmp_(target_p->fn, y_p->fn)) {
		y_p->left_p = target_p;
	} else {
		y_p->right_p = target_p;
	}
	return 1;
}

template<typename T, typename Compare>
int RedBlackTree<T, Compare>::Insert(const T &value)
{
	TNODE<T> *target_p = new TNODE<T>, *temp_p = m_sentinel_p;

	target_p->left_p = m_sentinel_p;
	target_p->right_p = m_sentinel_p;
	target_p->parent_p = m_sentinel_p;
	target_p->fn = value;

	m_sentinel_p->parent_p = target_p;

	if (!TreeInsert(target_p)) {
		delete target_p;
		return 0;
	}
	m_sentinel_p->parent_p = target_p;

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
}

template<typename T, typename Compare>
TNODE<T> *RedBlackTree<T, Compare>::TreeMinimum(TNODE<T> *target_p) const
{
	while (target_p->left_p != m_sentinel_p) {
		target_p = target_p->left_p;
	}

	return target_p;
}

template<typename T, typename Compare>
const T *RedBlackTree<T, Compare>::Minimum() const
{
	if (m_root_p == m_sentinel_p)
		return 0;

	return &TreeMinimum(m_root_p)->fn;
}

template<typename T, typename Compare>
TNODE<T> *RedBlackTree<T, Compare>::TreeMaximum(TNODE<T> *target_p) const
{
	if (m_root_p == m_sentinel_p)
		return 0;

	while (target_p->right_p != m_sentinel_p) {
		target_p = target_p->right_p;
	}

	return target_p;
}

template<typename T, typename Compare>
bool RedBlackTree<T, Compare>::RemoveMaximum(T *removed_p)
{
	TNODE<T> *node_p = TreeMaximum(m_root_p);
	if (node_p == 0)
		return false;

	return TreeDelete(node_p, removed_p);
}

template<typename T, typename Compare>
const T *RedBlackTree<T, Compare>::Maximum() const
{
	TNODE<T> *target_p = TreeMaximum(m_root_p);
	return target_p ? &target_p->fn : 0;
}

template<typename T, typename Compare>
TNODE<T> *RedBlackTree<T, Compare>::TreeSuccessor(TNODE<T> *target_p)
{
	TNODE<T> *trv_p;

	if (target_p == m_sentinel_p)
		return m_sentinel_p;

	if (target_p->right_p != m_sentinel_p)
		return TreeMinimum(target_p->right_p);

	trv_p = target_p->parent_p;
	while (trv_p != m_sentinel_p && target_p == trv_p->right_p) {
		target_p = trv_p;
		trv_p = trv_p->parent_p;
	}

	return trv_p;
}

template<typename T, typename Compare>
TNODE<T> *RedBlackTree<T, Compare>::Search(const T &value)
{
	TNODE<T> *trv_p = m_root_p;

	while (trv_p != m_sentinel_p) {
		if (cmp_(value, trv_p->fn)) {
			trv_p = trv_p->left_p;
		} else if (cmp_(trv_p->fn, value)) {
			trv_p = trv_p->right_p;
		} else {
			return trv_p;
		}
	}

	return 0;
}

template<typename T, typename Compare>
const TNODE<T> *RedBlackTree<T, Compare>::Search(const T &value) const
{
	const TNODE<T> *trv_p = m_root_p;

	while (trv_p != m_sentinel_p) {
		if (cmp_(value, trv_p->fn)) {
			trv_p = trv_p->left_p;
		} else if (cmp_(trv_p->fn, value)) {
			trv_p = trv_p->right_p;
		} else {
			return trv_p;
		}
	}

	return 0;
}

template<typename T, typename Compare>
const T *RedBlackTree<T, Compare>::Lookup(const T &value) const
{
	const TNODE<T> *trv_p = Search(value);
	return trv_p == 0 ? 0 : &trv_p->fn;
}

template<typename T, typename Compare>
bool RedBlackTree<T, Compare>::Delete(const T &value, T *removed_p)
{
	TNODE<T> *target_p = Search(value);
	return target_p == 0 ? false : TreeDelete(target_p, removed_p);
}

template<typename T, typename Compare>
bool RedBlackTree<T, Compare>::TreeDelete(TNODE<T> *target_p, T *removed_p)
{
	TNODE<T> *y_p, *x_p;
	m_sentinel_p->parent_p = target_p;

	if (target_p == m_sentinel_p)
		return false;

	if (target_p->left_p == m_sentinel_p || target_p->right_p == m_sentinel_p) {
		y_p = target_p;
	} else {
		y_p = TreeSuccessor(target_p);
	}

	if (y_p->left_p != m_sentinel_p) {
		x_p = y_p->left_p;
	} else {
		x_p = y_p->right_p;
	}

	x_p->parent_p = y_p->parent_p;

	if (y_p->parent_p == m_sentinel_p) {
		m_root_p = x_p;
	} else if (y_p == y_p->parent_p->left_p) {
		y_p->parent_p->left_p = x_p;
	} else {
		y_p->parent_p->right_p = x_p;
	}

	if (removed_p) {
		*removed_p = target_p->fn;
	}

	if (y_p != target_p) {
		target_p->fn = y_p->fn;
	}

	if (y_p->color == BLACK) {
		DeleteFixup(x_p);
	}
	delete y_p;

	return true;
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::DeleteFixup(TNODE<T> *target_p)
{
	TNODE<T> *w_p;
	m_sentinel_p->parent_p = target_p;

	while (target_p != m_root_p && target_p->color == BLACK) {
		if (target_p == target_p->parent_p->left_p) {
			w_p = target_p->parent_p->right_p;
			m_sentinel_p->parent_p = w_p;

			if (w_p->color == RED) {
				w_p->color = BLACK;
				target_p->parent_p->color = RED;

				LeftRotate(target_p->parent_p);

				w_p = target_p->parent_p->right_p;
				m_sentinel_p->parent_p = w_p;
			}

			if (w_p->left_p->color == BLACK && w_p->right_p->color == BLACK) {
				w_p->color = RED;
				target_p = target_p->parent_p;
			} else if (w_p->right_p->color == BLACK) {
				w_p->left_p->color = BLACK;
				w_p->color = RED;

				RightRotate(w_p);

				w_p = target_p->parent_p->right_p;
				m_sentinel_p->parent_p = w_p;
			} else {
				w_p->color = target_p->parent_p->color;
				target_p->parent_p->color = BLACK;
				w_p->right_p->color = BLACK;

				LeftRotate(target_p->parent_p);

				target_p = m_root_p;
				m_sentinel_p->parent_p = target_p;
			}
		} else {
			w_p = target_p->parent_p->left_p;
			m_sentinel_p->parent_p = target_p;

			if (w_p->color == RED) {
				w_p->color = BLACK;
				target_p->parent_p->color = RED;

				RightRotate(target_p->parent_p);

				w_p = target_p->parent_p->left_p;
				m_sentinel_p->parent_p = w_p;
			}

			if (w_p->right_p->color == BLACK && w_p->left_p->color == BLACK) {
				w_p->color = RED;
				target_p = target_p->parent_p;
			} else if (w_p->left_p->color == BLACK) {
				w_p->right_p->color = BLACK;
				w_p->color = RED;

				LeftRotate(w_p);

				w_p = target_p->parent_p->left_p;
				m_sentinel_p->parent_p = w_p;
			} else {
				w_p->color = target_p->parent_p->color;
				target_p->parent_p->color = BLACK;
				w_p->left_p->color = BLACK;

				RightRotate(target_p->parent_p);

				target_p = m_root_p;
				m_sentinel_p->parent_p = target_p;
			}
		}
	}

	target_p->color = BLACK;
}

template<typename T, typename Compare>
int RedBlackTree<T, Compare>::NodeCount(TNODE<T> *node_p, int level)
{
	int i = 1;

	if (node_p == m_sentinel_p)
		return 0;

	i += NodeCount(node_p->left_p, level + 1);
	i += NodeCount(node_p->right_p, level + 1);

	return i;
}

template<typename T, typename Compare>
int RedBlackTree<T, Compare>::NodeCount()
{
	int ret = 0;

	ret = NodeCount(m_root_p, 0);
	return ret;
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::InorderWalk(TNODE<T> *node_p, int level)
{
	if (node_p == m_sentinel_p)
		return;

	InorderWalk(node_p->left_p, level + 1);
	InorderWalk(node_p->right_p, level + 1);
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::DoWalk()
{
	InorderWalk(m_root_p, 0);
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::GetSubtreeDepths(int *left_tree, int *right_tree)
{
	GetSubtreeDepths(m_root_p, 0, left_tree, 0, right_tree);
}

template<typename T, typename Compare>
void RedBlackTree<T, Compare>::GetSubtreeDepths(
	TNODE<T> *node_p, int left_level, int *left_tree, int right_level, int *right_tree)
{
	if (node_p == m_sentinel_p)
		return;

	GetSubtreeDepths(node_p->left_p, left_level + 1, left_tree, 0, right_tree);
	GetSubtreeDepths(node_p->right_p, 0, left_tree, right_level + 1, right_tree);

	if (node_p->left_p == m_sentinel_p && node_p->right_p == m_sentinel_p) {
		if (left_level > *left_tree)
			*left_tree = left_level;
		if (right_level > *right_tree)
			*right_tree = right_level;
	}
}
