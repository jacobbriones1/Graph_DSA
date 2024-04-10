/*
    - Author: Jacob Briones
    
    - C++ program which creates a graph structure
        from an input text file containing 
        adjacency pairs: Name_1    Name_2
    - The graph is stored as a map:
        map<string, vector<string>> graphMap
        whose first key is the node name, and second node
        is the list of node names adjacent to it.
                                                            */
                                                            
#include<iostream>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;


int main(void) {
    string inputFileName = "input1.txt";
    string line, s1, s2;
    
    ifstream file;
    stringstream ss;
    
    int filenum = 1;
    int lines = 0;
    int max = -1;
    int min = 100000;
    
    bool next
    
    // For storing names of nodes with max/min centrality
    vector<string> maxStrings;
    vector<string> minStrings;
    
    list<string>::iterator iter;
    
    // Stores the entire Graph 
    map<string, list<string>> graphMap;
    
    //INPUT FILE NUMBER
    cin >> filenum;  
    inputFileName.at(5) = filenum+0x30; 
    //open file
    file.open(inputFileName);
    
    ss.clear();
    // READ IN DATA LINE BY LINE
    while(getline(file,line)){
        next = false; // true when s2 is being read in
        s1=""; // to store first word in line
        s2=""; // to store second word in line
        
        for (size_t i = 0; i < line.size(); ++i){
            if (!next && line[i]!=' ')
                s1 = s1+line[i];
                
            if (line[i]==' '||line[i]==','||line[i]=='\t')
                next=true;
            
            if (line[i]=='\n')
                break;
                
            else if (line[i]!=' '  && next==true)
                s2 = s2+line[i];
        }
        
        lines = lines + 1; // Total number of lines read
        ss<< s1 << " " << s2 << '\n';   // Parsed line stored in string stream
    }
    // Close file. Done processing text document.
    file.close();
    
    // Create Adjacency list (i.e., graph structure)
    for (int i = 0; i < lines; i++){
        ss >> s1; 
        ss >> s2;
        
        // index of s1's adjacency list where s2 appears. 
        // will be end of s1's adjacency list if it does not appear.
        iter = find(graphMap[s1].begin(),graphMap[s1].end(),s2); 
        
        // Create edge if s2 is not in s1's adjacency list.
        if (iter == graphMap[s1].end()){
            graphMap[s1].push_back(s2); // edge from s1->s2
            graphMap[s2].push_back(s1); // edge from s2->s1
        }
    }
    map<string, list<string>>::iterator it =  graphMap.begin(); // To iterate through vertices
    int tempDegree; // to store degree of each vertex
    int numNodes = 0; // to count number of nodes in graph
    
    //// FIND NODES WITH MAXIMUM AND MINIMUM CENTRALITY
    while (it!=graphMap.end()){
        tempDegree = (int)graphMap[it->first].size();
        
        // only store names of nodes that have max centrality 
        if (tempDegree >= max){
            if (maxStrings.size()!=0 && max < tempDegree) 
                maxStrings.clear(); // clear vector for new max(s)
                
            maxStrings.push_back(it->first);
            max = tempDegree;
        }
        
        // only store names of nodes that have min centrality 
        if (tempDegree <= min){
            if (minStrings.size()!=0 && min > tempDegree)
                minStrings.clear(); // clear vector for new min(s)
                
            minStrings.push_back(it->first);
            min = tempDegree;
        }
        numNodes+=1; // Count vertices
        ++it;
    }
    
    /////////// OUTPUT CENTRALITY DATA /////////////////////////////////////////
    cout << "There are " << numNodes << " nodes in the graph." << endl;
    
    cout << "Accounts with maximum Degree of Centrality:" <<endl;
    for (auto v : maxStrings)
        cout << v << " (" << max << ")" << endl;
    
    cout << endl << "Accounts with minimum Degree of Centrality:" <<endl;
    for (auto v : minStrings)
        cout << v << " (" << min << ")" << endl;
    
   return 0;   
}
