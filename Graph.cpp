#include "Graph.h"
#include <queue>
#include <vector>
#include <algorithm>  // For std::sort
#include <cctype>     // For std::tolower
#include <iostream>   // For std::cout
#include <set>

Graph::~Graph() {
    for (auto& pair : nodes) 
        delete pair.second;
}

Node* Graph::getNode(const std::string& name) const{
    auto it = nodes.find(name);
    if (it != nodes.end()){
        return it->second;
    }
    else return nullptr;
}

std::vector<std::pair<std::string,std::string>> Graph::getEdges() const{
    std::vector<std::pair<std::string,std::string>> edges;
    for (const auto &[user, node] : nodes){
        for (const auto& follower: node->followers)
            edges.push_back(std::make_pair(follower,user));
    }
    return edges;
}
int Graph::getSize() const{
    return nodes.size();
}

Node* Graph::addNode(const std::string& name) {
    auto it = nodes.find(name);
    if (it == nodes.end()) {
        nodes[name] = new Node(name);
        return nodes[name];
    }
    return it->second;
}

void Graph::addEdge(const std::string& follower, const std::string& followee) {
    Node* followeeNode = addNode(followee);
    followeeNode->addFollower(follower);
    addNode(follower);
}

void Graph::calculateInDegrees(std::unordered_map<std::string, int>& inDegrees) const {
    for (const auto& node : nodes) 
        inDegrees[node.first] = node.second->getInDegree();
}

std::string Graph::findMostConnected(const std::unordered_map<std::string, int>& inDegrees) const {
    int maxDegree = -1;
    std::string mostConnected;
    for (const auto& pair : inDegrees) {
        if (pair.second > maxDegree) {
            mostConnected = pair.first;
            maxDegree = pair.second;
		}
         else if (pair.second == maxDegree && pair.first < mostConnected) 
            mostConnected = pair.first;
    }
    return mostConnected;
}

void Graph::exploreNetwork(const std::string& root,
                           int depth,
                           std::vector<std::pair<int, std::string>>& results) const
{
    // Unvisited Queue containx the pair (name, depth).
    std::queue<std::pair<std::string, int>> q;

    // Push Root node to front of queue
    q.push({root, 0});
    std::set<std::string> visited;

    // Add Root node to visited set
    visited.insert(root);

    while (!q.empty()) {
        auto front = q.front();
        q.pop();

        //add current node = pop front of queue
        int currentDepth = front.second;
        const std::string& currentNode = front.first;

        // add current node to results
        results.emplace_back(currentDepth, currentNode);

            // followers is a vector containing all of the followers of the current node
            std::vector<std::string> followers(nodes.at(currentNode)->followers.begin(), nodes.at(currentNode)->followers.end());

            //for each follower in the current nodes followers
            for (const auto& follower : followers) {
                // if the follower has not been visited
               if (visited.find(follower) == visited.end()) {
                    // add the follower to the unvisited queue.
                    q.push({follower, currentDepth + 1});
                    // visit the follower to the visited set.
                    visited.insert(follower);
               }
            }

    }
}

void Graph::printNetwork() const {
    for (const auto &[user, node] :nodes){
        std:: cout << "("<< user << "): ";
        for (const auto& follower : node->followers){
            std:: cout << follower << " ";
        }
        std:: cout << std:: endl;
    }

}
