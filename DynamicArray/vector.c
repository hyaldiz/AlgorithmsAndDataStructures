/*
 * Dynamic Array Data Structure
 *
 * 2022 Huseyin YALDIZ <contact@huseyinyaldiz.com>
 */

#include "vector.h"

fptrAllocater  alocater = malloc;
fptr_reAllocater reAllocater = realloc;
fptrFree freeAddress = free;

HndVector initVector()
{
    return initVectorCapacity(INITIAL_CAPACITY);
}

HndVector initVectorCapacity(size_t capacity)
{
    HndVector pVector = (HndVector)alocater(sizeof(Vector));
    if(pVector == NULL)
    {
        fprintf(stderr,"Not Enough Space For Handle!");
        return NULL;
    }

    pVector->pArray = (valueType*)alocater(capacity*sizeof(valueType));
    if(pVector->pArray == NULL)
    {
        fprintf(stderr,"Not Enough Space For Capacity!");
        free(pVector);
        return NULL;
    }

    pVector->size = 0;
    pVector->capacity = capacity;

    return pVector;
}

void destroyVector(HndVector vector)
{
    freeAddress(vector->pArray);
    freeAddress(vector);
}

size_t getSize(const HndVector vec)
{
    return vec->size;
}

size_t getCapacity(const HndVector vec)
{
    return vec->capacity;
}

bool isEmpty(const HndVector vec)
{
    return !vec->size == 0;
}

valueType getAt(const HndVector vec , size_t index)
{
    if(index < 0 || index > vec->size)
        return ERROR_INDEX;

    return vec->pArray[index];
}

void displayVector(const HndVector vec , void* periphBuff)
{
    if(periphBuff == NULL)
    {
        for(int i = 0; i < getSize(vec);i++)
            printf("index = %d value = %d \n",i,vec->pArray[i]);
    }
    else
    {
        //Microcontrollerlarda haberlesme bufferlarinda kullanilabilir.
        for(int i = 0; i < getSize(vec);i++)
            *(uint32_t*)periphBuff = vec->pArray[i];
    }
}

/*Internal Linkage, Client Kodlar erisim saglayamaz!*/
static int setCapacity(HndVector vec)
{
    size_t memorySizeBytes = vec->capacity*2*VECTOR_CAPACITY_INCREASE_CONSTANT*sizeof(valueType);

    valueType *pnewArray = (valueType*)reAllocater(vec->pArray,sizeof(memorySizeBytes));
    if(pnewArray == NULL)
    {
        fprintf(stderr,"Not Enough Space For setCapacity(HndVector vec);!");
        return ERROR_CAPACITY;
    }

    vec->capacity = vec->capacity*VECTOR_CAPACITY_INCREASE_CONSTANT;
    vec->pArray = pnewArray;

    return vec->capacity;
}

int insertAt(HndVector vec , size_t index , valueType val)
{
    if(index < 0 || index > vec->size)
        return ERROR_INDEX;
    if(vec->size >= vec->capacity)
        if(setCapacity(vec) == ERROR_CAPACITY)
            return ERROR_CAPACITY;

    //Kesisen bellek bloklarını tasiyalima
    memmove(&vec->pArray[index + 1],&vec->pArray[index],(vec->size - index)*sizeof(valueType));
    vec->pArray[index] = val;
    ++vec->size;

    return index;
}

int removeAt(HndVector vec , size_t index)
{
    if(index < 0 || index > vec->size)
        return ERROR_INDEX;

    memmove(&vec->pArray[index],&vec->pArray[index + 1],(vec->size - index - 1)*sizeof(valueType));
    --vec->size;

    return index;
}

void popBack(HndVector vec)     //Wrapper Function
{
    removeAt(vec,vec->size - 1);
}

void swapVectorIndex(HndVector vec , size_t index1 , size_t index2)
{
    valueType tempValue;

    /*
    	Dynamic Assertion
        	NOT: Static Assertion'lar compile timeda hata verir.
    */
    assert((index1 < vec->size) && (index1 >= 0));
    assert((index2 < vec->size) && (index2 >= 0));

    tempValue = vec->pArray[index1];
    vec->pArray[index1] = vec->pArray[index2];
    vec->pArray[index2] = tempValue;
}

/*Manipulators*/
int pushBack(HndVector vec , valueType val)
{
    if(vec->size >= vec->capacity)
        if(setCapacity(vec) == ERROR_CAPACITY)
            return ERROR_PUSHBACK;

    vec->pArray[vec->size] = val;
    vec->size++;

    //Ekleme yapilan indexi dondur.
    return vec->size -1;
}
