#pragma anon_unions

#define LPC_GPIO_BASE         (0x2009C000UL)

#define LPC_GPIO0_BASE        (LPC_GPIO_BASE + 0x00000)
#define LPC_GPIO1_BASE        (LPC_GPIO_BASE + 0x00020)
#define LPC_GPIO2_BASE        (LPC_GPIO_BASE + 0x00040)
#define LPC_GPIO3_BASE        (LPC_GPIO_BASE + 0x00060)
#define LPC_GPIO4_BASE        (LPC_GPIO_BASE + 0x00080)


#define LPC_GPIO0             ((LPC_GPIO_TypeDef      *) LPC_GPIO0_BASE    )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef      *) LPC_GPIO1_BASE    )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef      *) LPC_GPIO2_BASE    )
#define LPC_GPIO3             ((LPC_GPIO_TypeDef      *) LPC_GPIO3_BASE    )
#define LPC_GPIO4             ((LPC_GPIO_TypeDef      *) LPC_GPIO4_BASE    )


/*  GPIO SET / RESET */
#define OUTPUT 1
#define INPUT 0

/*  GPIO PORT */
#define GPIO_PORT_0		0	 //  Port P0 
#define GPIO_PORT_1		1 	 //  Port P1 
#define GPIO_PORT_2		2 	 //  Port P2  
#define GPIO_PORT_3		3 	 //  Port P3  
#define GPIO_PORT_4		4 	 //  Port P4  

/*  GPIO PIN */
#define GPIO_PIN_0		0x00000001
#define GPIO_PIN_1		0x00000002
#define GPIO_PIN_2		0x00000004
#define GPIO_PIN_3		0x00000008

#define GPIO_PIN_4		0x00000010
#define GPIO_PIN_5		0x00000020
#define GPIO_PIN_6		0x00000040
#define GPIO_PIN_7		0x00000080

#define GPIO_PIN_8		0x00000100
#define GPIO_PIN_9		0x00000200
#define GPIO_PIN_10		0x00000400
#define GPIO_PIN_11		0x00000800

#define GPIO_PIN_12		0x00001000
#define GPIO_PIN_13		0x00002000
#define GPIO_PIN_14		0x00004000
#define GPIO_PIN_15		0x00008000

#define GPIO_PIN_16		0x00010000
#define GPIO_PIN_17		0x00020000
#define GPIO_PIN_18		0x00040000
#define GPIO_PIN_19		0x00080000

#define GPIO_PIN_20		0x00100000
#define GPIO_PIN_21		0x00200000
#define GPIO_PIN_22		0x00400000
#define GPIO_PIN_23		0x00800000

#define GPIO_PIN_24		0x01000000
#define GPIO_PIN_25		0x02000000
#define GPIO_PIN_26		0x04000000
#define GPIO_PIN_27		0x08000000

#define GPIO_PIN_28		0x10000000
#define GPIO_PIN_29		0x20000000			
#define GPIO_PIN_30		0x40000000			
#define GPIO_PIN_31		0x80000000			

#define ON 1
#define OFF 0

/* NULL pointer */

#ifndef NULL
#define NULL ((void*) 0)
#endif



    /* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;



/*------------- General Purpose Input/Output (GPIO) --------------------------*/
typedef struct
{
  union {
    volatile uint32_t FIODIR;
    struct {
    volatile uint16_t FIODIRL;
    volatile uint16_t FIODIRH;
    };
    struct {
    volatile uint8_t  FIODIR0;
    volatile uint8_t  FIODIR1;
	volatile uint8_t  FIODIR2;
    volatile uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    volatile uint32_t FIOMASK;
    struct {
    volatile uint16_t FIOMASKL;
    volatile uint16_t FIOMASKH;
    };
    struct {
    volatile uint8_t  FIOMASK0;
    volatile uint8_t  FIOMASK1;
    volatile uint8_t  FIOMASK2;
    volatile uint8_t  FIOMASK3;
    };
  };
  union {
    volatile uint32_t FIOPIN;
    struct {
    volatile uint16_t FIOPINL;
    volatile uint16_t FIOPINH;
    };
    struct {
    volatile uint8_t  FIOPIN0;
    volatile uint8_t  FIOPIN1;
    volatile uint8_t  FIOPIN2;
    volatile uint8_t  FIOPIN3;
    };
  };
  union {
    volatile uint32_t FIOSET;
    struct {
    volatile uint16_t FIOSETL;
    volatile uint16_t FIOSETH;
    };
    struct {
    volatile uint8_t  FIOSET0;
    volatile uint8_t  FIOSET1;
    volatile uint8_t  FIOSET2;
    volatile uint8_t  FIOSET3;
    };
  };
  union {
    volatile  uint32_t FIOCLR;
    struct {
    volatile  uint16_t FIOCLRL;
    volatile  uint16_t FIOCLRH;
    };
    struct {
    volatile  uint8_t  FIOCLR0;
    volatile  uint8_t  FIOCLR1;
    volatile  uint8_t  FIOCLR2;
    volatile  uint8_t  FIOCLR3;
    };
  };
} LPC_GPIO_TypeDef;


// portNum은 GPIO 몇번포트를 쓸건지
static LPC_GPIO_TypeDef *GPIO_GetPointer(uint8_t portNum)
{
	LPC_GPIO_TypeDef *pGPIO = NULL;

	switch (portNum) {
	case 0:
		pGPIO = LPC_GPIO0; // GPIO 0번의 주소
		break;
	case 1:
		pGPIO = LPC_GPIO1;
		break;
	case 2:
		pGPIO = LPC_GPIO2;
		break;
	case 3:
		pGPIO = LPC_GPIO3;
		break;
	case 4:
		pGPIO = LPC_GPIO4;
		break;
	default:
		break;
	}

	return pGPIO;
}

// dir OUTPUT : 1 INPUT : 0
void GPIO_SetDir(uint8_t portNum, uint32_t bitValue, uint8_t dir)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		// Enable Output
		if (dir) {
			pGPIO->FIODIR |= bitValue;
		}
		// Enable Input
		else {
			pGPIO->FIODIR &= ~bitValue;
		}
	}
}

void GPIO_ClearValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		pGPIO->FIOCLR = bitValue;
	}
}



void GPIO_SetValue(uint8_t portNum, uint32_t bitValue)
{
	LPC_GPIO_TypeDef *pGPIO = GPIO_GetPointer(portNum);

	if (pGPIO != NULL) {
		pGPIO->FIOSET = bitValue;
	}
}