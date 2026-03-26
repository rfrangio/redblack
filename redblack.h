
#ifndef _BOBREDBLACK
#define _BOBREDBLACK

#include <functional>

enum NCOLOR {RED, BLACK};

template<typename R>
struct TNODE {
   		R fn;
    	TNODE<R> *left_p, *right_p, *parent_p;
    	NCOLOR color;
};

template<typename T, typename Compare = std::less<T>>
class RedBlackTree final {

private:

	TNODE<T> *m_root_p, *m_sentinel_p;
	TNODE<T> m_sentinel;
	Compare cmp_;

	inline void    LeftRotate(TNODE<T>*);
	inline void    RightRotate(TNODE<T>*);
	inline void    DeleteFixup(TNODE<T>*);
	inline int    TreeInsert(TNODE<T>*);
	TNODE<T>*  TreeMaximum(TNODE<T>*) const;
	TNODE<T>*  TreeMinimum(TNODE<T>*) const;
	inline TNODE<T>*  TreeSuccessor(TNODE<T>*);
	void    InorderWalk(TNODE<T>*, int);
	int 	NodeCount(TNODE<T>*, int);
	bool TreeDelete(TNODE<T>*, T*);
	void GetSubtreeDepths(TNODE<T>*, int left_level, int *left, int right_level, int *rigth);
	inline TNODE<T>* Search(const T&);
	inline const TNODE<T>* Search(const T&) const;

public:

	RedBlackTree();
	~RedBlackTree();
	RedBlackTree(const RedBlackTree &other) = delete;
	RedBlackTree& operator=(const RedBlackTree &other) = delete;     
	const T* Lookup(const T&) const;
	const T* Minimum() const;
	const T* Maximum() const;
	int      Insert(const T&);
	bool Delete(const T&, T* removed_p = 0);
	void      DoWalk();
	int		  NodeCount();
	void GetSubtreeDepths(int *left, int *right);
	bool RemoveMaximum(T* removed_p = 0);

};

#include "redblack.tpp"

#endif
