class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x;
        int left = 0;
        int right = x;
        int middle;
        while (left < right)
        {
            middle = (right + left) / 2;
            if (x / middle < middle)
            {
                right = middle;
            }
            else if (x / middle > middle)
            {
                if (x / (middle + 1) < (middle + 1))
                {
                    return middle;
                }
                else
                {
                    left = middle + 1;
                }
            }
            else if (x / middle == middle)
            {
                return middle;
            }
        }
        return left;
    }
};
