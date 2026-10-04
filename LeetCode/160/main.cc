#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

//定义单链表节点
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x), next(nullptr){}
};

//核心算法
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB){
    //判空
    if(!headA || !headB){
        return nullptr;
    }

    //使用双指针
    ListNode* pA = headA;
    ListNode* pB = headB;

    while(pA != pB){
        //如果pA为空，则将其指向headB，否则指向下一个节点
        pA = pA ? pA->next : headB;
        //如果pB为空，则将其指向headA，否则指向下一个节点
        pB = pB ? pB->next : headA;
    }
    return pA;
}

//辅助函数：根据数组构建单链表
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
    int intersectVal;
    if (!(cin >> intersectVal))
        return 0;

    int n, m;
    // 读取链表 A
    cin >> n;
    vector<int> listA_vals(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> listA_vals[i];
    }

    // 读取链表 B
    cin >> m;
    vector<int> listB_vals(m);
    for (int i = 0; i < m; ++i)
    {
        cin >> listB_vals[i];
    }

    int skipA, skipB;
    cin >> skipA >> skipB;

    // 3. 构造链表结构
    ListNode *headA = buildList(listA_vals);
    ListNode *headB = nullptr;

    if (intersectVal == 0)
    {
        // 不相交情况
        headB = buildList(listB_vals);
    }
    else
    {
        // 相交情况：B 前 skipB 个节点独立，之后直接指向 A 的相交节点
        ListNode dummyB(0);
        ListNode *curB = &dummyB;
        for (int i = 0; i < skipB; ++i)
        {
            curB->next = new ListNode(listB_vals[i]);
            curB = curB->next;
        }

        // 定位链表 A 的相交起始点
        ListNode *intersectNode = headA;
        for (int i = 0; i < skipA; ++i)
        {
            intersectNode = intersectNode->next;
        }

        // 拼接公共段
        curB->next = intersectNode;
        headB = dummyB.next;
    }

    // 4. 调用核心算法并输出
    ListNode *res = getIntersectionNode(headA, headB);
    if (res)
    {
        cout << "Intersected at '" << res->val << "'" << endl;
    }
    else
    {
        cout << "null" << endl;
    }

    return 0;
}