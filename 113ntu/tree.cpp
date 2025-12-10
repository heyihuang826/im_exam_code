#include <iostream>
#include <string>
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
};

// ANSWER below

int BinarySearchTree::InsertNewEmployee(int newID, string newName, int newAge)
{
    // 建立新節點
    TreeNode* node = new TreeNode();
    node->employeeID = newID;
    node->emplyeeName = newName;
    node->age = newAge;
    node->leftChildPtr = NULL;
    node->rightChildPtr = NULL;

    // 若樹為空，直接插入為root
    if (rootPtr == NULL)
    {
        rootPtr = node;
        return 1;
    }

    // 否則開始搜尋插入位置
    TreeNode* parent = NULL; // 記錄Pointer c的parent node位置
    TreeNode* c = rootPtr; // 目前節點。從root開始掃描BST直到找到NULL
    int key; // 用來存放目前節點的key value
    while (c != NULL)
    {
        parent = c;
        key = c->employeeID; // 更新目前節點的key value
        if (newID < key) // Pointer c往左子樹走
            c = c->leftChildPtr;

        else if (newID > key) // Pointer c往右子樹走
            c = c->rightChildPtr;

        else {
            // 題目敘述：ID 不會重複，但仍保護性處理
            delete node; // 立委也沒注意到這裡會memory leak
            return 0;
        }
    }

    // c已訪問到NULL，將node插入parent的適當子樹
    if (newID < parent->employeeID)
        parent->leftChildPtr = node;
    else
        parent->rightChildPtr = node;

    return 1;
}


void BinarySearchTree::inorder(TreeNode *treePtr) {
    if (treePtr == NULL) return;
    inorder(treePtr->leftChildPtr);
    cout << treePtr->employeeID << " "
            << treePtr->emplyeeName << " "
            << treePtr->age << endl;
    inorder(treePtr->rightChildPtr);
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
    for(int i = 1; i <= 10; i++)
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
