#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <typeinfo>
#include <stdlib.h>


using namespace std;


void print(vector<int> A) {
   cout << "The vector elements are : ";

   for(int i=0; i < A.size(); i++){
    cout << A[i] << ' ';
   }
   cout<<endl;
};

class GraphCut{
    public:
        map<int,vector<int>> graph;
        int mincut_count = 0;
        int number_edges = 0;
        int node1;
        int node2;


        GraphCut(map<int,vector<int>> g){
            graph=g;
            edge_count();
        }

        void edge_count(){
            int flag=1;
            for (const auto& [key, value] : graph){
                number_edges = number_edges+value.size();
            }
        }

        void rand_edge(){
            int rand_num = rand() % number_edges;
            int counter = 0;
            for (const auto& [key,value] : graph){
                counter = counter+value.size();
                if (counter>=rand_num){
                    node1=key;
                    node2=value[counter - rand_num];
                    cout<<'h';
                }
            }
        }

        void contraction(){
            while (number_edges>2){
                rand_edge();
                vector<int> val1 = graph.find(node1)->second;
                vector<int> val2 = graph.find(node2)->second;
                val1.insert(val1.end(),val2.begin(),val2.end());
                graph.find(node1)->second = val1;
                graph.erase(node2);
                map<int,vector<int>>::iterator it;
                it = graph.find(node1);
                int size_val1=val1.size();
                int i=0;
                while(i<size_val1){
                    if (it->second[i]==node2 || it->second[i]==node1){
                        (it->second).erase((it->second).begin()+i);
                        number_edges=number_edges-1;
                        size_val1=size_val1-1;
                        i++;
                        cout<<"here";
                    }
                }
            }
            
            for(const auto& [key,val]:graph){
                cout<<key<<":";
                print(val);

            }
        }


};

int main(){
    string STRING;
    ifstream infile;
    int number;
    int key;
    int begining_line=0;
    map<int,vector<int>> graph;


    infile.open("G:\\My Drive\\course\\Algorithm\\MinCut\\graph.txt");

    while(!infile.eof()){
        getline(infile,STRING);
        stringstream iss(STRING);
        vector<int> value;
        begining_line=1;
        while( iss >> number){
            if(begining_line==1){
                key = number;
            }else{
                value.push_back(number);
            }
            begining_line=0;
        }
        graph.insert( pair<int,vector<int>>(key,value));
    }

    GraphCut gc(graph);
    gc.contraction();

    return 0;
}