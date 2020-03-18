// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DLList.h"

int main (void)
{
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));

    size_t nitems = DLListLength(myList);
    char *newI = "I did not hit her";
    char *newIt = "I did not";
    char *newIte = "I did nooooot";
    char *newItem = "Oh hi Mark";

	// TODO: more tests needed here
    printf("=== Test Begin ===\n\n");
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    
    printf(" >> MOVING: To line 3 'containing a few lines'\n");
    DLListMoveTo(myList, 3);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> MOVING: Back 2 lines to 'this is'\n");
    DLListMove(myList, -2);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'this is'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'a small file'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'containing a few lines'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'of boring text'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> Assert testing if List is empty\n");
    assert (DLListIsEmpty (myList));
    
    printf("\n >> ADDING: 'I did not'");
    DLListAfter(myList, newIt);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> ADDING: 'I did not hit her'\n");
    DLListBefore(myList, newI);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> ADDING: 'I did nooooot'\n");
    DLListAfter(myList, newIte);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> ADDING: 'Oh hi Mark'\n");
    DLListAfter(myList, newItem);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> MOVING: To line 1 'I did not hit her'\n");
    DLListMoveTo(myList, 1);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'I did not hit her'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> MOVING: To line 3 'Oh hi Mark'\n");
    DLListMoveTo(myList, 3);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n >> DELETING: 'Oh hi Mark'\n");
    DLListDelete(myList);
    assert (validDLList (myList));
    nitems = DLListLength(myList);
    printf(" >> %zu items are present in the list\n", nitems);
    printf(" >> Current item is: %s\n", DLListCurrent(myList));
    printf(" >> Displaying the entire List\n\n");
    putDLList(stdout, myList);
    
    printf("\n=== Test Complete ===\n");
    
	freeDLList (myList);
	return EXIT_SUCCESS;
}
