// TestFrame.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <unordered_map>

#include <numeric>      // std::accumulate
#include <algorithm>    // std::for_each
#include <list>
#include <thread>
#include <set>
#include <vector>
#include <map>
#include <random>
#include <strstream>
#include <stdio.h>
#include <windows.h>
using namespace std;


class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        vector<int> dp{ nums.size() };
        for (int s = nums.size(); s >= 0; s--) {
            for (int e = s + 1; e < nums.size(); e++) {
                int a = nums[s] - dp[e];
                int b = nums[e] - dp[e - 1];
                dp[e] = max(a, b);
            }
        }
        return dp[nums.size() - 1] >= 0;

    }
};

template<typename T>
void CalcStatFactor(list<T>& resultSet, double& mean, double& stdev)
{
    if (0 == resultSet.size())
    {
        mean = 0;
        stdev = 0;
        return;
    }

    if (1 == resultSet.size())
    {
        mean = resultSet.front();
        stdev = 0;
        return;
    }

    double sum = accumulate(std::begin(resultSet), std::end(resultSet), 0.0);
    mean = sum / resultSet.size();
    cout << "mean1" << mean << endl;
    double accum = 0.0;
    for_each(begin(resultSet), end(resultSet), [&](const T d) {
        accum += (d - mean)*(d - mean);
    });

    stdev = sqrt(accum / (resultSet.size() - 1));
}

void do_something(int i) {
    cout << "i=" << i << endl;
}
struct func
{
    int& i;
    func(int& i_) : i(i_) {}
    void operator() ()
    {
        for (unsigned j = 0; j < 100000; ++j)
        {
            do_something(i); // 1. 潜在访问隐患：悬空引用
        }
    }
};
void oops()
{
    int some_local_state = 10;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach(); // 2. 不等待线程结束
} // 3. 新线程可能还在运行
  /*
  随机从一组string set中抽取num个string
  */
template<typename T>
set<T>&  RandomExtractFromStringTemplate(set<T>& stringSet, int num)
{

    std::random_device rd;
    int setSize = stringSet.size();
    set<T> sampleSet;
    if (setSize == 0)
    {
        return sampleSet;
    }
    if (num > setSize)
    {
        return stringSet;
    }
    int curIndex = 0;
    int vecIndex = 0;

    set<int> sampleIndexSet;
    vector<int> sampleIndexVec;

    while (sampleIndexSet.size() != num)
    {
        sampleIndexSet.insert(rd() % setSize);
    }
    for (auto it : sampleIndexSet)
    {
        sampleIndexVec.push_back(it);
    }

    for (auto& it : stringSet)
    {
        if (curIndex == sampleIndexVec[vecIndex])
        {
            vecIndex++;
            sampleSet.insert(it);
            if (vecIndex == num)
            {
                break;
            }
        }
        curIndex++;

    }
    return sampleSet;
}

std::set<std::string> RandomExtractStock(std::set<std::string>& stockSet, int num)
{
    std::random_device rd;
    int totalSize = stockSet.size();
    std::set<string> extractSet;
    if (totalSize == 0)
    {
        std::move(extractSet);
    }
    if (num > totalSize)
    {
        return stockSet;
    }
    int curIndex = 0;
    int vecIndex = 0;

    std::set<int> extractIndexSet;
    std::vector<int> extractIndexVec;

    while (extractIndexSet.size() != num)
    {
        extractIndexSet.insert(rd() % totalSize);
    }
    for (auto it : extractIndexSet)
    {
        extractIndexVec.push_back(it);
    }

    for (auto& it : stockSet)
    {
        if (curIndex == extractIndexVec[vecIndex])
        {
            vecIndex++;
            extractSet.insert(it);
            if (vecIndex == num)
            {
                break;
            }
        }
        curIndex++;

    }
    return std::move(extractSet);
}


/*
测试随机从一组string set中抽取num个string
*/
/*
int main()
{
random_device rd;
set<string> object;
for (int n = 0; n < 500; ++n)
{
strstream ss;
string s;
ss << n;
ss >> s;
cout << s << endl;
object.insert(s);
}
for (int i = 0; i<5000000;i++)
{
set<string> sampleSet2 = RandomExtractStock(object, 10);
std::cout << "==============" << std::endl;
for (auto& it : sampleSet2)
{
std::cout << it << std::endl;
}
}

std::cout << "==============" << std::endl;
float nn = (float) 1 / 2;
std::cout << nn << std::endl;

getchar();
return 0;
}
*/

/*
测试从int转string，左边置0
*/
/*
int main()
{
char timeStr[8];
sprintf_s(timeStr, 8, "%06d", int(93555030 / 1000));
string date = "20180413";
string date_time = date + timeStr;
std::cout << date_time << std::endl;
getchar();
return 0;
}

/*
测试从int转string，左边置0
*/
/*
int main()
{

//  float 0.0 eq 0? ans = true   //

// 	double f = 0;
// 	if (f == 0.0) {
// 		cout << "0.0 == 0" << endl;
// 	}
// 	else
// 	{
// 		cout << "0.0 != 0" << endl;
//
// 	}

//  unordered_map set default capacity  //

//     std::unordered_map<std::string, std::string> u{1024};
//     cout << u.bucket_count() << endl;
//     u.reserve(128);
//     cout << u.bucket_count() << endl;


//  print format setw  //

//     cout << setw(10) << "index" << setw(10) <<"num"<< setw(10) << "num2" << endl;
//     int index = 1;
//     for (int i = -100000; i < 100000;i=i+10000) {
//         cout << setw(10) << index << setw(10) << i << setw(10) << index << endl;
//
//     }

//   test CalcStatFactor func//
//     list<int> resultSet;
//     //resultSet.push_back(2);
//
//     double mean, stdev;
//     CalcStatFactor<int>(resultSet, mean, stdev);
//     stdev++;
//
//     cout << "mean " << mean << "  stdev " << stdev << endl;
//
//     list<int> listNum;
//     cout << "list size " << listNum.size() << endl;
//     listNum.remove(8);

//     list<int> listNum;
//     cout << "list size " << listNum.size() << endl;
//     do
//     {
//         oops();
//     } while (0);
//

std::unordered_map<std::string, int> edges;
auto random_it = std::next(std::begin(edges), rand_between(0, edges.size()));

getchar();
return 0;
}
*/

/*

How do I convert a double into a string in C++ ?

/*
// The C way:
char buffer[32];
snprintf(buffer, sizeof(buffer), "%g", myDoubleVar);

// The C++03 way:
std::ostringstream sstream;
sstream << myDoubleVar;
std::string varAsString = sstream.str();

// The C++11 way:
std::string varAsString = std::to_string(myDoubleVar);

// The boost way:
std::string varAsString = boost::lexical_cast<std::string>(myDoubleVar);
*/
#include <sstream>
#include <iomanip>

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}
/*
int main()
{
string res = to_string_with_precision<double>(1127.265, 3);
cout << "res: " << res << endl;
//res: 1.13e+03
getchar();
return 0;
}
*/


/*
一般来说，迭代器是个数据结构，会将真实的数据地址保存在某个内部的成员变量中，并重载各种运算符（比如解引用运算符*）。
要取得数据地址，推荐的方法是&*，即先通过可能被重载过的星号运算符得到真实数据再取地址。

但是对于vector<int>，其实是typedef int *iterator，所以即使(int*)tmp也没啥问题。
*/

/*
int main()
{

vector<string> testVect;
testVect.push_back("testVect111111");
testVect.push_back("testVect222222");

cout << "\n &*testVect.begin()   " << &*testVect.begin()\
<< "\n &testVect[0]    " << &testVect[0] << endl;

cout << "\n *testVect.begin()   " << *testVect.begin()\
<< "\n testVect[0]    " << testVect[0] << endl;

set<string> testSet;
testSet.insert("testSet111111");
testSet.insert("testSet222222");

cout << "\n &*testSet.begin()   " << &*testSet.begin()<< endl;

cout << "\n *testSet.begin()   " << *testSet.begin()<< endl;

int index = 0;
std::random_device rd;
list<int> testList;
for (int i = 0; i < 819200; i++)
{
testList.push_back(i);
}
cout << "begin" << endl;
while (index++ < 10000)
{


list<int>::iterator it;
int random1 = rd() % 1023;
for (it = testList.begin(); it != testList.end(); it++)
{
if (*it == random1)
{
break;
}
}

int diff = *it;
int * diff_ptr = &*it;
int random2 = rd() % 1023;
if (random1 != random2)
{
testList.remove(random2);
if (diff != *it)
{
cout << "=========" << endl;
cout << "diff_ptr  " << diff_ptr << "*it   " << diff << endl;
cout << "&*it   " << &*it << "*it   " << *it << endl;
cout << "=========" << endl;
}
//             else
//             {
//                 cout << "eq" << &*it << "*it   " << *it << endl;
//             }

}

}

//     cout << "\n &*testList.begin()   " << &*testList.begin() << endl;
//     cout << "\n *testList.begin()   " << string(*testList.begin()).c_str() << endl;
//
//     testList.pop_back();
//     cout << "\n &*testList.begin()   " << &*testList.begin() << endl;
getchar();
return 0;
}
*/
void vectTest()
{
    vector<pair<int, string>> testPairVect;
    testPairVect.push_back({ 1,"aaaaaa" });
    testPairVect.push_back({ 2,"bbbbbb" });
    testPairVect.push_back({ 3,"bbbbbb" });
    vector<int> testInt(4, 2);
}

// std::find()
// // FUNCTION TEMPLATE for_each
// template<class _InIt,
//     class _Fn> inline
//     _Fn find_if(_InIt _First, _InIt _Last, _Fn _Func)
// {	// perform function for each element [_First, _Last)
//     _DEBUG_RANGE(_First, _Last);
//     auto _UFirst = _Unchecked(_First);
//     const auto _ULast = _Unchecked(_Last);
//     for (; _UFirst != _ULast; ++_UFirst)
//     {
//         _Func(*_UFirst);
//     }
// 
//     return (_Func);
// }

void testMapFind()
{
    map<int, string> mapTest;

    mapTest.insert({ 1,"aaaaaa" });
    mapTest.insert({ 2,"bbbbbb" });
    mapTest.insert({ 3,"bbbbbb" });
    for (int i = 0; i<100000; i++)
    {

    }
    map<int, string>::iterator it;
    if ((it = mapTest.find(2)) != mapTest.end())
    {
        cout << "found " << it->first<<endl;
    }
    else
    {
        cout << "not found " << endl;

    }


}

#include <iostream>  
using namespace std;

/*
* 简介：利用C++处理中文转换成拼音
* 作者：陈鲁勇
* 参数：dest_chinese 待转换中文
* 参数：out_py 返回的拼写
* 返回：0成功 非0失败
* 拾遗：如有拾遗，请联系我。
* 邮箱：727057301@qq.com
* CSDN：http://blog.csdn.net/csnd_ayo
* 码云：https://git.oschina.net/Mr_ChenLuYong
* github：http://github.com/chenluyong
* 创建时间：2017-3-18 1:52:48
* VS版本：VS2013
*/
int ChineseConvertPy(const std::string& dest_chinese, std::string& out_py) {
    const int spell_value[] = { -20319, -20317, -20304, -20295, -20292, -20283, -20265, -20257, -20242, -20230, -20051, -20036, -20032, -20026,
        -20002, -19990, -19986, -19982, -19976, -19805, -19784, -19775, -19774, -19763, -19756, -19751, -19746, -19741, -19739, -19728,
        -19725, -19715, -19540, -19531, -19525, -19515, -19500, -19484, -19479, -19467, -19289, -19288, -19281, -19275, -19270, -19263,
        -19261, -19249, -19243, -19242, -19238, -19235, -19227, -19224, -19218, -19212, -19038, -19023, -19018, -19006, -19003, -18996,
        -18977, -18961, -18952, -18783, -18774, -18773, -18763, -18756, -18741, -18735, -18731, -18722, -18710, -18697, -18696, -18526,
        -18518, -18501, -18490, -18478, -18463, -18448, -18447, -18446, -18239, -18237, -18231, -18220, -18211, -18201, -18184, -18183,
        -18181, -18012, -17997, -17988, -17970, -17964, -17961, -17950, -17947, -17931, -17928, -17922, -17759, -17752, -17733, -17730,
        -17721, -17703, -17701, -17697, -17692, -17683, -17676, -17496, -17487, -17482, -17468, -17454, -17433, -17427, -17417, -17202,
        -17185, -16983, -16970, -16942, -16915, -16733, -16708, -16706, -16689, -16664, -16657, -16647, -16474, -16470, -16465, -16459,
        -16452, -16448, -16433, -16429, -16427, -16423, -16419, -16412, -16407, -16403, -16401, -16393, -16220, -16216, -16212, -16205,
        -16202, -16187, -16180, -16171, -16169, -16158, -16155, -15959, -15958, -15944, -15933, -15920, -15915, -15903, -15889, -15878,
        -15707, -15701, -15681, -15667, -15661, -15659, -15652, -15640, -15631, -15625, -15454, -15448, -15436, -15435, -15419, -15416,
        -15408, -15394, -15385, -15377, -15375, -15369, -15363, -15362, -15183, -15180, -15165, -15158, -15153, -15150, -15149, -15144,
        -15143, -15141, -15140, -15139, -15128, -15121, -15119, -15117, -15110, -15109, -14941, -14937, -14933, -14930, -14929, -14928,
        -14926, -14922, -14921, -14914, -14908, -14902, -14894, -14889, -14882, -14873, -14871, -14857, -14678, -14674, -14670, -14668,
        -14663, -14654, -14645, -14630, -14594, -14429, -14407, -14399, -14384, -14379, -14368, -14355, -14353, -14345, -14170, -14159,
        -14151, -14149, -14145, -14140, -14137, -14135, -14125, -14123, -14122, -14112, -14109, -14099, -14097, -14094, -14092, -14090,
        -14087, -14083, -13917, -13914, -13910, -13907, -13906, -13905, -13896, -13894, -13878, -13870, -13859, -13847, -13831, -13658,
        -13611, -13601, -13406, -13404, -13400, -13398, -13395, -13391, -13387, -13383, -13367, -13359, -13356, -13343, -13340, -13329,
        -13326, -13318, -13147, -13138, -13120, -13107, -13096, -13095, -13091, -13076, -13068, -13063, -13060, -12888, -12875, -12871,
        -12860, -12858, -12852, -12849, -12838, -12831, -12829, -12812, -12802, -12607, -12597, -12594, -12585, -12556, -12359, -12346,
        -12320, -12300, -12120, -12099, -12089, -12074, -12067, -12058, -12039, -11867, -11861, -11847, -11831, -11798, -11781, -11604,
        -11589, -11536, -11358, -11340, -11339, -11324, -11303, -11097, -11077, -11067, -11055, -11052, -11045, -11041, -11038, -11024,
        -11020, -11019, -11018, -11014, -10838, -10832, -10815, -10800, -10790, -10780, -10764, -10587, -10544, -10533, -10519, -10331,
        -10329, -10328, -10322, -10315, -10309, -10307, -10296, -10281, -10274, -10270, -10262, -10260, -10256, -10254 };

    // 395个字符串，每个字符串长度不超过6  
    const char spell_dict[396][7] = { "a", "ai", "an", "ang", "ao", "ba", "bai", "ban", "bang", "bao", "bei", "ben", "beng", "bi", "bian", "biao",
        "bie", "bin", "bing", "bo", "bu", "ca", "cai", "can", "cang", "cao", "ce", "ceng", "cha", "chai", "chan", "chang", "chao", "che", "chen",
        "cheng", "chi", "chong", "chou", "chu", "chuai", "chuan", "chuang", "chui", "chun", "chuo", "ci", "cong", "cou", "cu", "cuan", "cui",
        "cun", "cuo", "da", "dai", "dan", "dang", "dao", "de", "deng", "di", "dian", "diao", "die", "ding", "diu", "dong", "dou", "du", "duan",
        "dui", "dun", "duo", "e", "en", "er", "fa", "fan", "fang", "fei", "fen", "feng", "fo", "fou", "fu", "ga", "gai", "gan", "gang", "gao",
        "ge", "gei", "gen", "geng", "gong", "gou", "gu", "gua", "guai", "guan", "guang", "gui", "gun", "guo", "ha", "hai", "han", "hang",
        "hao", "he", "hei", "hen", "heng", "hong", "hou", "hu", "hua", "huai", "huan", "huang", "hui", "hun", "huo", "ji", "jia", "jian",
        "jiang", "jiao", "jie", "jin", "jing", "jiong", "jiu", "ju", "juan", "jue", "jun", "ka", "kai", "kan", "kang", "kao", "ke", "ken",
        "keng", "kong", "kou", "ku", "kua", "kuai", "kuan", "kuang", "kui", "kun", "kuo", "la", "lai", "lan", "lang", "lao", "le", "lei",
        "leng", "li", "lia", "lian", "liang", "liao", "lie", "lin", "ling", "liu", "long", "lou", "lu", "lv", "luan", "lue", "lun", "luo",
        "ma", "mai", "man", "mang", "mao", "me", "mei", "men", "meng", "mi", "mian", "miao", "mie", "min", "ming", "miu", "mo", "mou", "mu",
        "na", "nai", "nan", "nang", "nao", "ne", "nei", "nen", "neng", "ni", "nian", "niang", "niao", "nie", "nin", "ning", "niu", "nong",
        "nu", "nv", "nuan", "nue", "nuo", "o", "ou", "pa", "pai", "pan", "pang", "pao", "pei", "pen", "peng", "pi", "pian", "piao", "pie",
        "pin", "ping", "po", "pu", "qi", "qia", "qian", "qiang", "qiao", "qie", "qin", "qing", "qiong", "qiu", "qu", "quan", "que", "qun",
        "ran", "rang", "rao", "re", "ren", "reng", "ri", "rong", "rou", "ru", "ruan", "rui", "run", "ruo", "sa", "sai", "san", "sang",
        "sao", "se", "sen", "seng", "sha", "shai", "shan", "shang", "shao", "she", "shen", "sheng", "shi", "shou", "shu", "shua",
        "shuai", "shuan", "shuang", "shui", "shun", "shuo", "si", "song", "sou", "su", "suan", "sui", "sun", "suo", "ta", "tai",
        "tan", "tang", "tao", "te", "teng", "ti", "tian", "tiao", "tie", "ting", "tong", "tou", "tu", "tuan", "tui", "tun", "tuo",
        "wa", "wai", "wan", "wang", "wei", "wen", "weng", "wo", "wu", "xi", "xia", "xian", "xiang", "xiao", "xie", "xin", "xing",
        "xiong", "xiu", "xu", "xuan", "xue", "xun", "ya", "yan", "yang", "yao", "ye", "yi", "yin", "ying", "yo", "yong", "you",
        "yu", "yuan", "yue", "yun", "za", "zai", "zan", "zang", "zao", "ze", "zei", "zen", "zeng", "zha", "zhai", "zhan", "zhang",
        "zhao", "zhe", "zhen", "zheng", "zhi", "zhong", "zhou", "zhu", "zhua", "zhuai", "zhuan", "zhuang", "zhui", "zhun", "zhuo",
        "zi", "zong", "zou", "zu", "zuan", "zui", "zun", "zuo" };

    try {
        // 循环处理字节数组  
        const int length = dest_chinese.length();
        for (int j = 0, chrasc = 0; j < length;) {
            // 非汉字处理  
            if (dest_chinese.at(j) >= 0 && dest_chinese.at(j) < 128) {
                out_py += dest_chinese.at(j);
                // 偏移下标  
                j++;
                continue;
            }

            // 汉字处理  
            chrasc = dest_chinese.at(j) * 256 + dest_chinese.at(j + 1) + 256;
            if (chrasc > 0 && chrasc < 160) {
                // 非汉字  
                out_py += dest_chinese.at(j);
                // 偏移下标  
                j++;
            }
            else {
                // 汉字  
                for (int i = (sizeof(spell_value) / sizeof(spell_value[0]) - 1); i >= 0; --i) {
                    // 查找字典  
                    if (spell_value[i] <= chrasc) {
                        out_py += spell_dict[i];
                        break;
                    }
                }
                // 偏移下标 （汉字双字节）  
                j += 2;
            }
        } // for end  
    }
    catch (exception _e) {
        std::cout << _e.what() << std::endl;
        return -1;
    }
    return 0;
}

#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

void CustomerAndProducer()
{
    queue<int> produce_nums;
    mutex m;
    condition_variable cond_var;
    bool done = false;
    bool notified = false;

    std::thread producer([&]()
    {
        for (int i = 0; i < 10; i++)
        {
            this_thread::sleep_for(chrono::microseconds(10));
            unique_lock<mutex> lock(m);
            produce_nums.push(i);
            cout << "producing " << i << endl;
            notified = true;

            cond_var.notify_one();
        }
        done = true;
        cond_var.notify_one();
    });

    std::thread customer([&]() {

        while (!done)
        {
            unique_lock<mutex> lock(m);
            while (!notified)
            {
                cond_var.wait(lock);
            }
            while (!produce_nums.empty())
            {
                cout << "consuming " << produce_nums.front() << endl;
                produce_nums.pop();
            }
        }
        notified = false;
    }
    );
    producer.join();
    customer.join();
}

// int main()
// {
//     std::string chang_query;
//     ChineseConvertPy("http://blog.csdn.net/csnd_ayo.重庆 重工.", chang_query);
// 
//     cout << chang_query.c_str() << endl;
//     getchar();
//     return 0;
// }

//给出一个字符串，找出其外层长度的组合
//{{'a','b'},{'d'},{'e','f'}} =>"ade","adf","bde","bdf"
//{{'a','b'},{'d'} =>"ad","bd"
void combineStr(vector<set<char>>& stringSet, vector<string>& res)
{
    for (auto& setChar: stringSet)
    {
        vector<string> tmpRes;
        for (auto i : setChar)
        {
            if (res.empty()) tmpRes.push_back(string(&i, 1));
            else for (auto &ori : res) tmpRes.push_back(ori + i);
        }
        res.clear();
        res = tmpRes;
    }
}

void FullCombinationImp(vector<string>& ovs, string& backStr, vector<set<char>>& vsc, int si)
{
    for (auto c:vsc[si])
    {
        backStr[si] = c;
        if (si == (vsc.size()-1)) ovs.push_back(backStr);
        else FullCombinationImp(ovs, backStr, vsc, si+1);
    }
}

void FullCombination(vector<set<char>>& vsc, vector<string>& ovs)
{
    string backStr;
    backStr.resize(vsc.size());
    FullCombinationImp(ovs, backStr, vsc, 0);
}
int main(int argc, char* argv[])
{
    long unsigned begin = GetTickCount64();
    int i = 0;
    while (i++< 1000)
    {
        char aa = 'a';
        string ss(&aa, 1);
        vector<set<char>> stringSet;
        set<char> tmp;
        tmp.insert('a');
        tmp.insert('b');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('1');
        tmp.insert('2');
        tmp.insert('3');
        tmp.insert('4');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('x');
        tmp.insert('y');
        tmp.insert('z');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('m');
        tmp.insert('n');
        tmp.insert('p');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('u');
        stringSet.push_back(tmp);
        vector<string> res;
        FullCombination(stringSet, res);
//         for (auto str : res)
//         {
//             cout << str << endl;
//         }
//         cout << res.size() << endl;
    }
    long unsigned end = GetTickCount64();

    cout << "last time: " << end - begin<< endl;

    i = 0;
    begin = GetTickCount64();
    while (i++ < 1000)
    {
        char aa = 'a';
        string ss(&aa, 1);
        vector<set<char>> stringSet;
        set<char> tmp;
        tmp.insert('a');
        tmp.insert('b');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('1');
        tmp.insert('2');
        tmp.insert('3');
        tmp.insert('4');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('x');
        tmp.insert('y');
        tmp.insert('z');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('m');
        tmp.insert('n');
        tmp.insert('p');
        stringSet.push_back(tmp);

        tmp.clear();
        tmp.insert('u');
        stringSet.push_back(tmp);
        vector<string> res;
        combineStr(stringSet, res);
//         for (auto str : res)
//         {
//             cout << str << endl;
//         }
//         cout << res.size() << endl;
    }
    end = GetTickCount64();

    cout << "last time: " << end - begin << endl;
    getchar();
    return 0;
}
/*
int main(int argc, char* argv[])
{

    
//     int index = 0;
//     while (index++ < 1000)
//     {
//     if (index%2 == 0)
//     {
//     int i;
//     int j;
//     if (argc == 100)
//     {
//     i = 0;
//     }
//     j++;
//     cout << i <<" &i= " << &i << " &j= " << &j << endl;
//     i = j;
//     }
//     else
//     {
//     int j;
//     int i;
// 
//     if (argc == 100)
//     {
//     i = 0;
//     }
//     j++;
//     cout <<"odd " << i << " &i= " << &i << " &j= " << &j << endl;
//     i = j;
//     }
// 
//     }
    
//     long long int a = 100;
//     char* str = nullptr;
//     printf("%s", str);

//    testMapFind();
    string str = "10100100111";
    size_t len = str.length();
    for (int index = (int)len - 3; index > 0; index -= 3)
        str.insert(index, ",");
    cout << str << endl;
    getchar();
    return 0;
}
*/