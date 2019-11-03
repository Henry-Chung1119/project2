#include <iostream>
#include <fstream>
using namespace std;
class space{
    private:
        int distance;
        bool obstacle;
    public:
        //freespace():row(0),col(0),distance(0){};
        //freespace(int row, int col):row(row),col(col),distance(0){};
        space():distance(-1),obstacle(1){};
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
    private:
        int row,col;
    public:
        space **matrixspace;
        floor(int row, int col):row(row),col(col){
            matrixspace=new space*[row];
            for(int i=0;i<row;i++){
                matrixspace[i]=new space[col];
            }
        }
        int getrow(){
            return this->row;
        }
        int getcol(){
            return this->col;
        }
};
int spacemindistance(floor *cleaningroom, int row, int col){
    /*
        2
    1-------3
        4
    */
    int dis1=cleaningroom->matrixspace[row][col-1].getdistance();
    int dis2=cleaningroom->matrixspace[row-1][col].getdistance();
    int dis3=cleaningroom->matrixspace[row][col+1].getdistance();
    int dis4=cleaningroom->matrixspace[row+1][col].getdistance();
    int mindistance=-1;
    if(dis1!=-1){
        mindistance=dis1;
    }
    if(dis2!=-1){ 
        if(mindistance==-1)
            mindistance=dis2;
        else if(dis2<mindistance)
            mindistance=dis2;
    }
    if(dis3!=-1){ 
        if(mindistance==-1)
            mindistance=dis3;
        else if(dis3<mindistance)
            mindistance=dis3;
    }
    if(dis4!=-1){ 
        if(mindistance==-1)
            mindistance=dis4;
        else if(dis4<mindistance)
            mindistance=dis4;
    }
    //回傳最小distance
    return mindistance;
}
/*bool checkdistance(floor *cleaningroom){
    for(int i=1;i<cleaningroom->getrow()-1;i++){
        for(int j=1;j<cleaningroom->getcol()-1;j++){
            spacedistanceset(cleaningroom,i,j);
        }
    }
}*/
void setcelldistance(floor *cleaningroom, int cleaningcellnum, int initial_row, int initial_col){
    /*switch(situation){
        case 2:
        //cout << "yes";
            //set initial_row distance
            for(int j=2;j<cleaningroom->getcol()-1;j++){
                if(!cleaningroom->matrixspace[initial_row][j].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[initial_row][j-1].getdistance()+1;
                    cleaningroom->matrixspace[initial_row][j].setdistance(newdistance);
                }
                else
                    break;
            }
            //set initial_col distance
            for(int i=2;i<cleaningroom->getrow()-1;i++){
                if(!cleaningroom->matrixspace[i][initial_col].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[i-1][initial_col].getdistance()+1;
                    cleaningroom->matrixspace[i][initial_col].setdistance(newdistance);
                }
                else
                    break;
            }
            for(int i=2;i<cleaningroom->getrow()-1;i++){
                for(int j=2;j<cleaningroom->getcol()-1;j++){
                    if(!cleaningroom->matrixspace[i][j].getobstacle()){
                        int newdistance=spacemindistance(cleaningroom,i,j);
                        if(newdistance!=-1)
                            cleaningroom->matrixspace[i][j].setdistance(newdistance+1);
                    }                 
                }
            }
            while(1){
                bool distancesetup=1;
                for(int i=1;i<cleaningroom->getrow()-1;i++){
                    for(int j=1;j<cleaningroom->getcol()-1;j++){
                        int newdistance=spacemindistance(cleaningroom,i,j);
                        if(!cleaningroom->matrixspace[i][j].getobstacle()){
                            if(cleaningroom->matrixspace[i][j].getdistance()==-1 || cleaningroom->matrixspace[i][j].getdistance()>newdistance+1)
                            {
                                cleaningroom->matrixspace[i][j].setdistance(newdistance+1);
                                distancesetup=0;
                            }
                        }        
                    }
                }
                if(distancesetup){
                    break;
                }
            }*/


        //case '2':
        //case '3':
        //case '4':
        //case '5':
        //case 1:
        //cout << "yes";
            //set initial_row distance
            //同一列向右
            for(int j=initial_col+1;j<cleaningroom->getcol()-1;j++){
                if(!cleaningroom->matrixspace[initial_row][j].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[initial_row][j-1].getdistance()+1;
                    cleaningroom->matrixspace[initial_row][j].setdistance(newdistance);
                }
                else
                    break;
            }
            //同一列向左
            for(int j=initial_col-1;j>0;j--){
                if(!cleaningroom->matrixspace[initial_row][j].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[initial_row][j+1].getdistance()+1;
                    cleaningroom->matrixspace[initial_row][j].setdistance(newdistance);
                }
                else
                    break;
            }
            //set initial_col distance
            //同一行向下
            for(int i=initial_row+1;i<cleaningroom->getrow()-1;i++){
                if(!cleaningroom->matrixspace[i][initial_col].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[i-1][initial_col].getdistance()+1;
                    cleaningroom->matrixspace[i][initial_col].setdistance(newdistance);
                }
                else
                    break;
            }
            //同一行向上
            for(int i=initial_row-1;i>0;i--){
                if(!cleaningroom->matrixspace[i][initial_col].getobstacle()){
                    int newdistance=cleaningroom->matrixspace[i+1][initial_col].getdistance()+1;
                    cleaningroom->matrixspace[i][initial_col].setdistance(newdistance);
                }
                else
                    break;
            }
            /*for(int i=2;i<cleaningroom->getrow()-1;i++){
                for(int j=2;j<cleaningroom->getcol()-1;j++){
                    if(!cleaningroom->matrixspace[i][j].getobstacle()){
                        int newdistance=spacemindistance(cleaningroom,i,j);
                        if(newdistance!=-1)
                            cleaningroom->matrixspace[i][j].setdistance(newdistance+1);
                    }                 
                }
            }*/
            while(1){
                bool distancesetup=1;
                for(int i=1;i<cleaningroom->getrow()-1;i++){
                    for(int j=1;j<cleaningroom->getcol()-1;j++){
                        int newdistance=spacemindistance(cleaningroom,i,j);
                        if(!cleaningroom->matrixspace[i][j].getobstacle()){
                            if(cleaningroom->matrixspace[i][j].getdistance()==-1 || cleaningroom->matrixspace[i][j].getdistance()>newdistance+1)
                            {
                                if(newdistance!=-1)
                                    cleaningroom->matrixspace[i][j].setdistance(newdistance+1);
                                distancesetup=0;
                            }
                        }        
                    }
                }
                if(distancesetup){
                    break;
                }
            }
    
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
    floor *cleaningroom=new floor(m+2,n+2);
    for(int i=1;i<m+1;i++){
        for(int j=1;j<n+1;j++){
            file1 >> cell;
            if(cell=='0'){
                cleaningroom->matrixspace[i][j].setobstacle(0);
                cleaningcellnum++;
            }
            else if(cell=='R'){
                cleaningroom->matrixspace[i][j].setobstacle(0);
                cleaningroom->matrixspace[i][j].setdistance(0);
                initial_row=i;
                initial_col=j;
            }
        }
    }
    //setdistance
    /*if(initial_row==1){
        if(initial_col==1)
            situation=1;
        else if(initial_col==n)
            situation=3;
        else
            situation=2;
    }
    else if(initial_row==m){
        if(initial_col==1)
            situation=4;
        else if(initial_col==n)
            situation=6;
        else
            situation=5;
    }
    else{
        if(initial_col==1)
            situation=7;
        else if(initial_col==n)
            situation=9;
        else
            situation=8;
    }
    cout << situation << endl;*/
    setcelldistance(cleaningroom,cleaningcellnum,initial_row,initial_col);
    for(int i=1;i<m+1;i++){
        for(int j=1;j<n+1;j++){
            if(i==initial_row && j==initial_col)
                cout << "R ";
            else
                cout << cleaningroom->matrixspace[i][j].getobstacle() << " ";
        }
        cout << endl;
    }
    cout << endl;
    for(int i=1;i<m+1;i++){
        for(int j=1;j<n+1;j++){
            if(cleaningroom->matrixspace[i][j].getdistance()!=-1)
                cout << " " << cleaningroom->matrixspace[i][j].getdistance() << " ";
            else
                cout << cleaningroom->matrixspace[i][j].getdistance() << " ";
        }
        cout << endl;
    }
    file1.close();
}