#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

vector <string>
CreateEdges(vector<string> Nodes , vector<vector<string>> ConnectedToNodes) // This function creates all possibles edges labeled as a string of start point to end point as from 0 to 3 is 03 
{
    unsigned int sizeoflhs = Nodes.size();
    vector <string> Edges ;
    for (int i = 0; i < sizeoflhs; i++)
    {
        unsigned int sizeofrhs = ConnectedToNodes[i].size();
        string lhs = Nodes[i];
        for (int j = 0; j < sizeofrhs; j++)
        {
            string rhs = ConnectedToNodes[i][j];
            string edge = lhs + "->" + rhs;
            Edges.push_back(edge);
        }
    }
    return Edges;
}

string
DecToBin(int n)
{
    string reversebinary;
    if (n == 0)
    {
        reversebinary = "0";
    }
    
    if (n > 0)
    {
        while (n >  0)
        {
            int remainder;
            remainder = n % 2;
            n /= 2;
            reversebinary += to_string(remainder);
        }
    }
    string binary;
    for (int i = reversebinary.length()-1; i >= 0; i--)
    {
        binary += reversebinary[i];
    }
    return binary;
}

vector <string> AllPossibleBinaries(int k)
{
    vector <string> AllPossibleBinary;
    
    for (int i = 0; i < pow(2,k); i++)
    {
        AllPossibleBinary.push_back(DecToBin(i));
    }
    return AllPossibleBinary;
}

vector <string>
FormatBinaries(vector <string> AllPossibleBinary , int k )
{
    vector <string> FormatedAllPossibleBinary;
    for (int i = 0; i < AllPossibleBinary.size(); i++)
    {
        
        string Original = AllPossibleBinary[i];
        string Formated = Original;
        if (Original.length() < k)
        {
            int NumberAddedZeroes = k - Original.length();
            
            for (int j = 0; j < NumberAddedZeroes; j++)
            {
                Formated = "0" + Formated;
            }
            FormatedAllPossibleBinary.push_back(Formated);
        }
        if (AllPossibleBinary[i].length() == k )
        {
            FormatedAllPossibleBinary.push_back(AllPossibleBinary[i]);
        }
        
        
    }
    return FormatedAllPossibleBinary;
}


vector <string>
EulerianCycle(vector<string> AdjacencyList) // Finds Eulerian Circle
{
    vector <string> OnNodes;
    string outputdelim ="->";
    
    
    // vectors used in parsing
    
    vector <string> rhss;
    vector <string> Nodes; //stores all vertices on the left hand side (Nodes)
    vector < vector <string> > ConnectedToNodes; // stores all vertices connected to the vertices in left hand side
    
    //vectors used in parsing end
    
    // Parsing Block Start
    for (int i = 0; i < AdjacencyList.size(); i++)
    {
        
        rhss.clear();
        string delim = " -> ";
        int pos = AdjacencyList[i].find(delim);
        string lhs , rhs;
        if (pos != string::npos)
        {
            lhs = AdjacencyList[i].substr(0,pos);
            Nodes.push_back(lhs);
            rhs = AdjacencyList[i].substr(pos+delim.length(), AdjacencyList[i].length()-1);
        }
        char delim2 = ',';
        int flag = 1;
        while (flag)
        {
            int pos2 = rhs.find(delim2);
            string lhs2 = rhs.substr(0,pos2);
            string rhs2 = rhs.erase(0,pos2+1);
            rhss.push_back(lhs2);
                if (pos2 == string::npos)
                {
                    flag = 0;
                }
        }
        
        ConnectedToNodes.push_back(rhss);
    }
    //Parsing Block End

    
    
    vector <string> Edges; //stores all edges created
    Edges = CreateEdges(Nodes,ConnectedToNodes); // Here it stores all edges 
    int NumberOfNodes = Nodes.size(); //Creates Number of Nodes to work with

    srand(time(NULL)); // seeds rand by time on computer by seconds to be random

    int StartNodePos = 0;
    string StartNode = Nodes[StartNodePos];
    int NodePos = StartNodePos; // Initializes NodePos with StartNodePos as it is the first Node
    OnNodes.push_back(StartNode);//stores Start Node as OnNodes[0]

    /*
    ***************************************************************Algorithm*************************************************
            form a cylce by randomly walking in the graph (DON'T VISIT THE SAME EDGE TWICE !) (Step 1)
            while (there are unexplored edges in Graph) (Step 2)
            select Node NewStart in Cycle with still uneplored edges(i.e still contains ConectedToNodes)
                form Cycle' (here i will name it Cycle2) by traversng Cycle (Starting at NewStart)
                and then randomly walking
                Cycle <- Cycle'
            return Cycle
    **************************************************************************************************************************        
    */

    string Cycle,Cycle2; // Initializes both Cycle and Cycle' (named Cycle2)
    int flag = 1; // Initializes flag by 1 (true) that will be used in while loop used in traversing Cycle
    Cycle = StartNode ; // Initializes Cycle by assigning it with StartNode

    vector <string> TempEdges = Edges; // Initializes TempEdges that Edges will be deleted from by inserting Edges To it
    vector <vector <string>> TempConnectedToNodes = ConnectedToNodes; //Initializes TempConnectedToNodes by inserting ConnectedToNodes so that it will be deleted from
    vector <string> CreatedEdgesinCycle;
    while (flag) // Creates Cycle By Walking Randomly (Step 1) || First I Created a loop till stuck
    {
        string OnNode = OnNodes[OnNodes.size()-1]; // OnNode is the Node on which we are on
        int NumberOfEdges = TempConnectedToNodes[NodePos].size() ; //NumberOfEdges remaining is determined by the size of vector which corresponds to NodePos (the position of Current Node)
        int ChosenConnectedNodePos; // Initializes the variable where the Node will go to
        ChosenConnectedNodePos = rand() % NumberOfEdges ; // Chooses randomly which ConnectedNode we will visit to create corresponding Edge (OnNode->ConnectedNode)
        string ChosenConnectedNode = TempConnectedToNodes[NodePos][ChosenConnectedNodePos]; // stores the ConnectedNode Chosen
        TempConnectedToNodes[NodePos].erase(TempConnectedToNodes[NodePos].begin() + ChosenConnectedNodePos);// Erases ChoosenConnectedNode from TempConnectedToNodes
        string CreatedEdge = OnNode + outputdelim +ChosenConnectedNode; // Creates CreatedEdge in The Format (OnNode->ChoosenConnectedNode)
        CreatedEdgesinCycle.push_back(CreatedEdge);
        TempEdges.erase(remove(TempEdges.begin(),TempEdges.end() , CreatedEdge),TempEdges.end()); // Removes From TempEdges The CreatedEdge after visiting it so we can't visit it again
        Cycle = Cycle + "->" + ChosenConnectedNode; // adds ->ChosenConnectedNode to Cycle Thus widening the cycle
        OnNodes.push_back(ChosenConnectedNode); // pushes back ChoosenConnctedNodes as it will be The next node after incrementing OnPos by 1
        string a = OnNodes[OnNodes.size()-1]; //creates string a which will be compared across all Nodes to find NodePos
        for (int i = 0; i < Nodes.size(); i++)
        {
            if (a == Nodes[i]) // finds the NodePos by comparing it across all Nodes and find the one which matches as they are unique
            {
                NodePos = i;
            }   
        }
        if (TempConnectedToNodes[NodePos].empty() == 1) // if there is No ConnectedNodes in TempConnectedToNode
        {
            flag = 0;
        }   
    }

   
   
    while (TempEdges.empty() != 1) //while there are Unexplored Edges in the graph is the condition
        {
            // Finding The Node which still has TempConnectedToNodes  i.e (NewStart)(Start)
            string NewStart;
            int NewStartPosinNodes;
            int NewStartPosinOnNodes;
            bool EnteredFindNewStart = 0;
            if (TempConnectedToNodes[NodePos].empty() == 1) // if there is no Nodes Connected to The Node We are on
            {
                EnteredFindNewStart = 1;
                for (int i = 0; i < OnNodes.size() - 1; i++) // This loop is to visit all nodes visited in the cycle
                {
                    bool toExit = 0; // indicates that we should leave bigger loop when finding NewStart
                    string TestedNode = OnNodes[i]; // TestedNode is the node that we are checking if it still has any unexplored edges
                    int TestedNodePosinNodes; //TestedNodePosinNodes is the position of TestedNode in Nodes
                    int TestedNodePosinOnNodes; // TestedPosinOnNodes is the position of TestedNodes in OnNodes
                    for (int j = 0; j < Nodes.size() ; j++) // This Loops is to go all over Nodes in Nodes
                    {
                        if (TestedNode == Nodes[j]) // if TestedNode is equal to Nodes[j] then its position is j in Nodes() and i in OnNodes
                        {
                            TestedNodePosinNodes = j;
                            TestedNodePosinOnNodes = i;
                            
                                if (TempConnectedToNodes[TestedNodePosinNodes].size() > 0) //If testedNode has any node to travel to 
                                {
                                    NewStart = TestedNode; // NewStart is the tested Node
                                    NewStartPosinNodes = TestedNodePosinNodes; // Position of NewStart is The TestedNodePosinNodes in Nodes
                                    Cycle2 = NewStart;
                                    NewStartPosinOnNodes = TestedNodePosinOnNodes;// Position of NewStart is The TestedNodePosinOnNodes in OnNodes
                                    OnNodes.push_back(NewStart);
                                    

                                    toExit = 1; // this indicates that NewStart was found
                                    break;
                                }
                        }
                        
                    }
                    if (toExit == 1) // if NewStart is Found we should exit
                    {
                        break;
                    }
                }
            }
            // Finding The Node which still has TempConnectedToNodes  (End)
            
            NodePos = NewStartPosinNodes;// NodePos is NewStartPosinNodes in Nodes
            

            
        
        if (EnteredFindNewStart) // When you get stuck start from Newstart then form the Old loop and end at newstart
        {
            for (int i = NewStartPosinOnNodes + 1 ; i < OnNodes.size() - 1 ; i++)
            {
                Cycle2 = Cycle2 + outputdelim + OnNodes[i];
                
            }

            for (int i = 1 ; i <= NewStartPosinOnNodes; i++)
            {
                Cycle2 = Cycle2 + outputdelim + OnNodes[i];
            }
            
            
            EnteredFindNewStart = 0;
        }
        
        string rhsss = Cycle2;// Creates a copy of Cycle2 to be parsed without damaging Cycle2
        
        for (int i = 0; i < OnNodes.size() ; i++)//Parses Cycle2 and inputs it in OnNodes with corret steps according to Cycle2
        {
            string lhs ;
            lhs = rhsss.substr(0,rhsss.find("->"));
            OnNodes[i] = lhs;
            rhsss.erase(0,rhsss.find("->")+outputdelim.length());
        }
        OnNodes.pop_back(); // pops out last element as it is useless 
        
            flag = 1;
            while (flag) // Creates Cycle By Walking Randomly from newstart
            {
            string OnNode = OnNodes[OnNodes.size()-1]; // OnNode is the Node on which we are on
            int NumberOfEdges = TempConnectedToNodes[NodePos].size() ; //NumberOfEdges remaining is determined by the size of vector which corresponds to NodePos (the position of Current Node)
            int ChosenConnectedNodePos; // Initializes the variable where the Node will go to
            ChosenConnectedNodePos = rand() % NumberOfEdges ; // Chooses randomly which ConnectedNode we will visit to create corresponding Edge (OnNode->ConnectedNode)
            string ChosenConnectedNode = TempConnectedToNodes[NodePos][ChosenConnectedNodePos]; // stores the ConnectedNode Chosen
            TempConnectedToNodes[NodePos].erase(TempConnectedToNodes[NodePos].begin() + ChosenConnectedNodePos);// Erases ChoosenConnectedNode from TempConnectedToNodes
            string CreatedEdge = OnNode + outputdelim +ChosenConnectedNode; // Creates CreatedEdge in The Format (OnNode->ChoosenConnectedNode)
            CreatedEdgesinCycle.push_back(CreatedEdge);
            TempEdges.erase(remove(TempEdges.begin(),TempEdges.end() , CreatedEdge),TempEdges.end()); // Removes From TempEdges The CreatedEdge after visiting it so we can't visit it again
            Cycle2 = Cycle2 + "->" + ChosenConnectedNode; // adds ->ChosenConnectedNode to Cycle Thus widening the cycle
            OnNodes.push_back(ChosenConnectedNode); // pushes back ChoosenConnctedNodes as it will be The next node after incrementing OnPos by 1
            string a = OnNodes[OnNodes.size()-1]; //creates string a which will be compared across all Nodes to find NodePos
            for (int i = 0; i < Nodes.size(); i++)
            {
                if (a == Nodes[i]) // finds the NodePos by comparing it across all Nodes and find the one which matches as they are unique
                {
                    NodePos = i;
                }   
            }
            if (TempConnectedToNodes[NodePos].empty() == 1) // if there is No ConnectedNodes in TempConnectedToNode
            {
            flag = 0;
            }
        }
        Cycle = Cycle2;      
    }

   
       
   return OnNodes;
   
}

vector <string>
DeBruijnFromPatterns(vector<string> Patterns , unsigned int k) // Finds Adjacency List
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

string
PathToGenome(vector <string> Path)
{
    string Genome = Path[0];
    int size = Path[0].size();
    for (int i = 1; i < Path.size(); i++)
    {
        Genome += Path[i][size - 1];
    }
    return Genome;
}

string
StringReconstruction(vector <string> Patterns , int k)
{
    vector <string> Db = DeBruijnFromPatterns(Patterns,k);
    vector <string> Path = EulerianCycle(Db);
    string Genome = PathToGenome(Path);
    for (int i = 0; i < k-1; i++)
    {
        Genome.pop_back();
    }
    
    return Genome;
}
   

int
main()
{
    int k;
    cin >> k;
    fstream myfile ("aa.txt");
    vector <string> AllPossibleBinary = AllPossibleBinaries(k);
    AllPossibleBinary = FormatBinaries(AllPossibleBinary,k);
    string aaa = StringReconstruction(AllPossibleBinary,k); 
    cout << aaa;
    
}

/*
For a string of length "n", if it is linear, then we will get "n-k+1" k-mers from it (last k-mer starting at index "n-k+1" if 1-indexed), but if it is circular, we will get all the previous "n-k+1" and "k-1" new k-mers, for a total of "n" k-mers (last k-mer starting at index "n" if 1-indexed). Additionally, since number of k-mers, say "p", for a linear string of length "n" is "n-k+1", it implies that "p = n-k+1", or "p+k-1 = n", i.e. from "p" k-mers we get a linear string of length "p+k-1".

Example: The number of 3-mers in string "ABCDE...VWXYZ" of length 26, if it is linear is 24 ("ABC", "BCD", ..., "XYZ"). But, if it is circular, we get 26 different 3-mers ("ABC", "BCD", ..., "XYZ", "YZA", "ZAB"), 24 from the linear aspect, plus "k-1 = 3-1 = 2" new ones since the string is circular, and wraps around to the beginning.

Now, to reconstruct the circular string "ABCDE...VWXYZ" from its "26" 3-mers ("ABC", "BCD", ..., "XYZ", "YZA", "ZAB"), we can generate a De-Bruijn graph of 2-mer ((k-1)-mer) nodes from the available 3-mers (k-mers, which are edges in the graph, remember?), and obtaining an Eulerian cycle in this graph (the 2-mer nodes will be suffix for one 3-mer and prefix for another 3-mer, given the circular nature of the string, hence all the nodes are balanced, and the graph will be strongly connected as the 3-mers are formed continuously from the string by shifting right one position at a time, thus graph is Eulerian), will give us the string "ABCDE...VWWXYZAB" of length 28 - the linear representation of the circular string reconstructed from its 3-mers (if we listed all the 3-mers from this representation, we would get all the 3-mers of the actual circular string, hence it's called linear representation of circular string reconstructed from its 3-mers).

This linear representation string, has length of 28, because having been formed from "p = n = 26" "k = 3"-mers it has length "n+k-1 = 26+3-1 = 26+2 = 28" and the last "2 = 3-1 = k-1" characters in the linear representation are same as the beginning "2 = 3-1 = k-1" characters, because they come from the last "k-1 = 3-1 = 2" edges in the Euler cycle, which in turn come from the last "k-1 = 3-1 = 2" new "k = 3"-mers, occurring due to the circular nature of the string.

Therefore, to get the actual circular string, (and not its linear representation from its k-mer composition) we have to either discard the last "k-1" edges in the Euler cycle, and then form the string - which will be circular, or simply discard the last "k-1" characters from the linear representation after it is formed.

The last "k-1" edges are necessary to ensure that the De-Bruijn graph formed is an Eulerian graph, and thus obtain an Euler cycle to get the linear representation of the circular string. But since circular strings are considered to wrap around, we have to discard the last "k-1" characters from the linear representation which are the same as its beginning "k-1" characters, to eliminate redundancy, and transform the linear representation into the circular string.

tldr: A linear string of length "n" has "n-k+1" k-mers while a circular string of same length will have "n" k-mers. The linear string formed from "p" k-mers is of length "p+k-1". Thus, the linear string, reconstructed from an Euler cycle in the De-Bruijn graph formed from the "n" k-mers of a circular string of length "n", will have length "n+k-1" and its last "k-1" characters will be the same as its beginning "k-1" characters. Thus, to convert this reconstructed linear string into a circular string, we simply discard its last "k-1" characters.
*/