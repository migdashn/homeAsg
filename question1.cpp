//Question 1 - basic STL

//Task 1: improve fill_vector and vecOfVec.push_back performance - execution time can be reduced significantly, please explain the changes you made and how they improve
// the application performance.

//Task 2: Implement count_total_elements without using a "visible" for loop

//Task 3: Implement merge_vec_of_vec 

// Make sure you compile the code in "Release" configuration (e.g O2 optimization level).
// Do not modify ELEMENT_COUNT and ITERATIONS and functions fill_vector,count_total_elements and merge_vec_of_vec function signatures  

#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>

constexpr size_t ELEMENT_COUNT = 1000 * 10000;
constexpr size_t ITERATIONS = 10;

std::vector<uint64_t> fill_vector(size_t elementCount) {
//TODO: improve function performance
    std::vector<uint64_t> vec(elementCount);
    iota (vec.begin(), vec.end(), 0);

return vec;
}

/// This function should return the total elements in all of the vectors
size_t count_total_elements(const std::vector<std::vector<uint64_t>>& vecOfVec) {
    size_t sum = 0, i = 0;
label:
    sum = sum +  vecOfVec[i++].size();
    if (i < vecOfVec.size() ){
        goto label;
    }
    return sum;


}

/// This function should return a single vector that contain all of the elements of the vectors in vecOfVec
std::vector<uint64_t> merge_vec_of_vec(std::vector<std::vector<uint64_t>>& vecOfVec) {
    std::vector<uint64_t> mergedVec;
    for (std::vector<uint64_t> vec : vecOfVec){
        mergedVec.insert(mergedVec.end(),vec.begin(),vec.end());
    }
    return mergedVec;
}

int main(int argc, char** argv)
{
    //Create vector of vectors
    std::vector<std::vector<uint64_t>> vecOfVec;    //init vector of vectors
    auto start = std::chrono::steady_clock::now();  //start clock
    for (size_t i = 0; i < ITERATIONS; i++) {
        std::vector<uint64_t> vec = fill_vector(ELEMENT_COUNT);  //fill 10 vectors in increasing order
        //TODO: improve inserting performance
        vecOfVec.push_back(vec);
    }
    auto end = std::chrono::steady_clock::now();   //end clock
    //calculate avg time for filling
    size_t averageIterationTimeUs = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / ITERATIONS;
    std::cout << "Average iteration duration in microseconds: " << averageIterationTimeUs << std::endl;

    //Count elements
    size_t totalElements = count_total_elements(vecOfVec);
    std::cout << "Total elements in vecOfVec: " << totalElements <<  " " << std::endl;

    //Merge vector of vectors
    std::vector<uint64_t> mergedVec = merge_vec_of_vec(vecOfVec);
    std::cout << "Total elements in merged mergedVec: " << mergedVec.size() << std::endl;

    std::cout << "Press enter to exit" << std::endl;
    getchar();
    return 0;
}
