// Author: Huahua
// Running time: 81 ms

// idea is fine.. not that hard.. 
class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
      vector<Interval> all;
      for (const auto intervals : schedule)
        all.insert(all.end(), intervals.begin(), intervals.end());
      std::sort(all.begin(), all.end(), 
                [](const Interval& a, const Interval& b){
                  return a.start < b.start;
                });
      vector<Interval> ans;
      int end = all.front().end;
      for (const Interval& busy : all) {
        if (busy.start > end) 
          ans.emplace_back(end, busy.start);  
        end = max(end, busy.end);
      }
      return ans;
    }
};
