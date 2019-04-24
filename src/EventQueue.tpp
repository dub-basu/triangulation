#ifndef EVENT_QUEUE
#define EVENT_QUEUE
#include<vector>

using namespace std;

/**
 * The event queue is a min heap
 * @tparam T class needs < function and defined
 */
template <class T>
class EventQueue
{
	vector <T> events; //!< Stores all the event points the sweep line intersects.
	/**
	* minHeapify to correct the event queue.
	*/
    void minHeapify(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        int heapSize = events.size();
        if (left < heapSize and events[left] < events[smallest])
            smallest = left;
        if (right < heapSize and events[right] < events[smallest])
            smallest = right;
        if (smallest != i) {
            swap(events[i], events[smallest]);
            minHeapify(smallest);
        }
    }

public:

	/**
	 * Extract the minimum element from the event queue.
	 * This also removes the element from queue.
	 * @return min element in the heap
	 */
    T extractMin() {
        if (events.size() <= 0)
        {
            cerr<<"Empty queue! Aborting!!"<<endl;
            // assert(false);
        }
        else if (events.size() == 1)
        {
            T p=events[0];
            events.pop_back();
            return p;
        }

        T root = events[0];
        swap(events[0], events[events.size() - 1]);
        events.pop_back();
        minHeapify(0);

        return root;
    }

	/**
	 *
	 * @return
	 */
    T peek()
    {
        return events[0];
    }


	/**
	 * Insert a new event in the event queue.
	 * @param element to insert
	 */
    void insert(T k) {
        events.push_back(k);

        int i = events.size() - 1;
        while (i != 0 and events[i] < events[(i - 1) >> 1] ) // if Parent has more value than child
        {
            swap(events[i], events[(i - 1) >> 1]);
            i = (i - 1) >> 1;
        }
    }

	/**
	 * Get size of the heap.
	 * @return number of elements in the event queue
	 */
    int size(){
        return events.size();
    }

};

#endif