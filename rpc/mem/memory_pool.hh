//
// Created by c on 03/08/2018 11:32 AM
//

#ifndef STC_MEMORY_POOL_HH
#define STC_MEMORY_POOL_HH

/* include section */

#include <utility>
#include <memory>
#include <array>

/* class & function section */

template<class T, std::size_t N = 16>
class ObjectPool {
public:
	using value_type = T;
	using pointer = T*;
	using reference = T&;
	using const_pointer = const T*;
	using const_reference = T const&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;

	static constexpr size_t block_size = N;

	template<class U>
	struct rebind {
		using other = ObjectPool<U>;
	};

private:
	union Item {
		value_type element;
		Item* next;
	};

	struct Block {
		std::array<Item, N> array;
		Item* free;
		std::unique_ptr<Block> next;

		Block() {
			for (size_type i = 0; i < N-1; ++i) { array[i].next = &array[i+1]; }
			free = &array[0];
			array[N-1].next = nullptr;
		}

		void set_next_block(std::unique_ptr<Block> &&n) { next.reset(n.release()); }
	};

	std::unique_ptr<Block> _p_block;
	Item* _freelist;

public:
	// ctors & dtors
	ObjectPool() : _p_block(std::make_unique<Block>()), _freelist(_p_block->free) {}
	ObjectPool(ObjectPool const&) = delete;
	ObjectPool(ObjectPool &&) = delete;
	ObjectPool& operator=(ObjectPool const&) = delete;
	ObjectPool& operator=(ObjectPool &&) = delete;

	~ObjectPool() noexcept {}

	pointer address(reference r) { return &r; }
	const_pointer address(const_reference s) { return &s; }

	template<class U, class... Args>
	inline void construct(U* p, Args&&... args) { new (p) U(std::forward<Args>(args)...); }

	template<class U>
	inline void destroy(U* p) { p->U::~U(); }

	// interface
	template<class... Args>
	T* alloc(Args&&... args) {
		if (_freelist == nullptr) {
			auto new_block = std::make_unique<Block>();
			new_block->set_next_block(std::move(_p_block));
			_p_block.reset(new_block.release());
			_freelist = _p_block->free;
		}

		Item* curr = _freelist;
		_freelist = curr->next;
		T* ret = &curr->element;
		new (ret) T(std::forward<Args>(args)...);
		return ret;
	}

	void free(T* t) {
		t->T::~T();
		Item* curr = reinterpret_cast<Item*>(t);
		curr->next = _freelist;
		_freelist = curr;
	}
};

#endif//


