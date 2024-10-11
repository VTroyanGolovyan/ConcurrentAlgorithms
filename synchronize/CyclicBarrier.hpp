#ifndef SYNC_CYCLIC_BARRIER_HPP
#define SYNC_CYCLIC_BARRIER_HPP
#include <array>

namespace synchronize {
    
class CyclicBarrier {
public:
    void Arrive() {
        
    }
private:
    std::array<uint32_t, 2> wawe_counters_; 
};

}
#endif
