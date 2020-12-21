// Circular_Queue Ŭ���� ���ø� �� ���� Ŭ���� ���Ǻ�

// Circual Queue Ŭ���� ���ø� ���� (����, �Ҹ�, ť ���� ��ȯ, ��� �� ��ȯ)
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
	this->queue_size = queue_size + 1; //������ ���� �� ���� �� ��ġ�� ���� �ϹǷ� queue_size��ŭ �����ϱ� ���� + 1

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
bool Circular_Queue<data_type, element_type>::is_empty() //���� ���� ����
{
	return (this->front == this->rear); //front�� rear�� ���� ������ �������
}

template <typename data_type, typename element_type>
bool Circular_Queue<data_type, element_type>::is_full() //��ȭ ���� ����
{
	return ((this->rear + 1) % this->queue_size == this->front); //������ ��ġ���� front�� ������� ��ȭ����
}

template <typename data_type, typename element_type>
data_type Circular_Queue<data_type, element_type>::get_count() //ť�� ��� ���� ��ȯ
{
	return (this->rear) - (this->front);
}

// Victim Block ��⿭ ���� (����, ���, ����, ����)

Spare_Block_Queue::Spare_Block_Queue(unsigned int queue_size) : Circular_Queue<unsigned int, spare_block_num>(queue_size)
{
	this->load_read_index();
}

void Victim_Block_Queue::print() //���
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //ť�� ������� ������
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

			if (i == this->rear) //rear��ġ���� ���� �� ����
				break;
		} while (i != this->front); //ť�� �� ���� ��������
	}
	printf("\n");
}

int Victim_Block_Queue::enqueue(victim_block_element src_block_element) //����
{
	if (this->is_full() == true) //���� á����
		return FAIL;

	//rear�� ���� ������Ų�� �����͸� �Է�
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_element;

	return SUCCESS;
}

int Victim_Block_Queue::dequeue(victim_block_element& dst_block_element) //����
{
	if (this->is_empty() == true) //���������
		return FAIL;

	//front�� ���� ������Ų�� front��ġ�� �����͸� ����
	this->front = (this->front + 1) % this->queue_size;

	dst_block_element = this->queue_array[this->front];

	return SUCCESS;
}

// Empty Block ��⿭ (���, ����, ����)

void Empty_Block_Queue::print() //���
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //ť�� ������� ������
	{
		unsigned int i = this->front;

		do {
			i = (i + 1) % (this->queue_size);

			printf("empty block num : %d\n", this->queue_array[i]);

			if (i == this->rear) //rear��ġ���� ���� �� ����
				break;
		} while (i != this->front); //ť�� �� ���� ��������
	}
	printf("\n");
}

int Empty_Block_Queue::enqueue(empty_block_num src_block_num) //����
{
	if (this->is_full() == true) //���� á����
		return FAIL;

	//rear�� ���� ������Ų�� �����͸� �Է�
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_num;

	return SUCCESS;
}

int Empty_Block_Queue::dequeue(empty_block_num& dst_block_num) //����
{
	if (this->is_empty() == true) //���������
		return FAIL;

	//front�� ���� ������Ų�� front��ġ�� �����͸� ����
	this->front = (this->front + 1) % this->queue_size;

	dst_block_num = this->queue_array[this->front];

	return SUCCESS;
}

//Spare Block ��⿭ (���, ����, ����, ��Ÿ �۾�)

void Spare_Block_Queue::print() //���
{
	printf("QUEUE(front = %u rear = %u)\n", this->front, this->rear);
	if (this->is_empty() != true) //ť�� ������� ������
	{
		unsigned int i = this->front;

		do {
			i = (i + 1) % (this->queue_size);

			printf("spare block num : %d\n", this->queue_array[i]);

			if (i == this->rear) //rear��ġ���� ���� �� ����
				break;
		} while (i != this->front); //ť�� �� ���� ��������
	}
	printf("\n");
}

int Spare_Block_Queue::enqueue(spare_block_num src_block_num) //����
{
	if (this->is_full() == true) //���� á����
		return FAIL;

	//rear�� ���� ������Ų�� �����͸� �Է�
	this->rear = (this->rear + 1) % this->queue_size;
	this->queue_array[this->rear] = src_block_num;


	this->load_read_index();

	return SUCCESS;
}

int Spare_Block_Queue::dequeue(spare_block_num& dst_block_num) //����
{
	if (this->is_empty() == true) //���������
		return FAIL;

	//front�� ���� ������Ų�� front��ġ�� �����͸� ����
	this->front = (this->front + 1) % this->queue_size;

	dst_block_num = this->queue_array[this->front];

	return SUCCESS;
}

int Spare_Block_Queue::save_read_index()
{
	printf("sbq index ����\n");
	return SUCCESS;
}

int Spare_Block_Queue::load_read_index()
{
	printf("sbq index �ҷ�����\n");
	return SUCCESS;
}
