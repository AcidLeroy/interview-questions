#include <iostream> 
#include <gtest/gtest.h>
#include <string>
#include <list>
#include <queue>

class Node {
  public: 
    explicit Node(const std::string &name) : name_{name}{
      
    }
    std::string name() { return name_; }

    void AddEdge(Node * const n){
      edges_.push_back(n);  
    }

    void AddEdges(std::initializer_list<Node*> l) {
      for (auto &i: l) {
        edges_.push_back(i); 
      }
    }

    const std::list<Node*> &GetEdges() {
      return edges_; 
    } 

    void visited(bool v) {
      visited_ = v; 
    }

    bool visited() { return visited_; }

  private: 
    std::string name_; 
    std::list<Node*> edges_; 
    bool visited_ = false; 
};

class Graph {
  public: 
    Graph(std::initializer_list<Node*> l) : node_list_{l}{}; 

    std::vector<Node> DFS(Node *root) {
      std::vector<Node> visited_list; 
      DFSImpl(root, &visited_list); 
      return visited_list; 
    }

    std::vector<Node> BFS(Node *const root) {
      std::vector<Node> visited_list; 
      BFSImpl(root, &visited_list); 
      return visited_list; 
    }

  private: 
    void DFSImpl(Node * const root, std::vector<Node> * const visited_list) {
      visited_list->push_back(*root); 
      root->visited(true); 

      auto connected_nodes = root->GetEdges(); 
      std::cout << "Current node " << root->name() << std::endl;
      for (auto &i: connected_nodes)  {
        if (!i->visited()) {
          DFSImpl(i, visited_list); 
        }
      }
    }

    void BFSImpl(Node * const root, std::vector<Node> * const visited_list) {
      std::queue<Node*> q; 
      q.push(root); 

      while (!q.empty()) {
        auto current = q.front(); 
        q.pop();
        std::cout << "Current node " << current->name() << std::endl;
        current->visited(true); 
        // Add for testing
        visited_list->push_back(*current); 
        auto connected_nodes = current->GetEdges(); 
        for (auto &i: connected_nodes) {
          if (!i->visited()) {
            q.push(i); 
          }
        }
      }
    }

    std::list<Node*> node_list_; 
}; 

TEST(AdjList, TwoNodes) {
 // Create a node A & B
 Node a("A"); 
 Node b("B"); 

 // Create a connection from a to b
 a.AddEdge(&b);

 // Add nodes to graph
 Graph g({&a, &b}); 

 // Traverse list in breadth first returning each 
 // node in the order it was visited. 
 auto node_list = g.DFS(&a); 
 ASSERT_EQ(2, node_list.size()); 
 ASSERT_EQ("A", node_list[0].name()); 
 ASSERT_EQ("B", node_list[1].name()); 

}

TEST(AdjList, FourNodesDFS) {
 // Create nodes
 Node zero("0"); 
 Node one("1"); 
 Node two("2"); 
 Node three("3"); 

 // Add edges to nodes
 zero.AddEdges({&one, &two});
 one.AddEdge(&two); 
 two.AddEdges({&zero, &three}); 
 three.AddEdges({&three}); 

 // Add nodes to graph
 Graph g({&zero, &one, &two, &three}); 

 // Traverse list in breadth first returning each 
 // node in the order it was visited. 
 auto node_list = g.DFS(&two); 
 for (auto &i: node_list) {
  std::cout << "The result is: " << i.name() << std::endl;
 }

 std::vector<std::string> expected{"2", "0", "1", "3"}; 
 ASSERT_EQ(4, node_list.size()); 
 ASSERT_EQ(expected[0], node_list[0].name()); 
 ASSERT_EQ(expected[1], node_list[1].name()); 
 ASSERT_EQ(expected[2], node_list[2].name()); 
 ASSERT_EQ(expected[3], node_list[3].name()); 

}

TEST(AdjList, FourNodesBFS) {
 // Create nodes
 Node zero("0"); 
 Node one("1"); 
 Node two("2"); 
 Node three("3"); 

 // Add edges to nodes
 zero.AddEdges({&one, &two});
 one.AddEdge(&two); 
 two.AddEdges({&zero, &three}); 
 three.AddEdges({&three}); 

 // Add nodes to graph
 Graph g({&zero, &one, &two, &three}); 

 // Traverse list in breadth first returning each 
 // node in the order it was visited. 
 auto node_list = g.BFS(&two); 
 for (auto &i: node_list) {
  std::cout << "The result is: " << i.name() << std::endl;
 }

 std::vector<std::string> expected{"2", "0", "3", "1"}; 
 ASSERT_EQ(4, node_list.size()); 
 ASSERT_EQ(expected[0], node_list[0].name()); 
 ASSERT_EQ(expected[1], node_list[1].name()); 
 ASSERT_EQ(expected[2], node_list[2].name()); 
 ASSERT_EQ(expected[3], node_list[3].name()); 

}
