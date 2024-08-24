#ifndef MOPER_STL_MEMORY_POOL_H
#define MOPER_STL_MEMORY_POOL_H

#include <cstdlib> // malloc()、free()

// MemoryPool的报错类型
enum __memory_error {
	CREATE_MEMORY_ERROR, // CreateMemoryBlock()错误
	CREATE_FREE_SAPCE_HEADER_ERROR,  // CreateOneFreeSpaceHeader()错误
};

class __memory_pool {
private: // 内部数据结构
	// 空闲存储结点
	struct FreeSpace {
		FreeSpace* next_free; // 指向下一个空闲存储结点
	};
	// 空闲存储头结点
	struct FreeSpaceHeader {
		std::size_t size; // 当前头结点下存储结点的大小
		FreeSpaceHeader* next_header; // 链表指向下一个头结点
		FreeSpace* next_free; // 指向该头结点下的第一个空闲存储结点
	};
	// Block头结点
	struct BlockHeader {
		BlockHeader* prev_block; // 指向当前Block的前一个Block
	};

private: // 内部别名、宏
	using data_address = unsigned char*; // 用于表示地址（并不一定要求使用unsigned char，只要大小为1B的类型即可）
	static const std::size_t INITIAL_SIZE = 8; // FreeSpace中第一个FreeSpaceHeader的size
	static const std::size_t ALIGN_SIZE = 4; // FreeSpace中相邻FreeSpceHeader之间size的差值
private: // 成员变量 
	// Block
	BlockHeader* current_block; // 指向当前Block。便于后续析构函数的实现
	// FreeSpace
	std::size_t max_size_of_free_space; // 记录当前FreeSpace链表中最后一个头结点的size，即当前FreeSapce所能分配的最大空闲存储空间
	FreeSpaceHeader* free_space_head; // 指向FreeSpace链表的第一个结点
	FreeSpaceHeader* free_space_rear; // 指向FreeSpace链表的最后一个结点。便于后续扩展FreeSpace
private: // 内部函数（用于实现接口）

	/* CreateOneFreeSpaceHeader()
	 *
	 * @brief 创建一个size = target_size的FreeSpaceHeader对象
	 * @return 返回对象的指针
	 */
	FreeSpaceHeader* CreateOneFreeSpaceHeader(std::size_t target_size) {
		FreeSpaceHeader* header = reinterpret_cast<FreeSpaceHeader*>(std::malloc(sizeof(FreeSpaceHeader)));
		if (header == NULL) throw __memory_error::CREATE_FREE_SAPCE_HEADER_ERROR;

		header->next_free = nullptr;
		header->next_header = nullptr;
		header->size = target_size;

		return header;
	}

	/* ExtendFreeSpaceHeaders()
	 *
	 * @brief 扩展FreeSpace，直到其所能分配的最大结点大小（即max_size_of_free_space） = target_size
	 */
	void ExtendFreeSpaceHeaders(std::size_t target_size) {
		while (max_size_of_free_space < target_size) {
			FreeSpaceHeader* header = CreateOneFreeSpaceHeader(max_size_of_free_space + ALIGN_SIZE);

			free_space_rear->next_header = header;
			free_space_rear = header;

			max_size_of_free_space = free_space_rear->size;
		}
	}

	/* FindFreeSpaceHeader()
	 *
	 * @brief 遍历FreeSpace，找到第一个符合分配大小要求的FreeSpaceHeader
	 * @param target_size 所需分配的大小
	 * @return 返回指向该FreeSpaceHeader的指针
	 */
	FreeSpaceHeader* FindFreeSpaceHeader(std::size_t target_size) const {
		FreeSpaceHeader* header = free_space_head;
		while (header != nullptr && header->size < target_size) header = header->next_header;

		return header;
	}

	/* CreateMemoryBlock()
	 *
	 * @brief 创建具有size大小可分配存储空间的Block（BlockHeader不包含在size内）
	 * @return 返回该Block中可size大小分配存储空间的首地址（即跳过BlockHeader）
	 */
	void* CreateMemoryBlock(std::size_t size) {
		BlockHeader* block = reinterpret_cast<BlockHeader*>(std::malloc(sizeof(BlockHeader) + size));
		if (block == NULL) throw __memory_error::CREATE_MEMORY_ERROR;

		block->prev_block = current_block;
		current_block = block;

		return block + 1;
	}

	/* ExtendFreeSpace()
	 *
	 * @brief 扩展header下的FreeSpace
	 */
	void ExtendFreeSpace(FreeSpaceHeader* header) {
		std::size_t num = header->size > 128 ? 1 : 20;

		data_address address = reinterpret_cast<data_address>(CreateMemoryBlock(num * header->size));

		for (std::size_t i = 0; i < num; ++i) {
			FreeSpace* free = reinterpret_cast<FreeSpace*>(address + i * header->size);
			free->next_free = header->next_free;
			header->next_free = free;
		}
	}

public: // 接口
	__memory_pool() noexcept : current_block(nullptr), max_size_of_free_space(INITIAL_SIZE) {
		FreeSpaceHeader* header = CreateOneFreeSpaceHeader(INITIAL_SIZE);

		free_space_head = header;
		free_space_rear = free_space_head;
	}

	~__memory_pool() noexcept {
		FreeSpaceHeader* header_iterator = free_space_head;
		while (header_iterator != nullptr) {
			FreeSpaceHeader* next_header = header_iterator->next_header;
			std::free(header_iterator);
			header_iterator = next_header;
		}

		BlockHeader* block_iterator = current_block;
		while (block_iterator != nullptr) {
			BlockHeader* prev_block = block_iterator->prev_block;
			std::free(block_iterator);
			block_iterator = prev_block;
		}
	}

	/* allocate()
	 *
	 * @brief 分配大小为 n 的未初始化存储空间
	 * @return 返回该未初始化存储空间的首地址
	 */
	void* allocate(std::size_t n) {
		ExtendFreeSpaceHeaders(n);

		FreeSpaceHeader* header = FindFreeSpaceHeader(n);

		if (header->next_free == nullptr) ExtendFreeSpace(header);

		FreeSpace* result = header->next_free;
		header->next_free = header->next_free->next_free;

		return result;
	}

	/* deallocate()
	 *
	 * @brief 解分配 p 地址处大小为 n 的存储空间
	 * @param p 必须为通过 allocate() 获得的指针
	 * @param n 必须为通过 allocate() 申请的空间大小
	 * 注意：本函数并不具备检查参数是否正确的能力，因此保证内存安全的任务由用户自己完成
	 */
	void deallocate(void* p, std::size_t n) {
		FreeSpaceHeader* header = free_space_head;
		while (header->size < n) header = header->next_header;

		reinterpret_cast<FreeSpace*>(p)->next_free = header->next_free;
		header->next_free = reinterpret_cast<FreeSpace*>(p);
	}
};

/* memory_pool
 *
 * @brief 静态MemoryPool实例对象
 * 由于MemoryPool支持任意大小的空间申请，
 * 但是用户使通常是通过template <class T>调用MemoryPool，
 * 如果将MemoryPool作为变量定义在class中，
 * 则可能造成许多FreeSpaceHeader无法得到有效利用
 * 举例：
 * 如果某一类型T的大小为24，则用户申请的空间一定为24的整数倍
 * 但是FreeSpace中FreeSpaceHeader的大小为8、12、16、20、24、28......
 * 其中大小为8、12、16、20、28......的FreeSpaceHeader永远无法得到使用
 *
 * 因此，在此定义静态MemoryPool实例对象memory_pool
 * 所有需要调用MemoryPool的class均通过memory_pool对象实现
 * 即所有调用MemoryPool的class对象内部使用的是同一个MemoryPool，即memory_pool
 *
 * 不过此方法仍存在缺点：
 * 即memory_pool所申请的空间除非在程序结束后自动释放外，几乎永远得到释放
 */
static __memory_pool memory_pool;


#endif /* MOPER_STL_MEMORY_POOL_H */
