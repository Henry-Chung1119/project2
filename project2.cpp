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
                first=first->getnext();
                delete tmp;
                pathelementnum--;
            }
        }
        path *front(){
            return this->first;
        }
        path *back(){
            return this->last;
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
void setcelldistance(floor *cleaningroom, int initial_row, int initial_col){
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
    while(1){
        bool distancesetup=1;
        for(int i=1;i<cleaningroom->getrow()-1;i++){
            for(int j=1;j<cleaningroom->getcol()-1;j++){
                //spacemindistance回傳附近空間的最小distance
                int newdistance=spacemindistance(cleaningroom,i,j);
                if(!cleaningroom->matrixspace[i][j].getobstacle()){
                    if(cleaningroom->matrixspace[i][j].getdistance()==-1 || cleaningroom->matrixspace[i][j].getdistance()>newdistance+1)
                    {
                        if(newdistance!=-1)
                            cleaningroom->matrixspace[i][j].setdistance(newdistance+1);
                        //假如有distance更新，distancesetup就設為0，重新檢查一次
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
    cleaningpath.setelementnum(0);
    //cout << cleaningpath.getelementnum() << endl;
    int power=battery;
    int tmp_row,tmp_col;
    int current_row=initial_row;
    int current_col=initial_col;
    int tmp_distance;
    int current_distance=0;
    int dis1,dis2,dis3,dis4;
    bool stuck;
    bool finish=0;
    while(!finish){
        //cout << power << endl;
        int dis1=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
        int dis2=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
        int dis3=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
        int dis4=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
        if(power>current_distance+1){
            bool find=0;
            //找周遭距離大於當前距離且還未被拜訪過
            //向左檢查
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                    if(current_distance<dis1){
                        current_row=current_row;
                        current_col=current_col-1;
                        current_distance=dis1;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                        if(current_distance<dis2){
                            current_row=current_row-1;
                            current_col=current_col;
                            current_distance=dis2;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                        if(current_distance<dis3){
                            current_row=current_row;
                            current_col=current_col+1;
                            current_distance=dis3;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                        if(current_distance<dis4){
                            current_row=current_row+1;
                            current_col=current_col;
                            current_distance=dis4;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //找還未被拜訪過
            //向左檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        current_row=current_row;
                        current_col=current_col-1;
                        current_distance=dis1;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                        current_row=current_row-1;
                        current_col=current_col;
                        current_distance=dis2;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                        current_row=current_row;
                        current_col=current_col+1;
                        current_distance=dis3;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                        current_row=current_row+1;
                        current_col=current_col;
                        current_distance=dis4;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //如果週遭都被拜訪過
            //向左檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(current_distance>dis1){
                        current_row=current_row;
                        current_col=current_col-1;
                        current_distance=dis1;
                        find=1;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(current_distance>dis2){
                        current_row=current_row-1;
                        current_col=current_col;
                        current_distance=dis2;
                        find=1;
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(current_distance>dis3){
                        current_row=current_row;
                        current_col=current_col+1;
                        current_distance=dis3;
                        find=1;
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(current_distance>dis4){
                        current_row=current_row+1;
                        current_col=current_col;
                        current_distance=dis4;
                        find=1;
                    }
                }
            }
        }
        else{
            bool find=0;
            //找距離較短且尚未被拜訪過
            //向左檢查
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(dis1<current_distance){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        current_col=current_col-1;
                        current_distance=dis1;
                        find=1;
                        cleaningcellnum--;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(dis2<current_distance){
                        if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                            current_row=current_row-1;
                            current_distance=dis2;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(dis3<current_distance){
                        if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                            current_col=current_col+1;
                            current_distance=dis3;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(dis4<current_distance){
                        if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                            current_row=current_row+1;
                            current_distance=dis4;
                            find=1;
                            cleaningcellnum--;
                        }
                    }
                }
            }
            //找距離較短
            //向左檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(dis1<current_distance){
                        current_col=current_col-1;
                        current_distance=dis1;
                        find=1;
                    }
                }
            }
            //向上檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(dis2<current_distance){
                        current_row=current_row-1;
                        current_distance=dis2;
                        find=1;
                    }
                }
            }
            //向右檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(dis3<current_distance){
                        current_col=current_col+1;
                        current_distance=dis3;
                        find=1;
                    }
                }
            }
            //向下檢查
            if(!find){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(dis4<current_distance){
                        current_row=current_row+1;
                        current_distance=dis4;
                        find=1;
                    }
                }
            }
        }
        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
        cleaningpath.push(current_row-1,current_col-1);
        power--;
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
        bool stop=0;
        for(int i=1;i<cleaningroom->getrow()-1;i++){
            for(int j=1;j<cleaningroom->getcol()-1;j++){
                if(!cleaningroom->matrixspace[i][j].getobstacle()){
                    if(!cleaningroom->matrixspace[i][j].getvisited()){
                        current_row=i;
                        current_col=j;
                        current_distance=cleaningroom->matrixspace[i][j].getdistance();
                        stop=1;
                        break;
                    }
                }
            }
            if(stop)
                break;
        }
        //倒回來走
        pathstack A;
        pathqueue B;
        //cout << current_row-1 << current_col-1 << endl;
        A.push(current_row-1,current_col-1);
        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
        cleaningcellnum--;
        power=battery-current_distance;
        while(current_distance!=0){
            int dis1=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
            int dis2=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
            int dis3=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
            int dis4=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
            //如果還沒被拜訪距離又較短
            //向左
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                    if(dis1<current_distance){
                        current_col=current_col-1;
                        current_distance=dis1;
                        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                        A.push(current_row-1,current_col-1);
                        cleaningcellnum--;
                        continue;
                    }
                }
            }
            //向上
            if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                    if(dis2<current_distance){
                        current_row=current_row-1;
                        current_distance=dis2;
                        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                        A.push(current_row-1,current_col-1);
                        cleaningcellnum--;
                        continue;
                    }
                }
            }
            //向右
            if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                    if(dis3<current_distance){
                        current_col=current_col+1;
                        current_distance=dis3;
                        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                        A.push(current_row-1,current_col-1);
                        cleaningcellnum--;
                        continue;
                    }
                }
            }
            //向下
            if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                    if(dis4<current_distance){
                        current_row=current_row+1;
                        current_distance=dis4;
                        cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                        A.push(current_row-1,current_col-1);
                        cleaningcellnum--;
                        continue;
                    }
                }
            }
            //如果都被造訪過造訪距離短的
            //向左
            if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                if(dis1<current_distance){
                    current_col=current_col-1;
                    current_distance=dis1;
                    A.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向上
            if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                if(dis2<current_distance){
                    current_row=current_row-1;
                    current_distance=dis2;
                    A.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向右
            if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                if(dis3<current_distance){
                    current_col=current_col+1;
                    current_distance=dis3;
                    A.push(current_row-1,current_col-1);
                    continue;
                }
            }
            //向下
            if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                if(dis4<current_distance){
                    current_row=current_row+1;
                    current_distance=dis4;
                    A.push(current_row-1,current_col-1);
                    continue;
                }
            }
        }
        //push 進cleaningpath isempty
        A.pop();
        while(!A.Isempty()){
            cleaningpath.push(A.top()->getrow(),A.top()->getcol());
            A.pop();
        }
        current_row=cleaningpath.back()->getrow()+1;
        current_col=cleaningpath.back()->getcol()+1;
        current_distance=cleaningroom->matrixspace[current_row][current_col].getdistance();
        while(current_distance!=0){
            int dis1=cleaningroom->matrixspace[current_row][current_col-1].getdistance();
            int dis2=cleaningroom->matrixspace[current_row-1][current_col].getdistance();
            int dis3=cleaningroom->matrixspace[current_row][current_col+1].getdistance();
            int dis4=cleaningroom->matrixspace[current_row+1][current_col].getdistance();
            if(power>current_distance+1){
                //如果還沒被拜訪距離又較長
                //向左
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        if(dis1>current_distance){
                            current_col=current_col-1;
                            current_distance=dis1;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向上
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                        if(dis2>current_distance){
                            current_row=current_row-1;
                            current_distance=dis2;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向右
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                        if(dis3>current_distance){
                            current_col=current_col+1;
                            current_distance=dis3;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向下
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                        if(dis4>current_distance){
                            current_row=current_row+1;
                            current_distance=dis4;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //如果還沒被拜訪距離又較短
                //向左
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        if(dis1<current_distance){
                            current_col=current_col-1;
                            current_distance=dis1;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向上
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                        if(dis2<current_distance){
                            current_row=current_row-1;
                            current_distance=dis2;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向右
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                        if(dis3<current_distance){
                            current_col=current_col+1;
                            current_distance=dis3;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向下
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                        if(dis4<current_distance){
                            current_row=current_row+1;
                            current_distance=dis4;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //如果都被造訪過造訪距離短的
                //向左
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(dis1<current_distance){
                        current_col=current_col-1;
                        current_distance=dis1;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向上
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(dis2<current_distance){
                        current_row=current_row-1;
                        current_distance=dis2;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向右
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(dis3<current_distance){
                        current_col=current_col+1;
                        current_distance=dis3;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向下
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(dis4<current_distance){
                        current_row=current_row+1;
                        current_distance=dis4;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
            }
            else{
                //如果還沒被拜訪距離又較短
                //向左
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col-1].getvisited()){
                        if(dis1<current_distance){
                            current_col=current_col-1;
                            current_distance=dis1;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向上
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row-1][current_col].getvisited()){
                        if(dis2<current_distance){
                            current_row=current_row-1;
                            current_distance=dis2;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向右
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row][current_col+1].getvisited()){
                        if(dis3<current_distance){
                            current_col=current_col+1;
                            current_distance=dis3;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //向下
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(!cleaningroom->matrixspace[current_row+1][current_col].getvisited()){
                        if(dis4<current_distance){
                            current_row=current_row+1;
                            current_distance=dis4;
                            cleaningroom->matrixspace[current_row][current_col].setvisited(1);
                            cleaningpath.push(current_row-1,current_col-1);
                            cleaningcellnum--;
                            power--;
                            continue;
                        }
                    }
                }
                //如果都被造訪過造訪距離短的
                //向左
                if(!cleaningroom->matrixspace[current_row][current_col-1].getobstacle()){
                    if(dis1<current_distance){
                        current_col=current_col-1;
                        current_distance=dis1;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向上
                if(!cleaningroom->matrixspace[current_row-1][current_col].getobstacle()){
                    if(dis2<current_distance){
                        current_row=current_row-1;
                        current_distance=dis2;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向右
                if(!cleaningroom->matrixspace[current_row][current_col+1].getobstacle()){
                    if(dis3<current_distance){
                        current_col=current_col+1;
                        current_distance=dis3;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
                //向下
                if(!cleaningroom->matrixspace[current_row+1][current_col].getobstacle()){
                    if(dis4<current_distance){
                        current_row=current_row+1;
                        current_distance=dis4;
                        cleaningpath.push(current_row-1,current_col-1);
                        power--;
                        continue;
                    }
                }
            }        
        }
    }
    file2.open("final.path");
    file2 << cleaningpath.getelementnum() << endl;
    while(!cleaningpath.Isempty()){
        file2 << cleaningpath.front()->getrow() << " " << cleaningpath.front()->getcol() << endl;
        cleaningpath.pop();
    }
    file2.close();
}
int main(){
    int m,n,battery;
    int situation;
    char cell;
    //int **matrix;
    int initial_row,initial_col;
    int cleaningcellnum=0;
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
    setcelldistance(cleaningroom,initial_row,initial_col);
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