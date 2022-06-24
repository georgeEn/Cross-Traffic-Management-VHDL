#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Arduino_FreeRTOS.h>

void setup() {
  char dir[1]; //direction  
  char tab[8][2] = {"WS", "SE", "EN", "NW", "WS", "SE", "EN", "NW"}; // Repeat states to be able to have a complete loop
  xTaskCreate(Queue, "Queue", 128, NULL, 1, NULL); //
  xTaskCreate(Movement, "Movement", 128, NULL, 2, NULL); //The task with the higher priority
}

void loop() {
  
}

void Movement(void *pvParameters)
{
  while(1){
    printf("Enter the direction (Ex: Enter NE if you come from North and going to East)");
    scanf("%s", dir);
    if (scanf(" %c", &dir) != 1)
    {
      printf("%s\n", "You didnt enter a valid value");
      return -1;
    }
  }
}


void Queue(void *pvParameters)
{
  while(1)
  {
    for (int i = 0; i <8 ; ++i) {
      if (dir[0] == tab[i][0]){       //check if the first bit of the direction and the first bit of the slot are the same 
        for (int j = i; j <8 ; ++j) {
        do{                           // Check the next slot and replace it with an 'x' if free, and then move and restore the old value of the slot
            char c;
            strcpy(c,tab[j]);   //Put the value of the slot in c
            strcpy(tab[j], "x"); //replace the slot value by x
            strcpy(tab[j],c); //restore the slot value 
          }while (dir[1] == tab[0][j]); //Exit when the last bit of the direction is the same as the last bit of the slot
        }
      }
    }
  }
}





    
