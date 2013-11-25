/* Hoang Huy Nguyen
 * UCSC Extension - Embedded Firmware Essentials
 * HW4 - Implement a circular buffer with one slot open
 * The following code is ported from Wikipedia
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
 
/**< Buffer Size */
#define IS_BUFFER_SIZE_POWER_OF_TWO  1
#define BUFFER_SIZE    8 
#define BUFFER_MASK  0x7 
#define NUM_OF_ELEMS   (BUFFER_SIZE-1)
 
/**< Circular Buffer Types */
typedef unsigned char INT8U;
typedef INT8U KeyType;
typedef struct
{
   INT8U writePointer; /**< write pointer */
   INT8U readPointer;  /**< read pointer */
   INT8U size;         /**< size of circular buffer */
   INT8U mask;         /**< bit Mask of circular buffer size*/
   KeyType keys[0];    /**< Element of ciruclar buffer */
} CircularBuffer;
 
/**< Init Ciruclar Buffer */
CircularBuffer* CircularBufferInit(CircularBuffer** pQue, int size)
{
        int sz = size*sizeof(KeyType)+sizeof(CircularBuffer);
        *pQue = (CircularBuffer*) malloc(sz);
        if(*pQue)
        {
            printf("Init CircularBuffer: keys[%d] (%d)\n", size, sz);
            if( !(size & (size-1)) )
            {
              (*pQue)->size=size;
              (*pQue)->mask=size-1; 
              (*pQue)->writePointer = 0;
              (*pQue)->readPointer  = 0;
            }
            else
            {
                 printf("Error Size:%d is not power of TWO!\n", size);
            }
        }
        return *pQue;
}
 
inline int CircularBufferIsFull(CircularBuffer* que)
{
#if IS_BUFFER_SIZE_POWER_OF_TWO
     return (((que->writePointer + 1) & que->mask) == que->readPointer); 
#else
     return (((que->writePointer + 1) % que->size) == que->readPointer); 
#endif
}
 
inline int CircularBufferIsEmpty(CircularBuffer* que)
{
     return (que->readPointer == que->writePointer); 
}
 
inline int CircularBufferEnque(CircularBuffer* que, KeyType k)
{
        int isFull = CircularBufferIsFull(que);
        if(!isFull) 
        {
        que->keys[que->writePointer] = k;
        que->writePointer++;
#if IS_BUFFER_SIZE_POWER_OF_TWO
        que->writePointer &= que->mask;
#else
        que->writePointer %= que->size;
#endif
        }
        return isFull;
}
 
inline int CircularBufferDeque(CircularBuffer* que, KeyType* pK)
{
        int isEmpty =  CircularBufferIsEmpty(que);
        if(!isEmpty) 
        {
        *pK = que->keys[que->readPointer];
        que->readPointer++;
#if IS_BUFFER_SIZE_POWER_OF_TWO
        que->readPointer &= que->mask;
#else
        que->readPointer %= que->size;
#endif
        }
        return(isEmpty);
}
 
inline int CircularBufferPrint(CircularBuffer* que)
{
        int i=0;
        int isEmpty =  CircularBufferIsEmpty(que);
        int isFull  =  CircularBufferIsFull(que);
        printf("\n==Q: w:%d r:%d f:%d e:%d\n", 
            que->writePointer, que->readPointer,  isFull, isEmpty);
        for(i=0; i< que->size; i++)
        {
           printf("%d ", que->keys[i]);
        }
        printf("\n");
        return(isEmpty);
}
 
int main(int argc, char *argv[])
{
        CircularBuffer* que;
        KeyType a = 101;
        int isEmpty, i;
 
        CircularBufferInit(&que, BUFFER_SIZE);
        CircularBufferPrint(que);
 
        for(i=1; i<=3; i++)
        {  
            a=10*i;
            printf("\n\n===\nTest: Insert %d-%d\n", a, a+NUM_OF_ELEMS-1);
            while(! CircularBufferEnque(que, a++));
 
            CircularBufferPrint(que);
            printf("\nRX%d:", i);
            a=0;
            isEmpty = CircularBufferDeque(que, &a); 
            while (!isEmpty)
            {
                printf("%02d ", a);
                a=0;
                isEmpty = CircularBufferDeque(que, &a); 
            }
            CircularBufferPrint(que);
        }
	printf("\n"); 
        free(que);
        return 0;
}
