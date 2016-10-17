/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 16, 2016
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "SaleDat.h"
using namespace std;

void getData(SaleDat&);
void save(const char*, SaleDat&);
void load(const char*, vector<SaleDat>&);
void clear(const char*);
void clear(char*, unsigned int);

int main(int argc, char** argv){
    const char *PATH = "salesdata.bin";
    SaleDat north, east, south, west;
    north.divName = "North";
    east.divName = "East";
    south.divName = "South";
    west.divName = "West";

    clear(PATH);
    cout << "INPUT QUARTERLY SALES DATA" << endl;
    getData(north);
    getData(east);
    getData(south);
    getData(west);
    cout << endl;
    cout << "WRITING DATA TO " << PATH << "...";
    save(PATH, north);
    save(PATH, east);
    save(PATH, south);
    save(PATH, west);
    cout << "DONE!" << endl;
    vector<SaleDat> data;
    cout << "READING FROM " << PATH << "...";
    load(PATH, data);
    cout << "DONE!" << endl;
    cout << endl;
    ofstream out;
    out.open("out.txt");
    for(int i = 0; i < data.size(); ++i){
        cout << "DIVISION: " << data[i].divName << endl;
        out << "DIVISION: " << data[i].divName << endl;
        for(int j = 0; j < SaleDat::SIZE; ++j){
            cout << "SALES FOR Q" << j + 1 << ": $" << data[i].sales[j] << endl;
            out << "SALES FOR Q" << j + 1 << ": $" << data[i].sales[j] << endl;
        }
    }
    out.close();

    return 0;
}

void save(const char *path, SaleDat &data){
    ofstream out;
    int len = data.divName.size();

    out.open(path, ios::binary | ios::app);
    out.write(reinterpret_cast<char*>(&len), sizeof (len));
    out.write(data.divName.c_str(), len);
    for(int i = 0; i < SaleDat::SIZE; ++i){
        out.write(reinterpret_cast<char*>(&data.sales[i]), sizeof (data.sales[i]));
    }
    out.close();
}

void load(const char *path, vector<SaleDat> &data){
    ifstream in;

    in.open(path, ios::binary);
    while(in.good() && !in.eof()){
        int len = 0;
        SaleDat tmp;
        //tmp.divName = "";
        in.read(reinterpret_cast<char*>(&len), sizeof (len));
        if(len > 0){
            char *buffer = new char[len];
            //clear(buffer, len);
            in.read(buffer, len);
            tmp.divName = buffer;
            delete [] buffer;
        }
        for(int i = 0; i < SaleDat::SIZE; ++i){
            in.read(reinterpret_cast<char*>(&tmp.sales[i]), sizeof (tmp.sales[i]));
        }
        if(!in.eof()){
            data.push_back(tmp);
        }
    }
    in.close();
}

void getData(SaleDat &data){
    cout << "DIVISION: " << data.divName << endl;
    for(int i = 0; i < SaleDat::SIZE; ++i){
        int input = 0;
        do{
            cout << "ENTER SALES FOR Q" << i + 1 << ": $";
            cin >> input;
        } while(input < 0);
        data.sales[i] = input;
    }
}

void clear(const char *path){
    ofstream out;
    out.open(path, ios::trunc);
    out.close();
}

void clear(char *array, unsigned int size){
    for(int i = 0; i < size; ++i){
        array[i] = 0;
    }
}