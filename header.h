#include <stdio.h> 
#include <stdint.h>
#include <windows.h>
#include <iostream>

#define SUCCESS 1 //����
#define	COMPLETE 0 //�ܼ� ���� �Ϸ�
#define FAIL -1 //����

struct VICTIM_BLOCK_INFO
{
	bool is_logical = true;
	unsigned int victim_block_num = 1;
	float victim_block_invalid_ratio = 1.0;
};

typedef struct VICTIM_BLOCK_INFO victim_block_element;
typedef unsigned int empty_block_num;
typedef unsigned int spare_block_num;

// <ť�� �Ҵ� �� �ڷ���, ť�� ����� Ÿ��>
template <typename data_type, typename element_type>
class Circular_Queue //Circular_queue.hpp
{
public:
	Circular_Queue();
	Circular_Queue(data_type queue_size);
	~Circular_Queue();

	element_type* queue_array; //���� �迭
	data_type front, rear;

	bool is_empty(); //���� ���� ����
	bool is_full(); //��ȭ ���� ����
	data_type get_count(); //ť�� ��� ���� ��ȯ

	//���, ����, ���� �� ��Ÿ �۾� �� ���� Ŭ�������� ���� ���� �� ����


	/*���ø����� ���� �Լ� ��� �Ұ� ����
	virtual void print()=0; //���
	virtual int enqueuet(type_name)=0; //����
	virtual int dequeue(type_name&)=0; //����
	*/
protected:
	data_type queue_size; //ť�� �Ҵ� ũ��
};

class Empty_Block_Queue : public Circular_Queue<unsigned int, empty_block_num> //Circular_queue.hpp
{
public:
	Empty_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, empty_block_num>(queue_size) {};

	void print(); //���
	int enqueue(empty_block_num src_block_num); //����
	int dequeue(empty_block_num& dst_block_num); //����
};

class Spare_Block_Queue : public Circular_Queue<unsigned int, spare_block_num> //Circular_queue.hpp
{
public:
	//���� Spare_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, spare_block_num>(queue_size) {};

	Spare_Block_Queue(unsigned int queue_size);

	void print(); //���
	int enqueue(spare_block_num src_block_num); //����
	int dequeue(spare_block_num& dst_block_num); //����

private:
	int save_read_index(); //���� read_index �� ����
	int load_read_index(); //���� read_index �� �ҷ�����
};

class Victim_Block_Queue : public Circular_Queue<unsigned int, victim_block_element> //Circular_queue.hpp
{
public:
	Victim_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, victim_block_element>(queue_size) {};

	void print(); //���
	int enqueue(victim_block_element src_block_element); //����
	int dequeue(victim_block_element& dst_block_element); //����
};

#include "Circular_Queue.hpp" //Circular_Queue Ŭ���� ���ø� �� ���� Ŭ���� ���Ǻ�