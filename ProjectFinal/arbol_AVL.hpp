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
		std::vector<int> get_posNode() {
			return posi;
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
	Node* find(Node*& n, T e) {
		if (n != nullptr) {
			if (key(e) == key(n->e)) {
				return n;
			}
			else if (key(e) < key(n->e)) {
				return find(n->l, e);
			}
			else if (key(e) > key(n->e)) {
				return find(n->r, e);
			};
		};
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
	std::vector<int> Find(T e){
		Node* tempNode;
		tempNode=find(root, e);
		return tempNode.get_posNode();
	}

	std::vector<int> greater_than(Node*& n) {

		if (n != nullptr) {
			if (key(e) == key(n->e)) {
				return n;
			}
			else if (key(e) < key(n->e)) {
				return find(n->l, e);
			}
			else if (key(e) > key(n->e)) {
				return find(n->r, e);
			};
		};
	}

	std::vector<int> smaller_than(Node* n, std::vector<int> valores) {
		if (n->l != nullptr) {
			valores= smaller_than(n->l, valores);
		}if (n->l == nullptr) {
			for (int i = 0; i < n->posi.size(); i++) {
				return valores.push_back(n->posi.at(0));
			};
		}
		if (n->r != nullptr) {
			valores = smaller_than(n->l, valores);
		}if (n->r == nullptr) {
			for (int i = 0; i < n->posi.size(); i++) {
				return valores.push_back(n->posi.at(0));
			};
		}

	}

	std::vector<int> Greater_Than(T e) {
		Node* inicia = new Node;
		inicia = find(n, e);
		inicia = inicia->r;
		return greater_than(inicia);
	}

	std::vector<int> Smaller_Than(T e) {
		Node* inicia = new Node;
		inicia = find(n, e);
		inicia = inicia->l;
		return smaller_than(inicia);
	}
};