#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <utility>
#include <stdlib.h>
#include <ctime>

class Cell{ //class cell with all of the properties

    public:
        Cell();
        bool isVisited() {return cellVisited;}
        bool hasUpWall() {return upWall;}
        bool hasLeftWall() {return leftWall;}
        bool isOnPath() {return onPath;}
        int getCorX() {return cellX;}
        int getCorY() {return cellY;}
        void setVisited(bool cellisVisited); //marks cell as visited
        void setUpWall(bool upperWall); //sets the cell upper boundery
        void setLeftWall(bool lefterWall); //sets the cell left boundery
        void setOnPath(bool onThePath); //sets the cell to belong to the correct path
        void setCordinates(int x, int y); //sets the cordinates of the cell

    private:
        bool cellVisited;
        bool upWall;
        bool leftWall;
        bool onPath;
        int cellX;
        int cellY;
        std::pair<int, int> cellCordinates;
};

Cell::Cell(){ //default constructor

    cellVisited = false;
    upWall = true;
    leftWall = true;
    onPath = false;
    cellX = 0;
    cellY = 0;
};

void Cell::setVisited(bool cellisVisited){
    cellVisited = cellisVisited;
}
void Cell::setUpWall(bool upperWall){
    upWall = upperWall;
}
void Cell::setLeftWall(bool lefterWall){
    leftWall = lefterWall;
}
void Cell::setCordinates(int x, int y){
    cellX = x;
    cellY = y;
}
void Cell::setOnPath(bool onThePath){
    onPath = onThePath;
}

class Maze{

    public:
        Maze(){};
        std::vector<std::vector<Cell> > cellVector; //vector in which all of the individual properties are stored, along with their properties
        void mazeGen(int inputMazeWidth, int inputMazeHeight); //sets the size of the maze (of the cell vector)
        void recBackTrack(std::stack<std::pair<int, int> >& stackOfCors, std::vector<std::pair<int, int> >& vectorOfCors); //generates random paths
        bool pathFinding(std::pair<int, int> start, std::pair<int, int> finish, int x, int y); //finds the correct path
        void mazePrint(); //prints the maze after the other functions are executed

    private:
        int mazeWidth;
        int mazeHeight;
};

void Maze::mazeGen(int inputMazeWidth, int inputMazeHeight){
    mazeWidth = inputMazeWidth;
    mazeHeight = inputMazeHeight;
    Cell cell;

    std::vector<Cell> rowsOfCells(mazeWidth, cell); //
    std::vector<std::vector<Cell> > colsOfCells(mazeHeight, rowsOfCells);
    cellVector = colsOfCells;
}

void Maze::recBackTrack(std::stack<std::pair<int, int> >& stackOfCors, std::vector<std::pair<int, int> >& vectorOfCors){

    std::pair<int, int> cellCordinates;

    if(stackOfCors.empty()){ //base case
        return;
    }
    else{
        cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second).setVisited(true); //sets the current cell as visited
        cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second).setCordinates(stackOfCors.top().first, stackOfCors.top().second); //sets the cordinates of teh current cell

        std::vector<int> cellNeighbours; //vector that stores int values of all of the possible directions

        if(stackOfCors.top().first > 0 && !cellVector.at(stackOfCors.top().first - 1).at(stackOfCors.top().second).isVisited()){ //up
            cellNeighbours.push_back(0);
        }
        if(stackOfCors.top().first < mazeHeight - 1 && !cellVector.at(stackOfCors.top().first + 1).at(stackOfCors.top().second).isVisited()){ //down
            cellNeighbours.push_back(1);
        }
        if(stackOfCors.top().second > 0 && !cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second - 1).isVisited()){ //left
            cellNeighbours.push_back(2);
        }
        if(stackOfCors.top().second < mazeWidth - 1 && !cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second + 1).isVisited()){//right
            cellNeighbours.push_back(3);
        }
        if(!cellNeighbours.empty()){

            int nextDir = cellNeighbours.at(rand() % cellNeighbours.size()); //choosed a random direction that has been pushed into the vector

            switch (nextDir){
                case 0: 
                        cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second).setUpWall(false);
                        stackOfCors.push(cellCordinates = std::make_pair(stackOfCors.top().first - 1, stackOfCors.top().second));
                        vectorOfCors.push_back(cellCordinates = std::make_pair(stackOfCors.top().first - 1, stackOfCors.top().second));
                break;

                case 1:
                        cellVector.at(stackOfCors.top().first + 1).at(stackOfCors.top().second).setUpWall(false);
                        stackOfCors.push(cellCordinates = std::make_pair(stackOfCors.top().first + 1, stackOfCors.top().second));
                        vectorOfCors.push_back(cellCordinates = std::make_pair(stackOfCors.top().first + 1, stackOfCors.top().second));
                break;

                case 2:
                        cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second).setLeftWall(false);
                        stackOfCors.push(cellCordinates = std::make_pair(stackOfCors.top().first, stackOfCors.top().second - 1));
                        vectorOfCors.push_back(cellCordinates = std::make_pair(stackOfCors.top().first, stackOfCors.top().second - 1));
                break;

                case 3:
                        cellVector.at(stackOfCors.top().first).at(stackOfCors.top().second + 1).setLeftWall(false);
                        cellCordinates = std::make_pair(stackOfCors.top().first, stackOfCors.top().second + 1);
                        stackOfCors.push(cellCordinates);
                        vectorOfCors.push_back(cellCordinates);
                break;
            }
        }
        else{ //if the vector of possible directions is empty (there is nowhere to go)
            stackOfCors.pop();
        }
        cellNeighbours.clear(); //clears the vector for the next itteration
        recBackTrack(stackOfCors, vectorOfCors); //recursive call
    }

}

bool Maze::pathFinding(std::pair<int, int> start, std::pair<int, int> finish, int x, int y){

    std::pair<int, int> pairCordinate;
cellVector.at(x).at(y).setOnPath(true); //sets current cell as onPath

if(start.first == finish.first && start.second == finish.second){ //base case
    return true;
}
else{
    std::vector<Cell> directNeigh; //stores the neighbours
    if(x > 0 && !cellVector.at(x).at(y).hasUpWall() && !cellVector.at(x - 1).at(y).isOnPath()){ //north neighbour
        directNeigh.push_back(cellVector.at(x - 1).at(y));
    }
    if(x < mazeHeight - 1 && !cellVector.at(x + 1).at(y).hasUpWall() && !cellVector.at(x + 1).at(y).isOnPath()){ //south neighbour
        directNeigh.push_back(cellVector.at(x + 1).at(y));
    }
    if(y < mazeWidth - 1 && !cellVector.at(x).at(y + 1).hasLeftWall() && !cellVector.at(x).at(y + 1).isOnPath()){ //east neighbour
        directNeigh.push_back(cellVector.at(x).at(y + 1));
    }
    if(y > 0 && !cellVector.at(x).at(y).hasLeftWall() && !cellVector.at(x).at(y - 1).isOnPath()){ //west neighbour
        directNeigh.push_back(cellVector.at(x).at(y - 1));
    }
    for (int i = 0; i < directNeigh.size(); i++){ //checks all the neighbours
        if(!directNeigh.at(i).isOnPath()){ //if the neighbour is on the path, do the recursive call
            if(pathFinding(pairCordinate = std::make_pair(directNeigh.at(i).getCorY(), directNeigh.at(i).getCorX()), finish, directNeigh.at(i).getCorX(), directNeigh.at(i).getCorY())){
                return true;
            }
        }
    }
        cellVector.at(x).at(y).setOnPath(false); //if there are no neighbours, set the current cell to false
    return false;
}

}

void Maze::mazePrint(){ //printing of the maze for every cell

    for(int i = 0; i < cellVector.size(); i++){
        for (int j = 0; j < cellVector.at(i).size(); j++){
            if(cellVector.at(i).at(j).hasUpWall()){
                std::cout << "+---";
            }
            else {
                std::cout << "+   ";
            }
        }
        std::cout << "+\n";
        for (int j = 0; j < cellVector.at(i).size(); j++){
            if(cellVector.at(i).at(j).hasLeftWall()){
                std::cout << "|";
                if(!cellVector.at(i).at(j).isOnPath()){
                    std::cout << "   ";
                }
                else{
                    std::cout << " . ";
                }
            }
            else{
                if(!cellVector.at(i).at(j).isOnPath()){
                    std::cout << "    ";
                }
                else{
                    std::cout << "  . ";
                }
            }
        }
        std::cout << "|\n";
    }
    for (int i = 0; i < cellVector.at(0).size(); i++){
        std::cout << "+---";
    }
    std::cout << "+";
}

int main(int argc, char* argv[]){
    
    Maze maze;
    Cell cell;
    int seed = time(NULL);

    if(argc == 4){ //uses the seed
        srand(atoi(argv[3]));
    }
    else if(argc == 3){
        srand(time(NULL));
    }
    std::stack<std::pair<int, int> > stackOfCells; //initiate the stack and the vector afor the Recursive Backtracking
    std::vector<std::pair<int, int> > vectorOfCells;

    std::pair<int, int> firstCors;
    firstCors = std::make_pair(0, 0);
    stackOfCells.push(firstCors);
    vectorOfCells.push_back(firstCors);

    maze.mazeGen(atoi(argv[2]), atoi(argv[1]));
    maze.recBackTrack(stackOfCells, vectorOfCells);
    cell.setVisited(false);

    std::pair<int, int> start = std::make_pair(0, 0);
    std::pair<int, int> finish = std::make_pair(atoi(argv[2]) - 1, atoi(argv[1]) - 1);
    int i = 0, j = 0;
    maze.pathFinding(start, finish, i, j);
    maze.mazePrint();

    return 0;
}