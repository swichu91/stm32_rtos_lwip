
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/lwip_timers.h"
#include "netif/etharp.h"
#include "err.h"
#include "ethernetif.h"
#include "lwip/tcpip.h"



#include <string.h>
#include "netconf.h"
#include "task.h"




static void tcpip_init_done(void *arg)
{

	sys_sem_t *sem;
	sem = (sys_sem_t *)arg;

    struct ip_addr ipaddr, netmask, gw;

    struct netif my_netif;

    	 /* Set network address variables */

    IP4_ADDR(&gw, 192,168,1,1);                   //ip address of the gateway

    IP4_ADDR(&ipaddr, 192,168,1,20);             //ip address of your device

    IP4_ADDR(&netmask, 255,255,255,0);      //netmask




    netif_add(&my_netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input);



    netif_set_default(&my_netif);

    netif_set_up(&my_netif);	//call this routine if you use an OS


    sys_sem_signal(sem);




}

void Lwip_init(void)
{

      /* Network interface variables */

	/*
	 sys_sem_t sem;

	 sys_sem_new(&sem,0); // Create a new semaphore.
*/


    tcpip_init(NULL, NULL);


    struct ip_addr ipaddr, netmask, gw;

       struct netif my_netif;

       	 /* Set network address variables */

       IP4_ADDR(&gw, 192,168,1,1);                   //ip address of the gateway

       IP4_ADDR(&ipaddr, 192,168,1,20);             //ip address of your device

       IP4_ADDR(&netmask, 255,255,255,0);      //netmask




       netif_add(&my_netif, &ipaddr, &netmask, &gw, NULL, ethernetif_init, tcpip_input);



       netif_set_default(&my_netif);

       netif_set_up(&my_netif);	//call this routine if you use an OS



   // sys_arch_sem_wait(&sem,10000);    // Block until the lwIP stack is initialized.
   // sys_sem_free(&sem);    // Free the semaphore.



}
