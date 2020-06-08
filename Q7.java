// https://leetcode.com/problems/reverse-integer/ (easy)
// https://stackoverflow.com/questions/2215318/difference-between-modulus-implementation-in-python-vs-java
// * one option is to use long int instead... kind of cheating

class Q7 {
    public int reverse(int x) {
        // assume 32-bit or find via O(n)
        int flowThreshold = (x >= 0) ? -Integer.MAX_VALUE : Integer.MIN_VALUE;
        int evalThreshold = (int)1e9; // could optimise with more prefilled digits
        int evalX = x;
        if (x > 0) evalX *= -1; // operate entirely in -ve region
        if (evalX < -evalThreshold) {
            while (evalThreshold != 0) { // guaranteed same number of digits
                int leadingFlowDigit = flowThreshold/evalThreshold;
                int trailingEvalDigit = evalX%10;
                //System.out.printf("%d > %d --> %b%n", evalX%10, leadingFlowDigit, evalX%10 > leadingFlowDigit);
                if (trailingEvalDigit > leadingFlowDigit) { // abs(trailing digit) is smaller
                    break;
                } else if (trailingEvalDigit < leadingFlowDigit) { // abs(trailing digit) is larger
                    return 0; // overflow
                }
                flowThreshold -= leadingFlowDigit * evalThreshold; // delete leading digit
                evalThreshold /= 10; // shift right (fix up)
                evalX /= 10;
            }
            // won't overflow: under/at flowThreshold
        }

        // reverse operation
        int result = 0;
        while (x != 0) {
            result = result * 10 + x%10; // either all add, or all subtract
            x /= 10;
        }
        return result;
    }

    public static void main(String[] args) {
        Q7 q7 = new Q7();
        System.out.printf("%d: %d%n", 123, q7.reverse(123));
        System.out.printf("%d: %d%n", -123, q7.reverse(-123));
        System.out.printf("%d: %d%n", -1234, q7.reverse(-1234));
        System.out.printf("%d: %d%n", 120, q7.reverse(120));
        System.out.printf("%d: %d%n", 1534236469, q7.reverse(1534236469));
        System.out.printf("%d: %d%n", -2147483412, q7.reverse(-2147483412));
        // supposed to do more edge cast testing, e.g. 0, various under/over-flow
    }
}