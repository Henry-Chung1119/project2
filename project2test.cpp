#include <iostream>
#include <fstream>
using namespace std;
class space{
    private:
        int row,col,distance;
        bool obstacle;
    public:
        //freespace():row(0),col(0),distance(0){};
        //freespace(int row, int col):row(row),col(col),distance(0){};
        space():distance(-1),obstacle(0){};
        /*int getrow(){
            return this->row;
        }
        int getcol(){
            return this->col;
        }*/
        int getdistance(){
            return this->distance;
        }
        bool getobstacle(){
            return this->obstacle;
        }
        /*
        void setrow(int row){
            this->row=row;
        }
        void setcol(int col){
            this->col=col;
        }*/
        void setobstacle(bool obstacle){
            this->obstacle=obstacle;
        }
        void setdistance(int distance){
            this->distance=distance;
        }
};
class floor{
    public:
        space **matrixspace;
        floor(int row, int col){
            matrixspace=new space*[row];
            for(int i=0;i<row;i++){
                matrixspace[i]=new space[col];
            }
        }
};

int main(){
    int m,n,battery;
    char cell;
    int **matrix;
    int initial_row,initial_col;
    ifstream file1;
    file1.open("floor.data");
    if(!file1){
        cout << "File1 open fail!" << endl;
        return 0;
    }
    file1 >> m >> n >> battery;
    floor *cleaningroom=new floor(m,n);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            file1 >> cell;
            if(cell=='1'){
                cleaningroom->matrixspace[i][j].setobstacle(1);
            }
            else if(cell=='R'){
                cleaningroom->matrixspace[i][j].setdistance(0);
                initial_row=i;
                initial_col=j;
            }
        }
    }
        /*matrix=new int*[m];
        for(int i=0;i<m;i++){
            matrix[i]=new int[n];
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                file1 >> matrix[i][j];
            }
        }*/
    
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout << cleaningroom->matrixspace[i][j].getobstacle() << " ";
        }
        cout << endl;
    }
    file1.close();
}