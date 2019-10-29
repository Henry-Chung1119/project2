#include <iostream>
#include <fstream>

using namespace std;
int main(){
    int m,n,battery;
    int **matrix;
    ifstream file1;
    file1.open("floor.data");
    if(!file1){
        cout << "File1 open fail!" << endl;
    }
    else{
        file1 >> m >> n >> battery;
        matrix=new int*[m];
        for(int i=0;i<m;i++){
            matrix[i]=new int[n];
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                file1 >> matrix[i][j];
            }
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}