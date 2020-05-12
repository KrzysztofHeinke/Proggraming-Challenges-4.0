#ifndef CPP_VECTOR_HPP_
#define CPP_VECTOR_HPP_

#include <cassert>
#include <string>

/**
 * @brief Vector. Holds pointers to the beginning. Items are located in dynamically allocated array.
 * The array is extended if required. The size of the array doubled each time.
 * @tparam T Type of items.
 */
template<typename T>
class CVector {

public:

	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////

	/**
	 * @brief Iterator for vector container. It is a random access iterator.
	 * @tparam T Type of items.
	 */
	class CVectorIterator {
		/**
		 * @brief Pointer to data.
		 */
		T* mPtr;
	public:
		explicit CVectorIterator(CVector<T>* aPtr) :
				mPtr(aPtr->mBegin) {
		}

		/**
		 * @brief Constructor.
		 * @param aPtr Pointer to vector's array.
		 */
		CVectorIterator(T* aPtr) :
				mPtr(aPtr) {
		}
		bool operator==(const CVectorIterator &aObj) {
			return mPtr == aObj.mPtr;
		}
		bool operator!=(const CVectorIterator &aObj) {
			return !(mPtr == aObj.mPtr);
		}
		CVectorIterator& operator++() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			++mPtr;
			return *this;
		}
		bool operator>(CVectorIterator aObj) {
			return mPtr > aObj.mPtr;
		}
		bool operator>=(CVectorIterator aObj) {
			return mPtr >= aObj.mPtr;
		}

		bool operator<(CVectorIterator aObj) {
			return mPtr < aObj.mPtr;
		}
		bool operator<=(CVectorIterator aObj) {
			return mPtr <= aObj.mPtr;
		}
		CVectorIterator& operator--() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			--mPtr;
			return *this;
		}
		CVectorIterator operator+(CVectorIterator aIndex) const {
			int size = mPtr + aIndex.mPtr;
			return size;
		}

		CVectorIterator operator+(int aIndex) const {
			return CVectorIterator(mPtr + aIndex);
		}
		int operator-(CVectorIterator aIndex) const {
			int size = mPtr - aIndex.mPtr;
			return size;
		}
		CVectorIterator operator-(int aIndex) const {
			return CVectorIterator(mPtr - aIndex);
		}

		T& operator*() const {
			return *mPtr;
		}
		T* operator->() {
			return &mPtr;
		}
	};

	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////

	/**
	 * @brief Reverse iterator for vector container. It is a random access iterator.
	 * @tparam T Type of items.
	 */
	class CReverseVectorIterator {
		/**
		 * @brief Pointer to data.
		 */
		T* mPtr;
	public:
		/**
		 * @brief Constructor.
		 * @param aPtr Pointer to vector's array.
		 */

		explicit CReverseVectorIterator(CVector<T>* aPtr) :
				mPtr(aPtr->end()) {
		}

		/**
		 * @brief Constructor.
		 * @param aPtr Pointer to vector's array.
		 */
		CReverseVectorIterator(T* aPtr) :
				mPtr(aPtr) {
		}
		bool operator==(const CReverseVectorIterator &aObj) {
			return mPtr == aObj.mPtr;
		}
		bool operator!=(const CReverseVectorIterator &aObj) {
			return !(mPtr == aObj.mPtr);
		}
		bool operator>(CReverseVectorIterator aObj) {
			return mPtr > aObj.mPtr;
		}
		bool operator>=(CReverseVectorIterator aObj) {
			return mPtr >= aObj.mPtr;
		}

		bool operator<(CReverseVectorIterator aObj) {
			return mPtr < aObj.mPtr;
		}
		bool operator<=(CReverseVectorIterator aObj) {
			return mPtr <= aObj.mPtr;
		}
		CReverseVectorIterator& operator++() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			++mPtr;
			return *this;
		}
		CReverseVectorIterator& operator--() {
			if (mPtr == nullptr) {
				throw std::string("Out of range");
			}
			--mPtr;
			return *this;
		}
		CReverseVectorIterator operator+(CReverseVectorIterator aIndex) const {
			int size = aIndex.mPtr + mPtr;
			return size;
		}

		CReverseVectorIterator operator+(int aIndex) const {
			return CReverseVectorIterator(mPtr - aIndex);
		}
		int operator-(CReverseVectorIterator aIndex) const {
			int size = aIndex.mPtr - mPtr;
			return size;
		}
		CReverseVectorIterator operator-(int aIndex) const {
			return CReverseVectorIterator(mPtr + aIndex);
		}

		T& operator*() const {
			return *mPtr;
		}
		T* operator->() {
			return &mPtr;
		}

	};

	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////
	// /////////////////////////////////////////////////////////////////////

	using DIterator = CVectorIterator;
	using DReverseIterator = CReverseVectorIterator;

	/**
	 * @brief Constructor. The array is dynamically allocated for one object. Therefore one default
	 * constructor is called.
	 */
	CVector() :
			mBegin(nullptr), mSize(0), mCapacity(0) {
	}

	/**
	 * @brief Copy constructor.
	 * @param aObj Object to copy.
	 */
	CVector(const CVector& aObj) :
			mBegin(nullptr), mSize(0), mCapacity(0) {
		mBegin = new T[aObj.mCapacity];
		mSize = aObj.mSize;
		for (unsigned int i = 0; i < aObj.mSize; ++i) {
			mBegin[i] = aObj.mBegin[i];
		}
	}

	/**
	 * @brief Assignment operator
	 * @param aObj Object to copy.
	 * @return this object with copied content.
	 */
	CVector& operator=(const CVector& aObj) {
		delete[] mBegin;
		mBegin = new T[aObj.mCapacity];
		mSize = aObj.mSize;
		for (unsigned int i = 0; i < aObj.mSize; ++i) {
			mBegin[i] = aObj.mBegin[i];
		}
		return *this;
	}

	/**
	 * @brief Compares vectors.
	 * @param aObj Object to compare
	 * @return true if vectors contain equal object; otherwise false
	 */

	bool operator==(const CVector& aObj) {
		if (this->mSize == aObj.mSize) {
			for (unsigned int i = 0; i < mSize; ++i) {
				if (this->mBegin[i] != aObj.mBegin[i]) {
					return false;
				}
			}
			return true;
		} else {
			return false;
		}
	}

	/**
	 * @brief Compares vectors.
	 * @param aObj Object to compare
	 * @return false if vectors contain equal object; otherwise true
	 */
	bool operator!=(const CVector& aObj) {
		return !(*this == aObj);
	}

	/**
	 * @brief Destructor. Deallocates memory.
	 */
	~CVector() {
		delete[] mBegin;
	}

	/**
	 * @brief Returns the number of objects.
	 * Complexity: O(1) - because vector has size field.
	 * @return Number of objects.
	 */
	unsigned int size() const {
		return mSize;
	}

	/**
	 * @brief Adds an item at the end of the array.
	 * Complexity: O(n) - because in the worst case, when new array will be allocated, it has to copy all elements
	 * to new array. In most cases complexity will be O(1).
	 * @param aValue Item that will be added.
	 */
	void pushBack(const T& aValue) {
		if (mBegin == nullptr) {
			mCapacity = 1;
			mBegin = new T[mCapacity];
			mBegin[0] = aValue;
			++mSize;
		} else {
			if (mSize == mCapacity) {
				mCapacity *= 2;
				T* tmp = new T[mCapacity];
				for (int i = 0; i <= mSize; ++i) {
					if (mSize == i) {
						tmp[i] = aValue;
						continue;
					}
					tmp[i] = mBegin[i];
				}
				++mSize;
				delete[] mBegin;
				mBegin = tmp;
			} else {

				mBegin[mSize] = aValue;
				++mSize;
			}
		}
	}

	/**
	 * @brief Pops the last item from the array. It doesn't deallocate memory, so destructor of the object in array
	 * is not called.
	 * Complexity: O(1) - because access to any element of the array is constant.
	 * @return THe last item from the array.
	 */
	T popBack() {
		T tmp = mBegin[mSize - 1];
		mBegin[mSize - 1] = 0;
		--mSize;
		return tmp;
	}

	/**
	 * @brief Pushes item to the front of the array.
	 * Complexity: O(n) - All item have to be copied.
	 * @param aValue Item that will be added.
	 */
	void pushFront(const T& aValue) {

		if (mBegin == nullptr) {
			mCapacity = 1;
			mBegin = new T[mCapacity] { aValue };
			//mBegin[0] = aValue;
			++mSize;
		} else {
			if (mSize == mCapacity) {
				mCapacity *= 2;
				T* tmp = new T[mCapacity];
				tmp[0] = aValue;
				for (unsigned int i = 0; i < mSize; ++i) {
					tmp[i + 1] = mBegin[i];
				}
				++mSize;
				delete[] mBegin;
				mBegin = tmp;
			} else {
				T* tmp = new T[mCapacity];
				tmp[0] = aValue;
				for (unsigned int i = 0; i < mSize; ++i) {
					tmp[i + 1] = mBegin[i];
				}
				++mSize;
				delete[] mBegin;
				mBegin = tmp;
			}
		}
	}

	/**
	 * @brief Pops the first item from the array. There wouldn't be called destructor of object from array. All items
	 * except the first one will be copied to new location: the second object would be copied to the first item.
	 * Complexity: O(n) - All items have to copied.
	 * @return The first item from the array.
	 */
	T popFront() {

		if (mBegin == nullptr) {
			throw std::string("Empty Vector");
		}
		T tmp;
		for (unsigned int i = 0; i < mSize; ++i) {
			if (i == 0) {
				tmp = mBegin[i];
				continue;
			}
			mBegin[i - 1] = mBegin[i];
		}
		--mSize;
		return tmp;
	}

	/**
	 * @brief Checks if the vector contains given object.
	 * Complexity: O(n) - The worst case: the vector doesn't contain the given item, or it is on the last position.
	 * In both cases entire array have to be checked.
	 * @param aValue Item to find.
	 * @return True if the vector contains the given item; otherwise false.
	 */
	bool contains(const T& aValue) {
		for (unsigned int i = 0; i < mSize; ++i) {
			if (mBegin[i] == aValue) {
				return true;
			}
		}
		return false;
	}

	/**
	 * @brief Indicates if the vector is empty.
	 * Complexity: O(1) - because the vector contains size field.
	 * @return True if vector is empty; otherwise false.
	 */
	bool empty() const {
		return mSize == 0u;
	}

	/**
	 * @brief Returns pointer to the item at the given position.
	 * Complexity: O(1) - because access to any element of the array is constant.
	 * @param aIndex Index of item in the array.
	 * @return Pointer to the item at the given position or null if the index is greater than the size of vector.
	 */
	const T* get(unsigned int aIndex) const {
		if (aIndex < mSize) {
			return &mBegin[aIndex];
		}
		return nullptr;
	}

	/**
	 * @brief Inserts the given item on the given position. Items at the given position and after it are copied.
	 * Complexity: O(n) - because in the worst case, when aIndex is zero, all items in the array have to be copied to
	 * their new position.
	 * @param aIndex Position when the given item should be put.
	 * @param aValue Item to insert.
	 */
	void insert(unsigned int aIndex, const T& aValue) {

		if (aIndex > mCapacity) {
			throw std::string("Out of boundry");
		}
		++mSize;
		if (mSize >= mCapacity) {
			mCapacity *= 2;
			T* tmp = new T[mCapacity];
			for (unsigned int i = 0; i < mSize; ++i) {
				if (aIndex == i) {
					tmp[i] = aValue;
				}
				if (aIndex > i) {
					tmp[i] = mBegin[i];
				}
				if (aIndex < i) {
					tmp[i] = mBegin[i - 1];
				}
			}
			delete[] mBegin;
			mBegin = tmp;
		} else {
			T* tmp = new T[mCapacity];
			for (unsigned int i = 0; i < mSize; ++i) {
				if (aIndex == i) {
					tmp[i] = aValue;
				}
				if (aIndex > i) {
					tmp[i] = mBegin[i];
				}
				if (aIndex < i) {
					tmp[i] = mBegin[i - 1];
				}
			}
			delete[] mBegin;
			mBegin = tmp;
		}

	}

	/**
	 * @brief Returns a random access iterator that points to the beginning.
	 * @return Iterator to the beginning.
	 */
	DIterator begin() {
		return DIterator(mBegin);
	}

	/**
	 * @brief Returns a random access iterator that points to the item after the last one.
	 * @return Iterator to the item after the last one.
	 */
	DIterator end() {
		return DIterator(&mBegin[mSize]);
	}

	/**
	 * @brief Returns a reverse random access iterator that points to the last item.
	 * @return Reverse iterator to the last item.
	 */
	DReverseIterator rbegin() {
		return DReverseIterator(&mBegin[mSize - 1]);
	}

	/**
	 * @brief Returns a reverse random access iterator that points to the item before the first one.
	 * @return Reverse iterator to the item before the first one.
	 */
	DReverseIterator rend() {
		return DReverseIterator(mBegin - 1);
	}

private:

	/**
	 * @brief Pointer to the dynamically allocated array to which item will be put.
	 */
	T* mBegin;

	/**
	 * @brief Number of elements in the array.
	 */
	unsigned int mSize;

	/**
	 * @brief Size of allocated memory. Only if vector is full it is the same as mSize.
	 */
	unsigned int mCapacity;
};

#endif // CPP_VECTOR_HPP_
