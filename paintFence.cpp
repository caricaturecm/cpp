//276. Paint Fence
/*
 * actually math, 
 * curSame means to paint the current post the same color with previous one, so the previous one should has different
 * color with its previous post, current post has 1 choice, so preDiff * 1
 *
 * curDiff means paint current post different color with previous post, so the previous post can has the same or
 * different colors with its previous post, and current post can has (k - 1) choices, so (preSame + preDiff) * (k - 1)
 *
 * the total choices equals to the last one preDiff + preSame
 * */
class Solution {
    public:
        int numWays(int n, int k) {
            if (n == 0) {
                return 0;
            }
            if (n == 1) {
                return k;
            }

            int preDiff = k, preSame = 0, curDiff, curSame;
            for (int i = 2; i <= n; i++) {
                curSame = preDiff;
                curDiff = (preDiff + preSame) * (k - 1);

                preDiff = curDiff;
                preSame = curSame;
            }

            return preDiff + preSame;
        }
};
