#include <gtest/gtest.h>
#include <list>
#include <tuple>

class Node {
  public: 
    explicit Node(int id) : id_{id}, left_{nullptr}, right_{nullptr}{}
    int id() { return id_;}

    Node *const left() {
      return left_; 
    }
    void left(Node *n) { left_=n; }

    Node *const right() {
      return right_; 
    }
    void right(Node *n) { right_=n; }
  private: 
    int id_; 
    Node *left_, *right_; 
};

class Tree {
  public: 

    // Copy the node in. This is a convenience so that this object takes ownership of the pointers. 
    // I could have used unique_ptrs too, but I got lazy. 
    void InsertNode(Node n){
      node_list_.push_back(n); 
      auto &current = node_list_.back();
      std::cout << "------Attempting to insert node: " << current.id() << std::endl;
      auto &root = node_list_.front(); 
      if (node_list_.size() == 1) return; 
      InsertNode(&root, &current); 
      std::cout << std::endl;
    }


    void InsertNode(Node *const root, Node *const current) {
      if (current == nullptr) std::cout << "CURRENT is NULL" << std::endl;
      if (root == nullptr) std::cout << "ROOT is NULL" << std::endl;
      // Is the current less than root? 
      if (current->id() < root->id()) {
        // yes: go left
        // Is the left null?
        if (root->left() == nullptr) {
          // yes: insert current here
          root->left(current);  
          if (root->left() == nullptr) std::cout << "nullptr AFTER assignment!!??" << std::endl;
          return; 
        } else {
          // no: left is new root
          InsertNode(root->left(), current);
        }

      } else {
        std::cout << current->id() << " >= " << root->id() << std::endl;
        // no: go right
        if (root->right() == nullptr) {
          root->right(current); 
          return; 
        } else {
          if (root->right() == nullptr) std::cout << "UH OH!!, right is null when it shouldn't be! " << std::endl;
          auto *right = root->right(); 
          InsertNode(root->right(), current); 
        }
      }
    }

    std::tuple<int, Node *> FindNode(int id){
      std::cout << "-------Attempting to find a node with id: " << id << std::endl;
      auto root = node_list_.front(); 
      int steps = 0; 
      auto *n = FindNode(&root, id, steps); 
      return std::make_tuple(steps, n); 
    }

  private: 

    Node* FindNode(Node *const root, int id, int &steps) {
      steps++; 
      if (root == nullptr) {
        std::cout << "Node not found!" << std::endl;
        return nullptr; 
      }
      if (id == root->id()) {
        return root; 
      } else { 
        // Is the current less than root? 
        if (id < root->id()) {
          return FindNode(root->left(), id, steps);
        } else {
          return FindNode(root->right(), id, steps);
        }
      }
    }
    // There is a very important reason why I am NOT using a vector. Can you figure out why?!? he he
    std::list<Node> node_list_; 
}; 

TEST(BST, FindNode) {
  Tree t; 
  t.InsertNode(Node{8});   
  t.InsertNode(Node{10});   
  t.InsertNode(Node{3});   
  t.InsertNode(Node{1});   
  t.InsertNode(Node{6});   
  t.InsertNode(Node{4});   
  t.InsertNode(Node{7});   
  t.InsertNode(Node{14});   
  t.InsertNode(Node{13});   
  auto steps = t.FindNode(13);   
  // Should only have to look at 4 nodes to find 13
  ASSERT_EQ(4, std::get<0>(steps)); 

  steps = t.FindNode(10);   
  // Should only have to look at 2 nodes to find 10
  ASSERT_EQ(2, std::get<0>(steps)); 

  steps = t.FindNode(11); 
  // Should not be able to find it!
  ASSERT_EQ(nullptr, std::get<1>(steps)); 
}
