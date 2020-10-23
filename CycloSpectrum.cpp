#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <time.h>
#include <fstream>

using namespace std;

vector <string>
CreateSubPeptides(string Peptide)
{
    vector <string> SubPeptides;
    for (int i = 1; i < Peptide.length(); i++)
    {
        int LastStartPos = Peptide.length() - i;
        string SubPeptide;
        for (int j = 0; j < Peptide.length(); j++)
        {
            if (j <= LastStartPos )
            {
                SubPeptide = Peptide.substr(j,i);
            }
            if (j > LastStartPos)
            {
                SubPeptide = Peptide.substr(j,i);
                int NumberOfCharsFromStart = i - SubPeptide.length();
                for (int jj = 0; jj < NumberOfCharsFromStart ;jj++)
                {
                    SubPeptide += Peptide[jj]; 
                }
            }
            SubPeptides.push_back(SubPeptide);
        }
       
    }
    SubPeptides.push_back(Peptide);
    return SubPeptides;
}

vector <int>
CycloSpectrum(string Peptide)
{
    vector <string> SubPeptides = CreateSubPeptides(Peptide);
    vector <char> AminoAcids = {'G', 'A', 'S', 'P', 'V', 'T', 'C', 'I', 'L', 'N', 'D', 'K', 'Q', 'E', 'M', 'H', 'F', 'R', 'Y', 'W'};
    vector <int> AminoAcidsMasses = {57, 71, 87, 97, 99, 101, 103, 113, 113, 114, 115, 128, 128, 129, 131, 137, 147, 156, 163, 186};
    vector <int> CycloSpectrum;
    CycloSpectrum.push_back(0);
    for (int i = 0; i < SubPeptides.size(); i++)
    {
        int SubPeptideMass = 0;
        for (int j = 0; j < SubPeptides[i].length(); j++)
        {
            char OnAminoAcid = SubPeptides[i][j];
            for (int jj = 0; jj < AminoAcids.size(); jj++)
            {
                if (AminoAcids[jj] == OnAminoAcid)
                {
                    int MassOfAminoAcid = AminoAcidsMasses[jj];
                    SubPeptideMass += MassOfAminoAcid;
                }   
            }
        }
        CycloSpectrum.push_back(SubPeptideMass);
    }
    sort(CycloSpectrum.begin() , CycloSpectrum.end());
    return CycloSpectrum;
}
int main()
{
    ofstream myfile ("aa.txt");
    vector <int> a = CycloSpectrum("IAMT");
    for (int i = 0; i < a.size()-1; i++)
    {
        cout << a[i] <<" ";
    }
    cout<< a[a.size()-1];
    
}