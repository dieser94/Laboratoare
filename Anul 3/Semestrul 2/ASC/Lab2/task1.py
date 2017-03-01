#a) Folosind clasa Thread, creati 10 threaduri care afiseaza un mesaj de forma:
#    Hello, I'm thread id_thread
from threading import Thread, current_thread

def thread_function(id_thread):
    print "Hello, I'm thread " + str(id_thread)

def task_a():
    print "Task a"

    lista_thread = []
    for i in range(10):
        t = Thread(target = thread_function, args = (i,))
        t.start()
        lista_thread.append(t)

    for t in lista_thread:
        t.join()

task_a()


#b) Modificati codul anterior astfel incat thread-urile sa primeasca un 
#   index si un mesaj date ca parametru sub forma de dictionar
#   *hint: exemplu in lab1 http://cs.curs.pub.ro/wiki/asc/asc:lab1:index#functii

def thread_function_dic(**dic):
    id_thread = current_thread().name.split('-')[1]
    print "Thread " + id_thread + " says " + dic[id_thread]

def task_b():
    print "Task b"

    dic = {}
    lista_thread = []

    for i in range(1,11):
        dic[str(i)] = "Hello, from " + str(i)

    for i in range(10):
        t = Thread(target = thread_function_dic, kwargs = (dic))
        t.start()
        lista_thread.append(t)

    for t in lista_thread:
        t.join()

#task_b()

#c) Modificati codul anterior astfel incat thread-urile sa afiseze si numele
#   thread-ului (campul 'name' din clasa Thread)

def thread_function_dic_c(**dic):
    id_thread = current_thread().name.split('-')[1]
    name = current_thread().name
    print "Thread " + id_thread + " called " + name + " says " + dic[id_thread]

def task_c():
    print "Task c"

    dic = {}
    lista_thread = []

    for i in range(1,11):
        dic[str(i)] = "Hello, from " + str(i)

    for i in range(10):
        t = Thread(target = thread_function_dic_c, kwargs = (dic))
        t.start()
        lista_thread.append(t)

    for t in lista_thread:
        t.join()

#task_c()

#d) Modificati codul anterior astfel incat thread-urile sa primeasca index-ul
#   drept nume al thread-ului, afisati-l ca la punctul b)
#   * hint: folositi campul 'name' al constructorului clasei Thread

def thread_function_dic_d(**dic):
    id_thread = current_thread().name
    print "Thread " + id_thread + " says " + dic[id_thread]

def task_d():
    print "Task d"

    dic = {}
    lista_thread = []

    for i in range(1,11):
        dic[str(i)] = "Hello, from " + str(i)

    for i in range(1,11):
        t = Thread(target = thread_function_dic_d, name = str(i), kwargs = (dic))
        t.start()
        lista_thread.append(t)

    for t in lista_thread:
        t.join()

#task_d()
