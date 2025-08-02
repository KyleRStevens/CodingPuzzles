#pragma once

struct ListNode
{
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// LeetCode #2: Add Two Numbers
class Solution_AddTwoNumbers
{
public:
    ListNode* addTwoNumbers(ListNode* pLn1, ListNode* pLn2)
    {
        int carry = 0;
        ListNode* pAnswer = nullptr;
        ListNode* pPreviousDigit = nullptr;

        // Go through each digit place (one's place, ten's place, etc.) and add the numbers, keeping track of a carry
        while (pLn1 != nullptr || pLn2 != nullptr)
        {
            // Retrieve number 1
            int number1 = 0;
            if (pLn1)
            {
                number1 = pLn1->val;

                // Incriment the digit pointer while we're here
                pLn1 = pLn1->next;
            }

            // Retrieve number 2
            int number2 = 0;
            if (pLn2)
            {
                number2 = pLn2->val;

                // Incriment the digit pointer while we're here
                pLn2 = pLn2->next;
            }

            // Add the numbers
            int currentDigit = number1 + number2 + carry;

            // Adjust for carry
            if (currentDigit >= 10)
            {
                currentDigit -= 10; // Same as (currentDigit %= 10) but slightly faster
                carry = 1;
            }
            else
            {
                carry = 0;
            }

            // Save digit to answer (and set pPreviousDigit to the current digit because it is about to be the previous)
            if (pPreviousDigit)
            {
                pPreviousDigit->next = new ListNode(currentDigit); // Caller handles memory
                pPreviousDigit = pPreviousDigit->next;
            }
            else
            {
                // First digit (or error)
                pAnswer = new ListNode(currentDigit); // Caller handles memory
                pPreviousDigit = pAnswer;
            }
        }

        // After everything, check the carry to see if we need to add one more digit
        if (carry != 0)
        {
            pPreviousDigit->next = new ListNode(1); // Caller handles memory
        }

        // Return
        return pAnswer;
    }

    void Test()
    {
        std::vector<ListNode> addTwoNumbersNumber1{ 2, 4, 3 };
        std::vector<ListNode> addTwoNumbersNumber2{ 5, 6, 4 };
        for (int i = 0; i < 2; ++i)
        {
            addTwoNumbersNumber1[i].next = &addTwoNumbersNumber1[i + 1];
            addTwoNumbersNumber2[i].next = &addTwoNumbersNumber2[i + 1];
        }
        auto addTwoNumbersResult = addTwoNumbers(&addTwoNumbersNumber1[0], &addTwoNumbersNumber2[0]);
    }
};