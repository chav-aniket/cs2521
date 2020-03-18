// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
	peaksL->nitems = 0;
	if(L->nitems < 2) return peaksL;
	L->curr = L->first->next;
	
	while (L->curr != L->last) {
        if (L->curr->prev->value < L->curr->value &&
            L->curr->next->value < L->curr->value) {
            if (DLListIsEmpty(peaksL)) {
                peaksL->first = L->curr;
                peaksL->last = L->curr;
            } else {
                peaksL->last->next = L->curr;
                L->curr->prev = peaksL->last;
            }
            peaksL->last = L->curr;
            peaksL->nitems++;
        }
        L->curr = L->curr->next;
    }
    //peaksL->last->next = NULL;
	return peaksL;
}

