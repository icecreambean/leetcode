// M: https://leetcode.com/problems/container-with-most-water/     // wtf big brain
// H: https://leetcode.com/problems/trapping-rain-water/

public class Q11 {
    public static int maxArea(int[] height) {
        // 2 cursors, increment the shorter one
        // only need to keep track of max area
        // start off by max distance, then iterate to max height as well
        int maxVal = 0, left = 0, right = height.length-1;
        while (left < right) {
            //System.out.printf("%d,%d,%d%n", left, right, Math.min(height[left], height[right]) * (right - left));
            maxVal = Math.max(maxVal, Math.min(height[left], height[right]) * (right - left));
            if (height[left] <= height[right]) left++;
            else right--;
        }
        return maxVal;
    }

    public static void main(String[] args) {
        int[] height = {1,8,6,2,5,4,8,3,7};
        //int[] height = {1,2,4,3};
        System.out.println(Q11.maxArea(height));
    }
}



// [really need to pen-and-paper stuff]

// // right is always ascending in size (left: prev right)
// // unless left gives a better deal (due to distance)
// // ...
// // equality of old and new area can't happen:
// // if newArea (width 1) == maxVal, then it must be the case
// // that accArea > maxVal
// int left = 0; int right = 1;
// int maxVal = Math.min(height[right], height[left]);
// for (int i = 2; i < height.length; i++) {
//     int newArea = Math.min(height[i], height[right]);
//     int accArea = Math.min(height[i], height[left]) * (i-left);
//     if (newArea > maxVal) {
//         maxVal = newArea;
//         left = right; 
//         right = i;
//     } else if (accArea > maxVal) {
//         maxVal = accArea;
//         right = i;
//     }
// }