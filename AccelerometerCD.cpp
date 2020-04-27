#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int main()
{
    ifstream in1;
    ofstream out1;
    in1.open("run1.csv");

    double X = 0, Y = 0, Z = 0; // used to extract data point from csv file;

    vector <double> acc, time, velo; // total acceleration, time, velocity
    vector<double> x, y, z; // avg value of x, y, z which will be used for final data analysis
    vector<double> xC, yC, zC; // values of x, y, and z for a one count
    int BigCount = 0; // BigCount tracks total amount of data points
    double Count = 0; // Count tracks how many data points per time
    double tim, vel, timecheck = 0; // used to determine when a switch of time is made to start new count
    int value = 3;  // this value is to determine the data sampling rate and used for differentiating time
    string temp;

    getline(in1, temp); // get rid of initial first line
    cout << temp << endl;
    while (!in1.eof())
    {
        getline(in1, temp, ',');    // used to take out not necessary info
        getline(in1, temp, ',');


        if (BigCount == 0 || Count == value) { // sets initial time and then resets it to
            in1 >> tim;                          // the new time once it hits  a certain amount of data samplings
            time.push_back(tim);
            // cout << time << endl;
        }
        else
            in1 >> timecheck;                     // uses this to make sure that time is the same

            // vector for time
            // look into calculating median
        in1.ignore();
        if (tim != timecheck) // done with data sampling for certain time so now does calculations and inputs
        {                      // to vector of average accelerations for that time.
            cout << "time(s): " << timecheck << endl;
            for (int i = Count - 1; i >= 0; i--) {   // sums all the values taken from xC
                X += xC[i];
                xC.pop_back();
            }
            X = X / Count; // creates average for x-axis
            cout << "x: " << X << "  ,";
            x.push_back(X); // saves into x vector
            for (int i = Count - 1; i >= 0; i--) {  // sums all the values taken from yC
                Y += yC[i];
                yC.pop_back();
            }
            Y = Y / Count; // creates average for y-axis
            cout << "y: " << Y << "  ";
            y.push_back(Y); // saves into the y vector
            for (int i = Count - 1; i >= 0; i--) {  // sums all the values taken from zC
                Z += zC[i];
                zC.pop_back();
            }
            Z = Z / Count; // creates average for z-axis
            cout << "z: " << Z << "  " << endl << endl;
            z.push_back(Z); // saves into the z vector
            Count = 0;
        }

        in1 >> X;
        xC.push_back(X);
        X = 0;
        in1.ignore();
        in1 >> Y;
        yC.push_back(Y);
        Y = 0;
        in1.ignore();
        in1 >> Z;
        zC.push_back(Z);
        Z = 0;
        Count++;
        BigCount++;
    }

    cout << "time(s): " << tim << endl;

    for (int i = Count - 1; i >= 0; i--) {   // sums all the values taken from xC
        X += xC[i];
        xC.pop_back();
    }
    X = X / Count; // creates average for x-axis
    cout << "x: " << X << "  ,";
    x.push_back(X);
    for (int i = Count - 1; i >= 0; i--) {  // sums all the values taken from yC
        Y += yC[i];
        yC.pop_back();
    }
    Y = Y / Count; // creates average for y-axis
    cout << "y: " << Y << "  ";
    y.push_back(Y);
    for (int i = Count - 1; i >= 0; i--) {  // sums all the values taken from zC
        Z += zC[i];
        zC.pop_back();
    }
    Z = Z / Count; // creates average for z-axis
    cout << "z: " << Z << "  " << endl << endl;
    z.push_back(Z);
    Count = 0;

    double accel;

    in1.close();

    // calculation for total acceleration
    // does conversion from g force in x,y,z to m/s^2 when finding total acceleration

    out1.open("output.csv");

    for (int i = 0; i < BigCount / value; i++)
    {
        X = pow(x[i], 2);
        Y = pow(y[i], 2);
        Z = pow(z[i], 2);

        accel = X + Y + Z;
        accel = sqrt(accel);
        accel = accel - 1.01408;
        accel = accel * 9.80665;

        cout << "Time: " << time[i] << endl;
        acc.push_back(accel);
        cout << "Acceleration: " << acc[i] << endl << endl;
        out1 << time[i] << "," << acc[i];
        if (i == 0)
        {
            velo.push_back(0);
        }
        else if (i > 0)
        {
            vel = velo[i - 1] + (acc[i] * (time[i] - time[i - 1]));
            //   cout << time[i] << endl;
           //    cout << time[i-1];
            velo.push_back(vel);
        }
        cout << "Speed: " << velo[i] << endl << endl;
        out1 << "," << velo[i] << endl;
    }
    cout << "BigCount: " << BigCount << endl;
    return 0;
}
