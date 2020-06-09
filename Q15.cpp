// https://leetcode.com/problems/3sum/
// * sorted list, 2 cursors - foreach i: 2 cursors on either end j,k (+/-/0)
// * map (val, count) - foreach i: foreach j not i: find required value HT

// the hint is in reducing from O(n^3) to O(n^2) - KISS and think time complexity!
// * use this question for C++ practice

// https://leetcode.com/problems/3sum/discuss/7438/C%2B%2B-two-pointes-solution-(easy-way-to-handle-duplicaiton).
// * 2 cursors is superior soln? less memory at the very least
//   guaranteed O(n^2) traversal across nums

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution { 
    // SLOW 1116ms total: .find() is slow, and I'm using a tree instead of HT
    // * replace map for unordered_map and extracted ordered keys some other way (see below)
    // * consumes even more memory than just using 2 pointers
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        // build HT
        // * maybe more efficient to sort list and count in sequence first,
        //   to reduce number of hash calls
        // * make sure to reserve memory in advance (not larger than nums)
        map<int,int> occurrences;
        for (int v1: nums) {
            auto it1 = occurrences.find(v1);
            if (it1 == occurrences.end()) {
                occurrences[v1] = 1;
            } else {
                it1->second++;
            }
        }
        for (auto p: occurrences) {
            std::cout << p.first << ": " << p.second << "\n";
        }

        // O(n^2) search for UNIQUE triplets
        for (auto e1: occurrences) {
            int v1 = e1.first;
            for (auto e2: occurrences) {
                int v2 = e2.first;
                int v3 = -(v1 + v2);
                // must ensure condition of v1 <= v2 <= v3
                if (!(v1 <= v2 && v2 <= v3)) continue;
                // check duplicate conditions met
                if (v1 == v3 && v1 == v2 && e1.second < 3) continue;
                else if (((v1 == v2 || v1 == v3) && e1.second < 2) ||
                         (v2 == v3 && e2.second < 2)) continue;
                // check unique conditions met, in cases (v1 == v2), or all unique
                auto it3 = occurrences.find(v3);
                if (it3 == occurrences.end()) continue;
                result.push_back(vector<int>{v1,v2,v3});
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    vector<vector<int>> tests = {
        {-1, 0, 1, 2, -1, -4}
    };

    Solution s;
    for (auto l: tests) {
        vector<vector<int>> result = s.threeSum(l);
        std::cout << "{";
        for (auto v: result) {
            std::cout << "{";
            for (auto i: v) {
                std::cout << i << ",";
            }
            std::cout << "\b}, ";
        }
        std::cout << "\b\b}\n\n";
    }

    return 0;
}