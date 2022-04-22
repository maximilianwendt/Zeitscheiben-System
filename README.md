# Zeitscheiben-System
Algorithmus zur zeitlichen Steuerung mehrerer Tasks bspw. auf einem Singlecore Mikrocontroller ohne Nebenläufigkeiten.

Anforderungen:
  1. Das Programm soll so lange ausgeführt werden bis der Prozess durch Eingriff von außen
  terminiert wird (schließen des Prozesses).
  2. Das Programm soll mindestens folgende zyklischen Tasks unterstützen:
  a. Ausführung eines Tasks im 1 Sekunden Zyklus
  b. Ausführung eines Tasks im 5 Sekunden Zyklus
  c. Ausführung eines Tasks im 10 Sekunden Zyklus
  d. Ausführung eines Tasks im 100 Sekunden Zyklus
  Hinweis: Ein zyklischer Task ist definiert als eine Funktion welche alle n-Sekunden aufgerufen
  wird. In dieser Funktion werden dann wiederum weitere Funktionen umgesetzt.
  3. Das Programm soll so umgesetzt werden das die Tasks mit möglichst wenig Aufwand
  erweitert oder in anderen Zykluszeiten umgesetzt werden können.
  4. Für jeden Task soll konfigurierbar sein welche Funktionen und in welcher Reihenfolge bei
  jedem Zyklus ausgeführt werden.
  5. Das Programm ist so zu implementieren, dass sich Funktionen selbst für die Ausführung in
  einem Task registrieren können.
  6. Das Programm soll so umgesetzt werden das der Jitter, also die zeitliche Abweichung der
  Task-Aufrufe, möglichst klein gehalten wird.
  7. Tasks dürfen ausgelassen werden, wird also zum Beispiel die 1 Sekunden Task nach 2
  Sekunden ausgeführt, wird sie trotzdem nur 1 Mal ausgeführt.
