//Maximilian Wendt programmierte:
//Diese C Datei sollte mit programmentwurf.c/Worstcase.c/BestCase.c und functions.c kompilliert werden!
#include<stdio.h> //Für Eingabe/Ausgabe
#include<stdlib.h> //Um Speicher allokieren und exit() benutzen zu können 

struct subfunction{
        long cyclelength;
        void (*functionname)();
        struct subfunction *followingSubfunction;
    };

extern short numberOfTasks;
extern short functionAdded;



struct subfunction *newList(long len){
    struct subfunction *list = (struct subfunction*) malloc(sizeof(struct subfunction)); //Es wird Speicher für den Kopf der Liste, also für den Beginn einer neuen LinkedList reserviert
    if(list == NULL){
        printf("No RAM accesable. Please close some programms.\n");
        exit(1);
    }

    if(len < 1){
        printf("Cyclelength has to be at least one second!\n");
        exit(1);
    }
  
    list -> cyclelength = len; //Zyklusdauer wird eingespeichert
    list -> functionname = NULL; //Der Kopf Knoten keine eingespeicherte Funktion
    list -> followingSubfunction = list; //Da der Kopf erstmal das letzte Element seiner Liste ist, zeigt er auf sich selbst
    
    numberOfTasks++; //Checkvariable hochzählen

    return list; //Erstellter erster Knoten wird zurueckgegeben, die Liste ist damit offiziell erstellt
}

void addSubfunction (struct subfunction* list, void (*function)()){ //Funktionspointer wird am Ende der Liste in einem neuen Knoten gespeichert
    struct subfunction *newSubfunction = (struct subfunction*) malloc(sizeof(struct subfunction) - sizeof(long)); //Es werden fuer die nicht Kopfelemente nur 16 Byte anstatt der 24Byte reserviert da die nicht Kopfelemente keine Attribut Zykluslaenge besitzt
	struct subfunction *currentSubfunction = list;

    if(newSubfunction == NULL){
        printf("No RAM accesable. Please close some programms\n");
        exit(1);
    }
    if(currentSubfunction == NULL){
        printf("The functionlist you want to enlarge is corrupt! Please initialise the Task correctly.\n ");
        exit(1);
    }


    newSubfunction -> functionname = function; //Funktionspointer wird in neuem Knoten gespeichert
    newSubfunction -> followingSubfunction = newSubfunction; //der neue Knoten wird zu einem Schwanzknoten gemacht, da er ganz hinten in die Liste kommt

    while(currentSubfunction -> followingSubfunction != currentSubfunction){ //solange der aktuelle Knoten noch nicht der letzte knoten in der Liste ist...
        currentSubfunction = currentSubfunction-> followingSubfunction; //...ist der aktuelle Knoten der Knoten, der nach dem aktuellen Knoten kommt
    }
    
    currentSubfunction -> followingSubfunction = newSubfunction; //neuerKnoten, also eine neue Funktion, wird hinten in der Liste eingefuegt

    functionAdded = 1;
}   
