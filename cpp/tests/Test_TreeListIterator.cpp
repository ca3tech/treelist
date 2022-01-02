#include <string>
#include <gtest/gtest.h>
#include "../TLNode.h"
#include "../TreeListIterator.h"

using namespace std;

TEST(TreeListIteratorTest, OneInt) {
    int val = 1;
    TLNode<int>* node = new TLNode<int>(0, val);
    TreeListIterator<int> it(node);
    ASSERT_EQ(*it, val);
}

TEST(TreeListIteratorTest, OneString) {
    string val = "test";
    TLNode<string>* node = new TLNode<string>(0, val);
    TreeListIterator<string> it(node);
    ASSERT_EQ(*it, val);
}

TEST(TreeListIteratorTest, TwoIntLeft) {
    int val[2] = {1, 2};
    TLNode<int>* tree = new TLNode<int>(1, val[1]);
    TLNode<int>* node = new TLNode<int>(0, val[0]);
    node->parent = tree;
    tree->left(node);
    TreeListIterator<int> it(tree->left());
    ASSERT_EQ(*it, tree->left()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
}

TEST(TreeListIteratorTest, TwoIntLeftReverse) {
    int val[2] = {1, 2};
    TLNode<int>* tree = new TLNode<int>(1, val[1]);
    TLNode<int>* node = new TLNode<int>(0, val[0]);
    node->parent = tree;
    tree->left(node);
    TreeListIterator<int> it(tree, true);
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->left()->data);
}

TEST(TreeListIteratorTest, TwoIntRight) {
    int val[2] = {1, 2};
    TLNode<int>* tree = new TLNode<int>(0, val[0]);
    TLNode<int>* node = new TLNode<int>(1, val[1]);
    node->parent = tree;
    tree->right(node);
    TreeListIterator<int> it(tree);
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->right()->data);
}

TEST(TreeListIteratorTest, TwoIntRightReverse) {
    int val[2] = {1, 2};
    TLNode<int>* tree = new TLNode<int>(0, val[0]);
    TLNode<int>* node = new TLNode<int>(1, val[1]);
    node->parent = tree;
    tree->right(node);
    TreeListIterator<int> it(tree->right(), true);
    ASSERT_EQ(*it, tree->right()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
}

TEST(TreeListIteratorTest, ThreeIntBalanced) {
    int val[3] = {1, 2, 3};
    TLNode<int>* tree = new TLNode<int>(1, val[1]);
    TLNode<int>* node = new TLNode<int>(0, val[0]);
    node->parent = tree;
    tree->left(node);
    node = new TLNode<int>(2, val[2]);
    node->parent = tree;
    tree->right(node);
    TreeListIterator<int> it(tree->left());
    ASSERT_EQ(*it, tree->left()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->right()->data);
}

TEST(TreeListIteratorTest, ThreeIntBalancedReverse) {
    int val[3] = {1, 2, 3};
    TLNode<int>* tree = new TLNode<int>(1, val[1]);
    TLNode<int>* node = new TLNode<int>(0, val[0]);
    node->parent = tree;
    tree->left(node);
    node = new TLNode<int>(2, val[2]);
    node->parent = tree;
    tree->right(node);
    TreeListIterator<int> it(tree->right(), true);
    ASSERT_EQ(*it, tree->right()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->left()->data);
}

TEST(TreeListIteratorTest, FiveIntBalanced) {
    int val[5] = {1, 2, 3, 4, 5};
    TLNode<int>* tree = new TLNode<int>(2, val[2]);
    TLNode<int>* node = new TLNode<int>(1, val[1]);
    node->parent = tree;
    tree->left(node);
    TLNode<int>* pnode = node;
    node = new TLNode<int>(0, val[0]);
    node->parent = pnode;
    pnode->left(node);
    node = new TLNode<int>(3, val[3]);
    node->parent = tree;
    tree->right(node);
    pnode = node;
    node = new TLNode<int>(4, val[4]);
    node->parent = pnode;
    pnode->right(node);
    TreeListIterator<int> it(tree->left()->left());
    ASSERT_EQ(*it, tree->left()->left()->data);
    ++it;
    ASSERT_EQ(*it, tree->left()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->right()->data);
    ++it;
    ASSERT_EQ(*it, tree->right()->right()->data);
}

TEST(TreeListIteratorTest, FiveIntBalancedReverse) {
    int val[5] = {1, 2, 3, 4, 5};
    TLNode<int>* tree = new TLNode<int>(2, val[2]);
    TLNode<int>* node = new TLNode<int>(1, val[1]);
    node->parent = tree;
    tree->left(node);
    TLNode<int>* pnode = node;
    node = new TLNode<int>(0, val[0]);
    node->parent = pnode;
    pnode->left(node);
    node = new TLNode<int>(3, val[3]);
    node->parent = tree;
    tree->right(node);
    pnode = node;
    node = new TLNode<int>(4, val[4]);
    node->parent = pnode;
    pnode->right(node);
    TreeListIterator<int> it(tree->right()->right(), true);
    ASSERT_EQ(*it, tree->right()->right()->data);
    ++it;
    ASSERT_EQ(*it, tree->right()->data);
    ++it;
    ASSERT_EQ(*it, tree->data);
    ++it;
    ASSERT_EQ(*it, tree->left()->data);
    ++it;
    ASSERT_EQ(*it, tree->left()->left()->data);
}