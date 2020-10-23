#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;



string
ProteinTranslate(string RNASequence)
{
    vector <string> Translation = {"G -> GGA,GGC,GGG,GGU","A -> GCA,GCC,GCG,GCU","L -> CUA,CUU,CUC,CUG,UUA,UUG","M -> AUG","F -> UUU,UUC","W -> UGG","K -> AAA,AAG","Q -> CAA,CAG","E -> GAA,GAG","S -> AGC,AGU,UCA,UCC,UCG,UCU","P -> CCA,CCC,CCG,CCU","V -> GUA,GUC,GUG,GUU","I -> AUA,AUC,AUU","C -> UGU,UGC","Y -> UAU,UAC","H -> CAC,CAU","R -> AGA,AGG,CGA,CGC,CGG,CGU","N -> AAC,AAU","D -> GAC,GAU","T -> ACA,ACC,ACG,ACU","STOP -> UAA,UAG,UGA"};
    vector <string> AminoAcids;
    vector <string> AminoFromRNA;
    vector <string> RNAToAmino;
    vector <vector <string>> RNAGivesAminoAcid;
    vector <string> RNACodons;
    vector <string> rhss;
    string Protein;
    for (int i = 0; i < Translation.size(); i++)
    {
        
        rhss.clear();
        string delim = " -> ";
        int pos = Translation[i].find(delim);
        string lhs , rhs;
        if (pos != string::npos)
        {
            lhs = Translation[i].substr(0,pos);
            AminoAcids.push_back(lhs);
            rhs = Translation[i].substr(pos+delim.length(), Translation[i].length()-1);
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
        
        RNAGivesAminoAcid.push_back(rhss);
    }
    //Parsing Block End
    for (int i = 0; i < 20; i++)
    {
        string Amino = AminoAcids[i];
        for (int j = 0; j < RNAGivesAminoAcid[i].size(); j++)
        {
            string RNA = RNAGivesAminoAcid[i][j];
            RNAToAmino.push_back(RNA);
            AminoFromRNA.push_back(Amino);
        }
        
    }

for (int i = 0; i < RNASequence.length(); i+=3)
{
    string OnRNA = RNASequence.substr(i,3);
    if (OnRNA == "UAA" || OnRNA == "UGA" ||OnRNA == "UAG" )
    {
        break;
    }
    else
    {
        for (int j = 0; j < 61; j++)
        {
            if (OnRNA == RNAToAmino[j])
            {
                Protein += AminoFromRNA[j];
                break;
            }   
        }
    }
    
}   
    return Protein;
}


int
main()
{
    fstream myfile("aa.txt");
    string RNASequence;
    // Enter RNASequence Manual
    cin >> RNASequence;
    string Protein = ProteinTranslate(RNASequence);
    cout << Protein;
}