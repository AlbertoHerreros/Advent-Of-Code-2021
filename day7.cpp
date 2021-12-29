/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   day7.cpp
 * Author: Alberto Herreros Magaña
 *
 * Created on 25 de diciembre de 2021, 23:38
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <climits>
#include <algorithm>

/*
 * Day 7
 */

void putIntoMap( std::map<int,int> *m, int n ){
    
    std::map<int,int>::iterator it = m->find(n);
        if( it != m->end() )
            (*it).second++;
        else
            m->insert( std::pair<int,int>( n,1) );
}

int main(int argc, char** argv) {
    
    std::string fileName = "day7_input.txt";
    std::ifstream file(fileName.c_str() );
    std::string line;
    int cut, n;
        
    std::map< int, int > input; // n, n times it appears
    std::map< int, int >::iterator it;
    std::map< int, int >::iterator it2;
    //Read the entire input
    getline( file,line );
        
    while( line.find(',') != -1 ){
        
        cut = line.find(',');
        n = stoi( line.substr(0,cut) );
        line.erase(0, cut + 1);
        
        putIntoMap( &input,n );
        
    }
    n = stoi(line);
    putIntoMap(&input,n);
    
    //Part One
    int sum = 0, min = INT_MAX;
    
    for( it = input.begin(); it != input.end(); it++ ){
        for( it2 = input.begin(); it2 != input.end(); it2++ )
            sum += abs( ((*it).first - (*it2).first)) * (*it2).second;
        
        if( sum < min ){
            min = sum;
            n = (*it).first;
        }
        sum = 0;
    }
    std::cout << "Minimal possible cost with " << n << " : " << min << " fuel." << std::endl;
    
    //Part Two
    
    int distance;
    min = INT_MAX;
    sum = 0;
    
    auto x = std::max_element(input.begin(),input.end());
    int max = (*x).first;
    
    for( int i = 0; i <= max; i++  ){
        for( it = input.begin(); it != input.end(); it++ ){
            distance = abs( (*it).first - i );
            sum += ( (distance*(distance+1))/2 )* (*it).second; //summation k=1...k * n times it appear
        }
        if( sum < min ){
            min = sum;
            n = (*it).first;
        }
        sum = 0;
    }
    std::cout << "Minimal possible cost : " << min << " fuel.";
    
    return 0;
}