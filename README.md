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
* [Wait Group](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/wait_group/WaitGroup.hpp)
* [Feature/Promise](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/future/)

### Other:
* [ThreadPool](https://github.com/VTroyanGolovyan/ConcurrentAlgorithmsAndDS/blob/main/synchronize/scheduler/)

### Documentation
You can use doxygen to get docs.
```
doxygen Doxyfile
```

### Third-party:
* [GoogleTest](https://github.com/google/googletest) (used for Testing)
