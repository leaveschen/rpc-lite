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

		Block() {}
	};

public:
	// ctors & dtors
	ObjectPool() noexcept {}
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
};

#endif//


