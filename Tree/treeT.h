/*
 * treeT.h
 *
 *  Created on: Oct 25, 2018
 *      Author: algorithm
 */

#ifndef TREET_H_
#define TREET_H_

#include <cassert>
#include <cstddef>
#include <iostream>
#include <memory>

/**
 * @brief Binary tree. Collects data in tree structure. Object values are compared using operator <
 * @tparam T
 */
template<typename T>
class CTree {

	template<typename TItem>
	class CTreeItem;

	/**
	 * @brief Item wrapper. Each value is wrapped in this class.
	 * @tparam TItem Type of stored item.
	 */
	template<typename TItem>
	class CTreeItem {
	public:
		explicit CTreeItem(const TItem& aValue) :
				mLeft(nullptr), mRight(nullptr), mValue(aValue), mParent(
						nullptr) {
		}
		CTreeItem(CTreeItem<TItem>* aLeft, CTreeItem<TItem>* aRight,
				const TItem& aValue, CTreeItem<TItem> *aParent) :
				mLeft(aLeft), mRight(aRight), mValue(aValue), mParent(aParent) {
		}
		std::weak_ptr<CTreeItem<TItem>> mParent;
		std::shared_ptr<CTreeItem<TItem>> mLeft;
		std::shared_ptr<CTreeItem<TItem>> mRight;
		TItem mValue;
	};

public:
	/**
	 * @brief Constructor.
	 */
	CTree() :
			mBegin(nullptr), mSize(0) {
		// @TODO
	}

	/**
	 * @brief Destructor. Deallocates memory.
	 */
	~CTree() {
		// @TODO
	}

	/**
	 * @brief Returns number of elements.
	 * @return Number of elements.
	 */
	unsigned int size() const {
		return mSize;  // @TODO
	}

	/**
	 * @brief Indicates if tree is empty.
	 * @return True if tree is empty; otherwise false.
	 */
	bool empty() const {
		return mBegin == nullptr; //@TODO
	}

	/**
	 * @brief Adds value to tree.
	 * Complexity: O(N) - the worst case is when all items are left/right children nodes of their parents. Therefore
	 * all items have to be checked if the new value is the lowest/greatest. Typical case when tree is close to be balanced, complexity is O(log N).
	 * @param aValue Value to add.
	 * @return True if value was added; false if value exists in tree.
	 */
	bool push(const T& aValue) {
		std::shared_ptr<CTreeItem<T>> ptr = mBegin;
		if (ptr == nullptr) {
			ptr = new CTreeItem<T>(nullptr, nullptr, aValue, nullptr);
			mSize++;
			return true;
		}
		while (1) {

			if (aValue == ptr->mValue) {
				return false;
			}
			if (aValue > ptr->mValue) {

				if (ptr->mRight == nullptr) {
					ptr->mRight = new CTreeItem<T>(nullptr, nullptr, aValue,
							ptr);
					mSize++;
					return true;
				}
				ptr = ptr->mRight;
			}
			if (aValue < ptr->mValue) {

				if (ptr->mLeft == nullptr) {
					ptr->mLeft = new CTreeItem<T>(nullptr, nullptr, aValue,
							ptr);
					mSize++;
					return true;
				}
				ptr = ptr->mLeft;
			}

		}

	}

	/**
	 * @brief Checks if the tree contains the given element.
	 * Complexity: O(N) - the worst case is when all items are left/right children nodes of their parents. Therefore
	 * all items have to be checked if the given value is the lowest/greatest. Typical case when tree is close to be balanced, complexity is O(log N).
	 * @param aValue Item to check.
	 * @return True if the tree contains the given value; otherwise false.
	 */
	bool contains(const T& aValue) const {

		return nodeReturn(aValue);
	}
	bool branchReconnect(std::shared_ptr<CTreeItem<T>> ptr) {
		std::shared_ptr<CTreeItem<T>> searchPtr = mBegin;
		for (; searchPtr != nullptr;) {
			if (searchPtr->mValue < ptr->mValue) {
				if (searchPtr->mRight == nullptr) {
					searchPtr->mRight = ptr;
					ptr->mParent = searchPtr;
					return true;
				} else {
					searchPtr = searchPtr->mRight;
				}
			} else if (searchPtr->mValue > ptr->mValue) {
				if (searchPtr->mLeft == nullptr) {
					searchPtr->mLeft = ptr;
					ptr->mParent = searchPtr;
					return true;
				} else {
					searchPtr = searchPtr->mLeft;
				}
			}
		}
		return false;
	}
	/**
	 * @brief Removes item from the tree.
	 * Complexity: O(N) - the worst case is when all items are left/right children nodes of their parents. Therefore
	 * all items have to be checked if the given value is the lowest/greatest. Typical case when tree is close to be balanced, complexity is O(log N).
	 * @param aValue Value to remove.
	 * @return True if the value was in the tree; otherwise false.
	 */
	bool remove(const T& aValue) {

		std::shared_ptr<CTreeItem<T>> ptr = nodeReturn(aValue);
		std::shared_ptr<CTreeItem<T>> leftNodeToConnect;
		std::shared_ptr<CTreeItem<T>> rightNodeToConnect;
		std::shared_ptr<CTreeItem<T>> parentNodeToConnect;
		std::shared_ptr<CTreeItem<T>> searchPtr;

		if (ptr == nullptr) {
			return false;
		}
		if (ptr->mParent == nullptr) { //usuwamy roota
			if (ptr->mRight != nullptr) {
				//podpinanmy za roota prawe dzeicko usuwanego elemtnu
				mBegin = ptr->mRight;
				mBegin->mParent = nullptr;
				leftNodeToConnect = ptr->mLeft;
				ptr = nullptr;
				branchReconnect(leftNodeToConnect);
				mSize--;
			} else if (ptr->mRight == nullptr && ptr->mLeft != nullptr) {
				//podpinamy lewe dziecko za roota usuwanego elementu
				mBegin = ptr->mLeft;
				mBegin->mParent = nullptr;
				rightNodeToConnect = ptr->mRight;
				searchPtr = mBegin;
				ptr = nullptr;
				branchReconnect(rightNodeToConnect);
				mSize--;

			} else {
				mBegin = nullptr; //usunelismy roota (jedyny node w drzewie)
				mSize--;
				return true;
			}
		} else {
			if (ptr == ptr->mParent->mLeft) //sprawdzamy czy jestemy lewym dzieckiem swojego rodzica
					{
				if (ptr->mRight != nullptr) {
					rightNodeToConnect = ptr->mRight;
					rightNodeToConnect->mParent = ptr->mParent;
					ptr->mParent->mLeft = rightNodeToConnect;
					leftNodeToConnect = ptr->mLeft;
					branchReconnect(leftNodeToConnect);
					ptr = nullptr;
					mSize--;

				} else if (ptr->mRight == nullptr && ptr->mLeft != nullptr) {
					leftNodeToConnect = ptr->mLeft;
					leftNodeToConnect->mParent = ptr->mParent;
					ptr->mParent->mLeft = leftNodeToConnect;
					rightNodeToConnect = ptr->mRight;
					branchReconnect(rightNodeToConnect);
					ptr = nullptr;
					mSize--;

				} else {
					ptr->mParent->mLeft = nullptr; // usunelismy node ktory nie ma dzieci
					mSize--;

				}
			} else {
				if (ptr->mRight != nullptr) {
					//podpinamy do prawego dziecka rodzica nasze prawe dziecko
					rightNodeToConnect = ptr->mRight;
					rightNodeToConnect->mParent = ptr->mParent;
					ptr->mParent->mRight = rightNodeToConnect;
					leftNodeToConnect = ptr->mLeft;
					branchReconnect(leftNodeToConnect);
					ptr = nullptr;
					mSize--;

				} else if (ptr->mRight == nullptr && ptr->mLeft != nullptr) {
					//podpinamy do prawego dziecka rodzica nasze lewe dziecko
					leftNodeToConnect = ptr->mLeft;
					leftNodeToConnect->mParent = ptr->mParent;
					ptr->mParent->mRight = leftNodeToConnect;
					rightNodeToConnect = ptr->mRight;
					branchReconnect(rightNodeToConnect);
					ptr = nullptr;
					mSize--;
				} else {
					ptr->mParent->mRight = nullptr; // usunelismy node ktory nie ma dzieci
					mSize--;

				}
			}
		}
		return true;
	}

private:
	int mSize;
	std::shared_ptr<T> mBegin;
	std::shared_ptr<CTreeItem<T>> nodeReturn(const T& aValue) const {
		std::shared_ptr<CTreeItem<T>> ptr = mBegin;
		if (ptr == nullptr) {

			return nullptr;
		}
		while (1) {

			if (aValue == ptr->mValue) {
				return ptr;
			}
			if (aValue > ptr->mValue) {

				if (ptr->mRight == nullptr) {
					return nullptr;
				}
				ptr = ptr->mRight;
			}
			if (aValue < ptr->mValue) {

				if (ptr->mLeft == nullptr) {
					return nullptr;
				}
				ptr = ptr->mLeft;
			}

		}

	}
};
#endif /* TREET_H_ */
