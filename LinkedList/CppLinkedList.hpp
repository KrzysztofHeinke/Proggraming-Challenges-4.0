#ifndef CPP_LINKED_LIST_HPP_
#define CPP_LINKED_LIST_HPP_

#include <cassert>
#include <cstddef>
#include <string>
/**
 * @brief Linked List. Holds pointers to the beginning. Each item has a pointer to the next one.
 * @tparam T Type of items.
 */
template<typename T>
class CLinkedList
{
	template<typename TItem>
	class CLinkedListItem;

	/**
	 * @brief List item. Each list's value is hold in this class.
	 * It wraps value by adding pointer to next element
	 * @tparam TItem Type of items stored in a list.
	 */
	template<typename TItem>
	class CLinkedListItem
	{
	public:
		CLinkedListItem(CLinkedListItem<T>* aNext, const T& aValue) :
				mNext(aNext), mValue(aValue)
		{
		}
		CLinkedListItem<TItem> *mNext;
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
	class CLinkedListIterator
	{
		/**
		 * @brief Pointer to data.
		 */
		CLinkedListItem<T>* mPtr;
	public:

		/**
		 * @brief Constructor.
		 * @param aPtr Pointer to DoublyLinked's array.
		 */
		explicit CLinkedListIterator(CLinkedListItem<T>* aPtr) :
				mPtr(aPtr)
		{
		}
		bool operator!=(const CLinkedListIterator &aObj) {
			return !(mPtr == aObj.mPtr);
		}

		bool operator==(const CLinkedListIterator &aObj) {
			return mPtr == aObj.mPtr;
		}
		CLinkedListIterator& operator++() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			mPtr = mPtr->mNext;
			return *this;
		}
		T operator*() const
		{
			return (mPtr->mValue);
		}
	};

	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////

	using DIterator = CLinkedListIterator;

	/**
	 * @brief Constructor. Initializes empty list.
	 */
	CLinkedList() :
			mBegin(nullptr)
	{

	}

	/**
	 * @brief Copy constructor.
	 * @param aObj Object to copy.
	 */
	CLinkedList(const CLinkedList<T>& aObj) :
			mBegin(nullptr)
	{
		CLinkedListItem<T>* aaObj = aObj.mBegin;
		for (; aaObj != nullptr; aaObj = aaObj->mNext)
		{
			this->pushBack(aaObj->mValue);
		}
	}

	/**
	 * @brief Assignment operator
	 * @param aObj Object to copy.
	 * @return this object with copied content.
	 */
	CLinkedList<T>& operator=(const CLinkedList<T>& aObj)
	{
		CLinkedListItem<T>* aaObj = aObj.mBegin;

		for (CLinkedListItem<T>* i = mBegin; i != nullptr; i = i->mNext)
		{
			if (i == nullptr)
			{
				mBegin = nullptr;
			}
			else
			{
				CLinkedListItem<T>* tmp = i->mNext;
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
	bool operator==(const CLinkedList<T>& aObj)
	{
		CLinkedListItem<T>* thisObj = this->mBegin;
		CLinkedListItem<T>* aaObj = aObj.mBegin;
		for (; thisObj != nullptr && aaObj != nullptr;
				thisObj = thisObj->mNext, aaObj = aaObj->mNext)
		{
			if (thisObj->mValue != aaObj->mValue)
			{
				return false;
			}
		}
		return true;
	}

	/**
	 * @brief Compares vectors.
	 * @param aObj Object to compare
	 * @return false if vectors contain equal object; otherwise true
	 */
	bool operator!=(const CLinkedList<T>& aObj)
	{
		return !(*this == aObj);
	}

	/**
	 * @brief Destructor. Deallocates memory.
	 */
	~CLinkedList()
	{
		for (CLinkedListItem<T>* i = mBegin; i != nullptr;)
		{
			CLinkedListItem<T>* tmp = i->mNext;
			delete i;
			i = tmp;
		}
	}

	/**
	 * @brief Returns a number of items.
	 * Complexity: O(n) - because it has to pass through all items.
	 * @return Number of items.
	 */
	unsigned int size() const
	{
		unsigned int result = 0;
		for (CLinkedListItem<T>* i = mBegin; i != nullptr; i = i->mNext)
		{
			result++;
		}
		return result;
	}

	/**
	 * @brief Adds value to list.
	 * Complexity: O(n) - because it has to pass through all items.
	 * @param aValue Value to add.
	 */
	void pushBack(const T& aValue)
	{
		CLinkedListItem<T>* endPtr;
		if (mBegin == nullptr)
		{
			mBegin = new CLinkedListItem<T>(nullptr, aValue);
		}
		else
		{
			for (endPtr = mBegin; endPtr->mNext != nullptr;
					endPtr = endPtr->mNext);
			endPtr->mNext = new CLinkedListItem<T>(nullptr, aValue);
		}
	}

	/**
	 * @brief Removes last item from list.
	 * Complexity: O(n) - because it has to pass through all items.
	 * @return Last item from list.
	 */
	T popBack()
	{
		if (mBegin != nullptr)
		{
			if (mBegin->mNext == nullptr)
			{
				T tmp1 = mBegin->mValue;
				delete mBegin;
				mBegin = nullptr;
				return tmp1;
			}
			else
			{
				CLinkedListItem<T>* beforeLast;
				for (beforeLast = mBegin; beforeLast->mNext->mNext != nullptr;
						beforeLast = beforeLast->mNext)
;
				T tmp = beforeLast->mNext->mValue;
				delete beforeLast->mNext;
				beforeLast->mNext = nullptr;
				return tmp;
			}
		}
		else
		{
			throw std::string("");
		}
	}

	/**
	 * @brief Puts new item at the beginning of the list.
	 * Complexity: O(1) - because the list holds pointer to the beginning.
	 * @param aValue Value.
	 */
	void pushFront(const T& aValue)
	{
		CLinkedListItem<T>* newBegin = new CLinkedListItem<T>(mBegin, aValue);
		mBegin = newBegin;
	}

	/**
	 * @brief Remove the first element from the list.
	 * Complexity: O(1) - because list has pointer to beginning.
	 * @return The first item from list.
	 */
	T popFront()
	{
		CLinkedListItem<T>* previousBegin = mBegin;
		T tmp = mBegin->mValue;

		mBegin = mBegin->mNext;
		delete previousBegin;
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
		for (CLinkedListItem<T>* endPtr = mBegin; endPtr; endPtr =
				endPtr->mNext)
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
	 * @brief Get pointer to the value at given position.
	 * Complexity: O(n) - because it has to check all items.
	 * @param aIndex Position of value.
	 * @return Pointer to value or null if there isn't value at given position.
	 */
	const T* get(unsigned int aIndex)
	{
		int i = 0;
		for (CLinkedListItem<T>* endPtr = mBegin; endPtr != nullptr; endPtr =
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

		CLinkedListItem<T> *i = mBegin;
		for (unsigned int k = 0; k < aIndex && i != nullptr; i = i->mNext, ++k)
		{
			if (k == aIndex - 1)
			{
				i->mNext = new CLinkedListItem<T>(i->mNext, aValue);
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
		return DIterator(mBegin);
	}

	/**
	 * @brief Returns a random access iterator that points to the item after the last one.
	 * @return Iterator to the item after the last one.
	 */
	DIterator end()
	{
		return DIterator(nullptr);
	}

private:

	/**
	 * @brief Pointer to the first item of the list.
	 */
	CLinkedListItem<T>* mBegin;
};

#endif // CPP_LINKED_LIST_HPP_
