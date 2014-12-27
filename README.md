Ein Graph und das Traveling Salesman-Problem
============================================

Das war die Übung 1 aus dem Praktikum von Algorithmen und Datenstrukturen II an der
[Fakultät 07](http://cs.hm.edu), [Hochschule München](http://hm.edu).

Aufgabe war, mit dem Algorithmus von Prim eine Lösung für das Traveling Salesman-Problem zu finden.
In einer anderen Vorlesung (Statistical Learning) wurde uns ein paar Wochen später von einem anderen
Ansatz, dem Simulated Annealing, erzählt. Das klang interessant, also haben wir das noch eingebaut.

Angewendet auf einen Testdatensatz mit Städten von <https://github.com/toddwschneider/shiny-salesman>
ergab, dass Simulated Annealing hier bessere Ergebnisse liefert als der Algorithmus von Prim:

```bash
$ # Using Simulated Annealing
$ algraph -a test/cities.txt | awk 'BEGIN{RS=" "};{sum+=$0};END{print sum}'
48585
$ 
$ # Using Prim's Algorithm
$ algraph -p test/cities.txt | awk 'BEGIN{RS=" "};{sum+=$0};END{print sum}'
51148
```

Allerdings musste man etwas mit den Parametern herumspielen...
