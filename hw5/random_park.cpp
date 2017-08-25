#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;
double randomReal(double fMin,double fMax){
    double f=(double)rand()/RAND_MAX;
    return fMin + f*(fMax-fMin);
}

int numOfCars(double start,double end){
    if((end-start)<1.0) return 0;
    else {
        double parkingSite=randomReal(start,end-1);
        return numOfCars(start,parkingSite)+numOfCars(parkingSite+1,end)+1;
    }
}

int main(int argc, char ** argv){
    srand(time(NULL));
    cout<<setw(7);
    while(true){
        double curb=0.0;
        cout<<"Pleas input length of curb in meter (the length of car is 1 m): "<<endl;
        cin>>curb;
        int totalCount=0;
        int numSimulation=100000;
        for (int i=0;i<numSimulation;i++){
            totalCount+=numOfCars(0,curb);
        }
        cout<<"average number of parked cars: \n"<<totalCount/double(numSimulation)<<endl;
    }
    return 0;

}