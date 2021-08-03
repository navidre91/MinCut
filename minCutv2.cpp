#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <typeinfo>
#include <stdlib.h>
#include <time.h>

using namespace std;


void print(vector<int> A) {
   cout <<endl<< "The vector elements are : ";

   for(int i=0; i < A.size(); i++){
    cout << A[i] << ' ';
   }
   cout<<endl;
};

void print_map(map<int, vector<int>> M) {
   for (auto &[key,value]:M){
       cout<<"key="<< key<< endl << "val:";
       print(value);
   }
};

class GraphCut{
    public:
        map<int,vector<int>> graph;
        map<int,vector<int>> graph_ans;
        map<int,vector<int>> graph_main;
        int mincut_count = 0;
        int number_edges = 0;
        int node1=0;
        int node2=0;
        int number_nodes=0;
        int ans=0;

        GraphCut(map<int,vector<int>> g){
            graph=g;
            graph_main=g;
            graph_ans=g;
            reset_params();
            mincut_count=number_edges;
        }

        void reset_params(){
            number_edges = 0;
            node1=0;
            node2=0;
            number_nodes=0;
            graph=graph_main;
            edge_count();
        }

        void edge_count(){

            for (auto &[key, value] : graph){
                number_edges = number_edges+value.size();
                number_nodes = number_nodes+1;
            }
            ans=number_edges;
        }

        void rand_edge(){
            int rand_num = rand() % number_edges;
            int counter = -1;
            int found = 0;
            for (auto& [key,value] : graph){
                counter = counter+value.size();
                if(found==0){
                    if (counter>=rand_num){
                        node1=key;
                        node2=value[counter - rand_num];
                        found=1;
                    }
                }
            }
        }

        void combin_two_nodes(){
            vector<int> &val1 = graph.find(node1)->second;
            vector<int> &val2 = graph.find(node2)->second;
            val1.insert(val1.end(),val2.begin(),val2.end());
            graph.erase(node2);
            map<int,vector<int>>::iterator it;
            it = graph.find(node1);
            int size_val1=val1.size();
            for(int i=0; i<size_val1; i++){
                if (it->second[i]==node2 || it->second[i]==node1){
                    (it->second).erase((it->second).begin()+i);
                    number_edges=number_edges-1;
                    size_val1=size_val1-1;
                    i--;
                }
            }

            for (auto &[key,val]:graph){
                for (int j=0; j<val.size(); j++){
                    if(val[j]==node2){
                        val[j]=node1;
                    }
                }
            }    
        }

        void contraction(){
            while (number_nodes>2){
                rand_edge();
                combin_two_nodes();
                number_nodes=number_nodes-1;
            }
            
            for(auto &[key,val]:graph){
                int temp_ans=val.size();
                if (temp_ans<ans){
                    ans=temp_ans;
                }
            }
        }

        void min_cut_find(){
            for (int i=0; i<1000; i++){
                reset_params();
                contraction();
                if (ans<mincut_count){
                    mincut_count=ans;
                }
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
    gc.min_cut_find();
    cout<<gc.mincut_count;
    

    return 0;
}