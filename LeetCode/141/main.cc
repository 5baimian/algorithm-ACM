#include "iostream"
#include "vector"
#include "sstream"
#include "string"

using namespace std;

// 1. 定义链表节点
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 2. 核心算法：快慢指针判断是否有环
bool hasCycle(ListNode *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (slow != fast)
    {
        if (fast == nullptr || fast->next == nullptr)
        {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return true;
}

// 辅助函数：根据节点数组和 pos 构造链表（修正了 vector 存放的指针类型）
ListNode *buildListWithCycle(const vector<int> &nums, int pos)
{
    if (nums.empty())
        return nullptr;

    // 此处必须是 ListNode* 类型的数组
    vector<ListNode*> nodes;
    for (int x : nums)
    {
        nodes.push_back(new ListNode(x));
    }

    // 串联所有节点
    for (size_t i = 0; i + 1 < nodes.size(); ++i)
    {
        nodes[i]->next = nodes[i + 1];
    }

    // 若 pos >= 0，尾节点指向对应下标的节点成环
    if (pos >= 0 && pos < static_cast<int>(nodes.size()))
    {
        nodes.back()->next = nodes[pos];
    }

    return nodes[0];
}

int main()
{
    string line;
    // 逐行读取输入
    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        // 如果输入的整行包含 "pos"，说明是 "head = [3,2,0,-4], pos = 1" 这种单行形式
        if (line.find("pos") != string::npos)
        {
            size_t pos_idx = line.find("pos");
            string list_part = line.substr(0, pos_idx);
            string pos_part = line.substr(pos_idx);

            // 提取数组
            for (char &c : list_part)
            {
                if (c == '[' || c == ']' || c == ',' || c == '=')
                    c = ' ';
            }
            stringstream ss(list_part);
            string temp;
            vector<int> nums;
            int val;
            while (ss >> temp)
            {
                if (temp == "head")
                    continue;
                try
                {
                    nums.push_back(stoi(temp));
                }
                catch (...)
                {
                }
            }

            // 提取 pos
            for (char &c : pos_part)
            {
                if (c == '=')
                    c = ' ';
            }
            stringstream ss_pos(pos_part);
            string dummy;
            int pos = -1;
            ss_pos >> dummy >> pos; // 跳过 "pos"，读取数值

            ListNode *head = buildListWithCycle(nums, pos);
            cout << (hasCycle(head) ? "true" : "false") << endl;
        }
        else
        {
            // 普通两行形式：第一行数组，第二行 pos
            for (char &c : line)
            {
                if (c == '[' || c == ']' || c == ',')
                    c = ' ';
            }
            stringstream ss(line);
            vector<int> nums;
            int val;
            while (ss >> val)
            {
                nums.push_back(val);
            }

            int pos = -1;
            if (cin >> pos)
            {
                string dummy;
                getline(cin, dummy); // 消费行末回车
                ListNode *head = buildListWithCycle(nums, pos);
                cout << (hasCycle(head) ? "true" : "false") << endl;
            }
        }
    }

    return 0;
}