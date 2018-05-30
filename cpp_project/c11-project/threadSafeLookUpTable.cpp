#include <string>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <utility>
#include <assert.h>
using namespace std;

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class ThreadSafeLookUpTable {
public:
private:
    class BucketType {

        using  bucketValue = std::pair<Key, Value> ;
        using  bucketData = std::list<bucketValue> ;
        typedef typename bucketData::iterator bucketIterator;

        bucketData data;
        mutable std::mutex bucketMutex;

        bucketIterator FindEntryFor(Key const& key) const
        {
            return std::find_if(data.begin(), data.end(), [&](cont bucketIterator& item) { return item->first == key;});
        }

    public:
        Value ValueFor(Key const& key, Value const& defaultValue) const
        {
            std::unique_lock<mutex> lock(bucketMutex);
            //locks.push_back(std::unique_lock<boost::shared_mutex>(buckets[i].mutex)); 
            //RW lock will be better than unique lock
            //使用 boost::shared_mutex 允许读者线程对每一个桶进行并发访问
            bucketIterator const foundEntry = FindEntryFor(key);
            return (foundEntry == data.begin()) ? defaultValue : foundEntry->second;
        }

        void AddOrUpdateMapping(Key const& key, Value const& value)
        {
            std::unique_lock<mutex> lock(bucketMutex);
            bucketIterator const foundEntry = ValueFor(key);
            if (foundEntry == data.end())
            {
                data.push_back(bucketValue(key, value));
            }
            else
            {
                data.erase(foundEntry);
            }
        }

        void RemoveMapping(Key const& key)
        {
            std::unique_lock<mutex> lock(bucketMutex);
            bucketIterator const foundEntry = ValueFor(key);
            if (foundEntry == data.end())
            {
                return;
            }
            else
            {
                data.erase(foundEntry);
            }
        }
    };
    
    std::vector<std::unique_ptr<BucketType>> buckets;
    Hash hasher;

    BucketType& GetBucket(Key const& key) const
    {
        std::size_t const bucketIndex = hasher(key) % buckets.size();
        return *buckets[bucketIndex];
    }
public:
    typedef Key KeyType;
    typedef Value ValueType;
    typedef Hash HashType;

    ThreadSafeLookUpTable(unsigned numBuckets = 19, Hash const& hasher_ = Hash()) :
        buckets(numBuckets), hasher(hasher_)
    {
        for (unsigned i = 0; i<numBuckets;i++)
        {
            buckets[i].reset(new BucketType);
        }
    }

    ThreadSafeLookUpTable(ThreadSafeLookUpTable const& other) =delete;
    ThreadSafeLookUpTable& operator=(ThreadSafeLookUpTable const& other) = delete;

    Value ValueFor(Key const& key, Value const& defaultValue = Value()) const {
        return GetBucket(key).ValueFor(key, defaultValue);
    }

    void RemoveMapping(Key const& key)
    {
        GetBucket(key).RemoveMapping(key);
    }

    std::map<KeyType, ValueType> GetMap()const
    {
        std::vector<unique_lock<mutex>> locks;
        for (unsigned i =0;i<buckets.size();i++)
        {
            locks.push_back(unique_lock<mutex>(buckets[i]->mutex));
        }
        std::map<KeyType, ValueType> res;
        for (unsigned i = 0; i < buckets.size(); i++)
        {
            for (bucketIterator it = buckets[i]->data.begin();it!= buckets[i]->data.end();++it)
            {
                res.insert(*it);
            }
        }
        return res;
    }
    
};


ThreadSafeLookUpTable<int, string> gThreadSafeLookUpTable;
std::atomic_bool gFlag = ATOMIC_FLAG_INIT;
void testThreadSafeLookUpTable(int id)
{
    int val;
    std::shared_ptr<int> dataPtr;
    for (int i = 0; i < 1000; i++)
    {
        int ran = rand();
        cout << "thread：" << id << " rand: " << ran % 5 << "\n" << std::flush;

        switch (ran % 5)
        {
        case 0:
            gThreadSafeLookUpTable;
            break;
        case 1:
           
            break;
        case 2:
           
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        }
        cout << "thread：" << id << " op end" << "\n" << std::flush;
    }
    cout << "thread：" << id << " end" << endl << std::flush;
    gFlag.store(true);
}

// void addVal(int id)
// {
//     while (!gFlag.load())
//     {
//         this_thread::sleep_for(std::chrono::milliseconds(1000));
//         int input = rand();
//         cout << "thread：" << id << " input: " << input << "\n" << std::flush;
//         gThreadSafeLookUpTable.Push(input);
// 
//     }
// 
// }
void testThreadQueue()
{
#define  CreateThread(Func, val)  std::thread Thread##val(testThreadSafeLookUpTable,val)
    CreateThread(testThreadSafeLookUpTable, 1);
    CreateThread(testThreadSafeLookUpTable, 2);
    CreateThread(testThreadSafeLookUpTable, 3);
    CreateThread(testThreadSafeLookUpTable, 4);
    CreateThread(testThreadSafeLookUpTable, 5);
#define  JoinThread(i) Thread##i.join()
    JoinThread(1);
    JoinThread(2);
    JoinThread(3);
    JoinThread(4);
    JoinThread(5);
}

int main(int argc, char* argv[])
{
    testThreadQueue();
    cout << "end" << endl;

    getchar();
    return 0;
}
