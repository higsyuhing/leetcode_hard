class Solution {
public:
    // feel kinds of brute force.. 
    // every two points will generate a line, thus has a hash value
    // compute its Determinant to check if in the same line.. 
    
    int maxPoints(vector<vector<int>>& points) {
        if (points.empty()) return 0;
        if (points.size() == 1) return 1;
        if (points.size() == 2) return 2;
        map<double, int> memo_k;
        int res = 2;
        while (points.size() > 2)
        {
            int vertical_cnt = 1;
            int base_x = points[points.size() - 1][0];
            int base_y = points[points.size() - 1][1];
            memo_k.clear();
            int tempres = 0;
            int same_points = 0;
            for (int i = points.size() - 2; i >= 0; i--)
            {
                if (points[i][0] == base_x && points[i][1] != base_y) ++vertical_cnt;
                else if (points[i][0] == base_x && points[i][1] == base_y)
                {
                    ++same_points;
                    points.erase(points.begin() + i);
                }
                else ++memo_k[((double)(points[i][1] - base_y) / (points[i][0] - base_x))];
            }
            for (auto &i : memo_k) if (++i.second > tempres) tempres = i.second;
            tempres = (tempres > vertical_cnt ? tempres : vertical_cnt) + same_points;
            res = max(res, tempres);
            points.pop_back();
        }
        return res;
    }
    //8ms beats 99.69%
    //8.7MB beats 100%
    
};

