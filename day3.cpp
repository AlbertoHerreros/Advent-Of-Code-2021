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
#include <algorithm>
#include <math.h>

/*
 * Day 3
 */

// Convert vector of digits to integer
long long vector_to_int(std::vector<int> num) { 
    long long n = 0;
    int N = num.size();
    for (int i = 0; i < N; i++) {
        n += num[i]*pow(10, N-i-1);
    }
    return n;
}

// function definition
int convert(long long n){
  int dec = 0, i = 0, rem;

  while (n!=0) {
    rem = n % 10;
    n /= 10;
    dec += rem * pow(2, i);
    ++i;
  }
  return dec;
}

 void eraseFromVector( std::vector<std::string> *v, int position, char c ){
     std::vector<std::string>::iterator it = v->begin();
     for( it; it != v->end(); ){
         
         if( (*it)[position] == c )
             it = v->erase(it);
         else
             ++it;
     }   
     
 }

int main(int argc, char** argv) {
    
    std::string fileName = "day3_input.txt";
    std::ifstream file(fileName.c_str() );
    std::string line;
    int cut;
    
    std::vector<std::string> vN;
    
    std::string str;
    
    //Read the entire input
    while( getline( file,line ) ){
        
        cut = line.find(' ');
        str = ( line.substr(0,cut) );
        str.erase(12,13); // \\r
        vN.push_back(str);
    }
    
    //Part One
    
    int nZero = 0, nOne = 0;
    std::vector<int> gam, ep;
    
    for( int j = 0; j < 12; j++ ){
        for( int i = 0; i < vN.size(); i++ ){
            if( vN[i][j] == '0' )
                nZero++;
            else
                nOne++;
        }
        
        if( nZero > nOne ){
            gam.push_back(0);
            ep.push_back(1);
        }
        else{
            gam.push_back(1);
            ep.push_back(0);
        }
        nZero = nOne = 0;
    }

    long long gamma = vector_to_int(gam);
    long long epsilon = vector_to_int(ep);
    
    int gammaRate = convert(gamma);
    int epsilonRate = convert(epsilon);
    
    std::cout << "\nGamma rate: " << gammaRate << "\nEpsilon rate: " << epsilonRate << std::endl;
    std::cout << "Power consumption: " << gammaRate * epsilonRate << std::endl;
    
    //Part Two
    
    std::vector<std::string> vOxygen = vN;
    std::vector<std::string> vCO2 = vN;

    //CO2 scrubber
    int j = 0;
    while( vCO2.size() > 1 ){
        for( int i = 0; i < vCO2.size(); i++){
            if( vCO2[i][j] == '0' )
                nZero++;
            else
                nOne++;
        }
        
        if( nZero <= nOne ){
            if( vCO2.size() > 1 )
                eraseFromVector(&vCO2,j,'1');
        }
        else{
            if( vCO2.size() > 1 )
                eraseFromVector(&vCO2,j,'0'); 
        }
        nZero = nOne = 0;
        j++;
    }
    
    //Oxygen generator
    j = 0;
    while( vOxygen.size() > 1 ){
        for( int i = 0; i < vOxygen.size(); i++){
            if( vOxygen[i][j] == '0' )
                nZero++;
            else
                nOne++;
        }
        
        if( nZero > nOne ){
            if( vOxygen.size() > 1 )
                eraseFromVector(&vOxygen,j,'1');
        }
        else{
            if( vOxygen.size() > 1 )
                eraseFromVector(&vOxygen,j,'0'); 
        }
        nZero = nOne = 0;
        j++;
    }

    int OxygenRate = convert( stoll( vOxygen[0] ) );
    int CO2Rate = convert( stoll( vCO2[0] ) );
    
    std::cout << "\nOxigen rate: " << OxygenRate << std::endl;
    std::cout << "CO2Rate: " << CO2Rate << std::endl;
    std::cout << "Life support rating of the submarine: " << CO2Rate * OxygenRate;
    
    return 0;
}