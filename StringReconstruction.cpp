#include <vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<time.h>
#include<fstream>



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

vector <string> 
FindTotalNodes(vector <string> Nodes, vector <vector <string>> ConnectedToNodes )
{
    vector <string> TotalNodes = Nodes;
    string TestedNode,ComparedWithNode;
    int Count1,Count2,Count3;
    Count1 = Nodes.size();

    for (int i = 0; i < Count1; i++)
    {
        Count2 = ConnectedToNodes[i].size();
        for (int j = 0; j < Count2; j++)
        {
            string TestedNode = ConnectedToNodes[i][j];
            bool flag = 1;
            
            int Count3 = TotalNodes.size();
            for (int jj = 0; jj < Count3; jj++)
            {
                ComparedWithNode = TotalNodes[jj];
                if (ComparedWithNode == TestedNode)
                {
                    flag = 0;
                    break;
                }
                
            }

            if (flag)
            {
                TotalNodes.push_back(TestedNode);
            }
        }
        
    }
    return TotalNodes;
}

vector <int>
FindOutDegree(vector <string> Nodes , vector <string> TotalNodes , vector < vector <string>> ConnectedToNodes)
{
    vector <int> OutDegrees;
    for (int i = 0; i < TotalNodes.size(); i++)
    {
        if (i < Nodes.size())
        {
            int OutDegree = ConnectedToNodes[i].size();
            OutDegrees.push_back(OutDegree);
        }
        if (i >= Nodes.size())
        {
            OutDegrees.push_back(0);
        }
    }
    return OutDegrees;
}

vector <int>
FindInDegree(vector <string> Nodes , vector <string> TotalNodes , vector < vector <string>> ConnectedToNodes)
{
    vector <int> InDegrees;
   /*
    1 ) identify The Node to compare with in TotalNodes
    2 ) Compare it across all nodes found on The ConnectedToNodes
    3) if it equal a node in ConnectedToNodes increment Indegree
    4) push back InDegree inside InDegrees
   */
  for (int i = 0; i < TotalNodes.size(); i++)
  {
      string TestedNode = TotalNodes[i]; //1 ) identify The Node to compare with in TotalNodes
      int InDegree = 0;
      for (int NodePos = 0; NodePos < Nodes.size() ; NodePos++)
      {
          for (int ConnectedToNodePos = 0; ConnectedToNodePos <ConnectedToNodes[NodePos].size() ; ConnectedToNodePos++)
          {
              string ComparedWithNode = ConnectedToNodes[NodePos][ConnectedToNodePos];
              if (ComparedWithNode == TestedNode)
              {
                  InDegree++;
              }
          }
      }
      InDegrees.push_back(InDegree);
  }
  
         
    
    
    return InDegrees;
}

vector <int> 
FindDegree (vector <int> OutDegrees , vector <int> Indegrees , vector <string> TotalNodes )
{
    vector <int> Degrees ;
    for (int i = 0; i < TotalNodes.size(); i++)
    {
        Degrees.push_back(OutDegrees[i] - Indegrees[i]);
    }
    return Degrees;
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

    int StartNodePos = rand() % NumberOfNodes;
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
EulerianPath(vector <string> AdjacencyList)
{
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
    
    vector <string> FakeAdjacencyList = AdjacencyList;
    vector <string>TotalNodes ;
    TotalNodes = FindTotalNodes(Nodes , ConnectedToNodes);
    vector <int>  InDegrees , OutDegrees , Degrees;
    OutDegrees = FindOutDegree(Nodes , TotalNodes , ConnectedToNodes);
    InDegrees = FindInDegree(Nodes , TotalNodes , ConnectedToNodes);
    Degrees = FindDegree(OutDegrees , InDegrees , TotalNodes);

    string Start , End;
    
    for (int i = 0; i < Degrees.size(); i++)
    {
        if (Degrees[i] == 1)
        {
            Start = TotalNodes[i]; 
        }
        if (Degrees[i] == -1)
        {
            End = TotalNodes[i];
        }
        
    }
    FakeAdjacencyList.push_back( End + " -> " + Start);
    
     vector <string> OnNodes = EulerianCycle(FakeAdjacencyList);
     OnNodes.pop_back();
     int StartPos ;
     for (int i = 0; i < OnNodes.size(); i++)
     {
         if (OnNodes[i] == End && OnNodes[i+1] == Start)
         {
             StartPos = i+1;
             break;
         }
     }
     vector <string> Path ;
     for (int i = StartPos; i < OnNodes.size(); i++)
     {
         Path.push_back(OnNodes[i]);
     }
     for (int i = 0; i < StartPos; i++)
     {
         Path.push_back(OnNodes[i]);
     }
     
  return Path;   
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
    vector <string> Path = EulerianPath(Db);
    string Genome = PathToGenome(Path);
    return Genome;
}

int
main()
{
    int k;
    cin >> k;
    ofstream myfile ("aa.txt");
    vector <string> Patterns;
    for (int i = 0; i < 2216; i++)
    {
        string a;
        cin >> a;
        Patterns.push_back(a);
    }
    myfile << StringReconstruction(Patterns,k);
}