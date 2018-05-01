#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    //771. Jewels and Stones
    //https://leetcode.com/problems/jewels-and-stones/description/
    int numJewelsInStones(string J, string S) {
        set<char> JewelsSet;
        for (auto j : J)
            JewelsSet.insert(j);
        int num = 0;
        for (auto s : S)
        {
            if (JewelsSet.find(s) != JewelsSet.end())
            {
                num++;
            }

        }
        return num;
    }

    //804. Unique Morse Code Words
    //https://leetcode.com/problems/unique-morse-code-words/description/
    int uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morseVect = { ".-","-...","-.-.","-..",".","..-.","--.",
            "....","..",".---","-.-",".-..","--","-.",
            "---",".--.","--.-",".-.","...","-","..-",
            "...-",".--","-..-","-.--","--.." };
        set<string> morseSet;
        for (auto& str : words)
        {
            string morseStr;
            for (auto i : str)
            {
                morseStr += morseVect[i - 'a'];
            }
            if (!morseStr.empty())
            {
                morseSet.insert(morseStr);
            }
        }
        return morseSet.size();
    }

    //461. Hamming Distance
    //https://leetcode.com/problems/hamming-distance/description/
    int hammingDistance(int x, int y) {
        int dist = 0;
        unsigned  val = x ^ y;

        // Count the number of bits set
        while (val != 0)
        {
            // A bit is set, so increment the count and clear the bit
            dist++;
            val &= val - 1;
        }

        // Return the number of differing bits
        return dist;
    }

    //657. Judge Route Circle
    //https://leetcode.com/submissions/detail/151706850/
    bool judgeCircle(string moves) {
        int left = 0, right = 0, up = 0, down = 0;
        for (auto i : moves)
        {
            switch (i) {
            case 'L':
                left++;
                break;
            case 'R':
                right++;
                break;
            case 'U':
                up++;
                break;
            case 'D':
                down++;
                break;
            default:
                break;
            }
        }
        return (left == right) && (up == down);
    }

    //617. Merge Two Binary Trees
    //https://leetcode.com/problems/merge-two-binary-trees/description/
    /**
    * Definition for a binary tree node.
    */
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr)
            return t2;
        else if (t2 == nullptr)
            return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }

    /*
    88. Lowest Common Ancestor of a Binary Tree
    https://www.lintcode.com/zh-cn/problem/lowest-common-ancestor-of-a-binary-tree/
    * @param root: The root of the binary search tree.
    * @param A: A TreeNode in a Binary.
    * @param B: A TreeNode in a Binary.
    * @return: Return the least common ancestor(LCA) of the two nodes.
    */
    TreeNode *dfs(TreeNode * root, TreeNode * A, TreeNode * B) {
        if ((root == NULL) || (root == A) || (root == B))
        {
            return root;
        }
        TreeNode *left = dfs(root->left, A, B);
        TreeNode *right = dfs(root->right, A, B);
        if ((left!=NULL)&&(right!=NULL))
        {
            return root;
        }
        else {
            return left==NULL ? right : left;
        }
    }
    TreeNode * lowestCommonAncestor(TreeNode * root, TreeNode * A, TreeNode * B) {
        // write your code here
        return dfs(root, A, B);
    }

    //728. Self Dividing Numbers
    //https://leetcode.com/problems/self-dividing-numbers/description/
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> selfDividingNumbersVec;
        for (int i = left; i <= right; i++)
        {
            int dec = i;
            int res = 0;
            bool selfDividing = false;
            while (res = (dec % 10))
            {
                if (i%res != 0)
                {
                    selfDividing = false;
                    break;
                }
                selfDividing = true;
                dec = dec / 10;
            }
            if (selfDividing && dec == 0)
                selfDividingNumbersVec.push_back(i);
        }
        return selfDividingNumbersVec;
    }

    //561. Array Partition I
    //https://leetcode.com/problems/array-partition-i/description/
    int arrayPairSum(vector<int>& nums) {
        int sum = 0;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i += 2)
            sum += nums[i];
        return sum;
    }

    //811. Subdomain Visit Count
    //https://leetcode.com/problems/subdomain-visit-count/description/
    vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> m;
        for (const auto& str : cpdomains)
        {
            int i = str.find(" ");
            int num = stoi(str.substr(0, i));
            string domain = str.substr(i + 1, str.size() - i - 1);
            for (int n = domain.size() - 1; n >= 0; n--)
            {
                if (domain[n] == '.') m[domain.substr(n + 1, domain.size() - n - 1)] += num;
                else if (n == 0) m[domain] += num;
            }

        }
        vector<string> v;
        for (const auto& e : m) v.push_back(to_string(e.second) + " " + e.first);
        return v;
    }

    //821. Shortest Distance to a Character
    //https://leetcode.com/problems/shortest-distance-to-a-character/description/
    int nearestIndex(string S, char C, int index) {
        int left = index, right = index;
        if (S[index] == C) return index;
        while (left >= 0 || right < S.size())
        {
            if (left >= 0 && S[left] == C) { return left; }
            if (right < S.size() && S[right] == C) { return right; }
            left--;
            right++;
        }
        return -1;
    }

    vector<int> shortestToChar(string S, char C) {
        vector<int> ret;
        for (int i = 0; i < S.size(); i++)
        {
            int index = nearestIndex(S, C, i);
            ret.push_back(abs(i - index));
        }
        return ret;
    }

    //476. Number Complement
    //https://leetcode.com/problems/number-complement/description/
    int findComplement(int num) {
        unsigned int mask = ~0;
        while (num & mask) mask <<= 1;
        return  ~num&~mask;

    }

    //344. Reverse String
    //https://leetcode.com/problems/reverse-string/description/
    string reverseString(string s) {
        int index = 0;
        int len = s.size();
        while (index < len / 2) {
            std::swap(s[index], s[len - 1 - index]);
            index++;
        }
        return s;
    }

    //557. Reverse Words in a String III
    //https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
    string reverseWords(string s) {
        size_t front = 0;
        for (int i = 0; i <= s.length(); ++i) {
            if (i == s.length() || s[i] == ' ') {
                reverse(&s[front], &s[i]);
                front = i + 1;
            }
        }

        return s;
    }

    //500. Keyboard Row
    //https://leetcode.com/problems/keyboard-row/description/
    vector<string> findWords(vector<string>& words) {
        vector<string> ret;
        vector<string> TabVect{ "QWERTYUIOPqwertyuiop","ASDFGHJKLasdfghjkl","ZXCVBNMzxcvbnm" };
        for (int index = 0; index < TabVect.size(); index++)
        {
            for (auto& items : words)
            {
                int count = 0;
                for (auto ch : items)
                {
                    if (TabVect[index].find(ch) != std::string::npos)
                    {
                        count++;
                    }
                }
                if (count == items.size())
                {
                    ret.push_back(items);
                }
            }
        }
        return ret;
    }

    //669. Trim a Binary Search Tree
    //https://leetcode.com/problems/trim-a-binary-search-tree/description/
    struct TreeNode* trimBST(struct TreeNode* root, int L, int R) {
        bool notFound = 0;
        if (root)
        {
            if (root->val < L) {
                root = root->right;
                notFound = 1;
            }
            else if (root->val > R) {
                root = root->left;
                notFound = 1;
            }

            if (notFound) {
                root = trimBST(root, L, R);
            }

            if (root) {
                root->left = trimBST(root->left, L, R);
                root->right = trimBST(root->right, L, R);
            }
        }
        return root;
    }

    //682. Baseball Game
    //https://leetcode.com/problems/baseball-game/description/
    int calPoints(vector<string>& ops) {
        stack<int> scoreValidStack;
        int score = 0;
        for (auto& it : ops) {
            if (it == "C")
            {
                score -= scoreValidStack.top();
                scoreValidStack.pop();
            }
            else if (it == "D")
            {
                score += 2 * scoreValidStack.top();
                scoreValidStack.push(2 * scoreValidStack.top());
            }
            else if (it == "+")
            {
                int first = scoreValidStack.top();
                scoreValidStack.pop();
                int second = scoreValidStack.top();
                scoreValidStack.pop();
                int addScore = first + second;
                scoreValidStack.push(second);
                scoreValidStack.push(first);
                scoreValidStack.push(addScore);
                score += addScore;
            }
            else {
                int getScore = stoi(it);
                score += getScore;
                scoreValidStack.push(getScore);
            }
        }

        return score;
    }

    //575. Distribute Candies
    //https://leetcode.com/problems/distribute-candies/description/
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> kinds;
        for (int kind : candies) {
            kinds.insert(kind);
        }
        return min(kinds.size(), candies.size() / 2);
    }

    //412. Fizz Buzz
    //https://leetcode.com/problems/fizz-buzz/description/
    vector<string> fizzBuzz(int n) {
        vector<string> ret;
        for (int index = 1; index <= n; index++)
        {
            if ((index % 3 == 0) && (index % 5 == 0))
            {
                ret.push_back("FizzBuzz");
            }
            else if (index % 3 == 0)
            {
                ret.push_back("Fizz");
            }
            else if (index % 5 == 0)
            {
                ret.push_back("Buzz");
            }
            else
            {
                ret.push_back(std::to_string(index));
            }
        }
        return ret;
    }

    //12. 带最小值操作的栈 
    //https://www.lintcode.com/zh-cn/problem/min-stack/


    //463. Island Perimeter
    //https://leetcode.com/problems/island-perimeter/description/
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int total = 0;
        for (auto& items : grid)
        {
            for (auto& item : items)
            {
                if (item == 1)
                {
                    total++;
                }
            }
        }
        total *= 4;
        int adjecent = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j])
                {
                    if ((i - 1 >= 0) && grid[i - 1][j])
                    {
                        adjecent++;
                    }
                    if ((j - 1 >= 0) && grid[i][j - 1])
                    {
                        adjecent++;
                    }
                }
            }
        }
        total -= (adjecent * 2);
        return total;
    }

    /**
    * @param num: A list of integers
    * @return: An integer
    124. 最长连续序列
    https://www.lintcode.com/zh-cn/problem/longest-consecutive-sequence/
    */
    int longestConsecutive(vector<int> &num) {
        // write your code here
        set<int> seqSet;
        vector<int> seqVect;
        for (auto i : num)
            seqSet.insert(i);
        for (auto i : seqSet)
        {
            seqVect.push_back(i);
        }
        int longest = 0;
        int pre = 1;
        for (int it =0; it < seqVect.size();it++)
        {
            if (it + 1 <= seqVect.size() - 1)
            {
                if (seqVect[it] +1 == seqVect[it + 1] )
                {
                    pre++;
                }
                else
                {
                    if (pre>longest)
                    {
                        longest = pre;
                    }
                    pre = 1;
                }
            }
            else
            {
                if (pre > longest)
                {
                    longest = pre;
                }
            }
        }
        return longest;
    }

};
//12. 带最小值操作的栈 
//https://www.lintcode.com/zh-cn/problem/min-stack/
class MinStack {
public:
    MinStack() {
        // do intialization if necessary
    }

    /*
    * @param number: An integer
    * @return: nothing
    */
    void push(int number) {
        // write your code here
        st.push_back(number);
        if ((mins.size() > 0) && (number > mins.back()))
        {
            mins.push_back(mins.back());
        }
        else {
            mins.push_back(number);
        }
    }

    /*
    * @return: An integer
    */
    int pop() {
        // write your code here
        int ret = st.back();
        st.pop_back();
        mins.pop_back();
        return ret;
    }

    /*
    * @return: An integer
    */
    int min() {
        // write your code here
        return mins.back();

    }
    vector<int> st;
    vector<int> mins;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    Solution ps;
    //vector<vector<int>> input{ {0, 1, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0 },{1, 1, 0, 0} };
    //int ret = ps.islandPerimeter(input);
    //cout << ret << endl;

//     MinStack ms;
//     ms.push(1);
//     cout << ms.pop() << endl;
//     ms.push(2);
//     ms.push(3);
//     cout << ms.min() << endl;
//     ms.push(1);
//     cout << ms.min() << endl;
    vector<int> test{ 9,1,-3,2,4,8,3,-1,6,-2,-4,7 };
    int ret = ps.longestConsecutive(test);
    cout << ret << endl;
    
    return 0;
}