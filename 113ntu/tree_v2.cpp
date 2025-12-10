#include <iostream>
#include <string>
#include <stack>
using namespace std;


class TreeNode
{
public:
    // ...
private:
    // ...
    int employeeID;
    string emplyeeName;
    int age;

    TreeNode *leftChildPtr;
    TreeNode *rightChildPtr;
    friend class BinarySearchTree;
};

class BinarySearchTree
{
public:
    BinarySearchTree() : rootPtr(NULL) {} // IMPORTANT: initialize rootPtr. ANSWER

    // ...
    int InsertNewEmployee(int newID, string newName, int newAge);

    void ListAllEmployee();

protected:
    void inorder(TreeNode *treePtr);

private:
    // ...
    TreeNode *rootPtr;
    TreeNode* add(TreeNode *root, TreeNode *newNode, bool &success);
};

// ANSWER below

//遞迴版本
int BinarySearchTree::InsertNewEmployee(int newID, string newName, int newAge)
{
    bool success = true; // 記錄插入過程是否遇到重複的key，若遇到視為插入不成功
    TreeNode* newNode = new TreeNode;
    newNode->employeeID = newID;
    newNode->emplyeeName = newName;
    newNode->age = newAge;
    newNode->leftChildPtr = NULL;
    newNode->rightChildPtr = NULL;

    rootPtr = add(rootPtr, newNode, success);

    return success ? 1 : 0;
}


// insert newNode to subtree which root named `root`.
TreeNode* BinarySearchTree::add(TreeNode *root, TreeNode *newNode, bool &success){
    if(root == NULL) return newNode; // empty tree, insert here
    // insert in leftTree
    if(newNode->employeeID < root->employeeID){
        root->leftChildPtr = add(root->leftChildPtr, newNode, success);
    }
    // insert in leftTree
    else if(newNode->employeeID > root->employeeID){
        root->rightChildPtr = add(root->rightChildPtr, newNode, success);
    }
    // change flag if key duplicated
    else{
        delete newNode;
        success = false;
    }

    // return the node pointer
    return root;
}


// 非遞迴版本
void BinarySearchTree::inorder(TreeNode *treePtr) {
    
    stack<TreeNode*> s; // 建立一個stack來存放node
    TreeNode* curr = treePtr; // 從root開始inorder traversal

    bool done = false; // traversal是否完成

    while(!done){
        if(curr != NULL){ // 尚未往左走到底
            s.push(curr); // 將node加入stack
            curr = curr->leftChildPtr; // 繼續往左子樹走
        }
        else{ // 往左已經走到底了
            if(!s.empty()){ // 還有節點尚未訪問
                curr = s.top(); // 取得stack的top節點訪問
                // 訪問節點
                cout << curr->employeeID << " "
                    << curr->emplyeeName << " "
                    << curr->age << endl;
                s.pop(); // 從stack中移除該節點
                curr = curr->rightChildPtr; // 訪問右子樹
            }
            else{ // 已經往左走到底，也沒有尚未訪問的node
                done = true; // traversal結束
            }
        }
    }
}


void BinarySearchTree::ListAllEmployee() {
    inorder(rootPtr);
}


int main()
{
    BinarySearchTree bst;
    bst.InsertNewEmployee(10, "Alice", 30);
    bst.InsertNewEmployee(5, "Bob", 25);
    bst.InsertNewEmployee(20, "Charlie", 40);
    for(int i = 1; i <= 100; i++)
        bst.InsertNewEmployee(20, "Charlie", 40);
    bst.InsertNewEmployee(6, "6", 40);
    bst.InsertNewEmployee(15, "6", 40);
    bst.InsertNewEmployee(30, "6", 40);
    bst.InsertNewEmployee(20, "Charlie2", 40);
    bst.InsertNewEmployee(4, "6", 40);
    bst.InsertNewEmployee(3, "6", 40);
    bst.InsertNewEmployee(8, "6", 40);

    cout << "All employees (in sorted order by ID):" << endl;
    bst.ListAllEmployee();
}
