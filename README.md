# ConcurrentAlgorithms

### Implemented structures:
* [Treiber Stack](https://books.google.ru/books/about/Systems_Programming_Coping_with_Parallel.html)
* [MSQueue](https://www.cs.rochester.edu/~scott/papers/1996_PODC_queues.pdf?)
* [Flat combining stack]() // TODO
  
### SMR schema(safe memory reclamation):
* [Hazard pointers](http://erdani.org/publications/cuj-2004-12.pdf)

Project contains some popular synchronization primitives implementation:
### Synchronization:
* [Mutex](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/Mutex.hpp)
* [Condition Variable](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/ConditionVariable.hpp)
* [Shared Mutex](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/SharedMutex.hpp)
* [Latch](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/Latch.hpp)
* [Cyclic Barierr](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/CyclicBarrier.hpp)
* [Semaphore](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/Semaphore.hpp)
* [Wait Group]
* [Feature/Promise]

### Other:
* ThreadPool

Third-party:
* https://github.com/google/googletest (Testing)
