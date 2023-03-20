#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

//I was helped by the answers to the test moed A in the model
typedef struct AdptArray_
{
    size_t size;
    PElement * array;
    COPY_FUNC copy; 
    DEL_FUNC delete;
    PRINT_FUNC print;

}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC cmp, DEL_FUNC del,PRINT_FUNC print){
    PAdptArray newArray = (PAdptArray) malloc (sizeof(AdptArray));
    if(!newArray){
        printf("Error\n");
        return NULL;
    }

    newArray->size = 0;
    newArray->array=NULL;
    newArray->copy=cmp;
    newArray->delete=del;
    newArray->print=print;

    return newArray;

}

void DeleteAdptArray(PAdptArray adptArray){
    if(!adptArray)
        return;
    if(adptArray->array != NULL){
        for (size_t i = 0 ; i < adptArray->size ; i++){
            if((adptArray->array)[i] != NULL){
                adptArray->delete((adptArray->array)[i]);
            }
        }
        free(adptArray->array);
    }
    free(adptArray);
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement newElement){
    if (!adptArray)
        return FAIL;
    if(adptArray->size <= index){
        PElement* newElemArray = (PElement*) calloc ((index+1) ,sizeof(PElement));
        if(!newElemArray)
            return FAIL;
        for (size_t i = 0; i < adptArray->size ; i++)
        {
           newElemArray[i] = adptArray->array[i];
        }
        adptArray->size = index+1;
        free(adptArray->array);
        adptArray->array = newElemArray;
    }
    if(adptArray->array[index] != NULL)
        adptArray->delete(adptArray->array[index]);
    if(newElement != NULL)
        adptArray->array[index] = adptArray->copy(newElement);
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int index){
    if(!adptArray)
        return NULL;
    if(adptArray->size <= index)
        return NULL;
    if(adptArray->array[index] != NULL)
        return adptArray->copy(adptArray->array[index]);
    return NULL;
}

int GetAdptArraySize(PAdptArray adptArray){
    if(adptArray == NULL)
        return -1;
    return adptArray->size;
}

void PrintDB(PAdptArray adptArray){
    if(adptArray !=NULL){
        for (size_t i = 0; i < adptArray->size ; i++)
        {
            if(adptArray->array[i] != NULL)
                adptArray->print(adptArray->array[i]);
        }
    }
    
}




