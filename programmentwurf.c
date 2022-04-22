//Maximilian Wendt programmierte:
//Diese C Datei muss mit list.c und functions.c kompilliert werden!
#include<stdio.h> //Für Eingabe/Ausgabe
#include <time.h> //Um Zeitsteuerung mit clock_t benutzen zu können

//Ausgelagerte Funktionen
extern void print();
extern void toggle0();
extern void toggle1();
extern void toggle2();
extern void sortArray();
extern void calcMatrix();
extern void countStopwatch();
extern void nop();
extern void T5();
extern void T10();
extern void T100();
extern struct subfunction *newList();
extern void addSubfunction();

struct subfunction{
    int cyclelength;
    void (*functionname)(); //Hier wird ein Funktionspointer auf eine Funktion gespeichert, die keine Mitgabeparameter hat
    struct subfunction *followingSubfunction;
};

enum {false, true}; //Für bessere Lesbarkeit
int numberOfTasks = 0;
short functionAdded = false;


void executeTask(struct subfunction *currentSubfunction){
    do{ 
        currentSubfunction = currentSubfunction -> followingSubfunction; //Setze momentane Funktion auf die naechste Funktion in der Liste
        if(currentSubfunction->functionname != NULL) currentSubfunction->functionname(); //Wenn Pointer wirklich auf eine Funktion zeigt, führe sie aus
    }
    while(currentSubfunction -> followingSubfunction !=  currentSubfunction); //Wenn die momentane Funktion nicht die letzte der Liste ist, wiederhole die Schleife 
}

void run(struct subfunction *array[numberOfTasks]){
    clock_t time;
    clock_t endOfSleep;
    int counter = -1; //Countervariable, welche jede Sekunde erhoeht wird, bei 16Bit(minimale groesse die C garantiert) von -32768 bis 32767
    int lastNumber = 0;

    //Zahl bestimmen, wann counter 0 gesetzt werden kann um Ueberlauf zu verhindern
    for(int i=32760;i>=30000; i--){
        for(int j=0;j<numberOfTasks; j++){
            if(i % array[j]->cyclelength != 0){ // Wenn i nicht durch eine Zykluslaenge restlosteilbar ist..
                lastNumber = 1;  //wird lastNumber 1 gesetzt
            }
        }
        if(lastNumber == 0){ //Es wurde eine Zahl gefunden, welche durch alle Zyklenlaengen restlos teilbar ist
            lastNumber = i;
            break;
        } else lastNumber = 0;
    }

    if(lastNumber == 0) { //Wenn es keine Zahl gefunden werden sollte, wird ab 30000 reseted (Während Tests nie vorgekommen)
        lastNumber = 30000; 
        printf("Warning: The cycle might be unstable.\n");
    } 

    
    for(;;){ //Endlosschleife
    
        time = clock();

        //Um vor einem Ueberlauf bei 16 Bit Systemen zu schuetzen
        if(counter >= lastNumber) counter = 0;
        else counter++;

        //Tasks im Array werden ausgefuehrt, wenn die momentane Sekundenanzahl seit Start der Endlosschleife restlos durch die Zykluslaenge des Tasks teilbar ist
        for(int i = 0; i < numberOfTasks; i++){
            if(counter % array[i] -> cyclelength == 0) executeTask(array[i]);
        }
        
        //Wenn kein clock überlauf:  Wartezeit = Wieviele Clocks braucht es noch bis eine Sekunde vorbei ist: clock() +( 1Sekunde in uS - Zeit in uSekunden, die Prozess bis hier brauchte)
        if(clock() >= time) endOfSleep = clock() + (CLOCKS_PER_SEC - (clock() - time));
        //Wenn clock überlauf: Wartezeit = Eine Sekunde, weil nicht mehr genau prüfbar wieviel Zeit vergangen ist
        else endOfSleep = clock() + CLOCKS_PER_SEC;
        
        // Solange Wartezeit noch nicht vorbei ist, tue nichts 
        while (clock() < endOfSleep);

    }
}


void main(){
    //In diesen Funktionslisten(Tasks) werden später Pointer auf Methoden gespeichert
    //Jede Funktionsliste kann eine unterschiedliche Zykluszeit haben, diese wird bei der Intialisierung in der Klammer in Sekunden angegeben
    //Bei dem Methodenaufruf newList(Zykluslaenge in Sekunden KEINE KOMMAZAHL) wird ein KopfKnoten in der jeweiligen Funktionsliste gespeichert und die eigentliche List somit erstellt
    struct subfunction *task1s = newList(1);
    struct subfunction *task5s = newList(5);
    struct subfunction *task10s = newList(10);
    struct subfunction *task100s = newList(100);
    //Zum Hinzufuegen:
    //struct subfunction *name = newList(ZyklusdauerInSekundenAlsInteger);
    

    //Hier einstellen welche Funktionen die jewilige Funktionsliste(Task) beinhalten soll:
    //Die Reihenfolge der Abarbeitung der Funktionen des jewiligen Tasks ist die Reihenfolge der Einspeicherung
    //Zum Hinzufuegen einer Funktion zum Task: addSubfunction(Task in der die Methode hinzugefuegt werden soll ,Funktionsname);
    addSubfunction(task1s, countStopwatch);
    addSubfunction(task5s, T5);
    addSubfunction(task10s, T10);
    addSubfunction(task100s, T100);
    //Zum Hinzufuegen:
    //addSubfunction(ebenErstellterTask, NameDerFunktionDieZumTaskHinzugefuegtWerdenSoll);



    //Zur einfachen Handhabung wird ein Array mit allen Tasks erstellt
    struct subfunction *array[numberOfTasks];

    for(int i=0; i< numberOfTasks; i++) array[i] = NULL; //Setze alle Felder für Testcase auf NULL

    //Es darf kein Arrayfeld leer gelassen werden! Reihenfolge der Einspeicherung ist Reihenfolge der Ausführung im Falle von mehreren Tasks pro Sekunde
    array[0]=task1s;
    array[1]=task5s;
    array[2]=task10s;
    array[3]=task100s;
    //Zum Hinzufuegen:
    //array[vorherigezahl+1]=ebenErstellterTask;



    //Testcases
    if(functionAdded == true){ //Wenn mindestens eine Funktion zu irgendeinem Task hinzugefuegt wurde
        
        if(numberOfTasks >= 0){ //Wenn mindestens ein Task erstellt wurde

            //Prüfe ob alle Arrayfelder gefüllt sind
            short arrayCompletelyFull = true;

            for(int i=0; i < numberOfTasks; i++ ){
                if(array[i] == NULL) arrayCompletelyFull = false; //Wenn ein Feld im Array noch NULL ist, ist das Array nicht komplett voll
            }
                
            if(arrayCompletelyFull == true){
                run(array);
            }else printf("You have to initialise all array fields!\n");
                
        }else printf("There have to be more than 0 Tasks in 'array'! Add at least one task\n");
        
    }else printf("You have to add at least one function to one of your tasks\n");

}
