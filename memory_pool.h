#ifndef MOPER_STL_MEMORY_POOL_H
#define MOPER_STL_MEMORY_POOL_H

#include <cstdlib> // malloc()��free()

// MemoryPool�ı�������
enum __memory_error {
	CREATE_MEMORY_ERROR, // CreateMemoryBlock()����
	CREATE_FREE_SAPCE_HEADER_ERROR,  // CreateOneFreeSpaceHeader()����
};

class __memory_pool {
private: // �ڲ����ݽṹ
	// ���д洢���
	struct FreeSpace {
		FreeSpace* next_free; // ָ����һ�����д洢���
	};
	// ���д洢ͷ���
	struct FreeSpaceHeader {
		std::size_t size; // ��ǰͷ����´洢���Ĵ�С
		FreeSpaceHeader* next_header; // ����ָ����һ��ͷ���
		FreeSpace* next_free; // ָ���ͷ����µĵ�һ�����д洢���
	};
	// Blockͷ���
	struct BlockHeader {
		BlockHeader* prev_block; // ָ��ǰBlock��ǰһ��Block
	};

private: // �ڲ���������
	using data_address = unsigned char*; // ���ڱ�ʾ��ַ������һ��Ҫ��ʹ��unsigned char��ֻҪ��СΪ1B�����ͼ��ɣ�
	static const std::size_t INITIAL_SIZE = 8; // FreeSpace�е�һ��FreeSpaceHeader��size
	static const std::size_t ALIGN_SIZE = 4; // FreeSpace������FreeSpceHeader֮��size�Ĳ�ֵ
private: // ��Ա���� 
	// Block
	BlockHeader* current_block; // ָ��ǰBlock�����ں�������������ʵ��
	// FreeSpace
	std::size_t max_size_of_free_space; // ��¼��ǰFreeSpace���������һ��ͷ����size������ǰFreeSapce���ܷ���������д洢�ռ�
	FreeSpaceHeader* free_space_head; // ָ��FreeSpace����ĵ�һ�����
	FreeSpaceHeader* free_space_rear; // ָ��FreeSpace��������һ����㡣���ں�����չFreeSpace
private: // �ڲ�����������ʵ�ֽӿڣ�

	/* CreateOneFreeSpaceHeader()
	 *
	 * @brief ����һ��size = target_size��FreeSpaceHeader����
	 * @return ���ض����ָ��
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
	 * @brief ��չFreeSpace��ֱ�������ܷ����������С����max_size_of_free_space�� = target_size
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
	 * @brief ����FreeSpace���ҵ���һ�����Ϸ����СҪ���FreeSpaceHeader
	 * @param target_size �������Ĵ�С
	 * @return ����ָ���FreeSpaceHeader��ָ��
	 */
	FreeSpaceHeader* FindFreeSpaceHeader(std::size_t target_size) const {
		FreeSpaceHeader* header = free_space_head;
		while (header != nullptr && header->size < target_size) header = header->next_header;

		return header;
	}

	/* CreateMemoryBlock()
	 *
	 * @brief ��������size��С�ɷ���洢�ռ��Block��BlockHeader��������size�ڣ�
	 * @return ���ظ�Block�п�size��С����洢�ռ���׵�ַ��������BlockHeader��
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
	 * @brief ��չheader�µ�FreeSpace
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

public: // �ӿ�
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
	 * @brief �����СΪ n ��δ��ʼ���洢�ռ�
	 * @return ���ظ�δ��ʼ���洢�ռ���׵�ַ
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
	 * @brief ����� p ��ַ����СΪ n �Ĵ洢�ռ�
	 * @param p ����Ϊͨ�� allocate() ��õ�ָ��
	 * @param n ����Ϊͨ�� allocate() ����Ŀռ��С
	 * ע�⣺�����������߱��������Ƿ���ȷ����������˱�֤�ڴ氲ȫ���������û��Լ����
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
 * @brief ��̬MemoryPoolʵ������
 * ����MemoryPool֧�������С�Ŀռ����룬
 * �����û�ʹͨ����ͨ��template <class T>����MemoryPool��
 * �����MemoryPool��Ϊ����������class�У�
 * �����������FreeSpaceHeader�޷��õ���Ч����
 * ������
 * ���ĳһ����T�Ĵ�СΪ24�����û�����Ŀռ�һ��Ϊ24��������
 * ����FreeSpace��FreeSpaceHeader�Ĵ�СΪ8��12��16��20��24��28......
 * ���д�СΪ8��12��16��20��28......��FreeSpaceHeader��Զ�޷��õ�ʹ��
 *
 * ��ˣ��ڴ˶��徲̬MemoryPoolʵ������memory_pool
 * ������Ҫ����MemoryPool��class��ͨ��memory_pool����ʵ��
 * �����е���MemoryPool��class�����ڲ�ʹ�õ���ͬһ��MemoryPool����memory_pool
 *
 * �����˷����Դ���ȱ�㣺
 * ��memory_pool������Ŀռ�����ڳ���������Զ��ͷ��⣬������Զ�õ��ͷ�
 */
static __memory_pool memory_pool;


#endif /* MOPER_STL_MEMORY_POOL_H */
