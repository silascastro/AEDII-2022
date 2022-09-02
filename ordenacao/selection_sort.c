#include <stdio.h>
#define TAM 5

int findMin(int *vector, int firstIndex) {
  int lowestElement = firstIndex;
  for (int index = firstIndex + 1; index < TAM; index++) {
    if (vector[index] < vector[lowestElement]) {
      lowestElement = index;
    }
  }

  return lowestElement;
}

void selection_sort(int *vector) {
  for (int index = 0; index < TAM ; index++) {
    int lowestElement = findMin(vector, index);
    int temp = vector[index];
    vector[index] = vector[lowestElement];
    vector[lowestElement] = temp;
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
    selection_sort(vector);
    display_vector(vector);
    return 0;
}
