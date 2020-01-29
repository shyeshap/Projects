/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *             HASH              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */

#include "ip.h" /* IP API */
#include "trie.h" /* trie API */
#include "dhcp.h" /*DHCP API */

#define FREE(ptr) free(ptr); ptr = NULL;

struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t avaliable_bits;
} dhcp_t;

dhcp_t *DhcpCreate(ipt_t subnet_mask, size_t subnet_mask_reserved_bits)
{

}

void DhcpDetroy(dhct_t *dhcp)
{

}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ipt_t requested_ip, ip_t allocated_ip)
{

}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}
