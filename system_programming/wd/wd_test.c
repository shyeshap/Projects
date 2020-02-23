#include "wd.h"

int main()
{
	init_status_t *status = SUCCESS;

	wd_t *wd = WDStart("wd_test", status);

	WDStop(wd);

	return 0;
}