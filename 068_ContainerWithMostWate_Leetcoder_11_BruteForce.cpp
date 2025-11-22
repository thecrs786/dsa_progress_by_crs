#include <iostream>
#include <vector>
#include <algorithm> // for std::min and std::max

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        int maxvolume = 0; // stores the maximum area found so far

        // Outer loop picks the first line
        for (size_t i = 0; i < height.size() - 1; i++) {
            // Inner loop picks the second line
            for (size_t j = i + 1; j < height.size(); j++) {
                // Height of the container is the shorter line
                int containerHeight = min(height[i], height[j]);

                // Width of the container is the distance between the lines
                int containerWidth = j - i;

                // Area (volume) of water = height × width
                int currentArea = containerHeight * containerWidth;

                // Update maximum area if current is greater
                maxvolume = max(maxvolume, currentArea);
            }
        }

        return maxvolume; // Return the maximum area found
    }
};

int main() {
    Solution sol;

    // Sample input
    vector<int> height = {1, 8, 6, 2, 5, 4, 8, 3, 7};

    // Expected output: 49
    int result = sol.maxArea(height);

    cout << "Maximum water that can be contained: " << result << endl;

    return 0;
}
