#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// 1. 定义单链表节点
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 2. 核心算法：迭代反转链表
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

// 辅助函数：根据 vector 构建链表
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

// 辅助函数：打印链表
void printList(ListNode *head)
{
    cout << "[";
    ListNode *cur = head;
    while (cur != nullptr)
    {
        cout << cur->val;
        if (cur->next != nullptr)
            cout << ",";
        cur = cur->next;
    }
    cout << "]" << endl;
}

int main()
{
    string line;
    // 支持按行读取（兼容一行数据或多组测试用例）
    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        // 过滤非数字字符（兼容包含括号、逗号等输入格式）
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

        // 构建、反转并输出
        ListNode *head = buildList(nums);
        ListNode *newHead = reverseList(head);
        printList(newHead);
    }

    return 0;
}