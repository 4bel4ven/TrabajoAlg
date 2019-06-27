#pragma once
#include <functional>
#include <algorithm>

template <typename T, typename R = T>
class AVLTree {

	struct Node {
		T     e;
		Node* l;
		Node* r;
		int   h;
		std::vector<int> posi;

		Node(T e, int pos) : e(e), l(nullptr), r(nullptr), h(0) { posi.push_back(pos); }

		static int height(Node* n) {
			return n == nullptr ? -1 : n->h;
		}

		void updateH() {
			h = std::max(Node::height(l), Node::height(r)) + 1;
		}

		void set_pos(int pos,Node* n) {
			n->posi.push_back(pos);
		}
	};

	Node* root;
	int length;
	std::function<R(T)>  key;

	void destroy(Node* n) {
		if (n != nullptr) {
			destroy(n->l);
			destroy(n->r);
			delete n;
		}
	}
	void rotAB(Node*& n) {
		Node* aux = n->l;
		n->l = aux->r;
		n->updateH();
		aux->r = n;
		n = aux;
		n->updateH();
	}
	void rotBA(Node*& n) {
		Node* aux = n->r;
		n->r = aux->l;
		n->updateH();
		aux->l = n;
		n = aux;
		n->updateH();
	}
	void balance(Node*& n) {
		int delta = Node::height(n->l) - Node::height(n->r);
		if (delta < -1) {
			if (Node::height(n->r->l) > Node::height(n->r->r)) {
				rotAB(n->r);
			}
			rotBA(n);
		}
		else if (delta > 1) {
			if (Node::height(n->l->r) > Node::height(n->l->l)) {
				rotBA(n->l);
			}
			rotAB(n);
		}
	}
	void add(Node*& n, T e, int pos) {
		if (n == nullptr) {
			n = new Node(e,pos);
			return;
		}
		else if (key(e) < key(n->e)) {
			add(n->l, e,pos);
		}
		else if (key(e) > key(n->e)){
			add(n->r, e,pos);
		}
		else if (key(e) == key(n->e)) {
			n->set_pos(pos,n);
			goto step1;
		}
		balance(n);
		step1:
		n->updateH();
	}
	void find(Node*& n, T e) {
	}

public:

	AVLTree(std::function<R(T)> key = [](T a) { return a; })
		: root(nullptr), length(0), key(key) {}
	~AVLTree() { }

	int Height() {
		return Node::height(root);
	}
	int Size() {
		return length;
	}
	void Add(T e, int pos) {
		add(root, e,pos);
		++length;
	}
	void Find(T e){
		find(root, e);
	}
	void greater_than(T e) {

	}
	void smaller_than(T e) {

	}
};