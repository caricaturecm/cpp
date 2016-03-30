//305. Number of Islands II
/*
 * Union Find
 * */
class UnionFind {
    int row, col, count;
    vector<int> root, size;
    public:
    UnionFind(int r, int c) : row(r), col(c), count(0) {
        root.assign(r * c, -1);
        size.assign(r * c, 0);
    }

    int index(int x, int y) {
        if (x >= 0 && x < row && y >= 0 && y < col) {
            return x * col + y;
        }
        return -1;
    }

    int getCount() {
        return count;
    }

    int add(int x, int y) {
        int i = index(x, y);
        root[i] = i;
        size[i] = 1;
        count++;
        return i;
    }

    void unionSet(int p, int q) {
        int r1 = find(p);
        int r2 = find(q);
        if (r1 == -1 || r2 == -1 || r1 == r2) {
            return;
        }
        if (size[r1] <= size[r2]) {//union by size
            root[r1] = r2;
            size[r2] += size[r1];
        } else {
            root[r2] = r1;
            size[r1] += size[r2];
        }
        count--;
    }

    int find(int i) {
        if (root[i] == -1) {
            return -1;
        }
        while (root[i] != i) {
            root[i] = root[root[i]];//path compression
            i = root[i];
        }

        return i;
    }
};

class Solution {
    public:
        vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
            vector<int> ret;
            UnionFind islands(m, n);

            int directions[][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
            for (auto position : positions) {
                int x = position.first, y = position.second;
                int curRoot = islands.add(x, y);
                for (auto direction : directions) {
                    int i = islands.index(x + direction[0], y + direction[1]);
                    if (i >= 0) {
                        islands.unionSet(curRoot, i);
                    }
                }
                ret.push_back(islands.getCount());
            }

            return ret;
        }
};
