#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <unordered_map>
#include <vector>
#include <utility> // For std::pair
#include <set>
#include <iostream>


class Node {

public:
    std::string name;
    std::set<std::string> followers; // followers are those that are following this node
    std::set<std::string> following; // following are those that this node follows

    Node(std::string name) : name(name) {}

    void addFollower(const std::string& name) {     followers.insert(name); }
    void addFollowing(const std::string& name) {    following.insert(name); }

    int getInDegree() const {   return followers.size();   }
    int getOutDegree() const {  return following.size();    }
};

class Graph {
private:
    std::unordered_map<std::string, Node*> nodes; // Maps name of node to Node object

public:
    ~Graph(); // Delete Object
    Node* getNode(const std::string&  name) const;
    int getSize() const;
    std::vector<std::pair<std::string, std::string>> getEdges() const; // Returns pair of strings
    Node* addNode(const std::string& name); // Add node to graph
    void addEdge(const std::string& follower, const std::string& followee); // add edge between nodes
    void calculateInDegrees(std::unordered_map<std::string, int>& inDegrees) const;
    std::string findMostConnected(const std::unordered_map<std::string, int>& inDegrees) const; // return name with highest inDeg
    void exploreNetwork(const std::string& root, int depth, std::vector<std::pair<int, std::string>>& results) const;
    void printNetwork() const;

};

class Tree : public Graph{

private:

};

#endif // GRAPH_H
