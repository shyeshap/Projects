/*********************************
 *          SHYE SHAIRA          *
 *          20/01/2020           *
 *                               *
 *             HASH              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy() */

#include "ip.h" /* IP API */
#include "trie.h" /* trie API */
#include "dhcp.h" /*DHCP API */

#define FREE(ptr) free(ptr); ptr = NULL;
#define BITS_IN_BYTE 8

struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t avaliable_bits;
};

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
	dhcp_t *new_dhcp = NULL;

	assert(NULL != subnet_mask);

	new_dhcp = (dhcp_t *)malloc(sizeof(*new_dhcp));
	if (NULL == new_dhcp)
	{
		return NULL;
	}

	new_dhcp->trie = TrieCreate();
	if (NULL == new_dhcp->trie)
	{
		FREE(new_dhcp);

		return NULL;
	}

	memcpy(new_dhcp->subnet_mask, subnet_mask, sizeof(ip_t));
	new_dhcp->avaliable_bits = (sizeof(ip_t) * BITS_IN_BYTE) - 
								subnet_mask_reserved_bits;

	return new_dhcp;
}

void DhcpDetroy(dhcp_t *dhcp)
{

}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{

}

free_status_t DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{

}

size_t DhcpCountFree(const dhcp_t *dhcp)
{

}
