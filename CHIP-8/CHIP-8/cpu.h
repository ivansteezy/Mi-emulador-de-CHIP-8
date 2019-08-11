#ifndef CPU_H_
#define CPU_H_

struct _cpu
{
	_cpu(){}
	//CHIP-8 tiene 35 opcodes, todo son de 2 bytes
	unsigned short opcode;

	//Tiene 4K de memoria, puede ser emulada tal que
	unsigned char memory[4096];

	//Existen 15 registros de 8 bits para uso general llamados Vx (x = {0x00, 0x01, 0x02... 0x0E})
	//Y un regitro para "carry flag" 
	unsigned char V[16];

	//Hay un registro indice <<I>> y program counter <<PC>> de 12bits que va de 0x000 a 0xFFF
	unsigned short i;
	unsigned short pc = 0;
	
	/*Memory map
	+---------------+= 0xFFF (4095) End of Chip-8 RAM
	|               |
	|               |
	|               |
	|               |
	|               |
	| 0x200 to 0xFFF|
	|     Chip-8    |
	| Program / Data|
	|     Space     |
	|               |
	|               |
	|               |
	+- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
	|               |
	|               |
	|               |
	+---------------+= 0x200 (512) Start of most Chip-8 programs
	| 0x000 to 0x1FF|
	| Reserved for  |
	|  interpreter  |
	+---------------+= 0x000 (0) Start of Chip-8 RAM */

	//El sistema de graficos del CHIP-8 se realiza mediante una
	//instrucci�n, se realiza en modo XOR y si un pixel esta
	//apagado como resultado el registro VF se setteara, esto 
	//Es utilizado para la deteccion de colisiones

	//Los graficos del CHIP-8 son unicamente blanco o negro
	//con un total de 2048 pixeles(64px x 32px)
	unsigned char gfx[64 * 32];

	//El CHIP-8 no cuenta con ningun tipo de interrupcion 
	//Pero existen 2 registros que cuentan a 60hz hasta 0
	unsigned char delay_timer;
	unsigned char sound_timer;

	//Las especificacion de CHIP-8 no hacen menci�n a 
	//un stack pointer pero se debe implementar uno 
	//puesto que se debe guardar el program counter
	//en el caso de que se haga un llamado a una subrutina

	unsigned short stack[16];
	unsigned short sp;

	//Finalmente el CHIP-8 tiene un teclado HEX based (0x0, 0xF)
	unsigned char key[16];

	void initialize();
	void emulateCycle();
	void decodeOpcode();
};

#endif // !CPU_H_