class Solution {
public:
    const int MOD =1e9+7,MOD1=1e9+9;
    const int D = 257;
    
    string get(string &str,int len)
    {
        set<pair<int,int>> vec;
        long long int curr1 = 0,curr2=0;
        long long int off1 = 1,off2=1;
        for(int i=0;i<len-1;i++)
        {
            off1 = off1*D%MOD;
            off2 = off2*D%MOD1;
        }    
        
        for(int i=0;i<len ;i++)
        {
            curr1 = (curr1*D + str[i])%MOD;
            curr2 = (curr2*D + str[i])%MOD1;
        }    
        vec.insert({curr1,curr2});
        for(int i=0,j=len;j<str.size();i++,j++)
        {
            curr1 = (D*(curr1-off1*str[i]) + str[j])%MOD;
            curr2 = (D*(curr2-off2*str[i]) + str[j])%MOD1;
            if(curr1<0)
                curr1 += MOD;
            if(curr2<0)
                curr2 += MOD1;
            if(vec.find({curr1,curr2})!=vec.end())
                return str.substr(i+1,len);
            
            vec.insert({curr1,curr2});
        }
        return "";
    }
    
    
    string longestDupSubstring(string S) {
        int l = 0, r = S.size();
        
        while(l<r)
        {
            int m = l + (r-l+1)/2;
            if(get(S,m).size()!=0)
            {
                l = m;
            }
            else
                r = m - 1;
        }
        return get(S,l);
    }
};

/*
// need to know Rabin-Karp 's algorithm

// interesting sol 1

typedef vector<int> VI;
typedef pair<int, int> PI;
typedef vector<PI> VPI;

#define FOR(i,a,n) for (int i = (a); i < (n); ++i)
#define FORE(i,a,n) for (int i = (a); i <= (n); ++i)
#define FORD(i,a,b) for (int i = (a); i >= (b); --i)
#define REP(i,n) FOR(i,0,n)
#define REPE(i,n) FORE(i,0,n)
#define LL long long
#define FIR(n) REP(i,n)
#define FJR(n) REP(j,n)
#define ALL(v) v.begin(), v.end()

#define FI FIR(n)
#define FJ FJR(n)
#define FR(i,a) FOR(i,a,n)
#define REPN(i) REP(i,n)


#define MAX_LEN 1000001

int pos[MAX_LEN];
int prm[MAX_LEN];
int cnt[MAX_LEN];
bool bh[MAX_LEN + 1];
int b2h[MAX_LEN];
int hit[MAX_LEN];

vector<int> make_suffix_array(const string& ss) {
	const string& s = ss;
	int n = s.size();
	int scnt[257] = {0, 1};
	FI ++scnt[s[i]+1];
	FOR(i, 1, 257) scnt[i] += scnt[i-1];
	FI bh[i] = false;bh[n] = false;
	FIR(257) bh[scnt[i]] = true;
	FI pos[scnt[s[i]]++] = i;
	pos[0]=  n++;
	FI prm[pos[i]] = i;

	int H = 1;
	int step = 0, steph = 0;
	memset(hit, 0, n*(sizeof hit[0]));
	memset(b2h, 0, n*(sizeof b2h[0]));
	while (H < n) {
		++steph;
		memset(cnt, 0, n*(sizeof (int)));
		int l = 0;
		while (l < n) { 
			int r = l + 1;
			while (!bh[r]) ++r;
			for (int c = l; c < r; ++c) prm[pos[c]] = l;
			l = r;
		}
		l = 0;
		while (l < n) { 
			int r = l + 1;
			++step;
			while (!bh[r]) ++r;
			for (int c = l; c < r; ++c) {
				int d = pos[c] - H;
				if (d >= 0) {
					int bck = prm[d];
					prm[d] += cnt[bck];
					++cnt[bck];
					if (hit[bck] != step) {
						b2h[prm[d]] = steph;
						hit[bck] = step;
					}
				}
			}
			l = r;
		}
		FI pos[prm[i]] = i;
		FI if (b2h[i] == steph) bh[i] = true;
		H <<= 1;
	}
	vector<int> res(pos, pos + n);
	return res;
}

vector<int> compute_lcp(string s, const vector<int>& sa) {
	s += (char)0;
	int n = s.size();
	FI prm[sa[i]] = i;

	int h = 0;
	FI {
		int k = prm[i];
		if (k) {
			int prev = sa[k-1];
			while (s[prev + h] == s[i + h]) ++h;
			pos[k] = h;
		} else
			pos[k] = -1;
		
		if (h) --h;
	}

	return vector<int>(pos, pos + n);
}

class Solution {
public:
	string longestDupSubstring(string S) {
		VI sa = make_suffix_array(S);
		VI lcp = compute_lcp(S, sa);

		int pos = max_element(lcp.begin(), lcp.end()) - lcp.begin();


		return S.substr(sa[pos], lcp[pos]);
	}
};


// interesting sol 2
template<typename T>
void induced_sorting(
    const T *text,
    size_t n,
    T min_item,
    size_t range,
    const vector<size_t> &starts,
    const vector<bool> &stype,
    const vector<size_t> &lms,
    vector<size_t> &sa
) {

  // Fill in LMS terms
  {
    vector<size_t> starts_copy = starts;
    for (auto i = lms.rbegin(); i != lms.rend(); i++) {
      auto &end = starts_copy[text[*i] - min_item + 1];
      end -= 1;
      sa[end] = *i;
    }
  }

  // Fill in L
  {
    vector<size_t> starts_copy = starts;
    // Special case: n-1. We don't use a sentinel.
    {
      auto &start = starts_copy[text[n - 1] - min_item];
      sa[start] = n - 1;
      start += 1;
    }

    for (auto i = 0; i < n; i++) {
      if (sa[i] != n && sa[i] > 0 && !stype[sa[i] - 1]) {
        auto &start = starts_copy[text[sa[i] - 1] - min_item];
        sa[start] = sa[i] - 1;
        start += 1;
      }
    }
  }

  // Fill in S
  {
    vector<size_t> starts_copy = starts;
    for (size_t i = n - 1; i < n; i--) {
      if (sa[i] != n && sa[i] > 0 && stype[sa[i] - 1]) {
        auto &end = starts_copy[text[sa[i] - 1] - min_item + 1];
        end -= 1;
        sa[end] = sa[i] - 1;
      }
    }
  }
}

template<typename T>
bool eq_lms(const T *text, size_t n, size_t a, size_t b, const vector<bool> &stype) {
  if (text[a] != text[b]) {
    return false;
  }
  auto hit_l = false;
  while (true) {
    a++;
    b++;
    if (b < n && stype[b] && a == n) {
      return true;
    }
    if (a < n && stype[a] && b == n) {
      return true;
    }
    if (a == n || b == n || text[a] != text[b] || stype[a] != stype[b]) {
      return false;
    }
    if (stype[a]) {
      if (hit_l) {
        return true;
      }
    } else {
      hit_l = true;
    }
  }
}

template<typename T>
static vector<bool> compute_stype(const T *text, size_t n) {
  vector<bool> stype(n, false);
  for (size_t i = n - 2; i < n; i--) {
    T a = text[i];
    T b = text[i + 1];
    if (a < b) {
      stype[i] = true;
    } else if (a == b) {
      stype[i] = stype[i + 1];
    }
  }

  return stype;
}

template<typename T>
vector<size_t> suffix_array(const T *text, size_t n) {
  vector<size_t> sa(n, n);
  if (n == 0) {
    return sa;
  }

  // Compute alphabet range
  T min_item = text[0];
  T max_item = text[0];

  for (size_t i = 1; i < n; i++) {
    auto item = text[i];
    if (min_item > item) {
      min_item = item;
    }
    if (max_item < item) {
      max_item = item;
    }
  }

  const size_t range = max_item - min_item + 1;

  // Bucketize result
  vector<size_t> counts(range, 0);
  auto needs_sorting = false;

  for (size_t i = 0; i < n; i++) {
    size_t item = text[i] - min_item;
    if (counts[item] == 0) {
      counts[item] = 1;
    } else {
      counts[item] += 1;
      needs_sorting = true;
    }
  }

  if (!needs_sorting) {
    // If all characters are different we can exit
    vector<size_t> rev(range, n);
    for (size_t i = 0; i < n; i++) {
      rev[text[i] - min_item] = i;
    }
    auto j = 0;
    for (size_t i = 0; i < n; i++) {
      if (rev[i] < n) {
        sa[j] = rev[i];
        j += 1;
      }
    }
    return sa;
  }

  vector<size_t> starts(range + 1, 0);
  for (size_t i = 1; i < range; i++) {
    starts[i] = starts[i - 1] + counts[i - 1];
  }
  starts[range] = n;

  // Separate the list into lms-blocks
  vector<bool> stype = compute_stype(text, n);

  vector<size_t> lms;
  for (size_t i = 1; i < n; i++) {
    if (stype[i] && !stype[i - 1]) {
      lms.push_back(i);
    }
  }

  induced_sorting(text, n, min_item, range, starts, stype, lms, sa);

  // Sort lms-suffixes
  if (lms.size() > 1) {
    vector<size_t> lms_blocks;
    for (size_t i = 0; i < n; i++) {
      if (sa[i] > 0 && sa[i] != n && stype[sa[i]] && !stype[sa[i] - 1]) {
        // lms
        lms_blocks.push_back(sa[i]);
      }
    }

    // Merge identical LMS blocks
    size_t lms_numbering = 0;
    sa[lms_blocks[0]] = lms_numbering;
    for (size_t i = 1, m = lms_blocks.size(); i < m; i++) {
      auto last = lms_blocks[i - 1];
      auto curr = lms_blocks[i];
      if (!eq_lms(text, n, last, curr, stype)) {
        lms_numbering += 1;
      }
      sa[lms_blocks[i]] = lms_numbering;
    }

    vector<size_t> sub_problem;
    sub_problem.reserve(lms.size());
    for (auto lm : lms) {
      sub_problem.push_back(sa[lm]);
    }

    auto sub_sa = suffix_array(&*sub_problem.begin(), sub_problem.size());
    vector<size_t> lms2;
    lms2.reserve(lms.size());
    for (auto i : sub_sa) {
      lms2.push_back(lms[i]);
    }

    // Reset SA
    for (auto i = 0; i < n; i++) {
      sa[i] = n;
    }
    induced_sorting(text, n, min_item, range, starts, stype, lms2, sa);
  }

  return sa;
}

template<typename T>
vector<size_t> lcp_sakai(const T *text, size_t n, const vector<size_t> &sa) {
  vector<size_t> lcp(n, 0);
  vector<size_t> rank(n, 0);
  for (size_t i = 0; i < n; i++) {
    rank[sa[i]] = i;
  }

  size_t k = 0;
  for (size_t i = 0; i < n; i++) {
    if (rank[i] == n - 1) {
      k = 0;
      continue;
    }

    auto j = sa[rank[i] + 1];
    while (i + k < n && j + k < n && text[i + k] == text[j + k]) {
      k += 1;
    }
    lcp[rank[i] + 1] = k;
    if (k > 0) {
      k -= 1;
    }
  }

  return lcp;
}

class Solution {
public:
    string longestDupSubstring(string S) {
      int n = S.length(), k;
      vector<size_t> sa = suffix_array(S.c_str(), S.size());
      vector<size_t> lcp = lcp_sakai(S.c_str(), S.size(), sa);
      
      int ans;
      int m = 0;
      for (int i = 0; i < n; i++) {
        if (lcp[i] > m) {
          m = lcp[i];
          ans = sa[i];
        }
      }
      if(m<=0) return "";
      return S.substr(ans, m);
    }
};


static const auto fast = []() {
   std::ios_base::sync_with_stdio(false);
   std::cin.tie(0);
   std::cout.tie(0);
   return 0;
} ();


*/
