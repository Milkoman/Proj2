#ifndef HASHMAP_H
#define HASHMAP_H
#include "HashNode.hpp"


// Default hash function class
template <typename K>
struct MyKeyHash
{
	int operator()(const string &k, int s) const
	{
		int i = 0;
		int temp = 0;
		while (k[i])
		{
			temp += k[i];
			i++;
		}
		return temp % s;
	}
};

template <typename K, typename V, typename F = MyKeyHash<K> >
class HashMap
{
	private:
		HashNode<K, V> **table;
		F hashFunc;
		int size;
		int numNodes;

	public:
		HashMap(int SIZE) : size(SIZE), numNodes(0) { table = new HashNode<K, V> *[SIZE](); }
		~HashMap();

		int getTableSize() const { return size; }
		int getNumNodes() const { return numNodes; }
		bool isEmpty() const { return numNodes == 0; }
		bool get(const K &key, V &value);
		void add(const K &key,  V *value);
		void remove(const K &key);
		void traverse(void visit(V)) const;
		void traverse(void visit(V, ostream &), ostream& file) const;
		void displayTable() const;
		int getNumCollisions() const;
		int getLongestChain() const;
		double getLoadFactor() const;
};
#endif

template<typename K, typename V, typename F>
inline HashMap<K, V, F>::~HashMap()
{
	for (int i = 0; i < size; ++i)
	{
		HashNode<K, V> *entry = table[i];
		while (entry != nullptr)
		{
			HashNode<K, V> *prev = entry;
			entry = entry->getNext();
			delete prev;
		}
		table[i] = nullptr;
	}
	delete[] table;
}

template<typename K, typename V, typename F>
inline bool HashMap<K, V, F>::get(const K & key, V & value)
{
	int hashValue = hashFunc(key, size);
	HashNode<K, V> *entry = table[hashValue];

	while (entry != nullptr)
	{
		if (entry->getKey() == key)
		{
			value = entry->getData();
			return true;
		}
		entry = entry->getNext();
	}
	return false;
}

template<typename K, typename V, typename F>
inline void HashMap<K, V, F>::add(const K & key, V * value)
{
	int hashValue = hashFunc(key, size);
	HashNode<K, V> *prev = nullptr;
	HashNode<K, V> *entry = table[hashValue];

	while (entry != nullptr && entry->getKey() != key)
	{
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == nullptr)
	{
		entry = new HashNode<K, V>(key, value);

		if (prev == nullptr)
		{
			table[hashValue] = entry; // insert as first bucket
		}
		else
		{
			prev->setNext(entry);
		}
	}
	else
	{
		entry->setData(value); // just update the value
	}
	numNodes++;
}

template<typename K, typename V, typename F>
inline void HashMap<K, V, F>::remove(const K & key)
{
	int hashValue = hashFunc(key, size);
	HashNode<K, V> *prev = nullptr;
	HashNode<K, V> *entry = table[hashValue];

	while (entry != nullptr && entry->getKey() != key)
	{
		prev = entry;
		entry = entry->getNext();
	}

	if (entry == nullptr)
		return;

	else
	{
		if (prev == nullptr)
		{
			table[hashValue] = entry->getNext(); // remove first bucket of the list
		}
		else
		{
			prev->setNext(entry->getNext());
		}

		delete entry;
	}
	--numNodes;
}

template<typename K, typename V, typename F>
inline void HashMap<K, V, F>::traverse(void visit(V)) const
{
	for (int i = 0; i < size; i++)
	{
		if (table[i])
		{
			HashNode<K, V> *node = table[i];
			while (node != nullptr)
			{
				visit(node->getData());
				node = node->getNext();
			}
		}
	}
}

template<typename K, typename V, typename F>
inline void HashMap<K, V, F>::traverse(void visit(V, ostream &), ostream &file) const
{
	for (int i = 0; i < size; i++)
	{
		if (table[i])
		{
			HashNode<K, V> *node = table[i];
			while (node != nullptr)
			{
				visit(node->getData(), file);
				node = node->getNext();
			}
		}
	}
}

template<typename K, typename V, typename F>
inline void HashMap<K, V, F>::displayTable() const
{
	for (int i = 0; i < size; i++)
	{
		if (table[i])
		{
			HashNode<K, V> *node = table[i];
			while (node != nullptr)
			{
				std::cout << node->getData();
				if (node->getNext())
					std::cout << " -> ";
				node = node->getNext();

			}
			std::cout << '\n';
		}
		//else
			//std::cout << "Empty\n";
	}
}

template<typename K, typename V, typename F>
inline int HashMap<K, V, F>::getNumCollisions() const
{
	int num = 0;
	for (int i = 0; i < size; i++)
	{
		if (table[i])
		{
			HashNode<K, V> *node = table[i];
			while (node != nullptr)
			{
				if (node->getNext())
					num++;
				node = node->getNext();
			}
		}
	}
	return num;
}

template<typename K, typename V, typename F>
inline int HashMap<K, V, F>::getLongestChain() const
{
	int highest = 0;
	for (int i = 0; i < size; i++)
	{
		if (table[i])
		{
			int num = 1;
			HashNode<K, V> *node = table[i];
			while (node != nullptr)
			{
				if (node->getNext())
				{
					num++;
				}
				node = node->getNext();
			}
			if (num > highest)
				highest = num;
		}
	}
	return highest;
}

template<typename K, typename V, typename F>
inline double HashMap<K, V, F>::getLoadFactor() const
{
	double num = 0.0;
	for (int i = 0; i < size; i++)
	{
		if (table[i])
			num++;
	}
	return numNodes/num;
}
