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
