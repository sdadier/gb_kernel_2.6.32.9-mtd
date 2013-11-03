/* linux/arch/arm/plat-s5p64xx/pwm-s5p6442.c
 *
 * (c) 2003-2005 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S5P64XX PWM core
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *
 *
 */
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/clk.h>
#include <linux/mutex.h>
#include <linux/gpio.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

#include <mach/hardware.h>
#include <mach/irqs.h>
#include <plat/map.h>
#include <plat/regs-timer.h>
#include <plat/gpio-cfg.h>
#include <plat/gpio-bank-d0.h>
#include "pwm-s5p6442.h"

s5p6442_pwm_chan_t s3c_chans[S3C_PWM_CHANNELS];

static inline void
s5p6442_pwm_buffdone(s5p6442_pwm_chan_t *chan, void *dev)
{

	if (chan->callback_fn != NULL) {
		(chan->callback_fn)( dev);
	}
}


static int s5p6442_pwm_start (int channel)
{
	unsigned long tcon;
	tcon = __raw_readl(S3C_TCON);
	switch(channel)
	{
	case 0:
		tcon |= S3C_TCON_T0START;
		tcon &= ~S3C_TCON_T0MANUALUPD;
	break;
	case 1:
		tcon |= S3C_TCON_T1START;
		tcon &= ~S3C_TCON_T1MANUALUPD;
	break;
	case 2:
		tcon |= S3C_TCON_T2START;
		tcon &= ~S3C_TCON_T2MANUALUPD;
	break;
	case 3:
		tcon |= S3C_TCON_T3START;
		tcon &= ~S3C_TCON_T3MANUALUPD;
	break;
	case 4:
		tcon |= S3C_TCON_T4START;
		tcon &= ~S3C_TCON_T4MANUALUPD;
	break;
	}
	__raw_writel(tcon, S3C_TCON);

	return 0;
}


int s5p6442_timer_setup (int channel, int usec, unsigned long g_tcnt, unsigned long g_tcmp)
{
	unsigned long tcon;
	unsigned long tcnt;
	unsigned long tcmp;
	unsigned long tcfg1;
	unsigned long tcfg0;
	unsigned long pclk;
	struct clk *clk;

//	printk("\nPWM channel %d set g_tcnt = %ld, g_tcmp = %ld \n", channel, g_tcnt, g_tcmp);

	tcnt = 0xffffffff;  /* default value for tcnt */

	/* read the current timer configuration bits */
	tcon = __raw_readl(S3C_TCON);
	tcfg1 = __raw_readl(S3C_TCFG1);
	tcfg0 = __raw_readl(S3C_TCFG0);

	clk = clk_get(NULL, "timers");
	if (IS_ERR(clk))
		panic("failed to get clock for pwm timer");

	clk_enable(clk);

	pclk = clk_get_rate(clk);

	/* configure clock tick */
	switch(channel)
	{
		case 0:
			/* set gpio as PWM TIMER0 to signal output*/
	                s3c_gpio_cfgpin(S5P64XX_GPD0(0), S5P64XX_GPD_0_0_TOUT_0);
                        gpio_set_value(S5P64XX_GPD0(0), 0);			
			tcfg1 &= ~S3C_TCFG1_MUX0_MASK;
			tcfg1 |= S3C_TCFG1_MUX0_DIV2;

			tcfg0 &= ~S3C_TCFG_PRESCALER0_MASK;
			tcfg0 |= (PRESCALER) << S3C_TCFG_PRESCALER0_SHIFT;
			tcon &= ~(7<<0);
			tcon |= S3C_TCON_T0RELOAD;
			break;

		case 1:
			/* set gpio as PWM TIMER1 to signal output*/
                        s3c_gpio_cfgpin(S5P64XX_GPD0(1), S5P64XX_GPD_0_1_TOUT_1);
                        gpio_set_value(S5P64XX_GPD0(1), 0);
			tcfg1 &= ~S3C_TCFG1_MUX1_MASK;
			tcfg1 |= S3C_TCFG1_MUX1_DIV2;

			tcfg0 &= ~S3C_TCFG_PRESCALER0_MASK;
			tcfg0 |= (PRESCALER) << S3C_TCFG_PRESCALER0_SHIFT;

			tcon &= ~(7<<8);
			tcon |= S3C_TCON_T1RELOAD;
			break;
		case 2:
					
			tcfg1 &= ~S3C_TCFG1_MUX2_MASK;
			tcfg1 |= S3C_TCFG1_MUX2_DIV2;

			tcfg0 &= ~S3C_TCFG_PRESCALER1_MASK;
			tcfg0 |= (PRESCALER) << S3C_TCFG_PRESCALER1_SHIFT;

			tcon &= ~(7<<12);
			tcon |= S3C_TCON_T2RELOAD;
			break;
		case 3:
			tcfg1 &= ~S3C_TCFG1_MUX3_MASK;
			tcfg1 |= S3C_TCFG1_MUX3_DIV2;

			tcfg0 &= ~S3C_TCFG_PRESCALER1_MASK;
			tcfg0 |= (PRESCALER) << S3C_TCFG_PRESCALER1_SHIFT;
			tcon &= ~(7<<16);
			tcon |= S3C_TCON_T3RELOAD;
			break;
		case 4:
			tcfg1 &= ~S3C_TCFG1_MUX4_MASK;
			tcfg1 |= S3C_TCFG1_MUX4_DIV2;

			tcfg0 &= ~S3C_TCFG_PRESCALER1_MASK;
			tcfg0 |= (PRESCALER) << S3C_TCFG_PRESCALER1_SHIFT;
			tcon &= ~(7<<20);
			tcon |= S3C_TCON_T3RELOAD;
			break;
	}

	__raw_writel(tcfg1, S3C_TCFG1);
	__raw_writel(tcfg0, S3C_TCFG0);


	__raw_writel(tcon, S3C_TCON);
	
	/*tcnt = 160;
	__raw_writel(tcnt, S3C_TCNTB(channel));
	tcmp = 110;
	__raw_writel(tcmp, S3C_TCMPB(channel));*/



	tcnt = g_tcnt;
	__raw_writel(tcnt, S3C_TCNTB(channel));

	tcmp = g_tcmp;
	__raw_writel(tcmp, S3C_TCMPB(channel));

	switch(channel)
        {
                case 0:
                        tcon |= S3C_TCON_T0MANUALUPD;
                        break;
                case 1:
                        tcon |= S3C_TCON_T1MANUALUPD;
                        break;
                case 2:
                        tcon |= S3C_TCON_T2MANUALUPD;
                        break;
                case 3:
                        tcon |= S3C_TCON_T3MANUALUPD;
                        break;
                case 4:
                        tcon |= S3C_TCON_T4MANUALUPD;
                        break;
        }

	__raw_writel(tcon, S3C_TCON);

	/* start the timer running */
	s5p6442_pwm_start ( channel);

	return 0;
}
EXPORT_SYMBOL(s5p6442_timer_setup);

static irqreturn_t s5p6442_pwm_irq(int irq, void *devpw)
{
	s5p6442_pwm_chan_t *chan = (s5p6442_pwm_chan_t *)devpw;
	void *dev=chan->dev;

	/* modify the channel state */
	s5p6442_pwm_buffdone(chan, dev);

	return IRQ_HANDLED;
}


int s5p6442_pwm_request(pwmch_t  channel, s3c_pwm_client_t *client, void *dev)
{
	s5p6442_pwm_chan_t *chan = &s3c_chans[channel];
	unsigned long flags;
	int err;

	pr_debug("pwm%d: s3c_request_pwm: client=%s, dev=%p\n",
		 channel, client->name, dev);


	local_irq_save(flags);


	if (chan->in_use) {
		if (client != chan->client) {
			printk(KERN_ERR "pwm%d: already in use\n", channel);
			local_irq_restore(flags);
			return -EBUSY;
		} else {
			printk(KERN_ERR "pwm%d: client already has channel\n", channel);
		}
	}

	chan->client = client;
	chan->in_use = 1;
	chan->dev = dev;

	if (!chan->irq_claimed) {
		pr_debug("pwm%d: %s : requesting irq %d\n",
			 channel, __FUNCTION__, chan->irq);
		 
		err = request_irq(chan->irq, s5p6442_pwm_irq, IRQF_DISABLED,
				  client->name, (void *)chan);

		if (err) {
			chan->in_use = 0;
			local_irq_restore(flags);

			printk(KERN_ERR "%s: cannot get IRQ %d for PWM %d\n",
			       client->name, chan->irq, chan->number);
			return err;
		}

		chan->irq_claimed = 1;
		chan->irq_enabled = 1;
	}

	local_irq_restore(flags);

	/* need to setup */

	pr_debug("%s: channel initialised, %p\n", __FUNCTION__, chan);

	return 0;
}

int s5p6442_pwm_free (pwmch_t channel, s3c_pwm_client_t *client)
{
	s5p6442_pwm_chan_t *chan = &s3c_chans[channel];
	unsigned long flags;


	local_irq_save(flags);

	if (chan->client != client) {
		printk(KERN_WARNING "pwm%d: possible free from different client (channel %p, passed %p)\n",
		       channel, chan->client, client);
	}

	/* sort out stopping and freeing the channel */


	chan->client = NULL;
	chan->in_use = 0;

	if (chan->irq_claimed)
		free_irq(chan->irq, (void *)chan);
	chan->irq_claimed = 0;

	local_irq_restore(flags);

	return 0;
}


int s5p6442_pwm_set_buffdone_fn(pwmch_t channel, s3c_pwm_cbfn_t rtn)
{
	s5p6442_pwm_chan_t *chan = &s3c_chans[channel];


	pr_debug("%s: chan=%d, callback rtn=%p\n", __FUNCTION__, channel, rtn);

	chan->callback_fn = rtn;

	return 0;
}


#define s5p6442_pwm_suspend NULL
#define s5p6442_pwm_resume  NULL

struct sysdev_class pwm_sysclass = {
	.name           = "s3c-pwm",	
	.suspend	= s5p6442_pwm_suspend,
	.resume		= s5p6442_pwm_resume,
};


/* initialisation code */

static int __init s5p6442_init_pwm(void)
{
	s5p6442_pwm_chan_t *cp;
	int channel;
	int ret;

	printk("S3C PWM Driver, (c) 2006-2007 Samsung Electronics\n");

	ret = sysdev_class_register(&pwm_sysclass);
	if (ret != 0) {
		printk(KERN_ERR "pwm sysclass registration failed\n");
		return -ENODEV;
	}

	for (channel = 0; channel < S3C_PWM_CHANNELS; channel++) {
		cp = &s3c_chans[channel];

		memset(cp, 0, sizeof(s5p6442_pwm_chan_t));

		cp->number = channel;
		/* pwm channel irqs are in order.. */
		cp->irq    = channel + IRQ_TIMER0;

		/* register system device */

		ret = sysdev_register(&cp->sysdev);

		pr_debug("PWM channel %d , irq %d\n",
		       cp->number,  cp->irq);
	}

	return ret;
}
__initcall(s5p6442_init_pwm);