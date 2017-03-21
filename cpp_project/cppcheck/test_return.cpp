/*************************************************************************
	> File Name: test_return.cpp
	> Author: Miko Song
	> Mail: mikosong2013@gmail.com 
	> Created Time: Tue 21 Mar 2017 12:14:10 AM PDT
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::vector<int> visited(256, -1);
        int start = 0;
        int maxlength = 0;
        for(int i = 0; i < s.size(); i++)
        {
            if(visited[s[i]] != -1)
            {
                start = visited[s[i]] + 1;
            }
            visited[s[i]] = i;
            maxlength = std::max(maxlength, i - start + 1);
        }


    }
};

int main(int argc, char * argv[])
{
    std::string s1 = "abcabcbb";
    std::string s2 = "bbbbb";
    std::string s3 = "pwwkew";
    std::string s4 = "ab";
    std::string s5 = "aab";
    std::string s6 = "dvdf";
    Solution s;
    assert(3==s.lengthOfLongestSubstring(s1));
    assert(1==s.lengthOfLongestSubstring(s2));
    assert(3==s.lengthOfLongestSubstring(s3));
    assert(2==s.lengthOfLongestSubstring(s4));
    assert(2==s.lengthOfLongestSubstring(s5));
    assert(3==s.lengthOfLongestSubstring(s6));



    return 0;

} 

