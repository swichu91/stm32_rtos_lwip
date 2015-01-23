#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__


#include "lwip/err.h"
#include "lwip/netif.h"
#include "semphr.h"



/* MAC address configuration. */
#define configMAC_ADDR0	0x00
#define configMAC_ADDR1	0x12
#define configMAC_ADDR2	0x13
#define configMAC_ADDR3	0x10
#define configMAC_ADDR4	0x15
#define configMAC_ADDR5	0x11




#define netifINTERFACE_TASK_STACK_SIZE 512
#define netifINTERFACE_TASK_PRIORITY   3

/* Exported types ------------------------------------------------------------*/
/* Structure that include link thread parameters */
struct link_str {
  struct netif *netif;
  xSemaphoreHandle semaphore;
};


/* Exported functions ------------------------------------------------------- */
err_t ethernetif_init(struct netif *netif);

void ethernetif_input( void const * argument );


void ethernetif_set_link(void const *argument);
void ethernetif_update_config(struct netif *netif);
void ethernetif_notify_conn_changed(struct netif *netif);


#endif 
