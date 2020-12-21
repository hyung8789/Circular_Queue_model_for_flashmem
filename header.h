#include <stdio.h> 
#include <stdint.h>
#include <windows.h>
#include <iostream>

#define SUCCESS 1 //성공
#define	COMPLETE 0 //단순 연산 완료
#define FAIL -1 //실패

struct VICTIM_BLOCK_INFO
{
	bool is_logical = true;
	unsigned int victim_block_num = 1;
	float victim_block_invalid_ratio = 1.0;
};

typedef struct VICTIM_BLOCK_INFO victim_block_element;
typedef unsigned int empty_block_num;
typedef unsigned int spare_block_num;

// <큐에 할당 할 자료형, 큐의 요소의 타입>
template <typename data_type, typename element_type>
class Circular_Queue //Circular_queue.hpp
{
public:
	Circular_Queue();
	Circular_Queue(data_type queue_size);
	~Circular_Queue();

	element_type* queue_array; //원형 배열
	data_type front, rear;

	bool is_empty(); //공백 상태 검출
	bool is_full(); //포화 상태 검출
	data_type get_count(); //큐의 요소 개수 반환

	//출력, 삽입, 삭제 및 기타 작업 등 하위 클래스에서 직접 선언 및 정의


	/*템플릿에서 가상 함수 사용 불가 삭제
	virtual void print()=0; //출력
	virtual int enqueuet(type_name)=0; //삽입
	virtual int dequeue(type_name&)=0; //삭제
	*/
protected:
	data_type queue_size; //큐의 할당 크기
};

class Empty_Block_Queue : public Circular_Queue<unsigned int, empty_block_num> //Circular_queue.hpp
{
public:
	Empty_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, empty_block_num>(queue_size) {};

	void print(); //출력
	int enqueue(empty_block_num src_block_num); //삽입
	int dequeue(empty_block_num& dst_block_num); //삭제
};

class Spare_Block_Queue : public Circular_Queue<unsigned int, spare_block_num> //Circular_queue.hpp
{
public:
	//삭제 Spare_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, spare_block_num>(queue_size) {};

	Spare_Block_Queue(unsigned int queue_size);

	void print(); //출력
	int enqueue(spare_block_num src_block_num); //삽입
	int dequeue(spare_block_num& dst_block_num); //삭제

private:
	int save_read_index(); //현재 read_index 값 저장
	int load_read_index(); //기존 read_index 값 불러오기
};

class Victim_Block_Queue : public Circular_Queue<unsigned int, victim_block_element> //Circular_queue.hpp
{
public:
	Victim_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, victim_block_element>(queue_size) {};

	void print(); //출력
	int enqueue(victim_block_element src_block_element); //삽입
	int dequeue(victim_block_element& dst_block_element); //삭제
};

#include "Circular_Queue.hpp" //Circular_Queue 클래스 템플릿 및 하위 클래스 정의부