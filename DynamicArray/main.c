#include "vector.h"

int main()
{
    HndVector vector = initVectorCapacity(100);

    printf("Size: %ld  Capacity: %ld",getSize(vector),getCapacity(vector));

    pushBack(vector,1);
    pushBack(vector,2);
    pushBack(vector,3);
    pushBack(vector,4);
    pushBack(vector,5);
    pushBack(vector,6);
    pushBack(vector,7);
    pushBack(vector,8);
    pushBack(vector,9);
    pushBack(vector,10);
    pushBack(vector,11);

    insertAt(vector,2,150);

    printf("\nValue Is: %d",getAt(vector,vector->size-1));
    printf("\nValue Is: %d",getAt(vector,-1));
    printf("\nIs Empty: %d\n",isEmpty(vector));

    popBack(vector);

    swapVectorIndex(vector,0,2);

    displayVector(vector,NULL);

    return EXIT_SUCCESS;
}
