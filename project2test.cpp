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
void setcelldistance(floor *cleaningroom, int cleaningcellnum, int initial_row, int initial_col, int situation){
    
}
int main(){
    int m,n,battery;
    int situation;
    char cell;
    //int **matrix;
    int initial_row,initial_col;
    int cleaningcellnum;
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
            else{
                cleaningcellnum++;
            }
        }
    }
    //setdistance
    if(initial_row==0){
        if(initial_col==0)
            situation=1;
        else if(initial_col==n-1)
            situation=3;
        else
            situation=2;
    }
    else if(initial_row==m-1){
        if(initial_col==0)
            situation=4;
        else if(initial_col==n-1)
            situation=6;
        else
            situation=5;
    }
    else{
        if(initial_col==0)
            situation=7;
        else if(initial_col==n-1)
            situation=9;
        else
            situation=8;
    }
    setcelldistance(cleaningroom,cleaningcellnum,initial_row,initial_col,situation);
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cout << cleaningroom->matrixspace[i][j].getobstacle() << " ";
        }
        cout << endl;
    }
    file1.close();
}