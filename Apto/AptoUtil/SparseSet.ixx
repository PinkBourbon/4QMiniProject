module;
#include <vector>

export module SparseSet;


export namespace apto
{
	template<typename T>
	class SparseSet
	{
	public:
		class iterator
		{
		public:
			iterator() noexcept : _ptr(nullptr) {}
			iterator(T* ptr) noexcept : _ptr(ptr) {}
			iterator(const iterator&) noexcept = default;
			iterator(iterator&&) noexcept = default;
			iterator& operator=(const iterator&) noexcept = default;
			iterator& operator=(iterator&&) noexcept = default;
			~iterator() noexcept = default;

			iterator& operator++() noexcept
			{
				++_ptr;
				return *this;
			}
			iterator operator++(int) noexcept
			{
				iterator tmp(*this);
				operator++();
				return tmp;
			}
			iterator& operator--() noexcept
			{
				--_ptr;
				return *this;
			}
			iterator operator--(int) noexcept
			{
				iterator tmp(*this);
				operator--();
				return tmp;
			}
			bool operator==(const iterator& rhs) const noexcept
			{
				return _ptr == rhs._ptr;
			}
			bool operator!=(const iterator& rhs) const noexcept
			{
				return _ptr != rhs._ptr;
			}
			T& operator*() noexcept
			{
				return *_ptr;
			}
			T* operator->() noexcept
			{
				return _ptr;
			}

		private:
			T* _ptr;
		};

	public:
		SparseSet();
		SparseSet(int capacity);

		~SparseSet();

		bool insert(T& data);
		void Reserve();
		T* Find(T& data);
		bool Remove(T& data);

	private:
		std::vector<T> _dense;
		std::vector<size_t> _sparse;
		size_t _size;
		size_t _capacity;

		size_t chunkSize;
		size_t chunkCount;
		size_t dataPerChunk;
	};

}