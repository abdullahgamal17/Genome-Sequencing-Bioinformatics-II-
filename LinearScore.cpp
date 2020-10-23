#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector <string>
CreateLinearSubPeptides(string Peptide)
{
    vector <string> LinearSubPeptides;
    for (int i = 1; i < Peptide.length(); i++)
    {
        int LengthOfSubPeptide = i;
        for (int j = 0; j <= Peptide.length() - LengthOfSubPeptide; j++)
        {
            string LinearSubPeptide = Peptide.substr(j,i);
            LinearSubPeptides.push_back(LinearSubPeptide);
        }
        
    }
    LinearSubPeptides.push_back(Peptide);
    return LinearSubPeptides;
}

vector <int>
CycloSpectrum(string Peptide)
{
    vector <string> SubPeptides = CreateLinearSubPeptides(Peptide);
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

vector <int>
ScoreRepresentation(string Peptide)
{
    // Score is determined by the number of times a mass is found in the theoritical Spectrum
    vector<int> TheoriticalSpectrum , Score, UniqueTheoriticalSpectrum;
    TheoriticalSpectrum = CycloSpectrum(Peptide);
    UniqueTheoriticalSpectrum = TheoriticalSpectrum;
    UniqueTheoriticalSpectrum.erase(unique(UniqueTheoriticalSpectrum.begin(),UniqueTheoriticalSpectrum.end()),UniqueTheoriticalSpectrum.end());
    for (int i = 0; i < UniqueTheoriticalSpectrum.size(); i++)
    {
        int TestedSpectra = UniqueTheoriticalSpectrum[i];
        int TestedSpectraScore = 0;
        for (int j = 0; j < TheoriticalSpectrum.size(); j++)
        {
            int TestedAgainst = TheoriticalSpectrum[j];
            if (TestedAgainst == TestedSpectra)
            {
                TestedSpectraScore++;
            }
        }
        Score.push_back(TestedSpectraScore);
    }
    return Score;
}

int
Score(string Peptide,vector <int> ExperimentalSpectrum)
{
    int Score = 0;
    vector <int> ScoreRepresentated = ScoreRepresentation(Peptide);
    vector <int> TheoriticalSpectrum = CycloSpectrum(Peptide);
    vector <int> UniqueExperimentalSpectrum = ExperimentalSpectrum;
    UniqueExperimentalSpectrum.erase(unique(UniqueExperimentalSpectrum.begin(),UniqueExperimentalSpectrum.end()),UniqueExperimentalSpectrum.end());
    vector <int> UniqueTheoriticalSpectrum = TheoriticalSpectrum;
    UniqueTheoriticalSpectrum.erase(unique(UniqueTheoriticalSpectrum.begin(),UniqueTheoriticalSpectrum.end()),UniqueTheoriticalSpectrum.end());
    int SpotOnScoreRepresented = -1;
    for (int i = 0; i < UniqueTheoriticalSpectrum.size(); i++)
    {
        int TestedSpectra = UniqueTheoriticalSpectrum[i];
        int TestedSpectraScore = 0;
        int MaxTestedSpectraScore;
        
        
        for (int j = 0; j < ExperimentalSpectrum.size(); j++)
        {
            int TestedAgainst = ExperimentalSpectrum[j];
            for (int ii = 0; ii < UniqueTheoriticalSpectrum.size(); ii++)
        {
            if (TestedAgainst == UniqueTheoriticalSpectrum[ii])
            {
                SpotOnScoreRepresented = ii;
                MaxTestedSpectraScore = ScoreRepresentated[SpotOnScoreRepresented];
                break;
            }
        }
            if (TestedSpectra == TestedAgainst && TestedSpectraScore < MaxTestedSpectraScore)
            {
                TestedSpectraScore++;
            }
            
        }
        
        Score += TestedSpectraScore;
    }
    return Score;
}

int main()
{
    string Peptide;
    vector <int> ExperimentalSpectrum;
    cin >> Peptide;
    // Enter Experimental Spectrum in a
    string a ="0 97 97 129 129 194 203 226 226 258 323 323 323 355 403 452";
    // Parsing Block Start
    string rhs = a;
    for (int i = 0; i < (Peptide.length() * (Peptide.length()-1)) +1; i++)
    {
        
        
        string delim = " ";
        int pos = rhs.find(delim);
        string lhs;
        if (pos != string::npos)
        {
            lhs = rhs.substr(0,pos);
            ExperimentalSpectrum.push_back(stoi(lhs));
            rhs = rhs.substr(pos+delim.length(), a.length()-1);
        }
        
        if (pos == string::npos)
        {
            ExperimentalSpectrum.push_back(stoi(rhs));
        }
        
    }
    //Parsing Block End
    int aa = Score(Peptide,ExperimentalSpectrum);
    cout << aa;
}