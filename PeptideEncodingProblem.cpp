#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
string
CreateComplementary(string text)
{
    int t = text.length();
    string Complementary;
    for (int i = 0 ; i < t ; i++ )
    {
        char s = text[i];
        switch(s)
        {
            case 'A' :
            Complementary+= 'T';
            break;

            case 'T' :
            Complementary+='A';
            break;

            case 'G' :
            Complementary+= 'C';
            break;

            case 'C' :
            Complementary+= 'G';
            break;

        }
    }
    string rev;

    for (int i = t-1 ; i >= 0 ; i--)
    {
        rev += Complementary[i];
    }
    return rev;
}
string
ProteinTranslate(string RNASequence , vector <string> AminoFromRNA , vector <string> RNAToAmino)
{
    string Protein;
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

string
TranslateDNAToRNA(string DNASequence)
{
    string RNASequence;
    for (int i = 0; i < DNASequence.length(); i++)
    {
        char OnDNA = DNASequence[i];
        if (OnDNA == 'A')
        {
            RNASequence += 'A';
        }
        if (OnDNA == 'T')
        {
            RNASequence += 'U';
        }
        if (OnDNA == 'C')
        {
            RNASequence += 'C';
        }
        if (OnDNA == 'G')
        {
            RNASequence += 'G';
        }
         
    }
    return RNASequence;
}

string
TranslateRNAToDNA(string RNASequence)
{
    string DNASequence;
    for (int i = 0; i < RNASequence.length(); i++)
    {
        char OnRNA = RNASequence[i];
        if (OnRNA == 'A')
        {
            DNASequence += 'A';
        }
        if (OnRNA == 'U')
        {
            DNASequence += 'T';
        }
        if (OnRNA == 'C')
        {
            DNASequence += 'C';
        }
        if (OnRNA == 'G')
        {
            DNASequence += 'G';
        }
         
    }
    return DNASequence;
}
vector <string>
PeptideEncodingProblem(string DNASequence , string ProteinCreated)
{
    string MainRNASequence = TranslateDNAToRNA(DNASequence);
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

    vector <string> Results;
    int SizeofComparedRNASequence = ProteinCreated.length() * 3;
    for (int i = 0; i < MainRNASequence.length() - SizeofComparedRNASequence; i++)
    {
        string RNASequence = MainRNASequence.substr(i,SizeofComparedRNASequence);
        string MainDNASequence = DNASequence.substr(i,SizeofComparedRNASequence);
        string RevComp = CreateComplementary(MainDNASequence);
        string RevRNA = TranslateDNAToRNA(RevComp);
        string MadeProtein = ProteinTranslate(RNASequence,AminoFromRNA ,RNAToAmino);
        string ReverseMadeProtein = ProteinTranslate(RevRNA , AminoFromRNA , RNAToAmino);
        if (MadeProtein == ProteinCreated || ReverseMadeProtein == ProteinCreated)
        {
            Results.push_back(MainDNASequence);
        }
        
    }
    return Results;
}
int
main()
{
    fstream myfile("aa.txt");
    myfile.clear();
    string MainDNASequence,ProteinCreated;
    // Enter Given DNA Sequence below
    MainDNASequence ="";
    cin >> ProteinCreated;
    vector<string> Results = PeptideEncodingProblem(MainDNASequence,ProteinCreated);
    for (int i = 0; i < Results.size()-1; i++)
    {
        cout << Results[i] <<"\n";
    }
    cout << Results[Results.size()-1];
}