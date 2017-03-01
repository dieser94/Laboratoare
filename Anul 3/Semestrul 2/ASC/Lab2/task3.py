# Implementati problema producator-consumator folosind semafoare.
# Mai multi producatori si mai multi consumatori comunica printr-un buffer partajat,limitat la un numar fix de valori.
# Un producator pune cate o valoare in buffer iar un consumator poate sa ia cate o valoare din buffer.
# Aveti nevoie de doua semafoare, unul pentru a indica daca se mai pot pune valori in buffer si celalalt pentru
# a arata daca exista vreo valoare care poate fi luata din buffer de catre consumatori

from threading import Thread, Semaphore
from random import randint
import time


def producator(semafor1, semafor2):
    global buff
    while 1:
        tmp = randint(0, 5)
        semafor1.acquire()
        buff.append(tmp)
        semafor2.release()

        print "created " + str(tmp) + "\n"
        time.sleep(1)


def consumator(semafor1, semafor2):
    global buff
    while 1:
        semafor2.acquire()
        tmp = buff.pop()
        semafor1.release()
        print "consumed " + str(tmp) + " from buff \n "
        time.sleep(1)


buff = []
lista_threads = []
semafor_producator = Semaphore(value=2)
semafor_consumator = Semaphore(value=0)

for i in range(2):
    t = Thread(target=producator, args=(semafor_producator, semafor_consumator))
    t.start()
    lista_threads.append(t)

for x in range(2):
    t = Thread(target=consumator, args=(semafor_producator, semafor_consumator))
    t.start()
    lista_threads.append(t)

for t in lista_threads:
    t.join()
