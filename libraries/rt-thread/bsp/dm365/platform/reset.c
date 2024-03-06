/*
 * File      : reset.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author		Notes
 * 2010-11-13     weety		first version
 */


#include <rthw.h>
#include <rtthread.h>
#include "dm36x.h"

/**
 * @addtogroup DM36X
 */
/*@{*/

/**
 * reset cpu by dog's time-out
 *
 */
void machine_reset()
{
	reset_system();
}

/**
 *  shutdown CPU
 *
 */
void machine_shutdown()
{

}

#ifdef RT_USING_FINSH

#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_cpu_reset, reset, restart the system);

#ifdef FINSH_USING_MSH
int cmd_reset(int argc, char** argv)
{
	rt_hw_cpu_reset();
	return 0;
}

int cmd_shutdown(int argc, char** argv)
{
	rt_hw_cpu_shutdown();
	return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_reset, __cmd_reset, restart the system.);
FINSH_FUNCTION_EXPORT_ALIAS(cmd_shutdown, __cmd_shutdown, shutdown the system.);

#endif
#endif

/*@}*/
