#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
class space{
    private:
        int distance;
        bool obstacle;
        bool visited;
    public:
        //freespace():row(0),col(0),distance(0){};
        //freespace(int row, int col):row(row),col(col),distance(0){};
        space():distance(-1),obstacle(1),visited(0){};
        int getdistance(){
            return this->distance;
        }
        bool getobstacle(){
            return this->obstacle;
        }
        bool getvisited(){
            return this->visited;
        }
        /*
        void setrow(int row){
            this->row=row;
        }
        void setcol(int col){
            this->col=col;
        }*/
        void setdistance(int distance){
            this->distance=distance;
        }
        void setobstacle(bool obstacle){
            this->obstacle=obstacle;
        }
        void setvisited(bool visited){
            this->visited=visited;
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
class path{
    private:
        int location_row,location_col;
        path *next;
    public:
        path(int row, int col):location_row(row),location_col(col),next(NULL){}
        int getrow(){
            return this->location_row;
        }
        int getcol(){
            return this->location_col;
        }
        path *getnext(){
            return this->next;
        }
        void setnext(path *newpath){
            this->next=newpath;
        }
};
class pathqueue{
    private:
        int pathelementnum;
        path *first;
        //path *next;
        path *last;
    public:
        pathqueue():pathelementnum(0),first(NULL),last(NULL){}
        void push(int row, int col){
            path *newpath=new path(row,col);
            if(first==NULL){
                first=newpath;
                last=newpath;
            }
            else{
                last->setnext(newpath);
                last=newpath;
            }
            pathelementnum++;
        }
        void pop(){
            path *tmp=first;
            if(first==last){
                first=NULL;
                last=NULL;
                delete tmp;
                pathelementnum=0;
            }
            else{
                /*path *current=first;
                while(current->getnext()!=last){
                    current=current->getnext();
                }
                current->setnext(NULL);
                last=current;
                delete tmp;
                pathelementnum--;*/
                first=first->getnext();
                delete tmp;
                pathelementnum--;
            }
        }
        path *front(){
            return this->first;
        }
        bool Isempty(){
            return this->first==NULL;
        }
        int getelementnum(){
            return this->pathelementnum;
        }
        void setelementnum(int num){
            this->pathelementnum=num;
        }
};
class pathstack{
    private:
        int pathelementnum;
        path *first;
        path *last;
    public:
        pathstack():pathelementnum(0),first(NULL),last(NULL){}
        void push(int row, int col){
            path *newpath=new path(row,col);
            if(first==NULL){
                first=newpath;
                last=newpath;
            }
            else{
                last->setnext(newpath);
                last=newpath;    
            }
            pathelementnum++;
        }
        void pop(){
            path *tmp=last;
            if(first==last){
                first=NULL;
                last=NULL;
                delete tmp;
                pathelementnum=0;
            }
            else{
                path *current=first;
                while(current->getnext()!=last){
                    current=current->getnext();
                }
                current->setnext(NULL);
                last=current;
                delete tmp;
                pathelementnum--;
            }
        }
        path *top(){
            return this->last;
        }
        bool Isempty(){
            return this->first==NULL;
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
void setcelldistance(floor *cleaningroom, int initial_row, int initial_col){
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
void clearfloor(floor *cleaningroom, int initial_row, int initial_col, int cleaningcellnum, int battery){
    ofstream file2;
    pathqueue cleaningpath;
    cleaningpath.push(initial_row-1,initial_col-1);
    int power=battery;
    int tmp_row,tmp_col;
    int current_row=initial_row;
    int current_col=initial_col;
    int tmp_distance;
    int current_distance=-1;
    int dis1,dis2,dis3,dis4;
    bool stuck;
    bool finish=0;
    while(!finish){
        if(power>current_distance+1){
            tmp_distance=-1;
            stuck=1;
            /*int dis1=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
            int dis2=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
            int dis3=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
            int dis4=cleaningroom->matrixspace[current_row+1][current_col].getdistance();*/
            //向左檢查
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                    tmp_row=current_row;
                    tmp_col=current_col-1;
                    tmp_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                    stuck=0;
                }
            }
            //向上檢查
            if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                    if(tmp_distance==-1){
                        tmp_row=current_row-1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                        stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row-1][current_col].getdistance()>tmp_distance){
                        tmp_row=current_row-1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                    }
                }
            }
            //向右檢查
            if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                    if(tmp_distance==-1){
                        tmp_row=current_row;
                        tmp_col=current_col+1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                        stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row][current_col+1].getdistance()>tmp_distance){
                        tmp_row=current_row;
                        tmp_col=current_col+1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                    }
                }
            }
            //向下檢查
            if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                    if(tmp_distance==-1){
                        tmp_row=current_row+1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                        stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row+1][current_col].getdistance()>tmp_distance){
                        tmp_row=current_row+1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                    }
                }
            }
            //if(tmp_distance==-1)
            if(stuck){
                //向左檢查
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                tmp_row=current_row;
                tmp_col=current_col-1;
                tmp_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                }
                //向上檢查
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(tmp_distance==-1){
                        tmp_row=current_row-1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                        //stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row-1][current_col].getdistance()<tmp_distance){
                        tmp_row=current_row-1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                    }
                }
                //向右檢查
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(tmp_distance==-1){
                        tmp_row=current_row;
                        tmp_col=current_col+1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                        //stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row][current_col+1].getdistance()<tmp_distance){
                        tmp_row=current_row;
                        tmp_col=current_col+1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                    }
                }
                //向下檢查
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(tmp_distance==-1){
                        tmp_row=current_row+1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                        //stuck=0;
                    }
                    else if(cleaningroom->matrixspace[current_row+1][current_col].getdistance()<tmp_distance){
                        tmp_row=current_row+1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                    }
                }
            }
        }
        else{
            bool find=0;
            //向左檢查
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(cleaningroom->matrixspace[current_row][current_col-1].getdistance()<current_distance){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        tmp_row=current_row;
                        tmp_col=current_col-1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                        find=1;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(cleaningroom->matrixspace[current_row-1][current_col].getdistance()<current_distance){
                        if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                            tmp_row=current_row-1;
                            tmp_col=current_col;
                            tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                            find=1;
                        }
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(cleaningroom->matrixspace[current_row][current_col+1].getdistance()<current_distance){
                        if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                            tmp_row=current_row;
                            tmp_col=current_col+1;
                            tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                            find=1;
                        }
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(cleaningroom->matrixspace[current_row+1][current_col].getdistance()<current_distance){
                        if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                            tmp_row=current_row+1;
                            tmp_col=current_col;
                            tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                            find=1;
                        }
                    }
                }
            }
            //還是沒找到
            //向左檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(cleaningroom->matrixspace[current_row][current_col-1].getdistance()<current_distance){
                        tmp_row=current_row;
                        tmp_col=current_col-1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                        find=1;
                        stuck=1;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(cleaningroom->matrixspace[current_row-1][current_col].getdistance()<current_distance){
                        tmp_row=current_row-1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                        find=1;
                        stuck=1;
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(cleaningroom->matrixspace[current_row][current_col+1].getdistance()<current_distance){
                        tmp_row=current_row;
                        tmp_col=current_col+1;
                        tmp_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                        find=1;
                        stuck=1;
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(cleaningroom->matrixspace[current_row+1][current_col].getdistance()<current_distance){
                        tmp_row=current_row+1;
                        tmp_col=current_col;
                        tmp_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                        find=1;
                        stuck=1;
                    }
                }
            }
        }
        
        current_row=tmp_row;
        current_col=tmp_col;
        current_distance=tmp_distance;
        cleaningpath.push(current_row-1,current_col-1);
        cleaningpath.setelementnum(cleaningpath.getelementnum()+1);
        power--;
        if(!stuck)
            cleaningcellnum--;
        if(current_row==initial_row && current_col==initial_col){
            power=battery;
            bool leftvisited=(cleaningroom->matrixspace[initial_row][initial_col-1].getobstacle())?1:cleaningroom->matrixspace[initial_row][initial_col-1].getvisited();
            bool upvisited=(cleaningroom->matrixspace[initial_row-1][initial_col].getobstacle())?1:cleaningroom->matrixspace[initial_row-1][initial_col].getvisited();
            bool rightvisited=(cleaningroom->matrixspace[initial_row][initial_col+1].getobstacle())?1:cleaningroom->matrixspace[initial_row][initial_col+1].getvisited();
            bool downvisited=(cleaningroom->matrixspace[initial_row+1][initial_col].getobstacle())?1:cleaningroom->matrixspace[initial_row+1][initial_col].getvisited();
            finish=leftvisited&upvisited&rightvisited&downvisited;
        }
    }
    //最後檢查
    while(cleaningcellnum>0){
        bool find=0;
        for(int i=1;i<cleaningroom->getrow()+1;i++){
            for(int j=1;j<cleaningroom->getcol()+1;j++){
                if(!cleaningroom->matrixspace[i][j].getobstacle()){
                    if(!cleaningroom->matrixspace[i][j].getvisited()){
                        current_row=i;
                        current_col=j;
                        current_distance=cleaningroom->matrixspace[i][j].getdistance();
                        find=1;
                        break;
                    }
                }
            }
            if(find)
                break;
        }
        //倒回來走
        pathstack A;
        pathqueue B;
        A.push(current_row-1,current_col-1);
        while(current_distance!=0){
            int dis1=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
            int dis2=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
            int dis3=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
            int dis4=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
            //向左
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                    if(dis1<current_distance){
                        current_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                        current_col=current_col-1;
                        A.push(current_row-1,current_col-1);
                        B.push(current_row-1,current_col-1);
                        continue;
                    }
                    /*else if(power>dis1){
                        current_col=current_col-1;
                        current_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();   
                    }*/
                }
            }
            //向上
            if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                    if(dis2<current_distance){
                        current_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                        current_row=current_row-1;
                        A.push(current_row-1,current_col-1);
                        B.push(current_row-1,current_col-1);
                        continue;
                    }
                }
            }
            //向右
            if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                    if(dis3<current_distance){
                        current_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                        current_col=current_col+1;
                        A.push(current_row-1,current_col-1);
                        B.push(current_row-1,current_col-1);
                        continue;
                    }
                }
            }
            //向下
            if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                    if(dis4<current_distance){
                        current_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                        current_row=current_row+1;
                        A.push(current_row-1,current_col-1);
                        B.push(current_row-1,current_col-1);
                        continue;
                    }
                }
            }
            //向左
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(dis1<current_distance){
                    current_distance=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
                    current_col=current_col-1;
                    A.push(current_row-1,current_col-1);
                    B.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向上
            if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                if(dis2<current_distance){
                    current_distance=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
                    current_row=current_row-1;
                    A.push(current_row-1,current_col-1);
                    B.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向右
            if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                if(dis3<current_distance){
                    current_distance=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
                    current_col=current_col+1;
                    A.push(current_row-1,current_col-1);
                    B.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向下
            if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                if(dis4<current_distance){
                    current_distance=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
                    current_row=current_row+1;
                    A.push(current_row-1,current_col-1);
                    B.push(current_row-1,current_col-1);
                    continue;
                }
            }
        }
        //push 進cleaningpath isempty
        while(!A.Isempty()){
            cleaningpath.push(A.top()->getrow()-1,A.top()->getcol()-1);
            A.pop();
            cleaningpath.setelementnum(cleaningpath.getelementnum()+1);
        }
        while(!B.Isempty()){
            cleaningpath.push(B.front()->getrow()-1,B.front()->getcol()-1);
            B.pop();
            cleaningpath.setelementnum(cleaningpath.getelementnum()+1);
        }
        cleaningcellnum--;
    }

    //if(tmp_distance==-1)
    file2.open("final.path");
    file2 << cleaningpath.getelementnum() << endl;
    while(!cleaningpath.Isempty()){
        file2 << cleaningpath.front()->getrow() << " " << cleaningpath.front()->getcol() << endl;
        cleaningpath.pop();
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
                cleaningroom->matrixspace[i][j].setvisited(1);
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
    setcelldistance(cleaningroom,initial_row,initial_col);
    //cout << initial_row << initial_col << endl;
    clearfloor(cleaningroom,initial_row,initial_col,cleaningcellnum,battery);
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
            if(cleaningroom->matrixspace[i][j].getdistance()==-1 || cleaningroom->matrixspace[i][j].getdistance()>=10)
                cout << cleaningroom->matrixspace[i][j].getdistance() << " ";
            else
                cout << " " << cleaningroom->matrixspace[i][j].getdistance() << " ";
        }
        cout << endl;
    }
    file1.close();
}