#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <unordered_set>
#include <queue>
#include <set>
#include <sstream>
#include <stack>

#include <vector>
using namespace std;

//represent each minterm with its number and binary representation 
ofstream out;

struct t
{
    int number;
    string binary;
    bool taken = false;

    t(int number)
    {
        this->number = number;
        taken = false;
    }
    t()
    {
        this->number = -1;
        taken = false;
    }
};

//to be used in step of circling 2 ones 
struct s2
{
    int term1, term2;
    string binary;
    bool taken = false;
};

//to be used in step of circling 4 ones 
struct s3
{
    int term1, term2, term3, term4;
    string binary;
};

vector<string> getTestCases(int& testcases) {
    vector<string> S;
    ifstream file;
    string path;
    cout << "please enter the testcases path:\n ";
    cin >> path;
    file.open(path);
    if (!file) {
        out << "error opening the file\n";
        exit(1);
    }
    file >> testcases;
    while (!file.eof()) {
        string temp;
        getline(file, temp);
        S.push_back(temp);
    }
    return S;
}
vector<t> getInput( string s,int& numVar) {
    string T;
    vector<t> minterms;
    unordered_map<int,t> setMinterms;
    stringstream X(s);
    int i = 0;
    while (getline(X, T, ' '))
    {
        if (!i) {
            numVar = T[0] - '0';
            i++;
            continue;
        }
        t temp(int(T[0] - '0'));
        setMinterms[temp.number] = temp;
        i++;
    }
    for (auto i : setMinterms) {
        minterms.push_back(i.second);
    }
    return minterms;
}
void checkInput(int variables, vector<t> terms)
{
    // Check if the minterm should not exist   
    if (terms.size() == 0)
        return;

    for (int i = 0; i < terms.size(); i++)
    {
        if (terms[i].number > pow(2, variables) - 1)
        {
            out << " Error , " << terms[i].number << " is out of range ! ";
            exit(1);
        }

    }
    //Check if there is a repeated term  
    for (int i = 0; i < terms.size() - 1; i++)
    {
        if (terms[i].number == terms[i + 1].number)
        {
            out << "The minterm " << terms[i].number << " is repeated !" << endl;
            exit(1);
        }
    }
}

/*  
    //getting the simplified expression 2x2
    vector<string> minterms;
    for(int i = 0; i < minterms_2.size(); i++)
    {
        minterms_2_b.push_back((minterms_2[i]));
    }


    for(int i = 0; i < minterms.size(); i++)
    {
        cout << minterms.[i].number;
        if(minterms.size() - i > 1)
            cout << " + ";
    }
    }

    else if(numOfOnes[0][0] && numOfOnes[0][1] && numOfOnes[1][0] && numOfOnes[1][1])
    {
        cout << "1";
    }

    else
    {
    for(int i = 0; i < minterms.size(); i++)
        {
            cout << minterms[i].number;
            if(minterms.size() - i > 1)
                cout << " + ";
        }
    }

    cout << endl << endl;
    }
}*/


int main()
{
    out.open("output.txt");
    //read from user the number of minterms 
    cout << "*" << "Hello, This is a Three-Variable K-Map Logic Minimization program" << "*" << endl;

    int numVar;
    int testcases;
    vector<string> S;
    S = getTestCases(testcases);
    int testCaseNum = 1;
    while (testcases--)
    {
        vector<t> minterms = getInput(S[testCaseNum],numVar);


        //special case: when number of minterms is 0, then the function is f = 0 (all cell are 0s) 
        if (minterms.size() == 0)
        {
            out << "K-map =" << endl;
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 4; j++)
                    out << "0  ";
                out << endl;
            }
            out << "\nF = 0\n";
        }

        //other cases 
        else
        {
            checkInput(numVar, minterms);
            unordered_map <int, bool> covered;         // to be used in evaluating the final result: it indicates whether each minterm is included in the result or not 
            //read minterms from the user 

            for (int i = 0; i < minterms.size(); i++)
            {
                covered[minterms[i].number] = false;

                if (numVar == 3) {
                    //assign each minterm its binary representation 
                    if (minterms[i].number == 0) minterms[i].binary = "000";
                    else if (minterms[i].number == 1) minterms[i].binary = "001";
                    else if (minterms[i].number == 2) minterms[i].binary = "010";
                    else if (minterms[i].number == 3) minterms[i].binary = "011";
                    else if (minterms[i].number == 4) minterms[i].binary = "100";
                    else if (minterms[i].number == 5) minterms[i].binary = "101";
                    else if (minterms[i].number == 6) minterms[i].binary = "110";
                    else if (minterms[i].number == 7) minterms[i].binary = "111";
                }
                else 
                {
                    if (minterms[i].number == 0) minterms[i].binary = "00";
                    else if (minterms[i].number == 1) minterms[i].binary = "01";
                    else if (minterms[i].number == 2) minterms[i].binary = "10";
                    else if (minterms[i].number == 3) minterms[i].binary = "11";
                }

            }
            int krk = 1;
            //print the k-map 
            out << krk << endl;
            krk++;
            out << "\nK-map= \n" << endl;

            bool flag = false;

            for (int i = 0; i < (1 << numVar) ; i++)
            {
                for (int j = 0; j < minterms.size(); j++)
                {
                    if (i == 2 || i == 6)
                    {
                        if (minterms[j].number == (i + 1))
                        {
                            out << 1 << "     ";

                            flag = true;
                            break;
                        }
                    }

                    else if (i == 3 || i == 7)
                    {

                        if (minterms[j].number == (i - 1))
                        {
                            out << 1 << "     ";
                            flag = true;
                            break;
                        }
                    }

                    else
                    {
                        if (minterms[j].number == i)
                        {
                            out << 1 << "     ";
                            flag = true;
                            break;
                        }
                    }
                }

                if (!flag)
                {
                    out << 0 << "     ";
                }
                if (i == 3)
                    out << endl;

                flag = false;
            }



            //grouping the minterms with respect to number of 1s in their binary representation 
            vector <vector<t>> numOfOnes(numVar+1);
            for (auto y : minterms)
            {
                if (y.number == 0) numOfOnes[0].push_back(y);                                          //0 ones 
                else if (y.number == 1 || y.number == 2 || y.number == 4) numOfOnes[1].push_back(y);   //1 one 
                else if (y.number == 3 || y.number == 5 || y.number == 6) numOfOnes[2].push_back(y);   //2 ones 
                else if (y.number == 7) numOfOnes[3].push_back(y);                                     //3 ones 
            }


            //circling possible 2 adjacent ones together to make a pair of ones 
            vector <vector<s2>> matched_pairs1(3);
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < (int)numOfOnes[i].size(); j++)
                {
                    for (int k = 0; k < (int)numOfOnes[i + 1].size(); k++)
                    {
                        int counter = 0, idx;
                        for (int l = 0; l < 3; l++)
                            if (numOfOnes[i][j].binary.at(l) != numOfOnes[i + 1][k].binary.at(l))  //if the same bit index is different 
                            {
                                counter++;
                                if (counter == 1) idx = l; //store the index 
                            }

                        //if the two minterms differ in only one bit, then circle these 2 minterms together 
                        if (counter == 1)
                        {
                            numOfOnes[i][j].taken = true;
                            numOfOnes[i + 1][k].taken = true;

                            //the new binary representation after combining the two minterms 
                            string  y = numOfOnes[i][j].binary;
                            y.at(idx) = '-';

                            //add the combined 2 minterms for the next step 
                            matched_pairs1[i].push_back({ numOfOnes[i][j].number, numOfOnes[i + 1][k].number, y });
                        }
                    }
                }
            }

            //circling possible 4 adjacent ones together to make 2 pairs of ones 
            vector<vector<s3>> matched_pairs2(2);
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < (int)matched_pairs1[i].size(); j++)
                {
                    for (int k = 0; k < (int)matched_pairs1[i + 1].size(); k++)
                    {
                        int counter = 0, idx;
                        for (int l = 0; l < 3; l++)
                            if (matched_pairs1[i][j].binary.at(l) != matched_pairs1[i + 1][k].binary.at(l)) //if the same bit index is different 
                            {
                                counter++;
                                if (counter == 1) idx = l;
                            }

                        if (counter == 1)
                        {
                            matched_pairs1[i][j].taken = true;
                            matched_pairs1[i + 1][k].taken = true;

                            //the new binary representation after combining the two minterms 
                            string  y =

                                matched_pairs1[i][j].binary;
                            y.at(idx) = '-';

                            //add the combined 4 minterms for the final step 
                            matched_pairs2[i].push_back({ matched_pairs1[i][j].term1, matched_pairs1[i][j].term2,
                                                         matched_pairs1[i + 1][k].term1, matched_pairs1[i + 1][k].term2, y });
                        }
                    }
                }
            }


            //constructing the table of all prime implicants 
            unordered_map <int, vector<string>> prime;  // for every minterm, which expression/binary representation include it 

            //minterms not included in the next simplification step 
            for (int i = 0; i < 4; i++)
                for (auto x : numOfOnes[i])
                    if (!x.taken)
                    {
                        prime[x.number].push_back(x.binary);
                    }

            //minterms not included in the next simplification step 
            for (int i = 0; i < 3; i++)
                for (auto x : matched_pairs1[i])
                    if (!x.taken)
                    {
                        prime[x.term1].push_back(x.binary);
                        prime[x.term2].push_back(x.binary);
                    }


            for (int i = 0; i < 2; i++)
                for (auto x : matched_pairs2[i])
                {
                    prime[x.term1].push_back(x.binary);

                    prime[x.term2].push_back(x.binary);

                    prime[x.term3].push_back(x.binary);

                    prime[x.term4].push_back(x.binary);
                    break;
                }

            set <string> result;
            unordered_map <string, vector<int>> mapp;

            for (auto x : prime)
                for (auto y : x.second)
                    mapp[y].push_back(x.first);

            for (auto x : prime)
                if (x.second.size() == 1)
                    result.insert(x.second[0]);


            for (auto x : result)
                for (auto y : mapp[x])
                    covered[y] = true;

            for (auto x : covered)
                if (!x.second)
                {
                    result.insert(prime[x.first][0]);
                    x.second = true;
                }


            //    for(auto x: result) 
            //        out<<x<<endl; 

            string finall = "";
            for (auto x : result)
            {
                string temp = "";
                if (x[0] == '0') temp += "A'";
                else if (x[0] == '1') temp += "A";

                if (x[1] == '0') temp += "B'";
                else if (x[1] == '1') temp += "B";

                if (x[2] == '0') temp += "C'";
                else if (x[2] == '1') temp += "C";

                finall += temp + " + ";

            }

            finall = finall.substr(0, finall.size() - 3);
            out << "\n\nSimplest function f= " << finall << "\n";


            /*   Test conditions used while working on the project   */

            //    for(auto x: prime) 
            //    { 
            //        for(auto y: x.second) 
            //        { 
            //            out<<x.first<<"  "<<y<<endl; 
            //        } 
            //    } 


            //    for (int i = 0 ; i<2 ; i++) 
            //        for (auto x: matched_pairs2[i]) 
            //        { 
            //            printf("%d-%d-%d-%d  ", x.term1, x.term2, x.term3, x.term4); 
            //            out<<x.binary<<endl; 
            //        } 


            //    for (int i = 0 ; i<4 ; i++) 
            //    { 
            //        for (auto x: numOfOnes[i]) 
            //            out<<x.number<<"  "<<x.binary<<"  "<<x.taken<<endl; 
            //    } 
            // 
            //    out<<endl<<endl; 
            // 
            //    for (int i = 0 ; i<3 ; i++) 
            //    { 
            //        for(auto x: matched_pairs1[i]) 
            //        { 
            //            out<<x.term1<<"-"<<x.term2<<"   "<<x.binary<<"  "<<x. taken<<endl; 
            //        } 
            // 
            //    } 


            //    for (int i =0 ; i<4 ; i++) 
            //    { 
            //        out<<i<<": "; 
            //        for (auto x :numOfOnes[i]) 
            //        { 
            //            out<<"  "<<x<<"  "; 
            //        } 
            //        out<<endl; 
            //    } 


        }

    }


    return 0;
}