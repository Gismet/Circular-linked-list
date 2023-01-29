#include <iostream>
#include <exception>

/**
 * @brief  A circular linked list is a normal linked list with the exception that the last node points back to the head of the list.
 * @note This implementation is not thorough nor clear-cut. It is meant for education purposes
 */
class CircularLinkedList
{
private:
    struct ListNode
    {
        int data;
        ListNode *next;
        ListNode() : data(0), next(NULL) {}
        ListNode(int val) : data(val), next(NULL) {}
    };

public:
    CircularLinkedList();
    CircularLinkedList(const CircularLinkedList &obj);
    void insertAtTheBeginning(int val);
    void insertAtTheEnd(int val);
    void deleteNodeAtTheBeginning();
    void deleteNodeAtTheEnd();
    void insert(int val, int index);
    void deleteNode(int val);
    void printLinkedList();
    int length();

private:
    ListNode *_last; // at the end of the circular linked list (where we cycle back to the head node)
    int _list_size;
};

/**
 * @brief Construct a new Circular Linked List:: Circular Linked List object
 *
 */
CircularLinkedList::CircularLinkedList()
{
    _last = NULL;
    _list_size = 0;
}

/**
 * @brief Construct a copy of Circular Linked List object
 *
 * @param obj a circular linked list object
 */
CircularLinkedList::CircularLinkedList(const CircularLinkedList &obj)
{
    _last = NULL;
    ListNode *head = obj._last->next;
    _list_size = 0;
    do
    {
        insertAtTheEnd(head->data);
        _list_size++;
        head = head->next;
    } while (head != obj._last->next);
}

/**
 * @brief Inserts a new node at the beginning of the circular linked list
 *
 * @param val
 */
void CircularLinkedList::insertAtTheBeginning(int val)
{
    if (_last == NULL)
    {
        ListNode *newNode = new ListNode(val);
        newNode->next = newNode;
        _last = newNode;
    }
    else
    {
        ListNode *newNode = new ListNode(val); // create a new node;
        newNode->next = _last->next;           // make it point to the head
        _last->next = newNode;                 // make the last poiner point to new head
    }
    _list_size++;
}

/**
 * @brief Inserts a new node at the end of the circular linked list
 *
 * @param val
 */
void CircularLinkedList::insertAtTheEnd(int val)
{
    if (_last == NULL)
    {
        ListNode *newNode = new ListNode(val);
        newNode->next = newNode;
        _last = newNode;
    }
    else
    {
        ListNode *newNode = new ListNode(val); // create a new node
        newNode->next = _last->next;
        _last->next = newNode;
        _last = newNode;
    }
    _list_size++;
}

/**
 * @brief Removes a node at the beginning of the cicular linked list
 *
 */
void CircularLinkedList::deleteNodeAtTheBeginning()
{
    if (_last == NULL) // if the list is null, just return;
        return;

    _list_size--;
    if (_last->next == _last) // if the list has one node, it is the last node pointing to itself, make it null
    {
        _last = NULL;
        return;
    }
    ListNode *temp = _last->next;
    _last->next = temp->next;
    delete temp;
}

/**
 * @brief Removes a node at the end of the circular linked list
 *
 */
void CircularLinkedList::deleteNodeAtTheEnd()
{
    if (_last == NULL)
        return;

    _list_size--;
    if (_last->next == _last)
    {
        _last = NULL;
        return;
    }
    ListNode *loopPtr = _last->next;
    while (loopPtr->next != _last)
    {
        loopPtr = loopPtr->next;
    }
    ListNode *temp = _last;
    loopPtr->next = _last->next;
    _last = loopPtr;
    delete temp;
}

/**
 * @brief prints the circular linked list from the beginning to the end
 *
 */
void CircularLinkedList::printLinkedList()
{
    if (_last == NULL)
        return;

    ListNode *loopPtr = _last->next;
    std::cout << loopPtr->data << " ";
    loopPtr = loopPtr->next;
    while (loopPtr != _last->next)
    {
        std::cout << loopPtr->data << " ";
        loopPtr = loopPtr->next;
    }
}

/**
 * @brief Returns the  number of the nodes in the  list
 *
 * @return int
 */
int CircularLinkedList::length()
{
    return _list_size;
}

/**
 * @brief  Insert a new node based on an index in the list
 *
 * @param val  new node value
 * @param index  the index where the node will be inserted
 */
void CircularLinkedList::insert(int val, int index)
{
    if (index == 0)
    {
        insertAtTheBeginning(val);
        return;
    }
    // when the index is greater than or equal to the last index of the list
    // insert the node at the end
    if (index >= _list_size - 1)
    {
        insertAtTheEnd(val);
        return;
    }

    int count = 0;
    ListNode *loopPtr = _last->next;
    while (count < index - 1)
    {
        loopPtr = loopPtr->next;
    }
    ListNode *newNode = new ListNode(val);
    newNode->next = loopPtr->next;
    loopPtr->next = newNode;
    _list_size++;
}

/**
 * @brief Delete a node with which the given value matches
 *
 * @param val value of the node that will be deleted
 */
void CircularLinkedList::deleteNode(int val)
{
    if (_list_size == 0)
        return;
    ListNode *loopPtr = _last->next;
    if (loopPtr->data == val)
    {
        deleteNodeAtTheBeginning();
        return;
    }

    ListNode *prev = loopPtr;
    loopPtr = loopPtr->next;
    while (loopPtr != _last->next && loopPtr->data != val)
    {
        prev = loopPtr;
        loopPtr = loopPtr->next;
    }
    if (loopPtr == _last->next)
    {
        return;
    }
    else
    {
        ListNode *node = loopPtr;
        prev->next = loopPtr->next;
        delete node;
    }
}

int main()
{
    CircularLinkedList list;
    list.insertAtTheBeginning(6);
    list.insertAtTheBeginning(9);
    list.insertAtTheEnd(3);
    list.deleteNodeAtTheBeginning();
    list.insert(45, 0);
    list.insert(5, 1);
    list.deleteNode(6);

    CircularLinkedList list2(list);

    list.printLinkedList();
    std::cout << std::endl;
    list2.printLinkedList();

    return 0;
}