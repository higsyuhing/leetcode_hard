class MedianFinder {
    priority_queue<int> lo;                              // max heap
    priority_queue<int, vector<int>, greater<int>> hi;   // min heap

public:
    // Adds a number into the data structure.
    void addNum(int num)
    {
        lo.push(num);                                    // Add to max heap

        hi.push(lo.top());                               // balancing step
        lo.pop();

        if (lo.size() < hi.size()) {                     // maintain size property
            lo.push(hi.top());
            hi.pop();
        }
    }

    // Returns the median of current data stream
    double findMedian()
    {
        return lo.size() > hi.size() ? lo.top() : ((double) lo.top() + hi.top()) * 0.5;
    }
};

/*
class MedianFinder {
public:
    // maintain a sorted array? binary insert
    vector<int> array; 
    
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        array.push_back(num); 
    }
    
    double findMedian() {
        sort(array.begin(), array.end()); 
        int len = array.size(); 
        if(len%2 == 0){ // len = 4: 0,1,2,3 => 1,2
            return (array[len/2-1] + array[len/2])/2.0; 
        }
        else{ // len = 3: 0,1,2 => (3-1)/2
            return array[(len-1)/2]; 
        }
    }
};
*/

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
