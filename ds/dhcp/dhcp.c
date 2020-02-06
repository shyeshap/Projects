/*********************************
 *          SHYE SHAIRA          *
 *          03/02/2020           *
 *                               *
 *             DHCP              *
 *********************************/

#include <stdlib.h> /* malloc() */
#include <assert.h> /* assert() */
#include <string.h> /* memcpy() */
#include <math.h> /* paw() */

#include "trie.h" /* trie API */
#include "dhcp.h" /*DHCP API */

#define FREE(ptr) free(ptr); ptr = NULL;
#define BITS_IN_BYTE 8
#define IP_SIZE sizeof(ip_t)
#define IP_ARR_SIZE (IP_SIZE * BITS_IN_BYTE)
#define MAX 0xFF
#define MIN 0


struct DHCP
{
	trie_t *trie;
	ip_t subnet_mask;
	size_t available_bits;
};

/******************************************************************/

static status_t CatchReservedAddresses(trie_t *trie);

/*******************************************************************/

dhcp_t *DhcpCreate(ip_t subnet_mask, size_t subnet_mask_reserved_bits)
{
	dhcp_t *new_dhcp = NULL;
	status_t status = SUCCESS;

	assert(NULL != subnet_mask);

	new_dhcp = (dhcp_t *)malloc(sizeof(*new_dhcp));
	if (NULL == new_dhcp)
	{
		return NULL;
	}

	memcpy(new_dhcp->subnet_mask, subnet_mask, sizeof(ip_t));
	new_dhcp->available_bits = (IP_ARR_SIZE) - 
								subnet_mask_reserved_bits;

	new_dhcp->trie = TrieCreate(new_dhcp->available_bits);
	if (NULL == new_dhcp->trie)
	{
		FREE(new_dhcp);

		return NULL;
	}

	status = CatchReservedAddresses(new_dhcp->trie);
	if (SUCCESS != status)
	{
		return NULL;
	}

	return new_dhcp;
}

void DhcpDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	TrieDestroy(dhcp->trie);

	FREE(dhcp);
}

alc_status_t DhcpAllocIp(dhcp_t *dhcp, ip_t requested_ip, ip_t allocated_ip)
{
	bool_t is_avilable = TRUE;
	status_t status = SUCCESS;
	
	if (TrieCountOccupiedLeafs(dhcp->trie) == pow(2, dhcp->available_bits))
	{
		return FAIL_TO_ALLOC;
	}

	memcpy(allocated_ip, requested_ip, IP_SIZE);
	is_avilable = TrieIsAvailable(dhcp->trie, requested_ip);
	if (FALSE == is_avilable)
	{
		TrieFindFirstAvailable(dhcp->trie, allocated_ip);
	}
	
	status = TrieInsert(dhcp->trie, allocated_ip);
	if (SUCCESS != status)
	{
		return FAIL_TO_ALLOC;
	}

	return !is_avilable;
}

void DhcpFreeIp(dhcp_t *dhcp, ip_t ip_address)
{
	assert(NULL != dhcp);

	TrieFreeLeaf(dhcp->trie, ip_address);
}

size_t DhcpCountFree(const dhcp_t *dhcp)
{
	assert(NULL != dhcp);

	return (pow(2, dhcp->available_bits) - 
			TrieCountOccupiedLeafs(dhcp->trie));
}

/****************************************************************/

static status_t CatchReservedAddresses(trie_t *trie)
{
	status_t status = SUCCESS;
	unsigned char first_ip[IP_SIZE] = {MIN, MIN, MIN, MIN};
	unsigned char last_ip[IP_SIZE]  = {MAX, MAX, MAX, MAX};
	unsigned char extra_ip[IP_SIZE] = {MAX, MAX, MAX, MAX - 1};

	status += TrieInsert(trie, first_ip);
	status += TrieInsert(trie, last_ip);
	status += TrieInsert(trie, extra_ip);

	return (SUCCESS < status);
}