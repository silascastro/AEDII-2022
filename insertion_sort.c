#include <stdio.h>
#define TAM 5

void insertion_sort(int *vector){
    int currentIndex = 1;
     
    for(currentIndex; currentIndex<TAM; currentIndex++){
        int previousIndex = currentIndex - 1;
        int newCurrentIndex = currentIndex;
        
        while(previousIndex >= 0){
            if(vector[newCurrentIndex] < vector[previousIndex]){
                int temp = vector[newCurrentIndex];
                vector[newCurrentIndex] = vector[previousIndex];
                vector[previousIndex] = temp;
            }
            
            newCurrentIndex--;
            previousIndex--;
        }
    }

    
}

void display_vector(int *vector){
     for(int index = 0; index<TAM; index++){
         printf("%d\n", vector[index]);
     }
}

int main()
{
    int vector[TAM] = {24,15,3,4,5};
    insertion_sort(vector);
    display_vector(vector);
    return 0;
}

