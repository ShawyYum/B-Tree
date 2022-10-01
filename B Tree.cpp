#include <vector>
#include <algorithm>
#include <iostream>

class BTreeNode {
firend class BTree;

protected:
    unsigned int n;
    std::vector<int> key;
    std::vector<BTreeNode *> child;

    BTreeNode():this->n(2) {
        this->key.reserve(2 * this->n - 1);
        this->child.reserve(2 * this->n);
    }

    BTreeNode(const unsigned int x):this->n(x) {
        this->key.reserve(2 * this->n - 1);
        this->child.reserve(2 * this->n);
    }

    ~BTreeNode() {
        for(auto &it : this->child) {
            delete it;
        }
    }

    BTreeNode * search(const int x) {
        unsigned int i = 0;
        while(i < this->key.size() && x > this->key[i]) i++;
        if(x == this->key[i]) return this;
        if(this->child.size() == 0) return NULL;
        return this->child[i]->search(x);
    }

    void traverse() {
        unsigned int i = 0;
        for(;i < this->key.size();i++) {
            if(this->child.size() != 0) this->child[i].traverse();
            std::cout << this->key[i];
        }
        if(this->child.size() != 0) this->child[i + 1].traverse();
    }

    void split((BTreeNode *) &x,const int k) {
        BTreeNode *y = new BTreeNode(this->n);
        for(int i = 0;i < n - 1;i++) {
            y->key[i] = x->key[n + i];
        }
        this->key.insert(this->key.begin() + k,x->key[this->n - 1]);
        for(int i = 0;i < n;i++) {
            x->key.pop_back();
        }
        for(int i = 0;i < n;i++) {
            y->key[i] = x->key[n + i];
        }
        this->child.insert(this->child.begin() + k + 1,y);
        for(int i = 0;i < n;i++) {
            delete x->key.back();
            x->key.pop_back();
        }
    }

    void insert(const int x) {
        int i = 0;
        while(i < this->key.size() && x > this->key[i]) i++;
        if(this->child.size() != 0) {
            if(this->child[i]->key.size() == 2 * this->n - 1) {
                this->split(this->child[i],i);
                if(x < this->key[i]) this->child[i]->insert(x);
                else this->child[i + 1]->insert(x);
            }
            else this->child[i]->insert(x);
        }
        else this->key.insert(this->key.begin() + i,x);
    }
};

class BTree {
protected:
    unsigned int n;
    BTreeNode *root;

    BTree():this->n(2) {
        this->root = NULL;
    }

    BTree(const unsigned int x):this->n(x) {
        this->root = NULL;
    }

    ~BTree() {
        delete this->root;
    }

    const (BTreeNode *) & search(const int x) const {
        return this->root == NULL ? NULL : this->root->search(x);
    }

    const void traverse() const {
        if(this->root != NULL) this->root->traverse();  
        std::cout << std::endl;
    }

    void insert(const int x) {
        if(this->root == NULL) {
            this->root = new BTreeNode(this->n);
            this->root->key[0] = k;
        }
        else {
            if(this->root->key.size() == 2 * this->n - 1) {
                BTreeNode * y = new BTreeNode(this->n);
                y->split(this->root,0);
                this->root = y;
                delete y;
                if(x < this->root->key[0]) this->root->child[0]->insert(x);
                else this->root->child[1]->insert(x);
            }
            else this->root->insert(x);
        }
    }

    void delete(const int x) {
        
    }
};
