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

/*
 * Day 1
 */
int main(int argc, char** argv) {
    
    std::string fileName = "day2_input.txt";
    std::ifstream file(fileName.c_str() );
    std::string line;
    int cut;
    
    std::vector<int> vN;
    std::vector<std::string> vOrder;
    
    int n;
    std::string str;
    
    //Read the entire input
    while( getline( file,line ) ){
        
        cut = line.find(' ');
        str = ( line.substr(0,cut) );
        line.erase( 0, cut + 1 );
        
        n = stoi(line);
        
        vOrder.push_back(str);
        vN.push_back(n);
        
    }
    
    //Part One
    
    int horizPos = 0, depth = 0;
    
    for( int i = 0; i < vN.size(); i++ ){
        
        if( vOrder[i] == "forward" )
            horizPos += vN[i];
        else if( vOrder[i] == "up" )
            depth -= vN[i];
        else
            depth += vN[i];
        
    }
    
    std::cout << "Horizontal position: " << horizPos << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Multiply both numbers: " << horizPos*depth << std::endl;
    
    //Part Two
    
    int aim = 0;
    horizPos = 0, depth = 0;
    
    for( int i = 0; i < vN.size(); i++ ){
        
        if( vOrder[i] == "forward" ){
            horizPos += vN[i];
            depth += ( vN[i] * aim );
        } 
        else if( vOrder[i] == "up" )
            aim -= vN[i];
        else //down
            aim += vN[i];
    }
    std::cout << "\nHorizontal position: " << horizPos << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    std::cout << "Multiply both numbers: " << horizPos * depth << std::endl;
    
    return 0;
}