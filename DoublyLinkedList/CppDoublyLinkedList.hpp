#ifndef CPP_DOUBLY_LINKED_LIST_HPP_
#define CPP_DOUBLY_LINKED_LIST_HPP_

#include <cassert> // assert
#include <string>

/**
 * @brief Doubly Linked List. Holds pointers to the beginning, end of the list and size of the list.
 * Therefore some operations have constant complexity.
 * @tparam T Type of items.
 */
template<typename T>
class CDoublyLinkedList
{
    template<typename TItem>
    class CDoublyLinkedListItem;


    /**
     * @brief List item. Each list's value is hold in this class.
     * It wraps value by adding pointer to next and previous element.
     * @tparam TItem Type of items stored in a list.
     */
    template<typename TItem>
    class CDoublyLinkedListItem
    {
    public:

        /**
         * @brief Constructor.
         * @param aValue Value.
         */
        explicit CDoublyLinkedListItem(const TItem& aValue)
        : mPrevious(nullptr)
        , mNext(nullptr)
        , mValue(aValue)
        {}

        /**
         * @brief Constructor.
         * @param aPrevious Pointer to previous item.
         * @param aNext Pointer to next item.
         * @param aValue Value.
         */
        CDoublyLinkedListItem(CDoublyLinkedListItem<TItem>* aPrevious,
                              CDoublyLinkedListItem<TItem>* aNext,
                              const TItem& aValue)
        : mPrevious(aPrevious)
          , mNext(aNext)
          , mValue(aValue)
        {}
    
        /**
         * @brief Pointer to previous Item.
         */
        CDoublyLinkedListItem<TItem>* mPrevious;

        /**
         * @brief Pointer to next item.
         */
        CDoublyLinkedListItem<TItem>* mNext;

        /**
         * @brief Value.
         */
        TItem mValue;
    };

public:
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////

    /**
     * @brief Iterator for DoublyLinked container. It is a random access iterator.
     * @tparam T Type of items.
     */
    class CDoublyLinkedListIterator
    {
        /**
         * @brief Pointer to data.
         */
        CDoublyLinkedListItem<T>* mPtr;
    public:

        /**
         * @brief Constructor.
         * @param aPtr Pointer to DoublyLinked's array.
         */
        explicit CDoublyLinkedListIterator(CDoublyLinkedListItem<T>* aPtr)
        : mPtr(aPtr)
        {
        }

		bool operator!=(const CDoublyLinkedListIterator &aObj) {
			return !(mPtr == aObj.mPtr);
		}

		bool operator==(const CDoublyLinkedListIterator &aObj) {
			return mPtr == aObj.mPtr;
		}

		CDoublyLinkedListIterator& operator++() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			mPtr = mPtr->mNext;
			return *this;
		}

		CDoublyLinkedListIterator operator+(int index) const {
			CDoublyLinkedListIterator temp(mPtr);
			for (int cnt = 0; cnt < index; ++cnt) {
				if (temp.mPtr == nullptr) {
					return temp;
				}
				temp.mPtr = temp.mPtr->mNext;
			}
			return temp;
		}

		CDoublyLinkedListIterator& operator--() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			mPtr = mPtr->mPrevious;
			return *this;
		}

		CDoublyLinkedListIterator operator-(int index) const {
			CDoublyLinkedListIterator temp(mPtr);
			for (int cnt = 0; cnt < index; ++cnt) {
				if (temp.mPtr == nullptr) {
					return temp;
				}
				temp.mPtr = temp.mPtr->mPrevious;
			}
			return temp;
		}
		T& operator*() const {
			return mPtr->mValue;
		}

		T* operator->() {

			return &mPtr->mValue;

		}


    };

    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////

    /**
     * @brief Reverse iterator for DoublyLinked container. It is a random access iterator.
     * @tparam T Type of items.
     */
    class CReverseDoublyLinkedListIterator
    {
        /**
         * @brief Pointer to data.
         */
        CDoublyLinkedListItem<T>* mPtr;
    public:
        /**
         * @brief Constructor.
         * @param aPtr Pointer to DoublyLinked's array.
         */
        explicit CReverseDoublyLinkedListIterator(CDoublyLinkedListItem<T>* aPtr) : mPtr(aPtr){}

		bool operator!=(const CReverseDoublyLinkedListIterator &aObj) {
			return !(mPtr == aObj.mPtr);
		}
		bool operator==(const CReverseDoublyLinkedListIterator &aObj) {
			return mPtr == aObj.mPtr;
		}
		CReverseDoublyLinkedListIterator& operator++() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			mPtr = mPtr->mPrevious;
			return *this;
		}
		CReverseDoublyLinkedListIterator operator+(int index) const {
			CReverseDoublyLinkedListIterator temp(mPtr);
			for (int cnt = 0; cnt < index; ++cnt) {
				if (temp.mPtr == nullptr) {
					return temp;
				}
				temp.mPtr = temp.mPtr->mPrevious;
			}
			return temp;
		}
		CReverseDoublyLinkedListIterator& operator--() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			mPtr = mPtr->mNext;
			return *this;
		}
		CReverseDoublyLinkedListIterator operator-(int index) const {
			CReverseDoublyLinkedListIterator temp(mPtr);
			for (int cnt = 0; cnt < index; ++cnt) {
				if (temp.mPtr == nullptr) {
					return temp;
				}
				temp.mPtr = temp.mPtr->mNext;
			}
			return temp;
		}
		T& operator*() const {
			return mPtr->mValue;
		}

		T* operator->() {

			return &mPtr->mValue;

		}


	};

    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////
    // /////////////////////////////////////////////////////////////////////

    using DIterator = CDoublyLinkedListIterator;
    using DReverseIterator = CReverseDoublyLinkedListIterator;
    
    /**
     * @brief Constructor. Initializes empty list.
     */
    CDoublyLinkedList()
    : mBegin(nullptr),
	  mLast(nullptr)
    {}

    /**
     * @brief Copy constructor.
     * @param aObj Object to copy.
     */
    CDoublyLinkedList(const CDoublyLinkedList<T>& aObj)
    : mBegin(nullptr),
	  mLast(nullptr)
    {

    	for(CDoublyLinkedListItem<T>* i = aObj.mBegin; i != nullptr; i = i->mNext)
    	{
    		this->pushBack(i->mValue);
    	}
    }

    /**
     * @brief Assignment operator
     * @param aObj Object to copy.
     * @return this object with copied content.
     */
	CDoublyLinkedList<T>& operator=(const CDoublyLinkedList<T>& aObj)
	{
		CDoublyLinkedListItem<T>* aaObj = aObj.mBegin;
		for (CDoublyLinkedListItem<T>* i = mBegin; i != nullptr; i = i->mNext)
		{
			if (i == nullptr)
			{
				mBegin = nullptr;
			}
			else
			{
				CDoublyLinkedListItem<T>* tmp = i->mNext;
				delete i;
				i = tmp;
			}
		}


		for (; aaObj != nullptr; aaObj = aaObj->mNext)
		{
			this->pushBack(aaObj->mValue);
		}
		return *this;
	}

    /**
     * @brief Compares vectors.
     * @param aObj Object to compare
     * @return true if vectors contain equal object; otherwise false
     */
    bool operator==(const CDoublyLinkedList<T>& aObj)
    {
    	CDoublyLinkedListItem<T>* thisObj = this->mBegin;
    	CDoublyLinkedListItem<T>* aaObj = aObj.mBegin;
    		for (; thisObj != nullptr && aaObj != nullptr;
    				thisObj = thisObj->mNext, aaObj = aaObj->mNext)
    		{
    			if (thisObj->mValue != aaObj->mValue)
    			{
    				return false;
    			}

    		}
    			return thisObj == nullptr && aaObj == nullptr;
    }

    /**
     * @brief Compares vectors.
     * @param aObj Object to compare
     * @return false if vectors contain equal object; otherwise true
     */
    bool operator!=(const CDoublyLinkedList<T>& aObj)
    {
        return !(*this == aObj);
    }

    /**
     * @brief Destructor. Deallocates memory.
     */
    ~CDoublyLinkedList()
    {
		for (CDoublyLinkedListItem<T>* i = mBegin; i != nullptr;)
		{
			CDoublyLinkedListItem<T>* tmp = i->mNext;
			delete i;
			i = tmp;
		}
    }
    
    /**
     * @brief Returns a number of items.
     * Complexity: O(n) - because it has to pass for all item.
     * @return Number of items.
     */
    unsigned int size() const
    {
		unsigned int result = 0;
		for (CDoublyLinkedListItem<T>* i = mBegin; i != nullptr; i = i->mNext)
		{
			result++;
		}
		return result;
    }
    
    /**
     * @brief Adds value to list.
     * Complexity: O(1) - because the list holds pointer to the last item.
     * @param aValue Value to add.
     */
	void pushBack(const T& aValue)
	{
		if(mBegin == nullptr)
		{
			mBegin = new CDoublyLinkedListItem<T>(nullptr, nullptr, aValue);
			mLast = mBegin;
		}
		else
		{
			mLast->mNext = new CDoublyLinkedListItem<T>(mLast, nullptr, aValue);
			mLast = mLast->mNext;
		}
	}
    
    /**
     * @brief Removes last item from list.
     * Complexity: O(n) - because it has to pass through all items
     * @return Last item from list.
     */
    T popBack()
    {
    	if( mBegin == nullptr)
    	{
    		throw std::string("");
    	}

		if (mBegin->mNext == nullptr)
		{
			const T tmp = mBegin->mValue;
			delete mBegin;
			mBegin = nullptr;
			mLast = nullptr;
			return tmp;
		}
		else
		{
			const T tmp = mLast->mValue;
			mLast = mLast->mPrevious;
			delete mLast->mNext;
			mLast->mNext = nullptr;
			return tmp;
		}

	}
    /**
     * @brief Puts new item at the beginning of the list.
     * Complexity: O(1) - because the list holds pointer to the beginning.
     * @param aValue Value.
     */
    void pushFront(const T& aValue)
    {
    	if(mBegin == nullptr)
    	{
    		this->pushBack(aValue);
    	}
    	else
    	{
    		CDoublyLinkedListItem<T>* newItem = new CDoublyLinkedListItem<T>(nullptr, mBegin, aValue);
    		mBegin->mPrevious = newItem;
    		mBegin = newItem;
    	}
    }
    
    /**
     * @brief Remove the first element from the list.
     * Complexity: O(1) - because list has pointer to beginning.
     * @return The first item from list.
     */
    T popFront()
    {
    	if (mBegin == nullptr)
    	{
    		throw std::string("");
    	}
		CDoublyLinkedListItem<T>* previousBegin = mBegin;
		const T tmp = mBegin->mValue;
		mBegin = mBegin->mNext;

		delete previousBegin;
		if( mBegin != nullptr)
		{
		mBegin->mPrevious = nullptr;
		}
		return tmp;
    }
    
    /**
     * @brief Checks the list contains object.
     * Complexity: O(n) - because it has to check all items. In the worst case entire list will be checked.
     * The worst case takes place if there isn't the value in the list or it is on the last position.
     * @param aValue Value to check.
     * @return true if list contains value, otherwise false.
     */
    bool contains(const T& aValue)
    {
		for (CDoublyLinkedListItem<T>* endPtr = mBegin; endPtr != nullptr; endPtr = endPtr->mNext)
		{
			if (endPtr->mValue == aValue)
			{
				return true;
			}
		}
		return false;
    }
    
    /**
     * @brief Indicates if the list empty.
     * Complexity: O(1)
     * @return true if list is empty, otherwise false.
     */
    bool empty() const
    {
        return mBegin == nullptr;
    }
 
    /**
     * @brief Get pointer to the value at given position. Complexity: O(n) - because it has to check all items in the worst case.
     * @param aIndex Position of value.
     * @return Pointer to value or null if there isn't value at given position.
     */
    const T* get(unsigned int aIndex) const
    {
		int i = 0;
		for (CDoublyLinkedListItem<T>* endPtr = mBegin; endPtr != nullptr; endPtr =
				endPtr->mNext, i++)
		{
			if (i == aIndex)
				return &endPtr->mValue;
		}
		return nullptr;
    }
    
    /**
     * @brief Inserts value at given position.
     * @param aIndex Position of value. Must be lower than size.
     * @param aValue Value to insert.
     */
    void insert(unsigned int aIndex, const T& aValue)
    {
    	if (aIndex == 0)
    			{
    				pushFront(aValue);
    				return;
    			}

    	CDoublyLinkedListItem<T> *i = mBegin;
    			for (unsigned int k = 0; k < aIndex && i != nullptr; i = i->mNext, ++k)
    			{
    				if (k == aIndex - 1)
    				{
    					i->mNext = new CDoublyLinkedListItem<T>(i,i->mNext, aValue);
    					if (i->mNext->mNext != nullptr)
    					{
    					i->mNext->mNext->mPrevious = i->mNext;
    					}
    					else
    					{
    						mLast = i->mNext;
    					}
    					return;
    				}
    			}
    			throw std::string("Wrong index");

    }

    /**
     * @brief Returns a random access iterator that points to the beginning.
     * @return Iterator to the beginning.
     */
    DIterator begin()
    {
    	if(mBegin == nullptr && mLast == nullptr)
    	{
    		return DIterator(nullptr);
    	}
        return DIterator(mBegin);
    }

    /**
     * @brief Returns a random access iterator that points to the item after the last one.
     * @return Iterator to the item after the last one.
     */
    DIterator end()
    {
    	if(mBegin == nullptr && mLast == nullptr)
    	{
    		return DIterator(nullptr);
    	}
        return DIterator(mLast);
    }

    /**
     * @brief Returns a reverse random access iterator that points to the last item.
     * @return Reverse iterator to the last item.
     */
    DReverseIterator rbegin()
    {
    	if(mBegin == nullptr && mLast == nullptr)
    	{
    		return DReverseIterator(nullptr);
    	}
        return DReverseIterator(mLast);
    }

    /**
     * @brief Returns a reverse random access iterator that points to the item before the first one.
     * @return Reverse iterator to the item before the first one.
     */
    DReverseIterator rend()
    {
    	if(mBegin == nullptr && mLast == nullptr)
    	{
    		return DReverseIterator(nullptr);
    	}
        return DReverseIterator(mBegin);
    }

private:
    
    /**
     * @brief Pointer to the first item of the list.
     */
    CDoublyLinkedListItem<T>* mBegin;
    CDoublyLinkedListItem<T>* mLast;
    
};

#endif //CPP_DOUBLY_LINKED_LIST_HPP_

