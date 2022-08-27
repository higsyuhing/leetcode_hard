class Solution {
public:
    
    int helper_gcd(int a, int b){
        if (b == 0) return a; 
        return gcd(b, a % b); 
    }
    
    int helper_lcm(int a, int b){
        return (a / gcd(a, b)) * b; 
    }
    
    int nthMagicalNumber(int n, int a, int b) {
        
        // several observations: 
        // - a, b will construct a loop: we can take a*b, 
        //      thus range [k, k+a*b] for any positive integer k 
        //      will have the same number of magical number
        // - the first range will be k = 0, i.e. [0, a*b]
        // 1. first step, generate magic number list in range [0, a*b]
        //      this can be improved by lcm(a, b): [0, lcm(a,b)]
        // 2. assume this range has m elements, we will take: n = m*p+q
        //      then it will be after p of lcm(a,b) and then q-th element
        
        // for step 1: 
        // 1.1 compute lcm(a,b)
        // 1.2 use an updated merge sort to generate this list
        int lcm = helper_lcm(a, b); 
        int curra, currb; 
        curra = a; currb = b; 
        vector<int> listrange; 
        while(1){
            if ((curra == lcm) && (currb == lcm)) break; 
            if (curra < currb){
                listrange.push_back(curra); 
                curra += a; 
            }
            else{ //  if (curra > currb)
                listrange.push_back(currb); 
                currb += b; 
            }
            // never fall this case since they are smaller than lcm. 
            // else{
            //     listrange.push_back(currb); // only 1 insert
            //     curra += a; 
            //     currb += b; 
            // }
        }
        listrange.push_back(lcm); 
        
        // for (int i = 0; i < listrange.size(); i++){
        //     cout << listrange[i] << endl; 
        // }
        
        // step 2
        int m = listrange.size(); 
        int p = (n-1) / m; 
        int q = (n-1) % m; 
        
        long long val = ((long long)p)*((long long)lcm); 
        long long div = 1000000000 + 7; 
        val += (long long)listrange[q]; 
        val = val % div; 
        
        return (int)val; 
    }
};


