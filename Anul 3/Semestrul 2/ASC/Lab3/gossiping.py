"""
Implementati o propagare ciclica de tip gossiping folosind bariere. 
  * Se considera N noduri (obiecte de tip Thread), cu indecsi 0...N-1.
  * Fiecare nod tine o valoare generata random.
  * Calculati valoarea minima folosind urmatorul procedeu:
     * nodurile ruleaza in cicluri
     * intr-un ciclu, fiecare nod comunica cu un subset de alte noduri pentru a
       obtine valoarea acestora si a o compara cu a sa
       * ca subset considerati random 3 noduri din lista de noduri primita in
        constructor si obtineti valoarea acestora (metoda get_value)
     * dupa terminarea unui ciclu, fiecare nod va avea ca valoare minimul
       obtinut in ciclul anterior
     * la finalul iteratiei toate nodurile vor contine valoarea minima
  * Folositi una din barierele reentrante din modulul barrier.
  * Pentru a simplifica implementarea, e folosit un numar fix de cicluri,
    negarantand astfel convergenta tutoror nodurilor la acelasi minim.
    Dan Adrian was here ! ....
"""

import sys
import random
from threading import Thread
from barrier import ReusableBarrierCond


#random.seed(1) # genereaza tot timpul aceeasi secventa pseudo-random

class Node(Thread):
    #TODO Node trebuie sa fie Thread

    def __init__(self, node_id, other_nodes, num_iteratii, barrier):
        #TODO nodurile trebuie sa foloseasca un obiect bariera

        Thread.__init__(self)
        self.node_id = node_id
        self.other_nodes = other_nodes
        self.num_iter = num_iteratii
        self.value = random.randint(1, 1000)
        self.barrier = barrier
    def get_value(self):
        return self.value

    def run(self):
        for i in range(0, self.num_iter):
            values = []
            values.append(self.value)
            for z in range(0, 3):
                r = random.randint(0, len(self.other_nodes) - 1)

                #asiguram ca nu pica acelas id
                while r == self.node_id:
                    r = random.randint(0, len(self.other_nodes)-1)

                values.append(self.other_nodes[r].get_value())

            minim = min(values)

            self.barrier.wait()
            self.value = minim


if __name__ == "__main__":
    if len(sys.argv) == 2:
        num_threads = int(sys.argv[1])
    else:
        print "Usage: python " + sys.argv[0] + " num_nodes"
        sys.exit(0)
    
    num_iter = 10  # numar iteratii/cicluri algoritm
    num_threads = int(num_threads)
    barrier_cond = ReusableBarrierCond(num_threads)
    #TODO Create nodes and start them
    list_threads = []
    for i in range(1, num_threads + 1):
        n = Node(i, [], num_iter, barrier_cond)
        # trimitem lista goala la other deoarece lista de nodurile nu este complet formata
        list_threads.append(n)

    for i in range(1, num_threads + 1):
        list_temp = [x for x in list_threads if x.node_id != i]
        list_threads[i-1].other_nodes = list_temp
        # actualizam lista de thread-uri

    for n in list_threads:
        n.start()

    #TODO Wait for nodes to finish

    for n in list_threads:
        n.join()

    for n in list_threads:
        print str(n.node_id) + ' = ' + str(n.value)
