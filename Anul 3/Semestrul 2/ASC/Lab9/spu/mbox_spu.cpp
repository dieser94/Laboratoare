#include <stdio.h>
#include <spu_intrinsics.h>
#include <spu_mfcio.h>

#define SIZE 80
 
int main(unsigned long long speid, unsigned long long argp, unsigned long long envp){
	uint32_t i ;
	unsigned int data[SIZE] __attribute__((aligned(16)));

	printf("[SPU 0x%llx] started\n", speid);

	argp = argp; //silence warnings
	envp = envp; //silence warnings

	for (i=0; i<SIZE; i++) {
		data[i] = (i + 1) * (i + 1);
	};
	unsigned int no = 0;
	//TODO: Task3 

	//TODO: Task1 - trimite un numar de la PPU la SPU(void)speid;
	
   unsigned int mbox_data;
   while(1) {
	   // citeste mesajul
	   mbox_data = spu_read_in_mbox();

	   if (mbox_data < 80) {

		//TODO: Task2 - trimite un numar de la  SPU la PPU

		spu_write_out_intr_mbox(data[mbox_data]);

	  	}
	  	else {
	  		spu_write_out_intr_mbox(no);
	  		break;
	  	}
	}
	printf("[SPU 0x%llx] finished\n", speid);

	return 0;
}



