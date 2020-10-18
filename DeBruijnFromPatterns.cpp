#include<iostream>
#include<string>
#include <vector>
#include <algorithm>
#include<fstream>



using namespace std;

vector <string>
DeBruijnFromPatterns(vector<string> Patterns , unsigned int k)
{
    vector <string> AdjacencyList;
    vector<string> Nodes;
    vector<vector<string>>ConnectedToNodes;
    string outputdelim = " -> ";
    unsigned int NodeLength = k-1;
    for (int i = 0; i < Patterns.size(); i++)
    {
        Nodes.push_back(Patterns[i].substr(0,NodeLength));
    }
    sort(Nodes.begin(),Nodes.end());
    Nodes.erase(unique(Nodes.begin(),Nodes.end()),Nodes.end());
    ConnectedToNodes.resize(Nodes.size());
    for (int i = 0; i < Nodes.size(); i++)
    {
        string TestedNode = Nodes[i];
        for (int j = 0; j < Patterns.size(); j++)
        {
            string PatternNode = Patterns[j].substr(0,NodeLength);
            if (TestedNode == PatternNode)
            {
                string ConnectedNode = Patterns[j].substr(1,NodeLength) ;
                ConnectedToNodes[i].push_back(ConnectedNode);
            }
        }
    }

    for (int i = 0; i < Nodes.size(); i++)
    {
        string TestedNode = Nodes[i];
        string Rhs;
        for (int j = 0; j < ConnectedToNodes[i].size(); j++)
        {
            string ConnectedNode = ConnectedToNodes[i][j];
            
            if(ConnectedToNodes[i].size() == 1)AdjacencyList.push_back(TestedNode+outputdelim+ConnectedNode);
            if (ConnectedToNodes[i].size() > 1 && j != ConnectedToNodes[i].size()-1)
            {
                Rhs += ConnectedToNodes[i][j]+",";
            }
            if (ConnectedToNodes[i].size() > 1 && j == ConnectedToNodes[i].size()-1)
            {
                Rhs += ConnectedToNodes[i][j];
                AdjacencyList.push_back(TestedNode+outputdelim+Rhs);
            }
            
            
        }
    }
    return AdjacencyList;
    
}

int
main ()
{
    ofstream myfile ("aa.txt");
    int size ,k;
    cin >>  k ;
    vector <string> Patterns;
    vector <string> AdjacencyList;
    for (int i = 0; i < 2177; i++)
    {
        string a;
        cin >> a;
        Patterns.push_back(a);
    }
    AdjacencyList = DeBruijnFromPatterns(Patterns,k);
    for (int i = 0; i < AdjacencyList.size()-1; i++)
    {
        myfile << AdjacencyList[i]<<"\n";
    }
    myfile << AdjacencyList[AdjacencyList.size()-1];
    
    
}