/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   day2.cpp
 * Author: Alberto Herreros Magaña
 *
 * Created on 25 de diciembre de 2021, 23:38
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

/*
 * Day 4
 */
struct cell{
    int n;
    bool marked;
};

int main(int argc, char** argv) {
    
    std::string fileName = "day4_input.txt";
    std::ifstream file(fileName.c_str() );
    std::string line;
    int cut, n;
        
    std::vector<int> gameInput;
    
    std::vector< std::vector<std::vector<cell> > > players;
    std::vector< cell > p;
    int nPlayers = 0;
    
    //Read the entire input
    //First line
    getline( file,line );
    line.erase(line.length()-1,line.length());
    while( line != "" ){
        cut = line.find(',');
        if( cut == -1 ) //Last number does not have ','
            cut = 2;
        n = stoi( line.substr(0,cut) );
        line.erase(0, cut + 1);
        gameInput.push_back(n);

    }
    //Every bingo player
    int i = 0;
    while( getline( file,line ) ){
        
        if( line != "" ){
            
            for( int j = 0; j < 5; j++){
                
                //1 digit numbers
                if( line[0] == ' ' )
                    line.erase(0,1);
                
                cut = line.find(' ');
                n = stoi( line.substr(0,cut) );
                line.erase(0, cut + 1);

                cell c;
                c.n = n;
                c.marked = false;
                p.push_back(c);
                
                if( j == 4){
                    players.push_back( std::vector<std::vector<cell>>() );
                    players[nPlayers].push_back(p); 
                    p.clear();
                }  
            }
            i++;
            if( i == 5 ){
                nPlayers++;
                i = 0;
            }
        }
    }
    
    //Part One
    
    int horizLine = 0, vertLine = 0;
    bool end = false;
    int whoWin = 0; //player who won
    int nWin = 0; //last number -> winning number
    
    for( int n = 0; n < gameInput.size() && !end; n++ ){

        //New number come out
        //Check on the board
        for( int i = 0; i < nPlayers && !end; i++ ){
            for( int j = 0; j < 5 && !end; j++ ){
                for( int k = 0; k < 5 && !end; k++ ){
                    
                    if( players[i][j][k].n == gameInput[n] )
                        players[i][j][k] = cell{gameInput[n],true}; 

                    if( players[i][j][k].marked == true )
                        horizLine++;
                    
                    if( horizLine == 5 ){
                        end = true;
                        whoWin = i;
                        nWin = gameInput[n];
                    }
                }
                horizLine = 0;
            }
        }
        
        for( int i = 0; i < nPlayers && !end; i++ ){
            for( int j = 0; j < 5; j++ ){
                for( int k = 0; k < 5; k++ ){
                    
                    if( players[i][k][j].marked == true )
                        vertLine++;
                    
                    if( vertLine == 5 ){
                        end = true;
                        whoWin = i;
                        nWin = gameInput[n];
                    }
                }
                vertLine = 0;
            }
        } 
    }
    int sum = 0;
    for( int j = 0; j < 5; j++ )
        for( int k = 0; k < 5; k++ )
            if( players[whoWin][j][k].marked == false )
                sum += players[whoWin][j][k].n;   
    
    
    std::cout << "Winner board: " << whoWin << std::endl; 
    std::cout << "Last number called before someone won: " << nWin << std::endl;
    std::cout << "Sum unmarked numbers: " << sum << std::endl;
    std::cout << "Final score: " << nWin * sum;
    
    //Part Two
    std::map<int,int> winnerBoards;
    std::map<int,int>::iterator it;
    std::pair<int,int> winner;
    
    int leftBoards = nPlayers, whoLose;
    
    for( int n = 0; n < gameInput.size() && leftBoards > 0; n++ ){
        if( n == 98 )
            std::cout << "Hol";
        //New number come out
        //Check on the board
        for( int i = 0; i < nPlayers && leftBoards > 0; i++ ){
            
            it = winnerBoards.find( i );
            if( it == winnerBoards.end() ){

                for( int j = 0; j < 5 && leftBoards > 0; j++ ){
                    for( int k = 0; k < 5 && leftBoards > 0; k++ ){

                        if( players[i][j][k].n == gameInput[n] )
                            players[i][j][k] = cell{gameInput[n],true}; 

                        if( players[i][j][k].marked == true )
                            horizLine++;

                        if( horizLine == 5 ){

                            it = winnerBoards.find( i );
                            if( it == winnerBoards.end() ){
                                winner.first = winner.second = i;
                                winnerBoards.insert(winner);
                                leftBoards--;
                                nWin = gameInput[n];
                                whoLose = i;
                            }
                        }
                    }
                    horizLine = 0;
                }
            }
        }

        for( int i = 0; i < nPlayers && leftBoards > 0; i++ ){

            it = winnerBoards.find( i );
            if( it == winnerBoards.end() ){
                for( int j = 0; j < 5 && leftBoards > 0; j++ ){
                    for( int k = 0; k < 5 && leftBoards > 0; k++ ){
                        
                        if( players[i][k][j].marked == true )
                            vertLine++;

                        if( vertLine == 5 ){

                            it = winnerBoards.find( i );
                            if( it == winnerBoards.end() ){
                                winner.first = winner.second = i;
                                winnerBoards.insert(winner);
                                leftBoards--;
                                whoLose = i;
                                nWin = gameInput[n];
                            }
                        }          
                    }
                    vertLine = 0;
                } 
            }
        }
    }

    sum = 0;
    for( int j = 0; j < 5; j++ )
        for( int k = 0; k < 5; k++ )
            if( players[whoLose][j][k].marked == false )
                sum += players[whoLose][j][k].n;   
    
    std::cout << "\n\nLoser board: " << whoLose << std::endl; 
    std::cout << "Last number called before loser won: " << nWin << std::endl;
    std::cout << "Sum unmarked numbers: " << sum << std::endl;
    std::cout << "Final score: " << nWin * sum;
    return 0;
}