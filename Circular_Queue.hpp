// Circular_Queue 클래스 템플릿 및 하위 클래스 정의부

// Circual Queue 클래스 템플릿 정의 (생성, 소멸, 큐 상태 반환, 요소 수 반환)
template <typename data_type, typename element_type>
Circular_Queue<data_type, element_type>::Circular_Queue()
{
	this->queue_array = NULL;
	this->queue_size = 0;
	this->front = this->rear = 0;

	printf("CC default init\n");
}

template <typename data_type, typename element_type>
Circular_Queue<data_type, element_type>::Circular_Queue(data_type queue_size)
{
	this->queue_array = NULL;
	this->queue_size = queue_size + 1; //데이터 삽입 시 증가 된 위치에 삽입 하므로 queue_size만큼 저장하기 위해 + 1

	if (this->queue_array == NULL)
	{
		this->queue_array = new element_type[this->queue_size];
	}

	this->front = this->rear = 0;

	printf("CC queue_size init\n");
}

template <typename data_type, typename element_type>
Circular_Queue<data_type, element_type>::~Circular_Queue()
{
	if (this->queue_array != NULL)
	{
		delete[] this->queue_array;
		this->queue_array = NULL;
	}

	printf("~cc\n");
}

template <typename data_type, typename element_type>
bool Circular_Queue<data_type, element_type>::is_empty() //공백 상태 검출
{
	return (this->front == this->rear); //front와 rear의 값이 같으면 공백상태
}

template <typename data_type, typename element_type>
bool Circular_Queue<data_type, element_type>::is_full() //포화 상태 검출
{
	return ((this->rear + 1) % this->queue_size == this->front); //증가된 위치에서 front를 만날경우 포화상태
}

template <typename data_type, typename element_type>
data_type Circular_Queue<data_type, element_type>::get_count() //큐의 요소 개수 반환
{
	return (this->rear) - (this->front);
}

// Victim Block 대기열 정의 (생성, 출력, 삽입, 삭제)

Spare_Block_Queue::Spare_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, spare_block_num>(queue_size)
{
	this->load_read_index();
}

void Victim_Block_Queue::print() //출력
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //큐가 비어있지 않으면
	{
		unsigned int i = this->front;

		do {
			i = (i + 1) % (this->queue_size);

			switch (this->queue_array[i].is_logical)
			{
			case true:
				std::cout << "victim_LBN : ";
				break;

			case false:
				std::cout << "victim_PBN : ";
				break;
			}
			std::cout << this->queue_array[i].victim_block_num << std::endl;
			std::cout << "victim_block_invalid_ratio : " << this->queue_array[i].victim_block_invalid_ratio << std::endl;
			std::cout << "----------------------------------" << std::endl;

			if (i == this->rear) //rear위치까지 도달 후 종료
				break;
		} while (i != this->front); //큐를 한 바퀴 돌때까지
	}
	printf("\n");
}

int Victim_Block_Queue::enqueue(victim_block_element src_block_element) //삽입
{
	if (this->is_full() == true) //가득 찼으면
		return FAIL;

	//rear의 값을 증가시킨후 데이터를 입력
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_element;

	return SUCCESS;
}

int Victim_Block_Queue::dequeue(victim_block_element& dst_block_element) //삭제
{
	if (this->is_empty() == true) //비어있으면
		return FAIL;

	//front의 값을 증가시킨후 front위치의 데이터를 리턴
	this->front = (this->front + 1) % this->queue_size;

	dst_block_element = this->queue_array[this->front];

	return SUCCESS;
}

// Empty Block 대기열 (출력, 삽입, 삭제)

void Empty_Block_Queue::print() //출력
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //큐가 비어있지 않으면
	{
		unsigned int i = this->front;

		do {
			i = (i + 1) % (this->queue_size);

			printf("empty block num : %d\n", this->queue_array[i]);

			if (i == this->rear) //rear위치까지 도달 후 종료
				break;
		} while (i != this->front); //큐를 한 바퀴 돌때까지
	}
	printf("\n");
}

int Empty_Block_Queue::enqueue(empty_block_num src_block_num) //삽입
{
	if (this->is_full() == true) //가득 찼으면
		return FAIL;

	//rear의 값을 증가시킨후 데이터를 입력
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_num;

	return SUCCESS;
}

int Empty_Block_Queue::dequeue(empty_block_num& dst_block_num) //삭제
{
	if (this->is_empty() == true) //비어있으면
		return FAIL;

	//front의 값을 증가시킨후 front위치의 데이터를 리턴
	this->front = (this->front + 1) % this->queue_size;

	dst_block_num = this->queue_array[this->front];

	return SUCCESS;
}

//Spare Block 대기열 (출력, 삽입, 삭제, 기타 작업)

void Spare_Block_Queue::print() //출력
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //큐가 비어있지 않으면
	{
		unsigned int i = this->front;

		do {
			i = (i + 1) % (this->queue_size);

			printf("spare block num : %d\n", this->queue_array[i]);

			if (i == this->rear) //rear위치까지 도달 후 종료
				break;
		} while (i != this->front); //큐를 한 바퀴 돌때까지
	}
	printf("\n");
}

int Spare_Block_Queue::enqueue(spare_block_num src_block_num) //삽입
{
	if (this->is_full() == true) //가득 찼으면
		return FAIL;

	//rear의 값을 증가시킨후 데이터를 입력
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_num;


	this->load_read_index();

	return SUCCESS;
}

int Spare_Block_Queue::dequeue(spare_block_num& dst_block_num) //삭제
{
	if (this->is_empty() == true) //비어있으면
		return FAIL;

	//front의 값을 증가시킨후 front위치의 데이터를 리턴
	this->front = (this->front + 1) % this->queue_size;

	dst_block_num = this->queue_array[this->front];

	return SUCCESS;
}

int Spare_Block_Queue::save_read_index()
{
	printf("sbq index 저장\n");
	return SUCCESS;
}

int Spare_Block_Queue::load_read_index()
{
	printf("sbq index 불러오기\n");
	return SUCCESS;
}
