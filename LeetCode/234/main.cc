#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// 1. 定义链表节点
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 辅助函数：反转单链表
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *curr = head;
    while (curr != nullptr)
    {
        ListNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

// 2. 核心算法：快慢指针 + 后半部分反转比较 (时间 O(n)，空间 O(1))
bool isPalindrome(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
        return true;

    // 快慢指针找前半部分的尾节点
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // 反转后半部分链表
    ListNode *secondHalfStart = reverseList(slow->next);

    // 双指针比对值
    ListNode *p1 = head;
    ListNode *p2 = secondHalfStart;
    bool result = true;
    while (result && p2 != nullptr)
    {
        if (p1->val != p2->val)
        {
            result = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }

    // 恢复链表（保持原链表结构完整）
    slow->next = reverseList(secondHalfStart);

    return result;
}

// 辅助函数：由动态数组构建链表
ListNode *buildList(const vector<int> &nums)
{
    if (nums.empty())
        return nullptr;
    ListNode dummy(0);
    ListNode *cur = &dummy;
    for (int x : nums)
    {
        cur->next = new ListNode(x);
        cur = cur->next;
    }
    return dummy.next;
}

int main()
{
    string line;
    // 逐行读取，支持多组用例输入
    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        // 统一过滤掉方括号、逗号等符号，兼容 "[1,2,2,1]" 或 "1 2 2 1"
        for (char &c : line)
        {
            if (c == '[' || c == ']' || c == ',')
            {
                c = ' ';
            }
        }

        stringstream ss(line);
        vector<int> nums;
        int val;
        while (ss >> val)
        {
            nums.push_back(val);
        }

        // 构建链表并运行算法
        ListNode *head = buildList(nums);
        if (isPalindrome(head))
        {
            cout << "true" << endl;
        }
        else
        {
            cout << "false" << endl;
        }
    }

    return 0;
}