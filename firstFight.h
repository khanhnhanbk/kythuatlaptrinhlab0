/*
    * Ho Chi Minh City University of Technology
    * Faculty of Computer Science and Engineering
    * Initial code for Assignment 0
    * Programming Fundamentals Spring 2021
    * Author: Nguyen Thanh Nhan
    * Date: 08.02.2021
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef firstFight_h
#define firstFight_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
int getReady(int &HP, const int &ID, int &M, const int &E1)
{
    HP = HP > 1000 ? 1000 : HP;
    HP = HP < 0 ? 0 : HP;
    M = M > 1000 ? 1000 : M;
    M = M < 0 ? 0 : M;
    if (E1 < 100 || E1 > 500)
        return -999;
    else
    {
        if (E1 < 200)
        {
            if (ID == 0)
            {
                int h = (E1 - 100) % 64;
                int J = HP % 100;
                if (J > h)
                {
                    if (M % 2 == 0 && M >= 200)
                    {
                        M -= 200;
                        HP += 25;
                    }
                    else if (HP >= 500 && M % 2 != 0 && M >= 300)
                    {
                        M -= 300;
                        HP += 50;
                    }
                }
            }
            else if (ID == 1)
                HP += 75;
        }
        else if (E1 < 300)
        {
            int arrayHP[4] = {5, 7, 9, 11};
            int arrayM[4] = {190, 195, 200, 205};
            int x = E1 % 4 + 1;
            if (ID != 0)
            {
                if (M >= arrayM[x - 1])
                {
                    M -= arrayM[x - 1];
                    HP += arrayHP[x - 1];
                }
            }
            else
            {
                if ((M - x) % 2 == 0 && M >= arrayM[x - 1])
                {
                    M -= arrayM[x - 1];
                    HP += arrayHP[x - 1];
                }
            }
        }
        else if (E1 < 400)
        {
            int a = E1 % 10;
            if (a == 2 || a == 3 || a == 5 || a == 7)
            {
                a = 2 * a;
            }
            else
                a = 1;
            if (HP >= 600)
            {
                int lastHP = HP % 10;
                if (lastHP == 2 || lastHP == 3 || lastHP == 5 || lastHP == 7)
                {
                    if (M >= 500) // du tien
                    {
                        M -= 500;
                        if (ID == 1)
                            HP += 200;
                        else
                            HP += ceilf(float(HP * 2.0 * a) * 0.01);
                    }
                }
                else
                {
                    if (M >= 300) // mua dao
                    {
                        M -= 300;
                        HP += ceilf(float(HP * a) *0.01);
                    }
                }
            }
        }
        else if (E1 < 500)
        {
            if (E1 % 5 == 0)
                HP = ceilf(HP * 0.9);
        }
        else
        {
            HP = ceilf(0.75 * HP);
            M = ceilf(0.75 * M);
        }
        HP = HP > 1000 ? 1000 : HP;
        HP = HP < 0 ? 0 : HP;
        return HP + M;
    }
}

int firstBattle(int &HP1, int &HP2, const int &ID1, const int &ID2, const int &E2)
{
    //Complete this function to gain point on task 2
    int res;
    if (E2 < 100 || E2 >= 500)
        return -999;
    else if (E2 < 200)
    {
        HP1 = ceilf(HP1 * 1.1);
        HP2 = ceilf(1.3 * HP2);
    }
    else if (E2 <= 299)
    {
        HP1 = ceilf(1.7 * HP1);
        HP2 = ceilf(1.2 * HP2);
    }
    else if (E2 <= 399)
        HP1 = E2 < 350 ? HP1 + 30 : HP1 + E2 % 100;
    else if (E2 <= 499)
    {
        HP1 = ceilf(1.3 * HP1);
        HP1 = HP1 > 1000 ? 1000 : HP1;
        HP1 = ceilf(0.5 * HP1);
        HP2 = ceilf(0.8 * HP2);
    }

    HP1 = HP1 > 1000 ? 1000 : HP1;
    HP2 = HP2 > 1000 ? 1000 : HP2;
    if (ID1 != 0 && ID2 != 0)
        res = 0;
    else if (ID1 != 0 && ID2 == 0)
    {
        res = 1;
        HP2 = 0;
    }
    else if (ID2 != 0 && ID1 == 0)
    {
        res = -1;
        HP1 = 0;
    }
    else if (ID1 == 0 && ID2 == 0)
    {
        int mu = ceilf((2.0 * HP1 * HP2) / (float(HP1 + HP2)));
        if (HP1 > HP2)
            res = 1;
        else if (HP1 < HP2)
            res = -1;
        else
            res = 0;
        int HP11 = HP1 - abs(HP2 - mu);
        HP2 = HP2 - abs(HP1 - mu);
        HP1 = HP11;
        HP1 = HP1 < 0 ? 0 : HP1;
        HP2 = HP2 < 0 ? 0 : HP2;
    }
    // th5
    HP1 = ceilf(0.8 * HP1);
    return res;
}

int secondBattle(int &HP1, int &HP2, const int &ID1, const int &ID2, const int &E3)
{
    int res;
    if (E3 < 100 || E3 >= 300)
        return -999;
    HP1 = ceilf(1.4 * HP1);
    HP2 = ceilf(1.6 * HP2);
    if (ID1 != 0)
        HP1 *= 2;
    HP1 = HP1 > 1000 ? 1000 : HP1;
    HP2 = HP2 > 1000 ? 1000 : HP2;
    if (E3 >= 200 && E3 <= 299)
    {
        if (ID2 == 0)
            HP2 = ceilf(0.95 * HP2);
        return 0;
    }
    if (ID1 != 0 && ID2 != 0)
        return 0;
    else if (ID1 != 0 && ID2 == 0)
    {
        HP2 = 0;
        return 1;
    }
    else if (ID2 != 0 && ID1 == 0)
    {
        // HP1 = 0;
        return -1;
    }
    // else
    if (E3 <= 199)
    {
        if (ID2 == 0)
            HP2 = ceilf(0.95 * HP2);
        int mu = ceilf((2.0 * HP1 * HP2) / ((float)HP1 + HP2));
        if (HP1 > HP2)
            res = 1;
        else if (HP1 < HP2)
            res = -1;
        else
            res = 0;
        int HP11 = HP1 - abs(HP2 - mu);
        int HP21 = HP2 - abs(HP1 - mu);
        if (res == -1)
            HP11 = HP1;
        else if (HP11 <= 0)
            HP11 = 0;
        else if (HP21 <= 0)
            HP21 = 0;
        HP1 = HP11;
        HP2 = HP21;
    }
    return res;
}

int finalBattle(int &HP1, int &HP2, const int &ID1, const int &ID2, const int &E4)
{
    int res = -999;
    if (E4 >= 100 && E4 <= 199)
    {
        if (ID2 == 0)
        {
            HP2 = ceilf(0.1 * HP2);
        }
        else
        {
            HP2 = ceilf(0.3 * HP2);
        }
        res = 0;
    }
    if (E4 >= 200 && E4 <= 299)
    {
        HP2 = 0;
        res = 1;
    }
    return res;
}
////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* firstFight_h */