
#ifndef _BOBREDBLACK
#define _BOBREDBLACK

#include <time.h>


enum NCOLOR {RED, BLACK};

template<typename R>
struct TNODE {
   		R *fn_p;
    	TNODE<R> *left_p, *right_p, *parent_p;
    	NCOLOR color;
	};

template<typename T>
class RedBlackTree final {

	TNODE<T> *m_root_p, *m_sent_p;
	TNODE<T> m_sentinel;
	int (*cmp_p)(T*, T*);

	inline void    LeftRotate(TNODE<T>*);
	inline void    RightRotate(TNODE<T>*);
	inline void    DeleteFixup(TNODE<T>*);
	inline int    TreeInsert(TNODE<T>*);
	TNODE<T>*  TreeMaximum(TNODE<T>*);
	TNODE<T>*  TreeMinimum(TNODE<T>*);
	inline TNODE<T>*  TreeSuccessor(TNODE<T>*);
	void    InorderWalk(TNODE<T>*, int);
	T* TreeDelete(TNODE<T>*);

public:

	RedBlackTree(int (*cmp_p)(T*, T*));
	~RedBlackTree();
	RedBlackTree(const RedBlackTree &other) = delete;
	RedBlackTree& operator=(const RedBlackTree &other) = delete;     
	inline TNODE<T>* Search(T*);
	T* Minimum();
	T* Maximum();
	int      Insert(T*);
	T* Delete(T*);
	void      DoWalk();
	T* RemoveMaximum();

};

#endif


