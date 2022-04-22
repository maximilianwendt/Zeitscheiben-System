//Maximilian Wendt programmierte:
//Diese C Datei sollte mit programmentwurf.c/Worstcase.c/BestCase.c und list.c kompilliert werden!
#include<stdio.h> //Für Eingabe/Ausgabe
#include<stdlib.h> //Um rand Methode nutzen zu können

//Eine Uhr zum testen und vorführen;
int seconds=0;
int minutes=0;
int hours=0;
long days=0;


//Ein Short Array zum Togglen
short data[3] = {0,0,0};

void print(){
    for(int i=0; i<sizeof(data)/sizeof(short); i++) printf("%d", data[i]);
    printf("\n");
    
}

void nop(){
    //#AssemblerLoveIsReal
}

void toggle0(){
    if(data[0] == 0) data[0] = 1;
    else data[0] = 0;
}

void toggle1(){
    if(data[1] == 0) data[1] = 1;
    else data[1] = 0;
}

void toggle2(){
    if(data[2] == 0) data[2] = 1;
    else data[2] = 0;
}


void T5(){ printf("5s long task was executed\n");}
void T10(){ printf("10s long task was executed\n");}
void T100(){ printf("100s long task was executed\n");}

void sortArray(){
    int cache = 0; 
    int array[100];

    for(int i=0; i<sizeof(array)/sizeof(int);i++){
        array[i]=(int)(rand()%1000+1);
    }

    for(int i=0;i< sizeof(array)/sizeof(int)-1;i++){ //-1 da der Rechte Knoten schon hinten angekommen ist, wenn man beim vorletzten "Index" ist
        for(int j=0;j< sizeof(array)/sizeof(int)-i-1;j++){ //-i da die Anzahl von i hinten am Array schon sortiert ist
            if((array[j]) > (array[j+1])){//Wenn getauscht werden muss
                //Tausche nur die WERTE der Knoten und NICHT die Knoten an sich, da snst auch die nachfolgenden Elemente umgespeichert werden müssen... 
                cache = array[j+1]; //Wert des rechten Knotens wird zwischengespeichert, da er danach mit dem Wert des linken Knoten überschrieben wird
                array[j+1] = array[j];
                array[j] = cache;
            }
        }
    }

    //Ausgabe
    printf("Sorted:\n");
    for(int i=0; i<sizeof(array)/sizeof(int);i++){
        printf("%d, ", array[i]);
    }
    printf("\n");
}

void calcMatrix(){
    int tab1[5][5]; //Operand1Matrix
    int tab2[5][5]; //Operand2Matrix
    int tab3[5][5]; //ErgebnisMatrix

    
    //Befülle Matrizen mit random Werten
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            tab1[i][j]=(int)(rand()%100+1); 
            tab2[i][j]=(int)(rand()%100+1); 
            tab3[i][j]=0;
        }
    }

    //Multipliziere Matrizen
   for (int i= 0;i < 5; i++){
    for (int j= 0;j < 5; j++){
        //Muster für Matrix Multiplikation
        tab3[i][j] = tab1[i][0]*tab2[0][j] + tab1[i][1]*tab2[1][j] + tab1[i][2]*tab2[2][j] + tab1[i][3]*tab2[3][j] + tab1[i][4]*tab2[4][j];
    }
   }

   //Ausgeben Ergebnismatrix
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(tab3[i][j]<10) printf("%d    ", tab3[i][j]); //Wenn eine einstellige Zahl setze 4 Leerzeichen hinter jeweiligen Wert
            else if(tab3[i][j]<100) printf("%d   ", tab3[i][j]); //Wenn eine zweistellige Zahl setze 3 Leerzeichen hinter jeweiligen Wert
            else printf("%d  ", tab3[i][j]); //Ansonsten setze 2 Leerzeichen hinter jeweiligen Wert
        }
        printf("\n"); // Leerzeichen für nächste Zeile
    }
    printf("\n");
}


void countStopwatch(){
    //Ausgaben:
    //Tage
    printf("      %ld-", days);

    //Stunden
    if(hours<10) printf("0%d:", hours);
    else printf("%d:", hours);

    //Minuten
    if(minutes<10) printf("0%d:", minutes);
    else printf("%d:", minutes);

    //Sekunden
    if(seconds<10) printf("0%d\n", seconds);
    else printf("%d\n", seconds);

    if(seconds>=59){
        seconds=0; 
        if(minutes>=59){
            minutes=0;
            if(hours>=23){
                hours=0;
                days++;
            }else hours++;
        }else minutes++;
    }else seconds++;

}