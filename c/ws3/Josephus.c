#include <stdio.h>
#include <string.h>
#include <stdlib.h> /*malloc*/
#include "Josephus.h"

void Final(int sward, int kill);

int *Solds(int n)
{
	int jos_arr[2];
	int i = 0;
	while (i < n)
	{
		jos_arr[i] = 1;
		++i;
	}
	return jos_arr;
}

void Final(int sward, int kill)
{
    if (sward == 1)
    {
        kill = 0;
    }
    else
    {
        sward = 0;
    }
}

void MoveSward(int sward, int kill, int n)
{
    while (jos_arr[sward] == 0 && sward < n)
    {
        ++sward;
    }
    if (sward < n)
    {
        Final(sward, kill);
    }
    else
    {
        kill = sward + 1;
    }
}

void MoveKill(int kill)
{
    while (kill == 0)
    {
        ++kill;
    }
}



void Stab(int *jos_arr, int sward, int kill, int alive)
{
    jos_arr[kill] = 0;
    --alive;
    sward = kill;
}

int Josephus(int n, int sward)
{
    int *jos_arr = Solds(n);
    int sward -= 1, kill = sward + 1, alive = n;
    
    while (alive > 1)
    {
        if (sward < (n - 1))
        {
            MoveSward(sward,kill, n);
            MoveKill(kill);
            Stab(jos_arr, sward, kill, alive);
        }
        else
        {
            Final(sward, kill);
        }
    }
    return sward +1;
}


