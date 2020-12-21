#include "header.h"

void main()
{
	//system("pause");

	Empty_Block_Queue* ebq = new Empty_Block_Queue(10);
	Spare_Block_Queue* sbq = new Spare_Block_Queue(10);
	Victim_Block_Queue* vq = new Victim_Block_Queue(10);

	VICTIM_BLOCK_INFO dummy[10];

	unsigned int output_dummy;

	printf("-----------------------------\n");
	printf("ebq 테스트\n");
	ebq->enqueue(1);
	ebq->enqueue(2);
	ebq->enqueue(3);
	ebq->dequeue(output_dummy);
	printf("%d\n", output_dummy);
	ebq->dequeue(output_dummy);
	printf("%d\n", output_dummy);
	ebq->dequeue(output_dummy);
	printf("%d\n", output_dummy);
	ebq->print();
	printf("-----------------------------\n");
	printf("sbq 테스트\n");
	sbq->enqueue(4);
	sbq->enqueue(5);
	sbq->enqueue(6);
	sbq->print();
	printf("-----------------------------\n");
	printf("vq 테스트\n");
	for(int i=0;i<10;i++)
	{
		if (vq->enqueue(dummy[i]) != SUCCESS)
			printf("삽입 실패");
		vq->print();

		vq->dequeue(dummy[i]);
	}
	vq->print();

	//system("pause");

	delete ebq;
	delete sbq;
	delete vq;

	system("pause");
}