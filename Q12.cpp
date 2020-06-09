// https://leetcode.com/problems/integer-to-roman/
// * online solutions include hard-coding the 4 and 9 cases as well

#include <iostream>
#include <array>
#include <vector>
#include <map>

class Solution {
public:
    struct DescendingInt {
        bool operator() (const int& x, const int& y) const {return x>y;}
    };
    
    std::string intToRoman(int num) {
        static std::map<int, std::string, DescendingInt> valueMap {
            {1, "I"}, {5, "V"}, {10, "X"}, {50, "L"},
            {100, "C"}, {500, "D"}, {1000, "M"}
        };
        static std::array<int,7> valueKeys {1000,500,100,50,10,5,1}; // TODO: redundant?

        std::string result;
        int ki = 0;
        int magnitude = 1000;
        while (num > 0) {
            // extract from largest digit downwards: known range [1,3999]
            int curDigit = num/magnitude;
            if (curDigit == 0) {
                magnitude /= 10;
                continue; // TODO: use while loop instead?
            }
            // try next largest key each time
            if (valueKeys[ki] > num) {
                ki++;
                continue; // TODO: use while loop instead?
            }
            //std::cout << curDigit << " " << ki << "(" << valueKeys[ki] << ")\n";
            // delete and replace if special 4, 9 encountered
            if (curDigit == 4 || curDigit == 9) {
                int sep = 1;
                if (curDigit == 9) { // handle intermediate "5" cases in valueMap
                    ki++;
                    sep++;
                } 
                //std::cout << "SPECIAL '" << valueMap[valueKeys[ki]] << "', '" << valueMap[valueKeys[ki-sep]] << "'\n";
                result += valueMap[valueKeys[ki]] + valueMap[valueKeys[ki-sep]]; 
                num -= curDigit * magnitude;
            } else {
                result += valueMap[valueKeys[ki]];
                num -= valueKeys[ki];
            }
        }
        return result;
    }
};

int main(int argc, char *argv[]) {
    std::vector<int> tests {
        3, 4, 9, 58, 1994
    };
    Solution s;
    for (int elem: tests) {
        std::cout << elem << ": " << s.intToRoman(elem) << "\n";
    }
    
    return 0;
}