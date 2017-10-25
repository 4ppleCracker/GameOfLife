//#include "stdafx.h"
#include "PrivateFuncs.h"
#include <functional>
#include <iostream>
#include <time.h>
#include <Windows.h>


void PrivateFuncs::ExecuteAfterWhenKey(int secs, std::function<void()> func, char c) {
	int Time = clock();
	int OldRT = (clock() - Time);
	int RT = (clock() - Time);
	bool done = false;
	while (done == false) {
		while (GetKey(c) && done == false) {
			if (RT >= secs) {
				RT = (clock() - Time);
				if (GetKey(c) && OldRT != RT) {
					func();
					done = true;
					OldRT = RT;
				}
				else {
					done = true;
				}
			}
			else {
				RT = (clock() - Time);
			}
		}
	}
}
void PrivateFuncs::ExecuteAfter(int ms, std::function<void()> func) {
	int RT = clock();
	int FirstRT = clock();
	bool done = false;
	while (!done) {
		RT = clock();
		if (RT >= FirstRT + ms) {
			done = true;
			func();
		}
	}
}

int PrivateFuncs::DistanceFrom(int x, int y) {
	return max(x, y) - min(x, y);
}

std::string PrivateFuncs::atos(int arr[], int size, char spacing) {
	std::string s("");
	for (int i = 0; i < size; i++) {
		s.push_back(arr[i]);
		s.push_back(spacing);
	}
	return s;
}
