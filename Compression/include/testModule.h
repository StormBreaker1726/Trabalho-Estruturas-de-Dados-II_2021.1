#ifndef DB4AF468_33F0_4CD2_8A83_ACF2BBF7412E
#define DB4AF468_33F0_4CD2_8A83_ACF2BBF7412E

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include "bmh.h"
#include "bruteforce.h"
#include "kmp.h"
#include "rabinKarp.h"
#include "Huffman.h"

void testModule(char* path, char* path2){

    string filename = "MetricsFile.txt";
    string metricFilePath = "";
    metricFilePath.append(path).append("/").append(filename);

    fstream metricFile;

    metricFile.open(metricFilePath, ios::out|ios::app);

    auto startTotal = std::chrono::steady_clock::now();

    auto start1 = std::chrono::steady_clock::now();
    cout<<"Huffman beginning"<<endl;
    huffmanCompressionStart(path);
    huffmanDecompressionStart(path);
    cout<<"Huffman ending"<<endl;
    auto end1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_secondsHuffman = end1 - start1;

    

    auto start4 = std::chrono::steady_clock::now();
    cout<<"BHM beginning"<<endl;
    bhmMainStart(path2);
    cout<<"BHM ending"<<endl;
    auto end4 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_secondsBMH = end4 - start4;

    

    auto start3 = std::chrono::steady_clock::now();
    cout<<"KMP beginning"<<endl;
    KmpMainStart(path2);
    cout<<"KMP ending"<<endl;
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_secondsKMP = end3 - start3;


    auto start2 = std::chrono::steady_clock::now();
    cout<<"BF beginning"<<endl;
    bruteForceMainStart(path2);
    cout<<"BF ending"<<endl;
    auto end2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_secondsBruteForce = end2 - start2;

    auto endTotal = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_secondsTotal = endTotal - startTotal;


    metricFile<<"----------------------------------------------------------------------------"<<endl;
    metricFile<<"Huffman time:"<<endl;
    metricFile<<elapsed_secondsHuffman.count()<<" seconds"<<endl;
    metricFile<<"----------------------------------------------------------------------------"<<endl;

    metricFile<<"----------------------------------------------------------------------------"<<endl;
    metricFile<<"BMH:"<<endl;
    metricFile<<elapsed_secondsBMH.count()<<" seconds"<<endl;
    metricFile<<"----------------------------------------------------------------------------"<<endl;

    metricFile<<"----------------------------------------------------------------------------"<<endl;
    metricFile<<"KMP:"<<endl;
    metricFile<<elapsed_secondsKMP.count()<<" seconds"<<endl;
    metricFile<<"----------------------------------------------------------------------------"<<endl;

    metricFile<<"----------------------------------------------------------------------------"<<endl;
    metricFile<<"Brute Force:"<<endl;
    metricFile<<elapsed_secondsBruteForce.count()<<" seconds"<<endl;
    metricFile<<"----------------------------------------------------------------------------"<<endl;

    metricFile<<"----------------------------------------------------------------------------"<<endl;
    metricFile<<"Time to execute the Test Module: "<<elapsed_secondsTotal.count()<<" seconds"<<endl;
    metricFile<<"----------------------------------------------------------------------------"<<endl;

    metricFile<<endl;
    metricFile<<endl;
    metricFile<<endl;
    metricFile<<endl;
}


#endif /* DB4AF468_33F0_4CD2_8A83_ACF2BBF7412E */
