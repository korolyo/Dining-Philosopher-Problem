# Dining-Philosopher-Problem!

The basics of threading a process. How to make threads. Discovering the mutex. In C..

![philos](https://user-images.githubusercontent.com/64440240/141085758-945121d2-f082-4640-a971-1168ebf3c0e0.png)


Решение задачи об обедающих философах на  языке C(Си). Сама проблема:
https://en.wikipedia.org/wiki/Dining_philosophers_problem


Ограничения проекта:

* Допустимые функции: memset, printf, malloc, free, write,
                      usleep, gettimeofday, pthread_create,
                      pthread_detach, pthread_join, pthread_mutex_init,
                      pthread_mutex_destroy, pthread_mutex_lock,
                      pthread_mutex_unlock

* Задание проекта: 
                      • There are some forks on the table.
                      • As spaghetti is difficult to serve and eat with a single fork, it is assumed that a
                        philosopher must eat with two forks, one for each hand.
                      • The philosophers must never be starving.
                      • Every philosopher needs to eat.
                      • Philosophers don’t speak with each other.
                      • Philosophers don’t know when another philosopher is about to die.
                      • Each time a philosopher has finished eating, he will drop his forks and start sleeping.
                      • When a philosopher is done sleeping, he will start thinking.
                      • The simulation stops when a philosopher dies.
                      • The status printed should not be scrambled or intertwined with another philosopher’s status.
                      • You can’t have more than 10 ms between the death of a philosopher and when it
                        will print its death.
                      • Again, philosophers should avoid dying!
