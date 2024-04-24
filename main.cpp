#include "Graph.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>  // Necessary for std::tolower
#include <algorithm>  // Necessary for std::transform
#include <iostream>

using namespace std;
int main(int argc, const char* argv[]) {
    if (argc != 2)
    {
        std::cout << "./project4 inputFile" << std::endl;
        return EXIT_FAILURE;
    }
    string inputFileName = argv[1];

    ifstream file(argv[1]);
    if (!file) {
        cerr << "File could not be opened.\n";
        return 1;
    }

    Graph socialGraph, tree;
    string line;

    while (getline(file, line)) {
        istringstream iss(line);
        string follower, followee;
        if (!(iss >> followee >> follower)) { break; } // Error checking

        // Convert to lowercase
        transform(follower.begin(), follower.end(), follower.begin(),
                  [](unsigned char c){ return tolower(c); });
        transform(followee.begin(), followee.end(), followee.begin(),
                  [](unsigned char c){ return tolower(c); });

        socialGraph.addEdge(follower, followee);
    }

    file.close();

    unordered_map<string, int> inDegrees;
    socialGraph.calculateInDegrees(inDegrees);
    Node* root = socialGraph.getNode(socialGraph.findMostConnected(inDegrees));

    cout << "The root user is "
         << root->name
         << ", with in-degree centrality of "
         << (root->followers).size()
         << "."
         << endl
         << "There are "
         << socialGraph.getSize()
         << " users in the social network."
         << endl;

    cout << root->name << " (0)" << endl;
    tree.addNode(root->name);
    for (const auto & node: root->followers){
        tree.addEdge(node,root->name);
        cout << node << " (1)\n";
        for (const auto &leaf: socialGraph.getNode(node)->followers){
            tree.addEdge(leaf,node);
            cout << leaf << " (2)\n";
        }
    }
    return 0;
}
