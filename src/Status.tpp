#include <iostream>

#ifndef STATUS
#define STATUS
/**
 * Status is a balanced tree, that allows for neighbour search
 * @tparam T : template class for which you want to build the status
 */
template <class T>
class Status {
private:
    /**
    * Internal node of the tree
    */
    typedef struct Node{
        T key;
        Node* left;
        Node* right;
        Node* parent;
        T rightmost;
        int height;
    } Node;
    Node *root= nullptr;

    Node* newNode(T key){
        Node* node = (Node *)malloc(sizeof(Node));
        node->left = node->right = NULL;
        node->height = 1;//!< Added at leaf initially.
        node->key = key;
        node->rightmost=key;
        return node;
    }

    Node* rightRotate(Node* y){
        Node *x = y->left;
        Node *t2 = x->right;

        x->right = y;
        y->left = t2;

        //Update heights
        y->height = max(height(y->left), height(y->right)) + 1; //!< height is 1+max possible heights possible by both subtrees.
        x->height = max(height(x->right), height(x->left)) + 1;

        return x;
    }

    Node* leftRotate(Node* x)
    {
        //cout<<"Left"<<endl;
        Node *y = x->right;
        Node *t2 = y->left;

        //Rotate now!!
        y->left = x;
        x->right = t2;
        x->height = max(height(x->right), height(x->left)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int height(Node* n){
        if (n == NULL)
            return 0;
        else return n->height;
    }

    int getBalance(Node* n){
        if (n == NULL)return 0;
        else return height(n->left) - height(n->right);
    }

    void __inorder(Node* n){
        if (n != NULL){
            __inorder(n->left);
            std::cout << n->key << " ";
            __inorder(n->right);
        }
    }

    bool checkLeaf(Node* n){
        if(n==NULL)return false;
        return (n->right==n->left and n->left==NULL and n->rightmost==n->key);
    }

    Node* __insert(Node* node, T key){
        int left=0;
        if (node == NULL)
            return newNode(key);
        if (key < node->key)
        {
            node->left = __insert(node->left, key),++left;
        }

        else if (key > node->key)
        {
            node->right = __insert(node->right, key),--left;
        }
        else
            return node; //!< We are not allowing duplicates

        node->height = 1 + max(height(node->left), height(node->right));
        int bal = getBalance(node);

        if (bal > 1 and key < node->left->key)
            return rightRotate(node);
        else if (bal < -1 and key> node->right->key)
            return leftRotate(node);
        else if (bal > 1 and key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (bal < -1 and key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* minValueNode(Node* node){
        Node *current = node;
        while (current->left != NULL)current = current->left;
        return current;
    }

    Node* __remove(Node* root, T key){
        int left=0;
        //cout<<(root->key)<<" and key="<<key<<endl;
        if (root == NULL)return root;
        //cout<<"Root==NULL done"<<endl;
        if (key < root->key)
        {
            //cout<<"C1"<<endl;
            root->left = __remove(root->left, key),left++;
        }
        else if (key > root->key)
        {
//            cout<<"C2"<<endl;
//            cout<<"Root->key="<<root->key<<" key="<<key<<endl;
            root->right = __remove(root->right, key),left--;
        }
        else
        {
            if(key!= root->key and checkLeaf(root))return root;
            if (root->left == NULL or root->right == NULL)
            {
                //cout<<"C4"<<endl;
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL)//Node is a leaf
                {
                    //cout<<"C5"<<endl;
                    temp = root;
                    root = NULL;

                }
                else
                    *root = *temp;
                free(temp);
            }
            else
            {
                //cout<<"C7"<<endl;
                struct Node* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = __remove(root->right, temp->key);
            }
        }
        //cout<<"all if-else done"<<endl;
        if (root == NULL)return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int bal = getBalance(root);

        if (bal > 1 and getBalance(root->left) >= 0)
            return rightRotate(root);
        else if (bal > 1 and getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        else if (bal < -1 and getBalance(root->right) <= 0)
            return leftRotate(root);
        else if (bal < -1 and getBalance(root->right)>0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    /**
     * Prints inorder traversal
     * Requires that operator<< for ostream be
     * overloaded for < T > class
     */
    void inorder(){
        __inorder(root);
    }
    /**
     * Insert an element into the tree
     * @param element to insert
     */
    void insert(T key){
        root = __insert(root, key);
    }

    /**
     * Removes element from tree
     * Does nothing is element is not present
     */
    void remove(T key){
        root = __remove(root, key);
    }

    /**
     * Searches for element to the left of the param
     * Returns null if no neighbour exists
     * If param doesnt exist, we search for the smallest element
     * greater than it
     * @param : Element who's left neighbour we want to search for
     */
    T* searchL(T key){
        Node *curr=root;
        //cout<<"SearchL"<<key<<" "<<(root->key)<<endl;
        while(curr->left != NULL)
            curr = curr->left;
        if(curr->key == key)
            return NULL;

        Node *ans = newNode(curr->key);
        curr = root;


        while(curr != NULL)
        {
            if(curr->key<key and ans->key <=curr->key)
                ans=curr;
            if(key <= curr->key)
                curr=curr->left;
            else
                curr=curr->right;
        }
        return &(ans->key);
    }

    /**
     * Searches for element to the right of the param
     * Returns null if no neighbour exists
     * If param doesnt exist, we search for the smallest element
     * greater than it
     * @param : Element who's right neighbour we want to search for
     */
    T* searchR(T key){
        Node *curr=root;
        while(curr->right != NULL)
            curr = curr->right;
        if (curr->key == key)
            return NULL;

        Node *ans = newNode(curr->key);
        curr = root;
        while(curr != NULL)
        {
            if(curr->key>key and curr->key <ans->key)
                ans=curr;
            if(key < curr->key)
                curr=curr->left;
            else
                curr=curr->right;
        }
        return &(ans->key);
    }



    T* getRoot(){
        if(root == NULL) return NULL;
        else return &(root->key);
    }

};

#endif