/*
 * Dynamic Array Data Structure
 *
 * 2022 Huseyin YALDIZ <contact@huseyinyaldiz.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define INITIAL_CAPACITY                     8
#define VECTOR_CAPACITY_INCREASE_CONSTANT    2

/*return type ERRORS*/
#define ERROR_CAPACITY  -1
#define ERROR_PUSHBACK  -2
#define ERROR_INDEX     -3

typedef void* (*fptrAllocater)(size_t);
typedef void* (*fptr_reAllocater)(void*,size_t);
typedef void  (*fptrFree)(void*);

typedef int valueType;

typedef struct Vector
{
    valueType* pArray;
    size_t capacity;
    size_t size;
}Vector,*HndVector;

/*Init Functions*/
HndVector initVector();
HndVector initVectorCapacity(size_t capacity);
void destroyVector(HndVector vector);

/*Getter Functions*/
size_t getSize(const HndVector vec);
size_t getCapacity(const HndVector vec);
valueType getAt(const HndVector vec , size_t index);
void displayVector(const HndVector vec , void* periphBuff);

/*Query,Predicate Functions*/
bool isEmpty(const HndVector vec);

/*Manipulators*/
int pushBack(HndVector vec , valueType val);
int insertAt(HndVector vec , size_t index , valueType val);
int removeAt(HndVector vec , size_t index);
void popBack(HndVector vec);
void swapVectorIndex(HndVector vec , size_t index1 , size_t index2);
