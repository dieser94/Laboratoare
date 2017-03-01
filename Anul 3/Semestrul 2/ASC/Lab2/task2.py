#
# Scrieti un program in care mai multe threaduri (numarul lor este dat ca
# argument in linia de comanda) aleg random un element dintr-o lista comuna si
# le adauga intr-o lista rezultat (tot comuna).
# a) in fiecare thread, afisati numele threadului si varianta din acel moment 
#    a listei rezultat
# b) in fiecare thread adunati elementul la o variabila globala. Protejati 
#    accesul la aceasta printr-un lock
# c) faceti thread-urile sa astepte un numar random de secunde pana sa inceapa
#    executia. Hint: modulul time
# !!! Verificati ca suma calculata in vareiabila globala este egala cu suma 
#    elementelor din lista rezultat. Rulati cu 1000 de threaduri.   
#


from threading import Thread, Lock, current_thread
from random import randint
import sys
import time


def fun_threads(lista_i, lista_f, lockx):
    global var_glob
    nume = current_thread().name
    time.sleep(randint(0, 5))
    tmp = lista_i[randint(0, len(lista_i)-1)]
    lista_f.append(tmp)
    print nume + " " + str(lista_f) + '\n'
    lockx.acquire()
    var_glob += tmp
    lockx.release()


lock = Lock()
lista_initiala = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
lista_finala = []
var_glob = 0
lista_threads = []
numar_thread = sys.argv[1]

for i in range(int(numar_thread)):
    t = Thread(target=fun_threads, args=(lista_initiala, lista_finala, lock))
    t.start()
    lista_threads.append(t)

for t in lista_threads:
    t.join()

print lista_finala
print "variabila globala = " + str(var_glob)
print "suma elemente = " + str(sum(lista_finala, 0))
