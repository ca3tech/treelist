#include <string>
#include <gtest/gtest.h>
#include "../TreeList.h"

using namespace std;

template <class T>
class MockTreeList : public TreeList<T> {
    public:
        TLNode<T>* getRoot();
    private:
        using TreeList<T>::root;
};

template <typename T>
TLNode<T>* MockTreeList<T>::getRoot() {
    return root;
}

TEST(TreeListTest, SetOneInt) {
    TreeList<int> t;
    int val = 1;
    t.set(0, val);
    ASSERT_EQ(*t[0], val);
}

TEST(TreeListTest, SetOneString) {
    TreeList<string> t;
    string val = "Hello Test";
    t.set(0, val);
    ASSERT_EQ(*t[0], val);
}

TEST(TreeListTest, SetTwoIntNoSkip) {
    TreeList<int> t;
    int exp[2] = {1, 2};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    ASSERT_EQ(*t[0], exp[0]);
    ASSERT_EQ(*t[1], exp[1]);
}

TEST(TreeListTest, SetTwoIntSkip) {
    TreeList<int> t;
    int exp[2] = {1, 2};
    t.set(0, exp[0]);
    t.set(9, exp[1]);
    ASSERT_EQ(*t[0], exp[0]);
    ASSERT_EQ(*t[9], exp[1]);
}

TEST(TreeListTest, SetTwoStringNoSkip) {
    TreeList<string> t;
    string exp[2] = {"item1", "item2"};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    ASSERT_EQ(*t[0], exp[0]);
    ASSERT_EQ(*t[1], exp[1]);
}

TEST(TreeListTest, SetTwoStringSkip) {
    TreeList<string> t;
    string exp[2] = {"item1", "item2"};
    t.set(0, exp[0]);
    t.set(9, exp[1]);
    ASSERT_EQ(*t[0], exp[0]);
    ASSERT_EQ(*t[9], exp[1]);
}

TEST(TreeListTest, SetTwoIntIncStructure) {
    MockTreeList<int> t;
    int exp[2] = {1, 2};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    EXPECT_EQ(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->right();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    ASSERT_EQ(node->left(), nullptr);
    ASSERT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, SetTwoIntDecStructure) {
    MockTreeList<int> t;
    int exp[2] = {1, 2};
    t.set(1, exp[1]);
    t.set(0, exp[0]);
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    ASSERT_NE(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    ASSERT_EQ(node->left(), nullptr);
    ASSERT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, SetThreeIntIncStructure) {
    MockTreeList<int> t;
    int exp[3] = {1, 2, 3};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    t.set(2, exp[2]);
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    EXPECT_NE(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->parent->right();
    ASSERT_EQ(node->i, 2);
    ASSERT_EQ(node->data, exp[2]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, SetThreeIntDecStructure) {
    MockTreeList<int> t;
    int exp[3] = {1, 2, 3};
    t.set(2, exp[2]);
    t.set(1, exp[1]);
    t.set(0, exp[0]);
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    EXPECT_NE(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->parent->right();
    ASSERT_EQ(node->i, 2);
    ASSERT_EQ(node->data, exp[2]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, SetFiveIntIncStructure) {
    MockTreeList<int> t;
    int exp[5] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) {
        t.set(i, exp[i]);
    }
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 2);
    ASSERT_EQ(node->data, exp[2]);
    ASSERT_NE(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    ASSERT_NE(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->parent->parent->right();
    ASSERT_EQ(node->i, 3);
    ASSERT_EQ(node->data, exp[3]);
    EXPECT_EQ(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->right();
    ASSERT_EQ(node->i, 4);
    ASSERT_EQ(node->data, exp[4]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, SetFiveIntDecStructure) {
    MockTreeList<int> t;
    int exp[5] = {1, 2, 3, 4, 5};
    for(int i = 4; i >= 0; i--) {
        t.set(i, exp[i]);
    }
    TLNode<int>* node = t.getRoot();
    ASSERT_EQ(node->i, 2);
    ASSERT_EQ(node->data, exp[2]);
    ASSERT_NE(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 1);
    ASSERT_EQ(node->data, exp[1]);
    ASSERT_NE(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->left();
    ASSERT_EQ(node->i, 0);
    ASSERT_EQ(node->data, exp[0]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
    node = node->parent->parent->right();
    ASSERT_EQ(node->i, 3);
    ASSERT_EQ(node->data, exp[3]);
    EXPECT_EQ(node->left(), nullptr);
    ASSERT_NE(node->right(), nullptr);
    node = node->right();
    ASSERT_EQ(node->i, 4);
    ASSERT_EQ(node->data, exp[4]);
    EXPECT_EQ(node->left(), nullptr);
    EXPECT_EQ(node->right(), nullptr);
}

TEST(TreeListTest, RemoveOneIntLenOne) {
    TreeList<int> t;
    int val = 1;
    t.set(0, val);
    int* rmval = t.remove(0);
    ASSERT_NE(rmval, nullptr); 
    ASSERT_EQ(*rmval, val);
    ASSERT_EQ(t[0], nullptr);
}

TEST(TreeListTest, RemoveLeafIntLenTwo) {
    TreeList<int> t;
    int exp[2] = {1, 2};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    int* rmval = t.remove(1);
    ASSERT_NE(rmval, nullptr); 
    ASSERT_EQ(*rmval, exp[1]);
    ASSERT_EQ(t[1], nullptr);
    ASSERT_EQ(*t[0], exp[0]);
}

TEST(TreeListTest, RemoveRootIntLenTwo) {
    TreeList<int> t;
    int exp[2] = {1, 2};
    t.set(0, exp[0]);
    t.set(1, exp[1]);
    int* rmval = t.remove(0);
    ASSERT_NE(rmval, nullptr); 
    ASSERT_EQ(*rmval, exp[0]);
    ASSERT_EQ(t[0], nullptr);
    ASSERT_EQ(*t[1], exp[1]);
}

TEST(TreeListTest, RemoveRootIntLenFive) {
    TreeList<int> t;
    int exp[5] = {1, 2, 3, 4, 5};
    for(int i = 0; i < 5; i++) {
        t.set(i, exp[i]);
    }
    int* rmval = t.remove(2);
    ASSERT_NE(rmval, nullptr); 
    ASSERT_EQ(*rmval, exp[2]);
    ASSERT_EQ(t[2], nullptr);
    for(int i = 0; i < 5; i++) {
        if(i != 2) {
            ASSERT_EQ(*t[i], exp[i]);
        }
    }
}