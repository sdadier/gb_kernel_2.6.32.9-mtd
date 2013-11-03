/* linux/arch/arm/mach-s5p6442/include/mach/gpio.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C6400 - GPIO lib support
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/
#ifndef S5P6442_GPIO_H
#define S5P6442_GPIO_H

#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep
#define gpio_to_irq	__gpio_to_irq

/* GPIO bank sizes */
#define S5P64XX_GPIO_A0_NR	(8)
#define S5P64XX_GPIO_A1_NR	(2)
#define S5P64XX_GPIO_B_NR	(4)
#define S5P64XX_GPIO_C0_NR	(5)
#define S5P64XX_GPIO_C1_NR	(5)
#define S5P64XX_GPIO_D0_NR	(2)
#define S5P64XX_GPIO_D1_NR	(6)
#define S5P64XX_GPIO_E0_NR	(8)
#define S5P64XX_GPIO_E1_NR	(5)
#define S5P64XX_GPIO_F0_NR	(8)
#define S5P64XX_GPIO_F1_NR	(8)
#define S5P64XX_GPIO_F2_NR	(8)
#define S5P64XX_GPIO_F3_NR	(6)
#define S5P64XX_GPIO_G0_NR	(7)
#define S5P64XX_GPIO_G1_NR	(7)
#define S5P64XX_GPIO_G2_NR	(7)

#define S5P64XX_GPIO_H0_NR	(8)
#define S5P64XX_GPIO_H1_NR	(8)
#define S5P64XX_GPIO_H2_NR	(8)
#define S5P64XX_GPIO_H3_NR	(8)

#define S5P64XX_GPIO_J0_NR	(8)
#define S5P64XX_GPIO_J1_NR	(6)
#define S5P64XX_GPIO_J2_NR	(8)
#define S5P64XX_GPIO_J3_NR	(8)
#define S5P64XX_GPIO_J4_NR	(5)

#define S5P64XX_GPIO_MP01_NR	(8)
#define S5P64XX_GPIO_MP02_NR	(4)
#define S5P64XX_GPIO_MP03_NR	(5)
#define S5P64XX_GPIO_MP04_NR	(8)
#define S5P64XX_GPIO_MP05_NR	(8)
#define S5P64XX_GPIO_MP06_NR	(8)
#define S5P64XX_GPIO_MP07_NR	(8)

#define S5P64XX_GPIO_MP10_NR	(8)
#define S5P64XX_GPIO_MP11_NR	(8)
#define S5P64XX_GPIO_MP12_NR	(8)
#define S5P64XX_GPIO_MP13_NR	(8)
#define S5P64XX_GPIO_MP14_NR	(8)
#define S5P64XX_GPIO_MP15_NR	(8)
#define S5P64XX_GPIO_MP16_NR	(8)
#define S5P64XX_GPIO_MP17_NR	(8)
#define S5P64XX_GPIO_MP18_NR	(7)

/* GPIO bank numbes */

/* CONFIG_S3C_GPIO_SPACE allows the user to select extra
 * space for debugging purposes so that any accidental
 * change from one gpio bank to another can be caught.
*/

#define S5P64XX_GPIO_NEXT(__gpio) \
	((__gpio##_START) + (__gpio##_NR) + CONFIG_S3C_GPIO_SPACE + 1)

enum s3c_gpio_number {
	S5P64XX_GPIO_A0_START 	= 0,
	S5P64XX_GPIO_A1_START 	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_A0),
	S5P64XX_GPIO_B_START 	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_A1),
	S5P64XX_GPIO_C0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_B),
	S5P64XX_GPIO_C1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_C0),
	S5P64XX_GPIO_D0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_C1),
	S5P64XX_GPIO_D1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_D0),
	S5P64XX_GPIO_E0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_D1),
	S5P64XX_GPIO_E1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_E0),
	S5P64XX_GPIO_F0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_E1),
	S5P64XX_GPIO_F1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_F0),
	S5P64XX_GPIO_F2_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_F1),
	S5P64XX_GPIO_F3_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_F2),
	S5P64XX_GPIO_G0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_F3),
	S5P64XX_GPIO_G1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_G0),
	S5P64XX_GPIO_G2_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_G1),
	S5P64XX_GPIO_H0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_G2),
	S5P64XX_GPIO_H1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_H0),
	S5P64XX_GPIO_H2_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_H1),
	S5P64XX_GPIO_H3_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_H2),
	S5P64XX_GPIO_J0_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_H3),
	S5P64XX_GPIO_J1_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_J0),
	S5P64XX_GPIO_J2_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_J1),
	S5P64XX_GPIO_J3_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_J2),
	S5P64XX_GPIO_J4_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_J3),
	S5P64XX_GPIO_MP01_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_J4),
	S5P64XX_GPIO_MP02_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP01),
	S5P64XX_GPIO_MP03_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP02),
	S5P64XX_GPIO_MP04_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP03),
	S5P64XX_GPIO_MP05_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP04),
	S5P64XX_GPIO_MP06_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP05),
	S5P64XX_GPIO_MP07_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP06),
	S5P64XX_GPIO_MP10_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP07),
	S5P64XX_GPIO_MP11_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP10),
	S5P64XX_GPIO_MP12_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP11),
	S5P64XX_GPIO_MP13_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP12),
	S5P64XX_GPIO_MP14_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP13),
	S5P64XX_GPIO_MP15_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP14),
	S5P64XX_GPIO_MP16_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP15),
	S5P64XX_GPIO_MP17_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP16),
	S5P64XX_GPIO_MP18_START	= S5P64XX_GPIO_NEXT(S5P64XX_GPIO_MP17),	
};

/* S5P64XX GPIO number definitions. */
#define S5P64XX_GPA0(_nr)	(S5P64XX_GPIO_A0_START + (_nr))
#define S5P64XX_GPA1(_nr)	(S5P64XX_GPIO_A1_START + (_nr))
#define S5P64XX_GPB(_nr)	(S5P64XX_GPIO_B_START + (_nr))
#define S5P64XX_GPC0(_nr)	(S5P64XX_GPIO_C0_START + (_nr))
#define S5P64XX_GPC1(_nr)	(S5P64XX_GPIO_C1_START + (_nr))
#define S5P64XX_GPD0(_nr)	(S5P64XX_GPIO_D0_START + (_nr))
#define S5P64XX_GPD1(_nr)	(S5P64XX_GPIO_D1_START + (_nr))
#define S5P64XX_GPE0(_nr)	(S5P64XX_GPIO_E0_START + (_nr))
#define S5P64XX_GPE1(_nr)	(S5P64XX_GPIO_E1_START + (_nr))
#define S5P64XX_GPF0(_nr)	(S5P64XX_GPIO_F0_START + (_nr))
#define S5P64XX_GPF1(_nr)	(S5P64XX_GPIO_F1_START + (_nr))
#define S5P64XX_GPF2(_nr)	(S5P64XX_GPIO_F2_START + (_nr))
#define S5P64XX_GPF3(_nr)	(S5P64XX_GPIO_F3_START + (_nr))
#define S5P64XX_GPG0(_nr)	(S5P64XX_GPIO_G0_START + (_nr))
#define S5P64XX_GPG1(_nr)	(S5P64XX_GPIO_G1_START + (_nr))
#define S5P64XX_GPG2(_nr)	(S5P64XX_GPIO_G2_START + (_nr))
#define S5P64XX_GPH0(_nr)	(S5P64XX_GPIO_H0_START + (_nr))
#define S5P64XX_GPH1(_nr)	(S5P64XX_GPIO_H1_START + (_nr))
#define S5P64XX_GPH2(_nr)	(S5P64XX_GPIO_H2_START + (_nr))
#define S5P64XX_GPH3(_nr)	(S5P64XX_GPIO_H3_START + (_nr))
#define S5P64XX_GPJ0(_nr)	(S5P64XX_GPIO_J0_START + (_nr))
#define S5P64XX_GPJ1(_nr)	(S5P64XX_GPIO_J1_START + (_nr))
#define S5P64XX_GPJ2(_nr)	(S5P64XX_GPIO_J2_START + (_nr))
#define S5P64XX_GPJ3(_nr)	(S5P64XX_GPIO_J3_START + (_nr))
#define S5P64XX_GPJ4(_nr)	(S5P64XX_GPIO_J4_START + (_nr))
#define S5P64XX_MP01(_nr)	(S5P64XX_GPIO_MP01_START + (_nr))
#define S5P64XX_MP02(_nr)	(S5P64XX_GPIO_MP02_START + (_nr))
#define S5P64XX_MP03(_nr)	(S5P64XX_GPIO_MP03_START + (_nr))
#define S5P64XX_MP04(_nr)	(S5P64XX_GPIO_MP04_START + (_nr))
#define S5P64XX_MP05(_nr)	(S5P64XX_GPIO_MP05_START + (_nr))
#define S5P64XX_MP06(_nr)	(S5P64XX_GPIO_MP06_START + (_nr))
#define S5P64XX_MP07(_nr)	(S5P64XX_GPIO_MP07_START + (_nr))
#define S5P64XX_MP10(_nr)	(S5P64XX_GPIO_MP10_START + (_nr))
#define S5P64XX_MP11(_nr)	(S5P64XX_GPIO_MP11_START + (_nr))
#define S5P64XX_MP12(_nr)	(S5P64XX_GPIO_MP12_START + (_nr))
#define S5P64XX_MP13(_nr)	(S5P64XX_GPIO_MP13_START + (_nr))
#define S5P64XX_MP14(_nr)	(S5P64XX_GPIO_MP14_START + (_nr))
#define S5P64XX_MP15(_nr)	(S5P64XX_GPIO_MP15_START + (_nr))
#define S5P64XX_MP16(_nr)	(S5P64XX_GPIO_MP16_START + (_nr))
#define S5P64XX_MP17(_nr)	(S5P64XX_GPIO_MP17_START + (_nr))
#define S5P64XX_MP18(_nr)	(S5P64XX_GPIO_MP18_START + (_nr))

/* the end of the S5P64XX specific gpios */
#define S5P64XX_GPIO_END	(S5P64XX_MP18(S5P64XX_GPIO_MP18_NR) + 1)
#define S3C_GPIO_END		S5P64XX_GPIO_END

/* define the number of gpios we need to the one after the S5P64XX_GPJ4() range */
#define ARCH_NR_GPIOS	(S5P64XX_MP18(S5P64XX_GPIO_MP18_NR) + 1)
#include <asm-generic/gpio.h>

#endif //S5P6442_GPIO_H