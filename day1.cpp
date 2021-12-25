/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Alberto Herreros Magaña
 *
 * Created on 25 de diciembre de 2021, 22:56
 */

#include <iostream>
#include <fstream>
#include <vector>

/*
 * Day 1
 */
int main(int argc, char** argv) {
    
    std::string fileName = "day1_input.txt";
    std::ifstream file(fileName.c_str() );
    std::string line;
    
    std::vector<int> v;
    int n = 0;
    
    //Read the entire input to push it into a vector
    while( getline( file,line ) ){
        v.push_back( stoi(line) );
    }
    
    //Part One
    for( int i = 1; i < v.size(); i++ )
        if( v[i-1] < v[i] )
            n++;
    
    std::cout << "Number of measurements that are larger than previous measurement: " << n << std::endl;
    
    //Part Two
    n = 0;
    int sum1, sum2;
    for( int i = 2; i < v.size()-1; i++ ){
        sum1 = v[i-2] + v[i-1] + v[i];
        sum2 = v[i-1] + v[i] + v[i+1];
        if( sum1 < sum2 )
            n++;
    }
    
    std::cout << "Number of sums that are larger than the previous sum: " << n;
    
    return 0;
}

